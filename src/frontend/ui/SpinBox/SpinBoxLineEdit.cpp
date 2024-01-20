#include "SpinBoxLineEdit.h"

SpinBoxLineEdit::SpinBoxLineEdit(double &initValue, double multiplier,
                                 QWidget *parent)
    : QLineEdit(parent), m_currentValue(initValue), m_isEditable(true),
      m_multiplier(multiplier) {
  bool isFract = ((int)(multiplier * 10)) % 10 > 0;
  if (isFract) {
    setValidator(new QDoubleValidator(this));
  } else {
    setValidator(new QIntValidator(this));
  }

  setAlignment(Qt::AlignCenter);
  //          setValidator(new QDoubleValidator(this));
  //        setReadOnly(true);

  connect(this, &SpinBoxLineEdit::textChanged, this,
          &SpinBoxLineEdit::updateCurrentValue);
  connect(&EventHandler::get(), &EventHandler::eventLeftMouseButtonReleased,
          this, &SpinBoxLineEdit::handleClickInWidget);
  connect(&EventHandler::get(), &EventHandler::eventLeftMouseButtonPressed,
          this, &SpinBoxLineEdit::handleClickInWidget);

  setMouseTracking(true);
}

void SpinBoxLineEdit::handleClickInWidget(const QPoint &clickPos) {
  if (!isClickInsideTextRect(clickPos) && this->hasFocus()) {
    emit focusOut();
    clearFocus(); // FIXME May need
  }
}

void SpinBoxLineEdit::setValue(double newValue) {
  m_currentValue = newValue;
  setText(QString::number(newValue));
}

void SpinBoxLineEdit::updateCurrentValue(const QString &text) {
  m_currentValue = text.toDouble();

  emit eventValueChanged(m_currentValue);
}

void SpinBoxLineEdit::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_isEditable = true;
    setReadOnly(false);
    setFocus();
    selectAll();
  }

  QLineEdit::mousePressEvent(event);
}

bool SpinBoxLineEdit::isClickInsideTextRect(const QPoint &clickPos) const {
  QRect textRect = QRect(2, 2, width() - 4, height() - 4);
  return textRect.contains(clickPos);
}

void SpinBoxLineEdit::focusOutEvent(QFocusEvent *event) {
  emit focusOut();
  QLineEdit::focusOutEvent(event);
}

void SpinBoxLineEdit::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ||
      event->key() == Qt::Key_Escape) {
    emit focusOut();
  } else {
    QLineEdit::keyPressEvent(event);
  }
}
