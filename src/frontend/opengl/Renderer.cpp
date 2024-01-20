#include "Renderer.h"

#include <iostream>

#include "Constants.h"
#include "frontend/ui/Preferences/Preferences.h"

Renderer::Renderer(const QSize &screenSize)
    : m_screenSize{screenSize}, m_screenRatio{
                                    static_cast<float>(m_screenSize.width()) /
                                    m_screenSize.height()} {}

void Renderer::initializeRenderingEnvironment() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void Renderer::setupShaders() {
  m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                          ":/vertexShader.vert");
  m_shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                          ":/fragmentShader.frag");
  if (!m_shaderProgram.link()) {
    std::cerr << "Shader program failed to link:"
              << m_shaderProgram.log().toStdString();
  }

  m_projectionMatrixLocation =
      m_shaderProgram.uniformLocation("projectionMatrix");
  m_viewMatrixLocation = m_shaderProgram.uniformLocation("viewMatrix");
  m_modelMatrixLocation = m_shaderProgram.uniformLocation("modelMatrix");
  m_fragColorLocation = m_shaderProgram.uniformLocation("fragColor");
}

void Renderer::clearBuffersAndBackgroundColor() {
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  QColor backgroundColor{Preferences::get().getBackgroundColor()};
  glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
               backgroundColor.blueF(), 1.0f);
}

void Renderer::bindShaderProgram() { m_shaderProgram.bind(); }

void Renderer::releaseShaderProgram() { m_shaderProgram.release(); }

void Renderer::updateProjectionMatrix(float fieldOfView, float orthoScale) {
  QMatrix4x4 projectionMatrix{};

  if (Preferences::get().getProjectionType() == Projection::Type::Perspective) {
    int nearPlane{Preferences::get().getNearPlane()};
    int farPlane{Preferences::get().getFarPlane()};
    projectionMatrix.perspective(fieldOfView, m_screenRatio, nearPlane,
                                 farPlane);
  } else {
    projectionMatrix.ortho(-orthoScale * m_screenRatio,
                           orthoScale * m_screenRatio, -orthoScale, orthoScale,
                           constants::defaultOrthographicNearPlane,
                           constants::defaultOrthographicFarPlane);
  }

  m_shaderProgram.setUniformValue(m_projectionMatrixLocation, projectionMatrix);
}

void Renderer::updateViewMatrix(const Camera &camera,
                                const FloatVec3 &mainMeshCenter) {
  QMatrix4x4 viewMatrix{};

  if (Preferences::get().getCameraMode() == CameraMode::Fly) {
    viewMatrix = camera.getLookAtMatrix();
  } else {
    viewMatrix.setToIdentity();
    viewMatrix.translate(camera.getPosition());
    viewMatrix.rotate(camera.getElevation(), constants::xAxis);
    viewMatrix.rotate(camera.getAzimuth(), constants::yAxis);
    viewMatrix.translate(-mainMeshCenter.x, -mainMeshCenter.y,
                         -mainMeshCenter.z);
  }

  m_shaderProgram.setUniformValue(m_viewMatrixLocation, viewMatrix);
}

void Renderer::updateModelMatrix(Mesh &mesh, const Transform &transform) {
  mesh.applyTransformations(transform);
  m_shaderProgram.setUniformValue(m_modelMatrixLocation, mesh.getModelMatrix());
}

void Renderer::renderMesh(Mesh &mesh) {
  mesh.renderEdges(m_shaderProgram, m_fragColorLocation);
  if (Preferences::get().getVertexDisplayMethod() !=
      Vertex::DisplayMethod::None) {
    mesh.renderPoints(m_shaderProgram, m_fragColorLocation);
  }
}

void Renderer::handleResizing(int newWidth, int newHeight) {
  m_screenSize.setWidth(newWidth);
  m_screenSize.setHeight(newHeight);
  m_screenRatio =
      static_cast<float>(m_screenSize.width()) / m_screenSize.height();
}
