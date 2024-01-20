#ifndef SPINBOXLINEEDIT_H
#define SPINBOXLINEEDIT_H

#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QValidator>
#include <QWidget>
#include <iostream>

#include "../EventHandler/EventHandler.h"

class SpinBoxLineEdit : public QLineEdit {
  Q_OBJECT

public:
  SpinBoxLineEdit(double &initValue, double multiplier,
                  QWidget *parent = nullptr);

  void handleClickInWidget(const QPoint &clickPos);

  double getValue() const { return m_currentValue; }

  void setValue(double newValue);

public slots:

  void updateCurrentValue(const QString &text);

signals:
  void eventValueChanged(double);
  void focusOut();

protected:
  void mousePressEvent(QMouseEvent *event) override;

  bool isClickInsideTextRect(const QPoint &clickPos) const;
  void focusOutEvent(QFocusEvent *event) override;

  void keyPressEvent(QKeyEvent *event) override;

signals:
  void eventEditingFinished(double value);

private:
  double &m_currentValue;
  bool m_isEditable;
  double m_multiplier;
};
#endif // SPINBOXLINEEDIT_H
