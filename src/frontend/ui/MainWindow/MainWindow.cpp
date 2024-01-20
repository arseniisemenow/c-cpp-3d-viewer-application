#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_aboutWindow(new AboutWindow()) {
  EventHandler::get();
  Preferences::get();
  FileHandler::get();

  m_preferencesWindow = new PreferencesWindow(this);

  m_modelViewer = new ModelViewer(this);
  m_modelEditor = new ModelEditor(this);

  connect(&EventHandler::get(), &EventHandler::eventOpenPreferencesWindow, this,
          &MainWindow::openPreferencesWindow);
  connect(&EventHandler::get(), &EventHandler::eventOpenAboutWindow, this,
          &MainWindow::openAboutWindow);
  connect(&EventHandler::get(), &EventHandler::eventCloseMainWindow, this,
          &MainWindow::closeWindow);
  connect(&FileHandler::get(), &FileHandler::fileLoaded,
          m_modelViewer->getOpenGlWidget(), &OpenGLWidget::loadMeshData);

  connect(this, &MainWindow::eventWidgetSizeChanged, &EventHandler::get(),
          &EventHandler::widgetSizeChanged);

  connect(
      &EventHandler::get(), &EventHandler::eventWidgetSizeChanged, this, [=]() {
        QSize mainWindowSize = this->size();
        QSize dockWidgetSettingsSize = m_dockWidgetSettings->size();
        QSize dockWidgetModelEditorSize = m_dockWidgetModelEditor->size();

        int dockWidgetModeEditorWidth = dockWidgetModelEditorSize.width() *
                                        m_dockWidgetModelEditor->getIsVisible();

        int GLNewWidth = mainWindowSize.width() - dockWidgetModeEditorWidth;
        int GLNewHeight =
            mainWindowSize.height() - dockWidgetSettingsSize.height();

        QSize GLNewSize(GLNewWidth, GLNewHeight);
        changeOpenGLWidgetSize(GLNewSize);
      });

  connect(this, &MainWindow::eventChangeOpenGLWidgetSize, &EventHandler::get(),
          &EventHandler::changeOpenGLWidgetSize);

  //    preferencesWindow->show();  // TODO REMOVE

  setGeometry(100, 100, 1280, 720);

  loadPreferences();

  updateStyles();

  setCorners();

  setDockWidgets();

  setMenu();
  setProgressBar();

  setModelViewer();
}

void MainWindow::changeOpenGLWidgetSize(const QSize GLNewSize) {
  emit eventChangeOpenGLWidgetSize(GLNewSize);
}

MainWindow::~MainWindow() {}

void MainWindow::updateStyles() {
  this->setStyleSheet(getStylesFromFile(PATH_MAIN_WINDOW_STYLES_FILE));
}

void MainWindow::setDockWidgets() {
  setSettingsDockWidget();
  setModelEditorDockWidget();
}

void MainWindow::setCorners() {
  setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
  setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
  setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
}

void MainWindow::setProgressBar() {
  m_statusBar = new StatusBar();
  //    statusBar->setVertexCount(1);
  //    statusBar->setPolygonsCount(1);
  setStatusBar(m_statusBar);
}

void MainWindow::setMenu() {
  m_menuBar = new MenuBar(this);
  this->setMenuBar(m_menuBar);
}

void MainWindow::loadPreferences() { Preferences::get().load(); }

void MainWindow::savePreferences() { Preferences::get().save(); }

void MainWindow::setSettingsDockWidget() {
  m_dockWidgetSettings = new DockWidgetSettings(this);

  m_dockWidgetSettings->setFeatures(
      DockWidgetModelEditor::NoDockWidgetFeatures);

  QWidget *titleBarWidget = new QWidget;
  titleBarWidget->setFixedHeight(0);

  m_dockWidgetSettings->setTitleBarWidget(titleBarWidget);

  addDockWidget(Qt::BottomDockWidgetArea, m_dockWidgetSettings);
}

void MainWindow::setModelViewer() { setCentralWidget(m_modelViewer); }

void MainWindow::setModelEditorDockWidget() {
  m_dockWidgetModelEditor = new DockWidgetModelEditor();
  TransformWidget *transformWidget = new TransformWidget(this);
  m_dockWidgetModelEditor->setWidget(transformWidget);
  addDockWidget(Qt::RightDockWidgetArea, m_dockWidgetModelEditor);
  m_dockWidgetModelEditor->setFeatures(
      DockWidgetModelEditor::NoDockWidgetFeatures);
}

void MainWindow::openPreferencesWindow() {
  m_preferencesWindow->loadSettings();
  m_preferencesWindow->show();
}

void MainWindow::closePreferencesWindow() { m_preferencesWindow->close(); }

void MainWindow::openAboutWindow() { m_aboutWindow->show(); }

void MainWindow::closeAboutWindow() { m_aboutWindow->close(); }

void MainWindow::closeWindow() {
  //    Preferences::get().save();
  closePreferencesWindow();
  closeAboutWindow();
  this->close();
}
