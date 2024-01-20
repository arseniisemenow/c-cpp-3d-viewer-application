#ifndef MENUMEDIA_H
#define MENUMEDIA_H

#include <QAction>
#include <QMenu>
#include <QObject>
#include <QVector>

#include "../../../opengl/OpenGLWidget/OpenGLWidget.h"
#include "../../EventHandler/EventHandler.h"
#include "../../MediaProcessor/MediaProcessor.h"
#include "../../Preferences/Preferences.h"
#include "../../styles/styles.h"

#define ACTION_TITLE_CREATE_IMAGE "Create image"
#define ACTION_TITLE_CREATE_ANIMATION "Create animation"

class MenuMedia : public QMenu {
  Q_OBJECT

public:
  MenuMedia(const QString &title = "Default Title");

  void requireOpenGLWidget() { emit eventRequireOpenGLWidget(); }

private:
  QAction *m_createImageAction;
  QAction *m_createAnimationAction;

  MediaProcessor *m_mediaProcessor;

signals:
  void eventRequireOpenGLWidget();
};

#endif // MENUMEDIA_H
