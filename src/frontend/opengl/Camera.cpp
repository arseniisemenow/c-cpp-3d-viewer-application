#include "Camera.h"

#include <QObject>
#include <QtMath>
#include <cmath>

#include "frontend/ui/Preferences/Preferences.h"

Camera::Camera(const QVector3D &position, const QVector3D &worldUp,
               float azimuth, float elevation)
    : m_position{position}, m_front{constants::defaultFrontVector},
      m_worldUp{worldUp}, m_azimuth{azimuth}, m_elevation{elevation},
      m_sensitivity{constants::defaultSensitivity},
      m_fieldOfView{constants::defaultFieldOfView},
      m_zoomSpeed{constants::defaultZoomSpeed},
      m_orthoScale{constants::defaultOrthographicScale},
      m_inertialMovementTimer{std::make_unique<QTimer>()} {
  connect(m_inertialMovementTimer.get(), &QTimer::timeout, this,
          &Camera::applyInertialMovement);
  updateCameraVectors();
}

void Camera::processKeyboard(QKeyEvent *event) {
  if (Preferences::get().getCameraMode() == CameraMode::Fly) {
    double speedCoefficient{0.2};
    double movementSpeed{Preferences::get().getCameraSpeed() *
                         speedCoefficient};
    if (event->key() == Qt::Key_W) {
      m_position += movementSpeed * m_front;
    }
    if (event->key() == Qt::Key_S) {
      m_position -= movementSpeed * m_front;
    }
    if (event->key() == Qt::Key_A) {
      m_position -= movementSpeed * m_right;
    }
    if (event->key() == Qt::Key_D) {
      m_position += movementSpeed * m_right;
    }
  }
}

void Camera::processMousePress(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_mouseDelta = QVector2D{0, 0};
    stopIntertialMovement();
    m_lastMousePosition = event->pos();
    event->accept();
  }
}

void Camera::updateAnglesAndVectors(int deltaX, int deltaY) {
  m_azimuth += deltaX * m_sensitivity;
  m_elevation += deltaY * m_sensitivity;

  clampElevation();
  updateCameraVectors();
}

void Camera::processMouseMovement(QMouseEvent *event) {
  if (event->buttons() & Qt::LeftButton) {
    QVector2D lastPos{m_lastMousePosition};
    m_mouseDelta = QVector2D{event->pos()} - lastPos;

    int deltaX{event->pos().x() - m_lastMousePosition.x()};
    int deltaY{};
    if (Preferences::get().getCameraMode() == CameraMode::Fly) {
      deltaY = m_lastMousePosition.y() - event->pos().y();
    } else {
      deltaY = event->pos().y() - m_lastMousePosition.y();
    }

    updateAnglesAndVectors(deltaX, deltaY);

    m_lastMousePosition = event->pos();
    event->accept();
  }
}

void Camera::processMouseScroll(QWheelEvent *event,
                                const MeshData &objectData) {
  if (Preferences::get().getCameraMode() == CameraMode::Turnable) {
    int delta{event->angleDelta().y()};
    m_position.setZ(m_position.z() + delta * m_zoomSpeed);
    if (m_position.z() >=
        objectData.center.z - constants::minimumDistanceToObjectCenter) {
      m_position.setZ(objectData.center.z -
                      constants::minimumDistanceToObjectCenter);
    }

    if (Preferences::get().getProjectionType() == Projection::Type::Parallel) {
      m_orthoScale -= delta * constants::orthoScaleChangeSpeed;
      if (m_orthoScale < constants::minimumOrthographicScale) {
        m_orthoScale = constants::minimumOrthographicScale;
      }
    }
  }
}

void Camera::processMouseRelease() { startIntertialMovement(); }

void Camera::setPosition(const QVector3D &position) { m_position = position; }

QMatrix4x4 Camera::getLookAtMatrix() const {
  QMatrix4x4 matrix{};
  matrix.lookAt(m_position, m_front + m_position, m_up);
  return matrix;
}

void Camera::setLookAt(const QVector3D &target, const QVector3D &up) {
  QMatrix4x4 viewMatrix{};
  viewMatrix.lookAt(m_position, target, up);

  m_front = -viewMatrix.column(2).toVector3D().normalized();
  m_right = viewMatrix.column(0).toVector3D().normalized();
  m_up = viewMatrix.column(1).toVector3D().normalized();

  m_azimuth = qRadiansToDegrees(std::atan2(-m_front.x(), -m_front.z())) - 90.0f;
  m_elevation = qRadiansToDegrees(std::asin(m_front.y()));

  updateCameraVectors();
}

void Camera::applyInertialMovement() {
  if (Preferences::get().getCameraMode() == CameraMode::Turnable) {
    m_mouseDelta *= constants::inertialMovementDampingFactor;

    if (m_mouseDelta.lengthSquared() < constants::inertialMovementThreshold) {
      stopIntertialMovement();
    }

    updateAnglesAndVectors(m_mouseDelta.x(), m_mouseDelta.y());
  }
}

void Camera::resetOrthographicScale() {
  m_orthoScale = constants::defaultOrthographicScale;
}

void Camera::clampElevation() {
  if (Preferences::get().getCameraMode() == CameraMode::Fly) {
    m_elevation = qBound(-constants::maximumElevationAngle, m_elevation,
                         constants::maximumElevationAngle);
  }
}

const QVector3D &Camera::getPosition() const { return m_position; }

const QPoint &Camera::getLastMousePosition() const {
  return m_lastMousePosition;
}

float Camera::getAzimuth() const { return m_azimuth; }

float Camera::getElevation() const { return m_elevation; }

float Camera::getOrthoScale() const { return m_orthoScale; }

float Camera::getFieldOfView() const { return m_fieldOfView; }

void Camera::updateCameraVectors() {
  m_front.setX(std::cos(qDegreesToRadians(m_azimuth)) *
               std::cos(qDegreesToRadians(m_elevation)));
  m_front.setY(std::sin(qDegreesToRadians(m_elevation)));
  m_front.setZ(std::sin(qDegreesToRadians(m_azimuth)) *
               std::cos(qDegreesToRadians(m_elevation)));
  m_front = m_front.normalized();

  m_right = QVector3D::crossProduct(m_front, m_worldUp).normalized();
  m_up = QVector3D::crossProduct(m_right, m_front).normalized();
}

void Camera::startIntertialMovement() {
  if (Preferences::get().getCameraMode() == CameraMode::Turnable) {
    if (!m_inertialMovementTimer->isActive())
      m_inertialMovementTimer->start(constants::millisecondsPerFrame);
  }
}

void Camera::stopIntertialMovement() {
  if (Preferences::get().getCameraMode() == CameraMode::Turnable) {
    if (m_inertialMovementTimer->isActive())
      m_inertialMovementTimer->stop();
  }
}
