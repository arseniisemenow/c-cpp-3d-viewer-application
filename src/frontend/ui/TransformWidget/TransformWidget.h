#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QGridLayout>
#include <QWidget>
#include <array>
#include <iostream>

#include "../SpinBox/SpinBox.h"

class TransformWidget : public QWidget {
  Q_OBJECT
public:
  TransformWidget(QWidget *parent = nullptr);
  void handleSpinBoxValueChanged(int);
  void clearSpinBoxes();

signals:
  void affineTransformationChanged(const std::array<QVector3D, 3> &matrix);

private:
  void setupUI();

  SpinBox *createCustomSpinBox(int, double);

  void addSpinBoxToLayout(QGridLayout *layout, int row, int col);
  SpinBox *m_spinBoxMatrix[3][3] = {0};
};
#endif // TRANSFORMWIDGET_H
