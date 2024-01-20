#include "TransformWidget.h"

#include <QVector3D>

#include "QtWidgets/qlabel.h"

TransformWidget::TransformWidget(QWidget *parent) : QWidget(parent) {
  setupUI();
  connect(this, &TransformWidget::affineTransformationChanged,
          &EventHandler::get(),
          &EventHandler::eventAffineTransformationChanged);

  connect(&EventHandler::get(), &EventHandler::eventLoadAnotherModel,
          &EventHandler::get(), &EventHandler::clearSpinBoxes);
}

void TransformWidget::setupUI() {
  QGridLayout *gridLayout = new QGridLayout(this);

  QStringList rowLabels = {"Position", "Rotation", "Scale"};
  QStringList colLabels = {"X", "Y", "Z"};

  for (int col = 0; col < 3; ++col) {
    QLabel *colLabel = new QLabel(colLabels[col]);
    colLabel->setAlignment(Qt::AlignCenter);
    gridLayout->addWidget(colLabel, 0, col + 1);
  }

  for (int row = 0; row < 3; ++row) {
    QLabel *rowLabel = new QLabel(rowLabels[row]);
    gridLayout->addWidget(rowLabel, row + 1, 0);

    for (int col = 0; col < 3; ++col) {
      addSpinBoxToLayout(gridLayout, row, col);
    }
  }
  setMaximumHeight(300);

  QPushButton *clearButton = new QPushButton("Clear");
  connect(clearButton, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::clearSpinBoxes);
  connect(&EventHandler::get(), &EventHandler::eventClearSpinBoxes, this,
          &TransformWidget::clearSpinBoxes);

  gridLayout->addWidget(clearButton, 4, 0, 1, 4, Qt::AlignCenter);
}

SpinBox *TransformWidget::createCustomSpinBox(int defaultValue,
                                              double multiplier) {
  SpinBox *spinBox = new SpinBox(defaultValue, multiplier, this);
  return spinBox;
}

void TransformWidget::addSpinBoxToLayout(QGridLayout *layout, int row,
                                         int col) {
  int defaultValue = 0;
  double multiplier = 1;
  if (row > 1) {
    defaultValue = 1;
    multiplier = 0.05;
  }
  m_spinBoxMatrix[row][col] = createCustomSpinBox(defaultValue, multiplier);
  connect(m_spinBoxMatrix[row][col], &SpinBox::eventValueChanged, this,
          &TransformWidget::handleSpinBoxValueChanged);

  layout->addWidget(m_spinBoxMatrix[row][col], row + 1, col + 1);
}

void TransformWidget::handleSpinBoxValueChanged(int someValue) {
  std::array<QVector3D, 3> matrix{};
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      matrix[i][j] = m_spinBoxMatrix[i][j]->getValue();
    }
  }
  emit affineTransformationChanged(matrix);
}

void TransformWidget::clearSpinBoxes() {
  for (int row = 0; row < 2; ++row) {
    for (int col = 0; col < 3; ++col) {
      m_spinBoxMatrix[row][col]->setValue(0);
      m_spinBoxMatrix[row][col]->getLineEdit()->setValue(0);
      m_spinBoxMatrix[row][col]->getPushButton()->setValue(0);
    }
  }

  for (int row = 2; row < 3; ++row) {
    for (int col = 0; col < 3; ++col) {
      m_spinBoxMatrix[row][col]->setValue(1);
      m_spinBoxMatrix[row][col]->getLineEdit()->setValue(1);
      m_spinBoxMatrix[row][col]->getPushButton()->setValue(1);
    }
  }
}
