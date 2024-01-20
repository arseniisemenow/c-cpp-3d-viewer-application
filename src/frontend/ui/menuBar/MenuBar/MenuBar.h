#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include <memory>

#include "../../structs.h"
#include "../../styles/styles.h"
#include "../MenuFile/MenuFile.h"
#include "../MenuMedia/MenuMedia.h"
#include "../MenuViews/MenuViews.h"

class MenuBar : public QMenuBar {
  Q_OBJECT
public:
  MenuBar(QWidget *parent = nullptr);

  void openPreferencesWindow();
  void closeWindow();
  void openAboutWindow();

signals:
  void eventOpenPreferencesWindow();
  void eventCloseWindow();
  void eventOpenAboutWindow();

private:
  void updateStyle();

  QMenu *m_applicationMenu;
  MenuFile *m_menuFile;
  MenuViews *m_menuViews;
  QMenu *m_menuMedia;
  QMenu *m_menuHelp;
};

#endif // MENUBAR_H
