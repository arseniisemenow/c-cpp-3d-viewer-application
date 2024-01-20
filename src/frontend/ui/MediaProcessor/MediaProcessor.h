#ifndef MEDIAPROCESSOR_H
#define MEDIAPROCESSOR_H

#include <QBuffer>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QImageWriter>
// #include <QMediaRecorder>
#include <QMessageBox>
#include <QObject>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QProcess>
#include <QScreen>
#include <QThread>
#include <iostream>

#include "../../opengl/OpenGLWidget/OpenGLWidget.h"
#include "QImageWriter"
#include "QMovie"

class MediaProcessor : public QObject {
  Q_OBJECT

public:
  explicit MediaProcessor(QObject *parent = nullptr,
                          OpenGLWidget *openGLWidget = nullptr);

public slots:
  void captureAndSaveImage();
  void captureAndSaveAnimation();

private:
  QString getSaveFilePath(const QString &fileType);
  OpenGLWidget *openGLWidget;
};

#endif // MEDIAPROCESSOR_H
