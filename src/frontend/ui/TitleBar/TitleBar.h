#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QWidget>

#include "../styles/styles.h"

class TitleBar : public QWidget {
  Q_OBJECT
public:
  TitleBar(QString title = "Default title name", QWidget *parent = nullptr);
  ~TitleBar();

private:
  void updateStyles();

  QHBoxLayout *m_layout;
  QLabel *m_titleLabel;
  QWidget *m_parent;
  QString m_title;
};

#endif // TITLEBAR_H
