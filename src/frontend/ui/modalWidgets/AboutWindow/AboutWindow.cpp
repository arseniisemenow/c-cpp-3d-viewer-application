#include "AboutWindow.h"

AboutWindow::AboutWindow() : QDialog(), ui(new Ui::AboutWindow) {
  ui->setupUi(this);

  lockMainWindowInteraction();
  QPixmap pixmapImage(PATH_COMPANY_LOGO);
  ui->label_image->setPixmap(pixmapImage.scaled(150, 150, Qt::KeepAspectRatio));

  connect(ui->pushButton_close, &QPushButton::clicked, this,
          &AboutWindow::closeWindow);
}

AboutWindow::~AboutWindow() { delete ui; }

void AboutWindow::lockMainWindowInteraction() { setModal(true); }

void AboutWindow::closeWindow() { this->close(); }
