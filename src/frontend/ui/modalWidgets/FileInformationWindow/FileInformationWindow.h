#ifndef FILEINFORMATIONWINDOW_H
#define FILEINFORMATIONWINDOW_H

#include <QWidget>

#include "QtWidgets/qdialog.h"
#include "ui_FileInformationWindow.h"

namespace Ui {
class FileInformationWindow;
}

class FileInformationWindow : public QDialog {
  Q_OBJECT

public:
  explicit FileInformationWindow();
  ~FileInformationWindow();

  void setVertexCount(int count) {
    m_vertexCount = count;
    updateValues();
  }
  void setEdgeCount(int count) {
    m_edgeCount = count;
    updateValues();
  }
  void setFilePath(QString filePath) {
    m_filePath = filePath;
    updateValues();
  }
  void updateVertexCount() {
    ui->label_vertexCountValue->setText(QString::number(m_vertexCount));
  }
  void updateEdgeCount() {
    ui->label_edgeCountValue->setText(QString::number(m_edgeCount));
  }
  void updateFilePath() { ui->label_filePathValue->setText(m_filePath); }

  void updateValues() {
    updateVertexCount();
    updateEdgeCount();
    updateFilePath();
  }

private:
  Ui::FileInformationWindow *ui;
  QString m_filePath{""};
  int m_vertexCount{0};
  int m_edgeCount{0};
};

#endif // FILEINFORMATIONWINDOW_H
