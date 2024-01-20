#include "MediaProcessor.h"

MediaProcessor::MediaProcessor(QObject *parent, OpenGLWidget *openGLWidget)
    : QObject(parent), openGLWidget(openGLWidget) {}

void MediaProcessor::captureAndSaveImage() {
  QImage screenshot = openGLWidget->grabFramebuffer();

  // Get save file path
  QString filePath = getSaveFilePath("png");

  // Save screenshot
  screenshot.save(filePath);

  std::cerr << "Image saved at: " << filePath.toStdString() << std::endl;
}

void MediaProcessor::captureAndSaveAnimation() {
  std::thread cast_gif(&OpenGLWidget::screencast, openGLWidget);
  cast_gif.detach();
}

QString MediaProcessor::getSaveFilePath(const QString &fileType) {
  QString executablePath = QCoreApplication::applicationDirPath();

  QString defaultFileName = "output";

  QStringList supportedFormats;
  supportedFormats << "JPEG Image (*.jpg *.jpeg)"
                   << "Bitmap Image (*.bmp)";
  QString selectedFilter;

  QString filePath = QFileDialog::getSaveFileName(
      nullptr, "Save File", executablePath + "/" + defaultFileName,
      supportedFormats.join(";;"), &selectedFilter);

  QString selectedFormat;
  if (selectedFilter.contains("JPEG")) {
    selectedFormat = "jpeg";
  } else if (selectedFilter.contains("Bitmap")) {
    selectedFormat = "bmp";
  } else {
    selectedFormat = fileType;
  }

  QFileInfo fileInfo(filePath);
  filePath = fileInfo.path() + QDir::separator() + fileInfo.completeBaseName() +
             "." + selectedFormat;

  return filePath;
}
