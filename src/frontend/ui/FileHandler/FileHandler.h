#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QObject>
#include <iostream>
#include <string>

#include "backend/mesh_data.h"
#include "backend/parser/parser.h"
#include "frontend/ui/EventHandler/EventHandler.h"

class FileHandler : public QObject {
  Q_OBJECT
public:
  static FileHandler &get() {
    static FileHandler instance;
    return instance;
  }

  ~FileHandler(){};

  void open(const QString &fileName) {
    const std::string stdString{fileName.toStdString()};
    const char *cString{stdString.data()};

    MeshData loadedData{};
    ModelLoadingError error = parseObjFile(cString, &loadedData);
    if (error == noModelLoadingError) {
      emit fileLoaded(loadedData, fileName);
    }
  };
  void close() { emit fileClosed(); };

signals:
  void fileLoaded(const MeshData &data, const QString &fileName);
  void fileClosed();

private:
  FileHandler() {
    connect(&EventHandler::get(), &EventHandler::eventOpenFile, this,
            &FileHandler::open);
    connect(&EventHandler::get(), &EventHandler::eventRecentFileActionClicked,
            this, &FileHandler::open);
    connect(&EventHandler::get(), &EventHandler::eventCloseFile, this,
            &FileHandler::close);
  };
};

#endif // FILEHANDLER_H
