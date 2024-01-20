#include "ColorPushButton.h"

ColorPushButton::ColorPushButton(QWidget *parent) : QPushButton(parent) {
  connect(this, &ColorPushButton::clicked, this, &ColorPushButton::changeColor);
}

void ColorPushButton::updateButtonTitle(const QString &colorString) {
  setText(m_hexColorCode);
  update();
}

void ColorPushButton::updateData(const QColor &color) {
  m_hexColorCode = color.name(QColor::HexRgb).toUpper();
  m_color = color;
  updateButtonTitle(m_hexColorCode);
}

void ColorPushButton::paintEvent(QPaintEvent *event) {
  QPushButton::paintEvent(event);
  QRect rect = this->rect();

  int roundedSquareSize = rect.height() - (rect.height() / 2);
  int x = rect.right() - roundedSquareSize - (rect.height() / 4);
  int y = rect.top() + (rect.height() / 4);

  QRect roundedRect{x, y, roundedSquareSize, roundedSquareSize};

  QPainter painter(this);
  QColor borderColor(100, 100, 100);

  painter.setPen(QPen(borderColor, 0));
  painter.setBrush(QColor(m_hexColorCode));
  painter.drawRoundedRect(roundedRect, roundedSquareSize, roundedSquareSize);
}

void ColorPushButton::changeColor() {
  QColorDialog dialog(QColor(m_hexColorCode), this);
  dialog.setOption(QColorDialog::ShowAlphaChannel);
  if (dialog.exec()) {
    updateData(dialog.currentColor());
  }
}

QColor ColorPushButton::getColor() { return m_color; }
