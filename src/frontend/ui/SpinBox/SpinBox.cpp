#include "SpinBox.h"

SpinBox::SpinBox(double initialValue, double multiplier, QWidget *parent)
    : QWidget(parent), m_currentValue(initialValue), m_multiplier(multiplier) {
  m_lineEdit = new SpinBoxLineEdit(m_currentValue, m_multiplier, this);
  m_pushButton = new SpinBoxPushButton(m_currentValue, m_multiplier, this);
  int height{30};
  int width{100};
  m_pushButton->setMinimumWidth(width);
  m_pushButton->setMaximumWidth(width);

  m_lineEdit->setMinimumWidth(width);
  m_lineEdit->setMaximumWidth(width);

  m_lineEdit->setMinimumHeight(height);
  m_lineEdit->setMaximumHeight(height);

  m_pushButton->setMinimumHeight(height);
  m_pushButton->setMaximumHeight(height);

  connect(m_pushButton, &SpinBoxPushButton::eventValueChanged, this,
          &SpinBox::setValue);
  connect(m_lineEdit, &SpinBoxLineEdit::eventValueChanged, this,
          &SpinBox::setValue);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(m_lineEdit);
  layout->addWidget(m_pushButton);

  m_lineEdit->hide();

  connect(m_pushButton, &SpinBoxPushButton::clicked, this,
          &SpinBox::toggleEditing);
  connect(m_lineEdit, &SpinBoxLineEdit::focusOut, this,
          &SpinBox::toggleEditing);
}

double SpinBox::getValue() const { return m_currentValue; }

void SpinBox::toggleEditing() {
  if (m_currentWidget == m_pushButton) {
    m_pushButton->hide();
    m_lineEdit->setValue(m_currentValue);
    m_lineEdit->show();
    m_lineEdit->selectAll();
    m_lineEdit->setFocus();
    m_lineEdit->setFixedSize(m_pushButton->size());
  } else {
    m_lineEdit->hide();
    m_currentValue = m_lineEdit->getValue();
    m_pushButton->setValue(m_currentValue);
    m_pushButton->show();
  }
  if (m_currentWidget == m_pushButton) {
    m_currentWidget = m_lineEdit;
  } else {
    m_currentWidget = m_pushButton;
  }
}

void SpinBox::setValue(double newValue) {
  m_currentValue = newValue;
  emit eventValueChanged(newValue);
}
