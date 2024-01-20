#include "MenuBar.h"

MenuBar::MenuBar([[maybe_unused]] QWidget *parent)
    : m_menuFile{new MenuFile{"File"}}, m_menuMedia{new MenuMedia{"Media"}},
      m_menuHelp{new QMenu{"Help"}} {
  updateStyle();

  m_applicationMenu = addMenu("s21_viewer");

  QAction *actionAbout{new QAction{"About", this}};
  QAction *actionPreferences{new QAction{"Preferences", this}};
  QAction *actionQuit{new QAction{"Quit", this}};

  m_applicationMenu->addAction(actionAbout);
  m_applicationMenu->addAction(actionPreferences);
  m_applicationMenu->addAction(actionQuit);

  m_menuViews = new MenuViews("Views");

  connect(actionPreferences, &QAction::triggered, &EventHandler::get(),
          &EventHandler::openPreferencesWindow);
  connect(actionQuit, &QAction::triggered, &EventHandler::get(),
          &EventHandler::closeMainWindow);
  connect(actionAbout, &QAction::triggered, &EventHandler::get(),
          &EventHandler::openAboutWindow);

  addMenu(m_menuFile);
  addMenu(m_menuViews);
  addMenu(m_menuMedia);
}

void MenuBar::updateStyle() {
  m_menuMedia->setStyleSheet(getStylesFromFile(PATH_MENU_BAR_STYLES_FILE));
  this->setStyleSheet(getStylesFromFile(PATH_MENU_BAR_STYLES_FILE));
}
