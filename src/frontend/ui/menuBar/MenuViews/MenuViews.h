#ifndef MENU_VIEWS_H
#define MENU_VIEWS_H

#include <QAction>
#include <QDockWidget>
#include <QMenu>

#include "../../structs.h"

class MenuViews : public QMenu {
  Q_OBJECT
public:
  MenuViews(const QString &title, QWidget *parent = nullptr);

  void setCheckedStatusModelEditorAction(bool visibility);

private:
  QList<QAction *> m_dockWidgetActions;
  QAction *m_actionModelEditor;
};

#endif // MENU_VIEWS_H
