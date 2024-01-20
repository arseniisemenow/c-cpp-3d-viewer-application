#ifndef MENUFILE_H
#define MENUFILE_H

#include <QAction>
#include <QFileDialog>
#include <QMenu>
#include <QObject>
#include <QString>
#include <QVector>

#include "../../EventHandler/EventHandler.h"
#include "../../Preferences/Preferences.h"
#include "../../RecentFile/RecentFile.h"
#include "../../modalWidgets/FileDialog/FileDialog.h"
#include "../../styles/styles.h"
#include "backend/mesh_data.h"
#include "frontend/ui/FileHandler/FileHandler.h"
#include "frontend/ui/modalWidgets/FileInformationWindow/FileInformationWindow.h"

#define ACTION_TITLE_OPEN_FILE "Open File"
#define ACTION_TITLE_CLOSE_FILE "Close File"
#define ACTION_TITLE_FILE_INFORMATION "File Information"
#define ACTION_TITLE_RECENT_FILES "Recent Files"
#define ACTION_TITLE_CLEAR_MENU "Clear menu"

#define S21_MAX_RECENT_FILES (10)

class MenuFile : public QMenu {
  Q_OBJECT

public:
  MenuFile(const QString &title = "Default Title");

  void addRecentFile(const RecentFile &recentFile);
  void updateRecentFiles();
  void clearRecentFiles();
  void openFileDialog();
  QString getFilePathFromAction(QAction *action);
  void updateMenu();

  void saveRecentFiles();
  void loadRecentFiles();

public slots:
  void handleRecentFilesChanged();
  void recentFileActionClicked(const QString &filePath);
  void openRecentFile();
  void openFileInformation();

  void updateFileInformation(const MeshData &data, const QString &fileName);
  void clearFileInformation();

  void loadAnotherModel() { emit eventLoadAnotherModel(); }

private:
  QVector<RecentFile> recentFiles;

  QAction *openFileAction;
  QAction *closeFileAction;
  QAction *fileInformationAction;
  QMenu *recentFilesMenu;

  int m_numberOfVertices{};
  int m_numberOfEdges{};
  QString m_openFileName{};

  int fillMenuWithRecentFiles();

signals:
  void eventRecentFileActionClicked(const QString &);
  void recentFilesChanged();
  void eventLoadAnotherModel();
};

#endif // MENUFILE_H
