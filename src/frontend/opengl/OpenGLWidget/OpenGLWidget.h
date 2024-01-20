#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <thread>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <OpenGL/gl.h>
#endif // QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)

#include <QCoreApplication>
#include <QDir>
#include <QFileDialog>

#include "../Constants.h"
#include "backend/mesh_data.h"
#include "frontend/opengl/Camera.h"
#include "frontend/opengl/Mesh.h"
#include "frontend/opengl/Renderer.h"
#include "gif_library/gif.hpp"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

public:
  OpenGLWidget(QWidget *parent = nullptr);
  ~OpenGLWidget();

  void loadMeshData(const MeshData &data);

  void screencast();

private:
  Camera m_camera;
  Mesh m_mesh{};
  Renderer m_renderer;
  Transform m_mainMeshTransform{};

public slots:
  void handleProjectionTypeChanged();
  void handleCameraModeChanged();
  void assignAffineTransformations(const std::array<QVector3D, 3> &matrix);
  void adjustSize(const QSize &size);
  void clearMeshInformation();

private slots:
  void updateFrame();

protected:
  void initializeGL() override;

  void resizeGL(int width, int height) override;

  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

private:
  void applyInertialCameraMovement();
  void resetCameraProperties();

  uint8_t m_image[constants::defaultWidthForScreenCast * 2 *
                  constants::defaultHeightForScreenCast * 2 * 4];
};

#endif // OPENGLWIDGET_H
