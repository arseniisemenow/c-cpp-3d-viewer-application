#include "OpenGLWidget.h"

#include <QTimer>
#include <QtMath>
#include <clocale>
#include <cmath>
#include <filesystem>
#include <iostream>

#include "backend/affine_transformations.h"
#include "backend/arrays.h"
#include "backend/parser/parser.h"
#include "frontend/ui/EventHandler/EventHandler.h"
#include "frontend/ui/Preferences/Preferences.h"
#include "frontend/ui/modalWidgets/FileDialog/FileDialog.h"

OpenGLWidget::OpenGLWidget(QWidget *parent)
    : QOpenGLWidget{parent}, m_camera{constants::defaultCameraPosition,
                                      constants::worldUpVector},
      m_renderer{size()} {
  QTimer *timer{new QTimer{this}};
  connect(timer, &QTimer::timeout, this, &OpenGLWidget::updateFrame);
  timer->start(constants::millisecondsPerFrame);
  setFocusPolicy(Qt::StrongFocus);

  connect(&EventHandler::get(), &EventHandler::eventProjectionTypeChanged, this,
          &OpenGLWidget::handleProjectionTypeChanged);
  connect(&EventHandler::get(), &EventHandler::eventCameraModeChanged, this,
          &OpenGLWidget::handleCameraModeChanged);
  connect(&EventHandler::get(), &EventHandler::eventChangeOpenGLWidgetSize,
          this, &OpenGLWidget::adjustSize);
  connect(&EventHandler::get(), &EventHandler::eventAffineTransformationChanged,
          this, &OpenGLWidget::assignAffineTransformations);
  connect(&EventHandler::get(), &EventHandler::eventCloseFile, this,
          &OpenGLWidget::clearMeshInformation);
}

OpenGLWidget::~OpenGLWidget() {}

void OpenGLWidget::clearMeshInformation() { m_mesh.unload(); }

void OpenGLWidget::initializeGL() {
  std::setlocale(LC_ALL, "C");
  initializeOpenGLFunctions();
  m_mesh.initializeBuffers();
  m_renderer.initializeRenderingEnvironment();
  m_renderer.setupShaders();

  m_mainMeshTransform.translation = {constants::defaultTranslation};
  m_mainMeshTransform.rotationAngles = {constants::defaultRotationAngles};
  m_mainMeshTransform.scaling = {constants::defaultScaling};
}

void OpenGLWidget::paintGL() {
  m_renderer.clearBuffersAndBackgroundColor();

  m_renderer.bindShaderProgram();

  m_renderer.updateProjectionMatrix(m_camera.getFieldOfView(),
                                    m_camera.getOrthoScale());
  m_renderer.updateViewMatrix(m_camera, m_mesh.getData().center);

  if (m_mesh.getData().faces.size != 0 && m_mesh.getData().vertices.size != 0) {
    m_renderer.updateModelMatrix(m_mesh, m_mainMeshTransform);
    m_renderer.renderMesh(m_mesh);
  }

  m_renderer.releaseShaderProgram();
  glReadPixels(0, 0, constants::defaultWidthForScreenCast,
               constants::defaultHeightForScreenCast, GL_RGBA, GL_UNSIGNED_BYTE,
               m_image);
}

void OpenGLWidget::handleProjectionTypeChanged() {
  if (Preferences::get().getProjectionType() == Projection::Type::Parallel) {
    m_camera.resetOrthographicScale();
  } else {
    m_camera.setPosition(constants::defaultCameraPosition);
  }
}

void OpenGLWidget::handleCameraModeChanged() { resetCameraProperties(); }

void OpenGLWidget::assignAffineTransformations(
    const std::array<QVector3D, 3> &matrix) {
  m_mainMeshTransform.translation = {matrix[0]};
  m_mainMeshTransform.rotationAngles = {matrix[1]};
  m_mainMeshTransform.scaling = {matrix[2]};
}

void OpenGLWidget::adjustSize(const QSize &size) {
  resizeGL(size.width(), size.height());
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
  m_camera.processMousePress(event);
  update();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
  m_camera.processMouseMovement(event);
  update();
}

void OpenGLWidget::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event);
  m_camera.processMouseRelease();
  update();
}

void OpenGLWidget::wheelEvent(QWheelEvent *event) {
  m_camera.processMouseScroll(event, m_mesh.getData());
  update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
  m_camera.processKeyboard(event);
  update();
}

void OpenGLWidget::resizeGL(int width, int height) {
  resize(width, height);
  m_renderer.handleResizing(width, height);
}

void OpenGLWidget::updateFrame() { update(); }

void OpenGLWidget::loadMeshData(const MeshData &data) {
  m_mesh.load(data);
  resetCameraProperties();
}

void OpenGLWidget::applyInertialCameraMovement() {
  m_camera.applyInertialMovement();
  update();
}

void OpenGLWidget::resetCameraProperties() {
  m_camera.clampElevation();
  m_camera.updateCameraVectors();
  if (Preferences::get().getCameraMode() == CameraMode::Fly) {
    m_camera.setLookAt({m_mesh.getData().center.x, m_mesh.getData().center.y,
                        m_mesh.getData().center.z},
                       constants::worldUpVector);
  }
  m_camera.setPosition(constants::defaultCameraPosition);
}

void OpenGLWidget::screencast() {
  QString exePath{QCoreApplication::applicationDirPath()};
  QDir dir{exePath};

  QString filePath{"./screencast.gif"};
  int delay{constants::defaultDelayForScreenCast};
  int totalLength{constants::defaultDurationScreenCast * 1000};
  GifWriter gifWriter{};

  GifBegin(&gifWriter, dir.filePath(filePath).toStdString().c_str(),
           constants::defaultWidthForScreenCast,
           constants::defaultHeightForScreenCast, delay);

  for (int timer{0}; timer <= totalLength; timer += delay) {
    GifWriteFrame(&gifWriter, m_image, constants::defaultWidthForScreenCast,
                  constants::defaultHeightForScreenCast, 1);

    std::this_thread::sleep_for(std::chrono::milliseconds{delay});
  }

  GifEnd(&gifWriter);

  std::cerr << "Screencast saved at: " << dir.filePath(filePath).toStdString()
            << std::endl;
}
