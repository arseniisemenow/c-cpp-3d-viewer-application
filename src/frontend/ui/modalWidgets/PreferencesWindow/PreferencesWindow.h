#ifndef PREFERENCESWINDOW_H
#define PREFERENCESWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QWidget>

#include "../../EventHandler/EventHandler.h"
#include "../../Preferences/Preferences.h"
#include "../../menuBar/MenuBar/MenuBar.h"
#include "ui_PreferencesWindow.h"

namespace Ui {
class PreferencesWindow;
}

class PreferencesWindow : public QDialog {
  Q_OBJECT

public:
  explicit PreferencesWindow(QWidget *parent);
  ~PreferencesWindow();
  void updateStyles();

  void openPreferencesWindow() { emit eventOpenPreferencesWindow(); }

  void lockMainWindowInteraction();
  void setButtonsConnections();

  void saveBackgroundColor();
  void saveCameraSpeed();
  void saveNearPlane();
  void saveFarPlane();

  void saveVertexDisplayMethod();
  void saveVertexColor();
  void saveVertexSize();

  void saveEdgeType();
  void saveEdgeColor();
  void saveEdgeSize();

  void saveSettings();

  void loadBackgroundColor();
  void loadCameraSpeed();
  void loadNearPlane();
  void loadFarPlane();

  void loadVertexDisplayMethodSettings();
  void loadVertexColor();
  void loadVertexSize();

  void loadEdgeTypeSettings();
  void loadEdgeColor();
  void loadEdgeSize();

  void loadSettings();

  void handleApplyButtonClick();
  void handleCancelButtonClick();
  void handleOkButtonClick();
  void handleResetSettingsButtonClick();

  void closeWindow();
signals:
  void eventOpenPreferencesWindow();

private:
  Ui::PreferencesWindow *ui;
};

namespace VertexDisplayMethodComboBoxIndex {
typedef enum {
  None = 0,
  Circle = 1,
  Square = 2,
} VertexDisplayMethodComboBoxIndex;
}

namespace EdgeTypeComboBoxIndex {

typedef enum {
  Solid = 0,
  Dashed = 1,
} EdgeTypeComboBoxIndex;

}
#endif // PREFERENCESWINDOW_H
