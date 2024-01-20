#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <QAction>
#include <QObject>
#include <QVector3D>

#include "../../opengl/OpenGLWidget/OpenGLWidget.h"
#include "QtCore/qdebug.h"
#include "backend/mesh_data.h"

class EventHandler : public QObject {
  Q_OBJECT
public:
  static EventHandler &get() {
    static EventHandler instance;
    return instance;
  }
  ~EventHandler(){};

private:
  EventHandler(){

  };
public slots:
  void openPreferencesWindow();
  void closePreferencesWindow();
  void openAboutWindow();
  void closeAboutWindow();
  void closeMainWindow();
  void recentFilesChanged();
  void updateFileMenu();
  void openFileDialog();
  void closeFile();

  void applySettings();
  void cancelSettings();
  void okSettings();
  void resetSettings();

  void openFile(const QString &fileName) { emit eventOpenFile(fileName); }
  void selectButtonClicked() { emit eventSelectButtonClicked(); }

  void recentFileActionClicked(const QString &filePath) {
    emit eventRecentFileActionClicked(filePath);
  }
  void fileDialogCloseWindow();
  void fileDialogUpdateSelectedPath(const QModelIndex &index);

  void toggleDockWidgetModelEditor() {
    emit eventToggleDockWidgetModelEditor();
  }

  void toggledDockWidgetModelEditor(bool visibility) {
    widgetSizeChanged();
    emit eventToggledDockWidgetModelEditor(visibility);
  }

  void leftMouseButtonPressed(const QPoint &pressedPos) {
    emit eventLeftMouseButtonPressed(pressedPos);
  }
  void leftMouseButtonReleased(const QPoint &releasedPos) {
    emit eventLeftMouseButtonReleased(releasedPos);
  }

  void projectionTypeChanged() { emit eventProjectionTypeChanged(); }
  void cameraModeChanged() { emit eventCameraModeChanged(); }

  void changeOpenGLWidgetSize(const QSize GLNewSize) {
    emit eventChangeOpenGLWidgetSize(GLNewSize);
  }

  void widgetSizeChanged() { emit eventWidgetSizeChanged(); }

  void openFileInformation() { emit eventOpenFileInformation(); }

  void openGLWidgetRequired() { emit eventOpenGLWidgetRequired(); }

  void openGLWidgetGiven(OpenGLWidget *openGLWidget) {
    emit eventOpenGLWidgetGiven(openGLWidget);
  }

  void clearSpinBoxes() { emit eventClearSpinBoxes(); }

  void loadAnotherModel() { emit eventLoadAnotherModel(); }

signals:
  void eventOpenPreferencesWindow();
  void eventClosePreferencesWindow();
  void eventOpenAboutWindow();
  void eventCloseAboutWindow();
  void eventCloseMainWindow();
  void eventRecentFilesChanged();
  void eventUpdateFileMenu();
  void eventOpenFileDialog();
  void eventCloseFile();

  void eventApplySettings();
  void eventCancelSettings();
  void eventOkSettings();
  void eventResetSettings();

  void eventRecentFileActionClicked(const QString &);
  void eventOpenFile(const QString &);
  void eventSelectButtonClicked();
  void eventFileDialogCloseWindow();
  void eventFileDialogUpdateSelectedPath(const QModelIndex &index);

  void eventToggleDockWidgetModelEditor();
  void eventToggledDockWidgetModelEditor(bool visibility);

  void eventLeftMouseButtonPressed(const QPoint &pressedPos);
  void eventLeftMouseButtonReleased(const QPoint &releasedPos);

  void eventProjectionTypeChanged();
  void eventCameraModeChanged();

  void eventChangeOpenGLWidgetSize(const QSize newSize);

  void eventWidgetSizeChanged();

  void eventAffineTransformationChanged(const std::array<QVector3D, 3> &matrix);

  void eventOpenFileInformation();

  void eventOpenGLWidgetRequired();

  void eventOpenGLWidgetGiven(OpenGLWidget *openGLWidget);

  void eventClearSpinBoxes();
  void eventLoadAnotherModel();
};

#endif // EVENTHANDLER_H
