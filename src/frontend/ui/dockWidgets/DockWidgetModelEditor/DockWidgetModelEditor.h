#ifndef DOCK_WIDGET_MODEL_EDITOR_H
#define DOCK_WIDGET_MODEL_EDITOR_H

#include <QtGui/qevent.h>

#include <QDockWidget>
#include <QHBoxLayout>
#include <QLabel>

#include "../../EventHandler/EventHandler.h"
#include "../../TitleBar/TitleBar.h"
#include "../../TransformWidget/TransformWidget.h"

class DockWidgetModelEditor : public QDockWidget {
  Q_OBJECT
public:
  DockWidgetModelEditor();
  ~DockWidgetModelEditor();

  void toggleVisibility();
  int getIsVisible();

signals:
  void eventToggledDockWidgetModelEditor(bool isVisible);
  void eventResized();

private:
  void resizeEvent(QResizeEvent *event);
  void toggledDockWidgetModelEditor(bool visibility);

  bool m_isVisible;
};

#endif // DOCK_WIDGET_MODEL_EDITOR_H
