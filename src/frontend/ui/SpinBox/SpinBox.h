#include <QFocusEvent>
#include <QIntValidator>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "SpinBoxLineEdit.h"
#include "SpinBoxPushButton.h"

class SpinBox : public QWidget {
  Q_OBJECT

public:
  SpinBox(double initialValue = 0, double multiplier = 1,
          QWidget *parent = nullptr);

  double getValue() const;
  void setValue(double newValue);
  SpinBoxLineEdit *getLineEdit() { return m_lineEdit; }
  SpinBoxPushButton *getPushButton() { return m_pushButton; }

public slots:
  void toggleEditing();

signals:
  void eventValueChanged(double newValue);

private:
  SpinBoxLineEdit *m_lineEdit;
  SpinBoxPushButton *m_pushButton;
  QWidget *m_currentWidget;
  double m_currentValue;
  double m_multiplier;
};
