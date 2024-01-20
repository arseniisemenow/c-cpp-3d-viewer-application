#ifndef STYLES_H
#define STYLES_H

#include <QFile>
#include <QString>
#include <QTextStream>
#include <iostream>

#include "globalStyles.h"

#define PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE ":/DockWidgetSettingsStyles.qss"
#define PATH_FILE_DIALOG_STYLES_FILE ":/FileDialogStyles.qss"
#define PATH_MENU_BAR_STYLES_FILE ":/MenuBarStyles.qss"
#define PATH_MAIN_WINDOW_STYLES_FILE ":/MainWindowStyles.qss"
#define PATH_TITLE_BAR_STYLES_FILE ":/TitleBarStyles.qss"
#define PATH_PREFERENCES_WINDOW_STYLES_FILE ":/PreferencesWindowStyles.qss"

QString getStylesFromFile(QString fileName);

#endif // STYLES_H
