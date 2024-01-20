#include "FileDialog.h"

FileDialog::FileDialog(const int width, const int height) {
  setFixedSize(width, height);
  setMinimumSize(640, 480);

  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

  setWindowTitle(FILE_DIALOG_WINDOW_TITLE);
  QVBoxLayout *layout = new QVBoxLayout(this);

  m_fileModel = new QFileSystemModel(this);

  setNameFilters({""});

  m_treeView = new QTreeView(this);

  m_treeView->setModel(m_fileModel);
  m_treeView->setRootIndex(m_fileModel->index(QDir::homePath()));
  QHeaderView *header = m_treeView->header();

  int borderWidth = 50;
  int borderCount = 2;
  int headerWidth = width - (borderWidth * borderCount);

  header->resizeSection(0, headerWidth * 0.70);
  header->resizeSection(1, headerWidth * 0.10);
  header->resizeSection(2, headerWidth * 0.10);
  header->resizeSection(3, headerWidth * 0.10);
  m_filePathLineEdit = new QLineEdit(this);
  m_filePathLineEdit->setEnabled(false);

  m_selectButton = new QPushButton(FILE_DIALOG_SELECT_BUTTON_TITLE, this);
  m_selectButton->setObjectName(STRINGIFY(selectButton));
  m_cancelButton = new QPushButton(FILE_DIALOG_CANCEL_BUTTON_TITLE, this);
  m_cancelButton->setObjectName(STRINGIFY(cancelButton));

  m_selectButton->setEnabled(false);

  layout->addWidget(m_treeView);
  layout->addWidget(m_filePathLineEdit);
  layout->addWidget(m_selectButton);
  layout->addWidget(m_cancelButton);

  updateStyles();

  connect(m_treeView, &QTreeView::clicked, this,
          &FileDialog::onTreeViewClicked);

  connect(m_selectButton, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::selectButtonClicked);
  connect(&EventHandler::get(), &EventHandler::eventSelectButtonClicked, this,
          &FileDialog::selectButtonClicked);
  connect(this, &FileDialog::eventSelectButtonClicked, &EventHandler::get(),
          &EventHandler::openFile);

  connect(m_cancelButton, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::fileDialogCloseWindow);
  connect(&EventHandler::get(), &EventHandler::eventFileDialogCloseWindow, this,
          &FileDialog::closeWindow);
}

QString FileDialog::getSelectedPath() const {
  return m_filePathLineEdit->text();
}

QString FileDialog::getSelectedFileName() const {
  QFileInfo fileInfo(getSelectedPath());
  return fileInfo.fileName();
}

void FileDialog::updateStyles() {
  this->setStyleSheet(getStylesFromFile(PATH_FILE_DIALOG_STYLES_FILE));
  m_treeView->header()->setStyleSheet(
      getStylesFromFile(PATH_FILE_DIALOG_STYLES_FILE));
}

void FileDialog::setSize(int weight, int height) {
  this->resize(weight, height);
}

void FileDialog::setRootPath(QString path) { m_fileModel->setRootPath(path); }

void FileDialog::selectFile() { accept(); }

void FileDialog::closeWindow() { this->close(); }
