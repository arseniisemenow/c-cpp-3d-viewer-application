#include "FileInformationWindow.h"

#include "ui_FileInformationWindow.h"

FileInformationWindow::FileInformationWindow()
    : ui(new Ui::FileInformationWindow) {
  ui->setupUi(this);
  setWindowModality(Qt::ApplicationModal);
  updateValues();

  connect(ui->pushButton_close, &QPushButton::clicked, this,
          [=]() { this->close(); });
}

FileInformationWindow::~FileInformationWindow() { delete ui; }
