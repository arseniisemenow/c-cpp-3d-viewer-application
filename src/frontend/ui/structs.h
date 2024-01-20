#ifndef STRUCTS_H
#define STRUCTS_H

#include <QMetaType>

enum class CameraMode {
  None = 0,
  Fly = 1 << 0,
  Turnable = 1 << 1,
};

Q_DECLARE_METATYPE(CameraMode);

namespace OpenType {
enum OpenType {
  None = 0,
  Inspector = 1 << 0,
  RecentFiles = 1 << 1,
};
}

namespace Projection {

enum Type {
  None = 0,
  Perspective = 1 << 0,
  Parallel = 1 << 1,
};

}

namespace Vertex {

enum DisplayMethod { None = 0, Circle = 1 << 0, Square = 1 << 1 };

}

namespace Edge {

enum Type { None = 0, Solid = 1 << 0, Dashed = 1 << 1 };

};

class DockWidgetSettings;
class DockWidgetModelEditor;

typedef struct {
  DockWidgetSettings *dockWidgetSettings;
  DockWidgetModelEditor *dockWidgetModelEditor;
} DockWidgets;

#endif // STRUCTS_H
