#include "TitleBar.h"

TitleBar::TitleBar(QString title, QWidget *parent) : QWidget(parent) {
  m_layout = new QHBoxLayout(this);
  m_layout->setContentsMargins(0, 0, 0, 0);

  m_titleLabel = new QLabel(title, this);
  updateStyles();

  m_layout->addWidget(m_titleLabel);
}

TitleBar::~TitleBar(){};

void TitleBar::updateStyles() {
  m_titleLabel->setStyleSheet(getStylesFromFile(PATH_TITLE_BAR_STYLES_FILE));
}
