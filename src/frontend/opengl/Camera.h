#ifndef CAMERA_H
#define CAMERA_H

#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QObject>
#include <QPoint>
#include <QTimer>
#include <QVector3D>
#include <QWheelEvent>
#include <memory>

#include "Constants.h"
#include "backend/mesh_data.h"

class Camera : public QObject {
public:
  Camera(const QVector3D &position, const QVector3D &up,
         float azimuth = constants::defaultAzimuthAngle,
         float elevation = constants::defaultElevationAngle);

  void processKeyboard(QKeyEvent *event);
  void processMousePress(QMouseEvent *event);
  void processMouseMovement(QMouseEvent *event);
  void processMouseScroll(QWheelEvent *event, const MeshData &objectData);
  void processMouseRelease();

  void setPosition(const QVector3D &position);
  void updateAnglesAndVectors(int deltaX, int deltaY);
  void updateCameraVectors();

  void setLookAt(const QVector3D &target, const QVector3D &up);
  QMatrix4x4 getLookAtMatrix() const;

  void applyInertialMovement();

  void resetOrthographicScale();
  void clampElevation();

  const QVector3D &getPosition() const;
  const QPoint &getLastMousePosition() const;
  float getAzimuth() const;
  float getElevation() const;
  float getOrthoScale() const;
  float getFieldOfView() const;

private:
  void startIntertialMovement();
  void stopIntertialMovement();

private:
  QVector3D m_position{};
  QVector3D m_front{};
  QVector3D m_right{};
  QVector3D m_up{};
  QVector3D m_worldUp{};

  float m_azimuth{};
  float m_elevation{};
  float m_sensitivity{};

  float m_fieldOfView{};
  float m_zoomSpeed{};
  float m_orthoScale{};

  QPoint m_lastMousePosition{};

  std::unique_ptr<QTimer> m_inertialMovementTimer{};
  QVector2D m_mouseDelta{};
};

#endif // CAMERA_H
