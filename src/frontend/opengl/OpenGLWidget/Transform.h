#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QVector3D>

struct Transform {
  QVector3D translation{};
  QVector3D rotationAngles{};
  QVector3D scaling{};
};

#endif // TRANSFORM_H
