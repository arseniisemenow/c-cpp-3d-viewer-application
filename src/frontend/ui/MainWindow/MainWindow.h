#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QActionGroup>
#include <QColorDialog>
#include <QDockWidget>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QMainWindow>
#include <QShortcut>
#include <QSplitter>
#include <QVBoxLayout>
#include <QVector>

#include "../EventHandler/EventHandler.h"
#include "../FileHandler/FileHandler.h"
#include "../Preferences/Preferences.h"
#include "../StatusBar/StatusBar.h"
#include "../TransformWidget/TransformWidget.h"
#include "../dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.h"
#include "../dockWidgets/DockWidgetSettings/DockWidgetSettings.h"
#include "../menuBar/MenuBar/MenuBar.h"
#include "../menuBar/MenuFile/MenuFile.h"
#include "../menuBar/MenuViews/MenuViews.h"
#include "../modalWidgets/AboutWindow/AboutWindow.h"
#include "../modalWidgets/PreferencesWindow/PreferencesWindow.h"
#include "../styles/styles.h"
#include "../userInteractionWidgets/ModelEditor.h"
#include "../userInteractionWidgets/ModelViewer.h"

#define S21_MIN_MODEL_EDITOR_WIDTH (30)

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

public slots:
  void setMenu();
  void setProgressBar();

  void loadPreferences();
  void savePreferences();

  void setCorners();

  void setModelEditorDockWidget();
  void setSettingsDockWidget();
  void setDockWidgets();

  void setModelViewer();

  void openPreferencesWindow();
  void closePreferencesWindow();

  void openAboutWindow();
  void closeAboutWindow();

  void closeWindow();

  void mousePressEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton) {
      QPoint pressedPos = event->pos();
      EventHandler::get().leftMouseButtonPressed(pressedPos);
    }

    QWidget::mousePressEvent(event);
  }

  void mouseReleaseEvent(QMouseEvent *event) override {
    if (event->button() == Qt::LeftButton) {
      QPoint releasePos = event->pos();
      EventHandler::get().leftMouseButtonReleased(releasePos);
    }

    QWidget::mouseReleaseEvent(event);
  }

  void changeOpenGLWidgetSize(const QSize GLNewSize);
  void widgetSizeChanged() { emit eventWidgetSizeChanged(); }

signals:
  void eventChangeOpenGLWidgetSize(const QSize GLNewSize);
  void eventWidgetSizeChanged();

protected:
  void resizeEvent(QResizeEvent *event) override {
    widgetSizeChanged();
    QMainWindow::resizeEvent(event);
  }

private:
  void updateStyles();

  ModelViewer *m_modelViewer;
  ModelEditor *m_modelEditor;
  PreferencesWindow *m_preferencesWindow;
  AboutWindow *m_aboutWindow;

  DockWidgetSettings *m_dockWidgetSettings;
  DockWidgetModelEditor *m_dockWidgetModelEditor;

  MenuBar *m_menuBar;
  StatusBar *m_statusBar;
};

#endif // MAINWINDOW_H
