#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QObject>
#include <QProgressBar>
#include <QStatusBar>

#define DEFAULT_PROGRESS_BAR_HEIGHT (15)

class StatusBar : public QStatusBar {
  Q_OBJECT
public:
  StatusBar() {
    m_vertexLabel = new QLabel("");
    m_polygonsLabel = new QLabel("");

    m_progressBarLabel = new QLabel("");
    m_progressBar = new QProgressBar();
    setFixedHeight(DEFAULT_PROGRESS_BAR_HEIGHT);

    setStyleSheet("QStatusBar{"
                  "border: 0px;"
                  "background-color: rgb(55, 55, 55);"
                  "}");

    //        addWidget(vertexLabel);
    //        addWidget(polygonsLabel);
    //        addWidget(progressBarLabel);
    //        addWidget(progressBar);
  }

  void setVertexCount(int count) {
    m_vertexLabel->setText("Vertices: " + QString::number(count));
  }
  void setPolygonsCount(int count) {
    m_polygonsLabel->setText("Polygons: " + QString::number(count));
  }
  void setProgress(int value) { m_progressBar->setValue(value); }
  void setProgressBarTitle(const QString &title) {
    m_progressBarLabel->setText(title);
  }

private:
  QLabel *m_vertexLabel;
  QLabel *m_polygonsLabel;
  QLabel *m_progressBarLabel;
  QProgressBar *m_progressBar;
};

#endif // STATUSBAR_H
