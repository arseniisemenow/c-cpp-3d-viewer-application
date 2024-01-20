#include "Preferences.h"

Preferences::~Preferences(){};

void Preferences::saveSceneScale() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_sceneScale),
                                          m_sceneScale);
}
// dockWidgetSettings
void Preferences::saveProjectionType() {
  Preferences::get().m_dockWidgetSettings->setValue(STRINGIFY(m_projectionType),
                                                    m_projectionType);
}
void Preferences::saveBackgroundColor() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_backgroundColor),
                                          m_backgroundColor);
}
void Preferences::saveVertexDisplayMethod() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_vertexDisplayMethod),
                                          m_vertexDisplayMethod);
}
void Preferences::saveVertexColor() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_vertexColor),
                                          m_vertexColor);
}
void Preferences::saveVertexSize() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_vertexSize),
                                          m_vertexSize);
}
void Preferences::saveEdgeType() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_edgeType), m_edgeType);
}
void Preferences::saveEdgeColor() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_edgeColor), m_edgeColor);
}
void Preferences::saveEdgeSize() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_edgeSize), m_edgeSize);
}

void Preferences::saveLastOpenedDir() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_lastOpenedDir),
                                          m_lastOpenedDir);
}

// dockWidgetSettings
void Preferences::saveCameraMode() {
  Preferences::get().m_dockWidgetSettings->setValue(
      STRINGIFY(m_cameraMode), static_cast<int>(m_cameraMode));
}
void Preferences::saveCameraSpeed() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_cameraSpeed),
                                          m_cameraSpeed);
}
void Preferences::saveNearPlane() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_nearPlane), m_nearPlane);
}

void Preferences::saveFarPlane() {
  Preferences::get().m_settings->setValue(STRINGIFY(m_farPlane), m_farPlane);
}

void Preferences::save() {
  std::cerr << "Preferences::save()\n";
  saveSceneScale();
  saveBackgroundColor();
  saveCameraSpeed();
  saveNearPlane();
  saveFarPlane();

  saveVertexDisplayMethod();
  saveVertexColor();
  saveVertexSize();

  saveEdgeType();
  saveEdgeColor();
  saveEdgeSize();

  saveLastOpenedDir();
  saveProjectionType();
  saveCameraMode();
}

void Preferences::loadSceneScale() {
  m_sceneScale =
      Preferences::get()
          .m_settings->value(STRINGIFY(m_sceneScale), S21_DEFAULT_SCALE)
          .toDouble();
}

// dockWidgetSettings
void Preferences::loadProjectionType() {
  m_projectionType =
      Preferences::get()
          .m_dockWidgetSettings
          ->value(STRINGIFY(m_projectionType), Projection::Type::Perspective)
          .toInt();
}

void Preferences::loadBackgroundColor() {
  m_backgroundColor = Preferences::get()
                          .m_settings
                          ->value(STRINGIFY(m_backgroundColor),
                                  QColor(S21_DEFAULT_BACKGROUND_COLOR))
                          .value<QColor>();
}

void Preferences::loadVertexDisplayMethod() {
  m_vertexDisplayMethod = Preferences::get()
                              .m_settings
                              ->value(STRINGIFY(m_vertexDisplayMethod),
                                      Vertex::DisplayMethod::Circle)
                              .toInt();
}

void Preferences::loadVertexColor() {
  m_vertexColor =
      Preferences::get()
          .m_settings
          ->value(STRINGIFY(m_vertexColor), QColor(S21_DEFAULT_VERTEX_COLOR))
          .value<QColor>();
}

void Preferences::loadVertexSize() {
  m_vertexSize =
      Preferences::get()
          .m_settings->value(STRINGIFY(m_vertexSize), S21_DEFAULT_VERTEX_SIZE)
          .toInt();
}

void Preferences::loadEdgeType() {
  m_edgeType = Preferences::get()
                   .m_settings->value(STRINGIFY(m_edgeType), Edge::Type::Solid)
                   .toInt();
}

void Preferences::loadEdgeColor() {
  m_edgeColor =
      Preferences::get()
          .m_settings
          ->value(STRINGIFY(m_edgeColor), QColor(S21_DEFAULT_EDGE_COLOR))
          .value<QColor>();
}

void Preferences::loadEdgeSize() {
  m_edgeSize =
      Preferences::get()
          .m_settings->value(STRINGIFY(m_edgeSize), S21_DEFAULT_EDGE_SIZE)
          .toDouble();
}

void Preferences::loadLastOpenedDir() {
  m_lastOpenedDir =
      Preferences::get()
          .m_settings->value(STRINGIFY(m_lastOpenedDir), QDir::homePath())
          .toString();
}

