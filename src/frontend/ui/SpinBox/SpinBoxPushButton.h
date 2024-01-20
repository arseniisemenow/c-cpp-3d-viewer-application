#ifndef SPINBOXPUSHBUTTON_H
#define SPINBOXPUSHBUTTON_H

#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#define DELTA_VALUE (1)

class SpinBoxPushButton : public QPushButton {
  Q_OBJECT

public:
  SpinBoxPushButton(double &initValue, double multiplier,
                    QWidget *parent = nullptr);

  double getValue();

  void setValue(double newValue);

protected:
  void mousePressEvent(QMouseEvent *event) override;

  void mouseReleaseEvent(QMouseEvent *event) override;

  void mouseMoveEvent(QMouseEvent *event) override;

#ifdef Q_OS_MACOS

  void enterEvent(QEnterEvent *event) override;

#elif defined(Q_OS_LINUX)

  void enterEvent(QEvent *event) override;

#endif // Q_OS_MACOS

  void leaveEvent(QEvent *event) override;

signals:
  void eventValueChanged(double);

private:
  void setupUI();
  double singleStep() const;
  void updateButtonText();

  bool m_isMousePressed = false;
  QPoint m_lastMousePos;
  double &m_currentValue;
  double m_multiplier;
  double m_stepSize;
};

#endif // SPINBOXPUSHBUTTON_H
