#include "MenuViews.h"

#include "../../EventHandler/EventHandler.h"
#include "../../dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.h"

MenuViews::MenuViews(const QString &title, QWidget *parent) {
  this->setTitle(title);

  m_actionModelEditor = new QAction("Model Editor");
  m_actionModelEditor->setCheckable(true);
  setCheckedStatusModelEditorAction(true);

  connect(m_actionModelEditor, &QAction::toggled, &EventHandler::get(),
          &EventHandler::toggleDockWidgetModelEditor);

  /* Set right action status when dock widget is toggled */
  connect(&EventHandler::get(),
          &EventHandler::eventToggledDockWidgetModelEditor, this,
          &MenuViews::setCheckedStatusModelEditorAction);

  m_dockWidgetActions.append(m_actionModelEditor);

  for (QAction *action : m_dockWidgetActions) {
    this->addAction(action);
  }
}

void MenuViews::setCheckedStatusModelEditorAction(bool visibility) {
  /* Temporarily disabling all signals to prevent a feedback loop */
  m_actionModelEditor->blockSignals(true);
  m_actionModelEditor->setChecked(visibility);
  m_actionModelEditor->blockSignals(false);
}
