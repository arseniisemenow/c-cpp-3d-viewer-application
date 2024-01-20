#include "MenuMedia.h"

MenuMedia::MenuMedia(const QString &title) {
  setTitle(title);

  m_createImageAction = new QAction(ACTION_TITLE_CREATE_IMAGE);
  m_createAnimationAction = new QAction(ACTION_TITLE_CREATE_ANIMATION);

  connect(this, &MenuMedia::eventRequireOpenGLWidget, &EventHandler::get(),
          &EventHandler::openGLWidgetRequired);
  connect(&EventHandler::get(), &EventHandler::eventOpenGLWidgetGiven, this,
          [=](OpenGLWidget *openGLWidget) {
            m_mediaProcessor = new MediaProcessor(this, openGLWidget);
            connect(m_createImageAction, &QAction::triggered, this,
                    [this]() { m_mediaProcessor->captureAndSaveImage(); });
            connect(m_createAnimationAction, &QAction::triggered, this,
                    [this]() { m_mediaProcessor->captureAndSaveAnimation(); });
          });

  requireOpenGLWidget();

  addAction(m_createImageAction);
  addAction(m_createAnimationAction);
}
