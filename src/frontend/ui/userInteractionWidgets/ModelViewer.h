#ifndef MODELVIEWER_H
#define MODELVIEWER_H

// #include "QtOpenGLWidgets/qopenglwidget.h"
#include <QHBoxLayout>
#include <QWidget>

#include "../../opengl/OpenGLWidget/OpenGLWidget.h"
#include "../EventHandler/EventHandler.h"

class ModelViewer : public QWidget {
  Q_OBJECT

public:
  ModelViewer(QWidget *parent = nullptr) {
    m_openGLWidget = new OpenGLWidget(this);

    connect(&EventHandler::get(), &EventHandler::eventOpenGLWidgetRequired,
            this, &ModelViewer::openGLWidgetGive);

    connect(this, &ModelViewer::eventOpenGLWidgetGiven, &EventHandler::get(),
            &EventHandler::openGLWidgetGiven);
  }
  ~ModelViewer(){};

  void openGLWidgetGive() { emit eventOpenGLWidgetGiven(m_openGLWidget); }

  const OpenGLWidget *getOpenGlWidget() const { return m_openGLWidget; }
signals:
  void eventOpenGLWidgetGiven(OpenGLWidget *openGLWidget);

private:
  OpenGLWidget *m_openGLWidget;
};

#endif // MODELVIEWER_H
