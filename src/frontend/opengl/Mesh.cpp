#include "Mesh.h"

#include <QQuaternion>
#include <iostream>

#include "Constants.h"
#include "backend/affine_transformations.h"
#include "frontend/ui/Preferences/Preferences.h"

Mesh::Mesh()
    : m_vertexBuffer{QOpenGLBuffer::Type::VertexBuffer},
      m_indexBuffer{QOpenGLBuffer::Type::IndexBuffer} {}

Mesh::~Mesh() {
  floatArrayDestroy(&m_data.vertices);
  intArrayDestroy(&m_data.faces);
}

void Mesh::initializeBuffers() {
  initializeOpenGLFunctions();
  m_vertexBuffer.create();
  m_indexBuffer.create();
  m_vertexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
  m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);

  bindVertexBuffer();
  glVertexAttribPointer(
      0, constants::numberOfVertexCoordinates, GL_FLOAT, GL_FALSE,
      constants::numberOfVertexCoordinates * sizeof(float), nullptr);
  glEnableVertexAttribArray(0);
  releaseVertexBuffer();
}

void Mesh::load(const MeshData &data) {
  unload();

  m_data = data;

  bindBuffers();

  m_vertexBuffer.allocate(nullptr, 0);
  m_indexBuffer.allocate(nullptr, 0);
  m_vertexBuffer.allocate(m_data.vertices.data,
                          m_data.numberOfVertices *
                              constants::numberOfVertexCoordinates *
                              sizeof(float));
  m_indexBuffer.allocate(m_data.faces.data, m_data.numberOfEdges *
                                                constants::numberOfEdgePoints *
                                                sizeof(int));

  releaseBuffers();
}

void Mesh::unload() {
  floatArrayDestroy(&m_data.vertices);
  intArrayDestroy(&m_data.faces);
  m_data.numberOfEdges = 0;
  m_data.numberOfVertices = 0;
  m_data.center = {0.0f, 0.0f, 0.0f};
}

void Mesh::renderEdges(QOpenGLShaderProgram &shaderProgram,
                       GLint colorLocation) {
  bindBuffers();

  if (Preferences::get().getEdgeType() == Edge::Type::Dashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 10);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineWidth(Preferences::get().getEdgeSize());

  shaderProgram.setUniformValue(colorLocation,
                                Preferences::get().getEdgeColor());
  glDrawElements(GL_LINES, m_data.numberOfEdges * constants::numberOfEdgePoints,
                 GL_UNSIGNED_INT, nullptr);

  releaseBuffers();
}

void Mesh::renderPoints(QOpenGLShaderProgram &shaderProgram,
                        GLint colorLocation) {
  bindBuffers();

  if (Preferences::get().getVertexDisplayMethod() ==
      Vertex::DisplayMethod::Circle) {
    glEnable(GL_POINT_SMOOTH);
  } else {
    glDisable(GL_POINT_SMOOTH);
  }
  glPointSize(Preferences::get().getVertexSize());

  shaderProgram.setUniformValue(colorLocation,
                                Preferences::get().getVertexColor());
  glDrawArrays(GL_POINTS, 0, m_data.numberOfVertices);

  releaseBuffers();
}

void Mesh::bindVertexBuffer() { m_vertexBuffer.bind(); }

void Mesh::bindIndexBuffer() { m_indexBuffer.bind(); }

void Mesh::releaseVertexBuffer() { m_vertexBuffer.release(); }

void Mesh::releaseIndexBuffer() { m_indexBuffer.release(); }

void Mesh::bindBuffers() {
  bindVertexBuffer();
  bindIndexBuffer();
}

void Mesh::releaseBuffers() {
  releaseVertexBuffer();
  releaseIndexBuffer();
}

const MeshData &Mesh::getData() const { return m_data; }

void Mesh::applyTransformations(const Transform &transform) {
  m_modelMatrix.setToIdentity();
  translate(m_modelMatrix.data(), transform.translation.x(),
            transform.translation.y(), transform.translation.z());
  rotate(m_modelMatrix.data(), transform.rotationAngles.x(), 1.0, 0.0, 0.0);
  rotate(m_modelMatrix.data(), transform.rotationAngles.y(), 0.0, 1.0, 0.0);
  rotate(m_modelMatrix.data(), transform.rotationAngles.z(), 0.0, 0.0, 1.0);
  scale(m_modelMatrix.data(), transform.scaling.x(), transform.scaling.y(),
        transform.scaling.z());
}

const QMatrix4x4 &Mesh::getModelMatrix() const { return m_modelMatrix; }
