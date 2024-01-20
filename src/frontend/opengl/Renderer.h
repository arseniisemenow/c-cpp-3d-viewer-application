#ifndef RENDERER_H
#define RENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "Camera.h"
#include "Constants.h"
#include "Mesh.h"

class Renderer : protected QOpenGLFunctions {
public:
  Renderer(const QSize &screenSize);
  void initializeRenderingEnvironment();
  void setupShaders();

  void clearBuffersAndBackgroundColor();

  void bindShaderProgram();
  void releaseShaderProgram();

  void updateProjectionMatrix(float fieldOfView, float orthoScale);
  void updateViewMatrix(const Camera &camera, const FloatVec3 &mainMeshCenter);
  void updateModelMatrix(Mesh &mesh, const Transform &transform);

  void renderMesh(Mesh &mesh);
  void handleResizing(int newWidth, int newHeight);

private:
  QSize m_screenSize{};
  float m_screenRatio{};

  QOpenGLShaderProgram m_shaderProgram{};

  GLint m_projectionMatrixLocation{};
  GLint m_viewMatrixLocation{};
  GLint m_modelMatrixLocation{};
  GLint m_fragColorLocation{};
};

#endif // RENDERER_H
