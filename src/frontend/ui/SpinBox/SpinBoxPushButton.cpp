#include "SpinBoxPushButton.h"

SpinBoxPushButton::SpinBoxPushButton(double &initValue, double multiplier,
                                     QWidget *parent)
    : m_currentValue(initValue), m_multiplier(multiplier) {
  setMinimumWidth(100);
  setMaximumWidth(200);
  setupUI();
}

double SpinBoxPushButton::getValue() { return m_currentValue; }

void SpinBoxPushButton::setValue(double newValue) {
  m_currentValue = newValue;

  m_stepSize = (m_multiplier == m_multiplier) ? m_multiplier : DELTA_VALUE;

  updateButtonText();
  emit eventValueChanged(m_currentValue);
}

void SpinBoxPushButton::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    m_isMousePressed = true;
    m_lastMousePos = event->pos();
  }

  QPushButton::mousePressEvent(event);
}

void SpinBoxPushButton::mouseReleaseEvent(QMouseEvent *event) {
  m_isMousePressed = false;
  QPushButton::mouseReleaseEvent(event);
}

void SpinBoxPushButton::mouseMoveEvent(QMouseEvent *event) {
  if (m_isMousePressed) {
    double deltaX = event->pos().x() - m_lastMousePos.x();
    double deltaValue = deltaX / singleStep();
    double newValue = m_currentValue + deltaValue;
    setValue(newValue);
    m_lastMousePos = event->pos();
  }

  QPushButton::mouseMoveEvent(event);
}
#ifdef Q_OS_MACOS
void SpinBoxPushButton::enterEvent(QEnterEvent *event) {
  setCursor(Qt::SizeHorCursor);
  QPushButton::enterEvent(event);
}
#elif defined(Q_OS_LINUX)
void SpinBoxPushButton::enterEvent(QEvent *event) {
  setCursor(Qt::SizeHorCursor);
  QPushButton::enterEvent(event);
}
#endif // Q_OS_MACOS
void SpinBoxPushButton::leaveEvent(QEvent *event) {
  unsetCursor();
  QPushButton::leaveEvent(event);
}

void SpinBoxPushButton::setupUI() {
  setFocusPolicy(Qt::NoFocus);

  setText(QString::number(m_currentValue));
}

double SpinBoxPushButton::singleStep() const {
  return DELTA_VALUE / m_stepSize;
}

void SpinBoxPushButton::updateButtonText() {
  setText(QString::number(m_currentValue));
}
