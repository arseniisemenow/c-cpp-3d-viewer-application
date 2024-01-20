#include "DockWidgetModelEditor.h"

DockWidgetModelEditor::DockWidgetModelEditor() {
  m_isVisible = 1;

  TitleBar *titleBar = new TitleBar("Object properties", this);
  setTitleBarWidget(titleBar);

  connect(&EventHandler::get(), &EventHandler::eventToggleDockWidgetModelEditor,
          this, &DockWidgetModelEditor::toggleVisibility);
  connect(this, &DockWidgetModelEditor::eventToggledDockWidgetModelEditor,
          &EventHandler::get(), &EventHandler::toggledDockWidgetModelEditor);
  connect(this, &DockWidgetModelEditor::eventResized, &EventHandler::get(),
          &EventHandler::eventWidgetSizeChanged);
};

DockWidgetModelEditor::~DockWidgetModelEditor(){};

void DockWidgetModelEditor::toggleVisibility() {
  if (m_isVisible) {
    this->hide();
    m_isVisible = 0;
  } else {
    this->show();
    m_isVisible = 1;
  }

  toggledDockWidgetModelEditor(m_isVisible);
}

int DockWidgetModelEditor::getIsVisible() { return m_isVisible; }

void DockWidgetModelEditor::resizeEvent(QResizeEvent *event) {
  emit eventResized();
  QDockWidget::resizeEvent(event);
}

void DockWidgetModelEditor::toggledDockWidgetModelEditor(bool visibility) {
  emit eventToggledDockWidgetModelEditor(visibility);
}