// dockWidgetSettings
void Preferences::loadCameraMode() {
  m_cameraMode =
      Preferences::get()
          .m_dockWidgetSettings
          ->value(STRINGIFY(m_cameraMode), QVariant::fromValue(CameraMode::Fly))
          .value<CameraMode>();
}

void Preferences::loadCameraSpeed() {
  m_cameraSpeed =
      Preferences::get()
          .m_settings
          ->value(STRINGIFY(m_cameraSpeed), S21_DEFAULT_CAMERA_SPEED_VALUE)
          .value<int>();
}

void Preferences::loadNearPlane() {
  m_nearPlane =
      Preferences::get()
          .m_settings
          ->value(STRINGIFY(m_nearPlane), S21_DEFAULT_NEAR_PLANE_VALUE)
          .value<int>();
}

void Preferences::loadFarPlane() {
  m_farPlane =
      Preferences::get()
          .m_settings->value(STRINGIFY(m_farPlane), S21_DEFAULT_FAR_PLANE_VALUE)
          .value<int>();
}

void Preferences::load() {
  std::cerr << "Preferences::load()\n";
  loadSceneScale();
  loadBackgroundColor();
  loadCameraSpeed();
  loadNearPlane();
  loadFarPlane();

  loadVertexDisplayMethod();
  loadVertexColor();
  loadVertexSize();

  loadEdgeType();
  loadEdgeColor();
  loadEdgeSize();

  loadProjectionType();
  loadCameraMode();
}

double Preferences::getScale() { return m_sceneScale; }
// dockWidgetSettings
int Preferences::getProjectionType() { return m_projectionType; }

QColor Preferences::getBackgroundColor() { return m_backgroundColor; }

int Preferences::getVertexDisplayMethod() { return m_vertexDisplayMethod; }

QColor Preferences::getVertexColor() { return m_vertexColor; }

double Preferences::getVertexSize() { return m_vertexSize; }

int Preferences::getEdgeType() { return m_edgeType; }

QColor Preferences::getEdgeColor() { return m_edgeColor; }

double Preferences::getEdgeSize() { return m_edgeSize; }
// dockWidgetSettings
CameraMode Preferences::getCameraMode() { return m_cameraMode; }
int Preferences::getCameraSpeed() { return m_cameraSpeed; }
int Preferences::getNearPlane() { return m_nearPlane; }
int Preferences::getFarPlane() { return m_farPlane; }

int Preferences::setScale(double newSceneScale) {
  if (newSceneScale <= 0) {
    return 1;
  }
  if (newSceneScale > S21_BIG_NUMBER) {
    return 1;
  }
  m_sceneScale = newSceneScale;
  return 0;
}

// dockWidgetSettings
int Preferences::setProjectionType(Projection::Type newProjectionType) {
  if (newProjectionType == Projection::Type::None) {
    return 1;
  }
  m_projectionType = newProjectionType;
  return 0;
}
// dockWidgetSettings
int Preferences::setCameraMode(CameraMode newCameraMode) {
  if (m_cameraMode == CameraMode::None) {
    return 1;
  }
  m_cameraMode = newCameraMode;
  return 0;
}

int Preferences::setBackgroundColor(QColor newColor) {
  m_backgroundColor = newColor;
  return 0;
}

int Preferences::setVertexDisplayMethod(
    Vertex::DisplayMethod newVertexDisplayMethod) {
  m_vertexDisplayMethod = newVertexDisplayMethod;
  return 0;
}

int Preferences::setVertexColor(QColor newColor) {
  m_vertexColor = newColor;
  return 0;
}

int Preferences::setVertexSize(double newSize) {
  if (newSize <= 0) {
    return 1;
  }
  if (newSize > S21_BIG_NUMBER) {
    return 1;
  }
  m_vertexSize = newSize;
  return 0;
}

int Preferences::setEdgeType(Edge::Type newEdgeType) {
  if (newEdgeType == Edge::Type::None) {
    return 1;
  }
  m_edgeType = newEdgeType;
  return 0;
}

int Preferences::setEdgeColor(QColor newColor) {
  m_edgeColor = newColor;
  return 0;
}

int Preferences::setEdgeSize(double newSize) {
  if (newSize <= 0) {
    return 1;
  }
  if (newSize > S21_BIG_NUMBER) {
    return 1;
  }
  m_edgeSize = newSize;
  return 0;
}

int Preferences::setCameraSpeed(int newCameraSpeed) {
  m_cameraSpeed = newCameraSpeed;
  return 0;
}
int Preferences::setNearPlane(int newNearPlane) {
  m_nearPlane = newNearPlane;
  return 0;
}
int Preferences::setFarPlane(int newFarPlane) {
  m_farPlane = newFarPlane;
  return 0;
}
