#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QColor>
#include <QDir>
#include <QList>
#include <QMetaType>
#include <QSettings>
#include <QVariant>
#include <iostream>

#include "../RecentFile/RecentFile.h"
#include "../structs.h"

#define S21_COMPANY_NAME "s21"
#define S21_GLOBAL_SETTINGS_NAME "settings"
#define S21_DOCK_WIDGET_SETTINGS_NAME "dock_widget_settings"
#define S21_RECENT_FILES_SETTINGS_NAME "recent_files_settings"

#define DARK_GRAY_HEX_COLOR ("#050505")
#define ORANGE_HEX_COLOR ("#D24D00")
#define SKY_BLUE_HEX_COLOR ("#09c4ce")

#define S21_DEFAULT_BACKGROUND_COLOR DARK_GRAY_HEX_COLOR
#define S21_DEFAULT_VERTEX_COLOR ORANGE_HEX_COLOR
#define S21_DEFAULT_EDGE_COLOR SKY_BLUE_HEX_COLOR

#define S21_DEFAULT_SCALE (50.0)

#define S21_DEFAULT_VERTEX_SIZE (4.0)
#define S21_DEFAULT_EDGE_SIZE (1.0)

#define S21_BIG_NUMBER (1000000)

#define S21_DEFAULT_CAMERA_SPEED_VALUE (1)

#define S21_DEFAULT_NEAR_PLANE_VALUE (1)
#define S21_DEFAULT_FAR_PLANE_VALUE (100000)

#define STRINGIFY(x) #x

class Preferences {
public:
  static Preferences &get() {
    static Preferences instance;
    return instance;
  }

  ~Preferences();

  void saveSceneScale();
  void saveProjectionType();
  void saveBackgroundColor();
  void saveVertexDisplayMethod();
  void saveVertexColor();
  void saveVertexSize();
  void saveEdgeType();
  void saveEdgeColor();
  void saveEdgeSize();
  void saveLastOpenedDir();
  void saveCameraMode();
  void saveCameraSpeed();
  void saveNearPlane();
  void saveFarPlane();

  void loadSceneScale();
  void loadProjectionType();
  void loadBackgroundColor();
  void loadVertexDisplayMethod();
  void loadVertexColor();
  void loadVertexSize();
  void loadEdgeType();
  void loadEdgeColor();
  void loadEdgeSize();
  void loadLastOpenedDir();
  void loadCameraMode();
  void loadCameraSpeed();
  void loadNearPlane();
  void loadFarPlane();

  void load();
  void save();

  double getScale();

  int getProjectionType();

  QColor getBackgroundColor();

  int getVertexDisplayMethod();
  QColor getVertexColor();
  double getVertexSize();

  int getEdgeType();
  QColor getEdgeColor();
  double getEdgeSize();
  CameraMode getCameraMode();
  int getCameraSpeed();
  int getNearPlane();
  int getFarPlane();

  int setScale(double);
  int setProjectionType(Projection::Type);

  int setBackgroundColor(QColor);

  int setVertexDisplayMethod(Vertex::DisplayMethod);
  int setVertexColor(QColor);
  int setVertexSize(double);

  int setEdgeType(Edge::Type);
  int setEdgeColor(QColor);
  int setEdgeSize(double);

  int setCameraMode(CameraMode cameraMode);
  int setCameraSpeed(int newCameraSpeed);
  int setNearPlane(int newNearPlane);
  int setFarPlane(int newFarPlane);

  void addRecentFile(QString name, QString path);
  void clearRecentFiles();
  QVector<RecentFile> getRecentFiles();

  QSettings *m_settings;
  QSettings *m_dockWidgetSettings;
  QSettings *m_recentFilesSettings;

private:
  Preferences() {
    m_settings = new QSettings(S21_COMPANY_NAME, S21_GLOBAL_SETTINGS_NAME);
    m_dockWidgetSettings =
        new QSettings(S21_COMPANY_NAME, S21_DOCK_WIDGET_SETTINGS_NAME);
    m_recentFilesSettings =
        new QSettings(S21_COMPANY_NAME, S21_RECENT_FILES_SETTINGS_NAME);
  };

  /*
   * Object parameters
   */
  double m_sceneScale = S21_DEFAULT_SCALE;
  /*
   * Viewer parameters
   */

  int m_projectionType = Projection::Type::Perspective;

  QColor m_backgroundColor = S21_DEFAULT_BACKGROUND_COLOR;

  int m_vertexDisplayMethod = Vertex::DisplayMethod::Circle;
  QColor m_vertexColor = S21_DEFAULT_VERTEX_COLOR;
  double m_vertexSize = S21_DEFAULT_VERTEX_SIZE;

  int m_edgeType = Edge::Type::Solid;
  QColor m_edgeColor = S21_DEFAULT_EDGE_COLOR;
  double m_edgeSize = S21_DEFAULT_EDGE_SIZE;

  CameraMode m_cameraMode = CameraMode::Fly;
  int m_cameraSpeed = S21_DEFAULT_CAMERA_SPEED_VALUE;

  int m_nearPlane = S21_DEFAULT_NEAR_PLANE_VALUE;
  int m_farPlane = S21_DEFAULT_FAR_PLANE_VALUE;

  /*
   * Current Object information
   */

  QString m_fileDir{};
  int m_vertexCount{};
  int m_edgeCount{};

  /*
   * Recent files
   */
  int m_recentFilesCount{0};
  QVector<RecentFile> m_recentFiles{};

  QString m_lastOpenedDir{};
};

#endif // PREFERENCES_H
