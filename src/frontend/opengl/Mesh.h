#ifndef MESH_H
#define MESH_H

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "backend/mesh_data.h"
#include "frontend/opengl/OpenGLWidget/Transform.h"

class Mesh : protected QOpenGLFunctions {
public:
  Mesh();
  ~Mesh();

  void initializeBuffers();
  void load(const MeshData &data);
  void unload();
  void renderEdges(QOpenGLShaderProgram &shaderProgram, GLint colorLocation);
  void renderPoints(QOpenGLShaderProgram &shaderProgram, GLint colorLocation);

  void bindVertexBuffer();
  void bindIndexBuffer();
  void releaseVertexBuffer();
  void releaseIndexBuffer();
  void bindBuffers();
  void releaseBuffers();

  const MeshData &getData() const;
  void applyTransformations(const Transform &transform);
  const QMatrix4x4 &getModelMatrix() const;

  void setEdgeColor(const QVector3D &color);
  void setPointColor(const QVector3D &color);

private:
  QOpenGLBuffer m_vertexBuffer{};
  QOpenGLBuffer m_indexBuffer{};
  MeshData m_data{};

  GLint m_fragColorLocation{};

  QMatrix4x4 m_modelMatrix{};
};

#endif // MESH_H
