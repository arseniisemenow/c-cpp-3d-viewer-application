#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QMouseEvent>
#include <QTranslator>

#include "frontend/ui/FileHandler/FileHandler.h"
#include "frontend/ui/MainWindow/MainWindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow mainWindow;

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "3d_viewer_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      app.installTranslator(&translator);
      break;
    }
  }

  mainWindow.show();

  return app.exec();
}
