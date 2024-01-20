#ifndef ABOUTWINDOW_H
#define ABOUTWINDOW_H

#include <QDialog>
#include <QPixmap>

#include "ui_AboutWindow.h"

#define PATH_COMPANY_LOGO ":/company_logo.png"

namespace Ui {
class AboutWindow;
}

class AboutWindow : public QDialog {
  Q_OBJECT

public:
  explicit AboutWindow();
  ~AboutWindow();

  void lockMainWindowInteraction();

  void closeWindow();

private:
  Ui::AboutWindow *ui;
};

#endif // ABOUTWINDOW_H
