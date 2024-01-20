#ifndef COLORPUSHBUTTON_H
#define COLORPUSHBUTTON_H

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QWidget>

class ColorPushButton : public QPushButton {
  Q_OBJECT

public:
  ColorPushButton(QWidget *parent = nullptr);
  void updateButtonTitle(const QString &colorString);
  void updateData(const QColor &color);
  QColor getColor();
  void changeColor();

protected:
  void paintEvent(QPaintEvent *event) override;

private:
  QString m_hexColorCode;
  QColor m_color;
};

#endif // COLORPUSHBUTTON_H
