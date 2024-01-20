#ifndef DOCKWIDGETSETTINGS_H
#define DOCKWIDGETSETTINGS_H

#include <QComboBox>
#include <QDebug>
#include <QDockWidget>
#include <QEvent>
#include <QFile>
#include <QLabel>
#include <QMoveEvent>
#include <QPushButton>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QSplitter>
#include <QVBoxLayout>
#include <iostream>

#include "../../EventHandler/EventHandler.h"
#include "../../Preferences/Preferences.h"
#include "../../styles/styles.h"

#define FIXED_WIDTH_COMBOBOX_SETTINGS_DOCKWIDGET (130)
#define FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET (18)
#define PROJECTION_TYPE_PERSPECTIVE_STRING "Perspective"
#define PROJECTION_TYPE_PARALLEL_STRING "Parallel"

#define CAMERA_MODE_FLY_STRING "Fly"
#define CAMERA_MODE_TURNABLE_STRING "Turnable"

#define DOCK_WIDGET_MARGIN_VALUE (4)

#define OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_DEFAULT "hideRightDockButton"
#define OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_CHECKED "hideRightDockButton_checked"

#define OBJECT_NAME_CAMERA_ICON_LABEL "cameraIconLabel"

namespace ProjectionTypeComboBoxIndex {
typedef enum {
  Perspective = 0,
  Parallel = 1,
} ProjectionTypeComboBoxIndex;
}

namespace CameraModeComboBoxIndex {
typedef enum {
  Fly = 0,
  Turnable = 1,
} CameraModeComboBoxIndex;
}

class DockWidgetSettings : public QDockWidget {
  Q_OBJECT

public:
  DockWidgetSettings(QWidget *parent = nullptr);

signals:
  void eventProjectionTypeChanged();
  void eventCameraModeChanged();
  void eventToggleRightDockWidget();

private:
  void toggleChecked();

  void setCameraIconLabel();

  void setProjectionTypeComboBox();

  void setHideDockButton();

  void setLayoutForWidget();

  void setCameraModeComboBox();

  void updateDockWidgetModelEditorButtonStatus();

  void handleProjectionTypeChanged(int index);
  void handleCameraModeChanged(int index);

  void saveProjectionTypeSettings();
  void loadProjectionTypeSettings();

  void saveCameraModeSettings();
  void loadCameraModeSettings();
  void updateDockWidget();

  void projectionTypeChanged() { emit eventProjectionTypeChanged(); }
  void cameraModeChanged() { emit eventCameraModeChanged(); };
  void updateHideRightDockWidgetButtonStyle();
  void updateStyles();

  QLabel *m_cameraIconLabel;
  QComboBox *m_projectionTypeComboBox;
  QComboBox *m_cameraModeComboBox;
  QPushButton *m_hideRightDockButton;

  QWidget *m_centralWidget;
  QHBoxLayout *m_layout;

  bool m_isRightDockButtonChecked;
};

#endif // DOCKWIDGETSETTINGS_H
