#include "MenuFile.h"

MenuFile::MenuFile(const QString &title) {
  setTitle(title);

  openFileAction = new QAction(ACTION_TITLE_OPEN_FILE);
  closeFileAction = new QAction(ACTION_TITLE_CLOSE_FILE);
  fileInformationAction = new QAction(ACTION_TITLE_FILE_INFORMATION);
  recentFilesMenu = new QMenu(ACTION_TITLE_RECENT_FILES);

  connect(openFileAction, &QAction::triggered, &EventHandler::get(),
          &EventHandler::openFileDialog);
  connect(&EventHandler::get(), &EventHandler::eventOpenFileDialog, this,
          &MenuFile::openFileDialog);

  connect(closeFileAction, &QAction::triggered, &EventHandler::get(),
          &EventHandler::closeFile);
  connect(&EventHandler::get(), &EventHandler::eventCloseFile,
          &EventHandler::get(), &EventHandler::clearSpinBoxes);

  connect(this, &MenuFile::recentFilesChanged, &EventHandler::get(),
          &EventHandler::updateFileMenu);
  connect(&EventHandler::get(), &EventHandler::eventUpdateFileMenu, this,
          &MenuFile::updateMenu);
  connect(&EventHandler::get(), &EventHandler::eventResetSettings, this,
          &MenuFile::updateMenu);
  connect(this, &MenuFile::eventRecentFileActionClicked, &EventHandler::get(),
          &EventHandler::recentFileActionClicked);

  connect(fileInformationAction, &QAction::triggered, &EventHandler::get(),
          &EventHandler::openFileInformation);
  connect(&EventHandler::get(), &EventHandler::eventOpenFileInformation, this,
          &MenuFile::openFileInformation);

  connect(&FileHandler::get(), &FileHandler::fileLoaded, this,
          &MenuFile::updateFileInformation);
  connect(&FileHandler::get(), &FileHandler::fileClosed, this,
          &MenuFile::clearFileInformation);

  connect(this, &MenuFile::eventLoadAnotherModel, &EventHandler::get(),
          &EventHandler::loadAnotherModel);

  updateMenu();
}

void MenuFile::updateMenu() { handleRecentFilesChanged(); }

int MenuFile::fillMenuWithRecentFiles() {
  for (const RecentFile &recentFile : recentFiles) {
    QAction *recentFileAction = new QAction(recentFile.path);
    connect(recentFileAction, &QAction::triggered, this,
            &MenuFile::openRecentFile);
    recentFilesMenu->addAction(recentFileAction);
  }

  QAction *clearRecentFilesAction = new QAction(ACTION_TITLE_CLEAR_MENU);
  connect(clearRecentFilesAction, &QAction::triggered, this,
          &MenuFile::clearRecentFiles);
  recentFilesMenu->addSeparator();
  recentFilesMenu->addAction(clearRecentFilesAction);

  return recentFiles.count() > 0;
}

void MenuFile::addRecentFile(const RecentFile &recentFile) {
  for (int i = 0; i < recentFiles.size(); i++) {
    if (recentFiles[i].path == recentFile.path) {
      recentFiles.removeAt(i);
    }
  }

  recentFiles.prepend(recentFile);

  while (recentFiles.size() > S21_MAX_RECENT_FILES) {
    recentFiles.removeLast();
  }
  saveRecentFiles();
  emit recentFilesChanged();
}

void MenuFile::clearRecentFiles() {
  recentFiles.clear();
  saveRecentFiles();
  emit recentFilesChanged();
}

void MenuFile::openFileDialog() {
  auto *fileDialog = new FileDialog(1000, 600);
  fileDialog->setNameFilters({"obj"});
  fileDialog->setRootPath(QDir::homePath());

  if (fileDialog->exec() == QDialog::Accepted) {
    QString path = fileDialog->getSelectedPath();
    QString name = fileDialog->getSelectedFileName();

    RecentFile recentFile{name, path};
    this->addRecentFile(recentFile);
    loadAnotherModel();
  }
}

void MenuFile::openFileInformation() {
  auto *fileInformationWindow = new FileInformationWindow();
  fileInformationWindow->setFilePath(m_openFileName);
  fileInformationWindow->setVertexCount(m_numberOfVertices);
  fileInformationWindow->setEdgeCount(m_numberOfEdges);
  fileInformationWindow->show();
}

void MenuFile::updateFileInformation(const MeshData &data,
                                     const QString &fileName) {
  m_numberOfVertices = data.numberOfVertices;
  m_numberOfEdges = data.numberOfEdges;
  m_openFileName = fileName;
}

void MenuFile::clearFileInformation() {
  m_numberOfVertices = 0;
  m_numberOfEdges = 0;
  m_openFileName.clear();
}

void MenuFile::openRecentFile() {
  QAction *action = qobject_cast<QAction *>(sender());
  if (action) {
    QString filePath = getFilePathFromAction(action);
    QFileInfo fileInfo(filePath);
    if (!filePath.isEmpty()) {
      QString path = filePath;
      QString name = fileInfo.fileName();

      RecentFile recentFile{name, path};

      addRecentFile(recentFile);
      recentFileActionClicked(path);
      loadAnotherModel();
    }
  }
}

QString MenuFile::getFilePathFromAction(QAction *action) {
  QString fileName = action->text();
  for (const RecentFile &recentFile : recentFiles) {
    if (recentFile.path == fileName) {
      return recentFile.path;
    }
  }
  return "";
}

void MenuFile::handleRecentFilesChanged() {
  clear();
  recentFilesMenu->clear();

  loadRecentFiles();

  addAction(openFileAction);

  int isRecentFiles = fillMenuWithRecentFiles();

  if (isRecentFiles) {
    addMenu(recentFilesMenu);
  }
  addAction(fileInformationAction);
  addAction(closeFileAction);
}

void MenuFile::saveRecentFiles() {
  QVariantList recentFilesList{};

  for (const RecentFile &file : recentFiles) {
    QVariantMap fileData;
    fileData["name"] = file.name;
    fileData["path"] = file.path;
    recentFilesList.append(fileData);
  }

  Preferences::get().m_recentFilesSettings->setValue(STRINGIFY(recentFiles),
                                                     recentFilesList);
}

void MenuFile::loadRecentFiles() {
  QVariantList recentFilesList =
      Preferences::get()
          .m_recentFilesSettings->value(STRINGIFY(recentFiles))
          .toList();
  recentFiles.clear();

  for (const QVariant &fileData : recentFilesList) {
    if (fileData.type() == QVariant::Map) {
      QVariantMap fileMap = fileData.toMap();
      RecentFile file{};
      file.name = fileMap["name"].toString();
      file.path = fileMap["path"].toString();
      recentFiles.append(file);
    }
  }
}

void MenuFile::recentFileActionClicked(const QString &filePath) {
  emit eventRecentFileActionClicked(filePath);
}
