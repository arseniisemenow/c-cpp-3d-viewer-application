#ifndef FILE_DIALOG_H
#define FILE_DIALOG_H

#include <QApplication>
#include <QDialog>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

#include "../../EventHandler/EventHandler.h"
#include "../../styles/styles.h"
#include "frontend/ui/Preferences/Preferences.h"

#define FILE_DIALOG_WINDOW_TITLE "Open File"
#define FILE_DIALOG_SELECT_BUTTON_TITLE "Select"
#define FILE_DIALOG_CANCEL_BUTTON_TITLE "Cancel"

class FileDialog : public QDialog {
  Q_OBJECT
public:
  FileDialog(const int width, const int height);

public:
  QString getSelectedPath() const;

  QString getSelectedFileName() const;

  void setSize(int weight, int height);

  void setRootPath(QString path);

  void selectButtonClicked() {
    accept();
    emit eventSelectButtonClicked((const QString &)getSelectedPath());
  }

  void setNameFilters(const QStringList &filters) {
    m_allowedExtensions = filters;

    QStringList nameFilters;
    for (const QString &extension : m_allowedExtensions) {
      if (extension.isEmpty()) {
        nameFilters << "*";
      } else {
        nameFilters << "*" + extension;
      }
    }

    m_fileModel->setNameFilters(nameFilters);
    m_fileModel->setNameFilterDisables(false);
  }

  void onTreeViewClicked(const QModelIndex &index) {
    QString selectedPath = m_fileModel->fileInfo(index).absoluteFilePath();
    m_filePathLineEdit->setText(selectedPath);

    bool isValidExtension = false;

    for (const QString &extension : m_allowedExtensions) {
      if (extension == "") {
        if (QFileInfo(selectedPath).isDir()) {
          isValidExtension = true;

          break;
        }
      } else {
        if (selectedPath.endsWith(extension, Qt::CaseInsensitive)) {
          isValidExtension = true;
          break;
        }
      }
    }
    m_selectButton->setEnabled(isValidExtension);
  }
signals:
  void eventSelectButtonClicked(const QString &);
public slots:
  void selectFile();

  void closeWindow();

private:
  void updateStyles();

  QFileSystemModel *m_fileModel;
  QTreeView *m_treeView;
  QLineEdit *m_filePathLineEdit;
  QPushButton *m_cancelButton;
  QPushButton *m_selectButton;

  QStringList m_allowedExtensions{};
};

#endif // FILE_DIALOG_H
