#include "styles.h"

#include <QDebug>

QString readStylesFromFile(QString fileName) {
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    std::cerr << "Failed to open styles file: " << fileName.toStdString()
              << std::endl;
    return "";
  }

  QTextStream inputStreamGlobal(&file);
  QString stylesString = inputStreamGlobal.readAll();

  file.close();
  return stylesString;
}

void applyGlobalVariables(QString &string) {
  QVector<QString> variableNames = {
      "@purple", "@purpleAlpha", "@gray0",  "@gray1", "@gray2",
      "@gray3",  "@gray4",       "@gray5",  "@gray6", "@gray7",
      "@gray8",  "@gray9",       "@gray10", "@gray11"};
  QVector<QString> replacements = {
      styles::colorPurple, styles::colorPurpleAlpha, styles::colorGray0,
      styles::colorGray1,  styles::colorGray2,       styles::colorGray3,
      styles::colorGray4,  styles::colorGray5,       styles::colorGray6,
      styles::colorGray7,  styles::colorGray8,       styles::colorGray9,
      styles::colorGray10, styles::colorGray11};

  for (int i = 0; i < variableNames.size(); ++i) {
    for (int j = i + 1; j < variableNames.size(); ++j) {
      if (variableNames[i].length() < variableNames[j].length()) {
        qSwap(variableNames[i], variableNames[j]);
        qSwap(replacements[i], replacements[j]);
      }
    }
  }

  // Perform replacements in the original string
  for (int i = 0; i < variableNames.size(); ++i) {
    string.replace(variableNames[i], replacements[i]);
  }
}

QString getStylesFromFile(QString fileName) {
  QString stylesString = readStylesFromFile(fileName);

  applyGlobalVariables(stylesString);

  return stylesString;
}
