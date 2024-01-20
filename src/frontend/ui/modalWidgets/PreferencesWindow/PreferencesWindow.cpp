#include "PreferencesWindow.h"

PreferencesWindow::PreferencesWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::PreferencesWindow) {
  ui->setupUi(this);

  lockMainWindowInteraction();

  setButtonsConnections();

  loadSettings();
  updateStyles();
}

PreferencesWindow::~PreferencesWindow() { delete ui; }
void PreferencesWindow::updateStyles() {
  this->setStyleSheet(getStylesFromFile(PATH_PREFERENCES_WINDOW_STYLES_FILE));
}

void PreferencesWindow::setButtonsConnections() {
  connect(ui->pushButton_apply, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::applySettings);
  connect(&EventHandler::get(), &EventHandler::eventApplySettings, this,
          &PreferencesWindow::handleApplyButtonClick);

  connect(ui->pushButton_cancel, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::cancelSettings);
  connect(&EventHandler::get(), &EventHandler::eventCancelSettings, this,
          &PreferencesWindow::handleCancelButtonClick);

  connect(ui->pushButton_ok, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::okSettings);
  connect(&EventHandler::get(), &EventHandler::eventOkSettings, this,
          &PreferencesWindow::handleOkButtonClick);

  connect(ui->pushButton_resetSettings, &QPushButton::clicked,
          &EventHandler::get(), &EventHandler::resetSettings);
  connect(&EventHandler::get(), &EventHandler::eventResetSettings, this,
          &PreferencesWindow::handleResetSettingsButtonClick);

  connect(this, &PreferencesWindow::eventOpenPreferencesWindow,
          &EventHandler::get(), &EventHandler::eventOpenPreferencesWindow);
}

void PreferencesWindow::lockMainWindowInteraction() { setModal(true); }

void PreferencesWindow::loadVertexDisplayMethodSettings() {
  if (Preferences::get().getVertexDisplayMethod() ==
      Vertex::DisplayMethod::None) {
    ui->comboBox_vertexDisplayMethod->setCurrentIndex(
        VertexDisplayMethodComboBoxIndex::None);
  } else if (Preferences::get().getVertexDisplayMethod() ==
             Vertex::DisplayMethod::Circle) {
    ui->comboBox_vertexDisplayMethod->setCurrentIndex(
        VertexDisplayMethodComboBoxIndex::Circle);
  } else if (Preferences::get().getVertexDisplayMethod() ==
             Vertex::DisplayMethod::Square) {
    ui->comboBox_vertexDisplayMethod->setCurrentIndex(
        VertexDisplayMethodComboBoxIndex::Square);
  }
}
void PreferencesWindow::loadEdgeTypeSettings() {
  if (Preferences::get().getEdgeType() == Edge::Type::Solid) {
    ui->comboBox_edgeType->setCurrentIndex(EdgeTypeComboBoxIndex::Solid);
  } else if (Preferences::get().getEdgeType() == Edge::Type::Dashed) {
    ui->comboBox_edgeType->setCurrentIndex(EdgeTypeComboBoxIndex::Dashed);
  }
}
void PreferencesWindow::loadVertexSize() {
  int vertexSize = Preferences::get().getVertexSize();
  ui->spinBox_vertexSize->setValue(vertexSize);
}
void PreferencesWindow::loadEdgeSize() {
  int edgeSize = Preferences::get().getEdgeSize();
  ui->spinBox_edgeSize->setValue(edgeSize);
}
void PreferencesWindow::loadCameraSpeed() {
  int cameraSpeed = Preferences::get().getCameraSpeed();
  ui->spinBox_cameraSpeed->setValue(cameraSpeed);
}
void PreferencesWindow::loadNearPlane() {
  int nearPlane = Preferences::get().getNearPlane();
  ui->spinBox_nearPlane->setValue(nearPlane);
}
void PreferencesWindow::loadFarPlane() {
  int farPlane = Preferences::get().getFarPlane();
  ui->spinBox_farPlane->setValue(farPlane);
}

void PreferencesWindow::saveVertexDisplayMethod() {
  if (ui->comboBox_vertexDisplayMethod->currentIndex() ==
      VertexDisplayMethodComboBoxIndex::None) {
    Preferences::get().setVertexDisplayMethod(Vertex::DisplayMethod::None);
  } else if (ui->comboBox_vertexDisplayMethod->currentIndex() ==
             VertexDisplayMethodComboBoxIndex::Circle) {
    Preferences::get().setVertexDisplayMethod(Vertex::DisplayMethod::Circle);
  } else if (ui->comboBox_vertexDisplayMethod->currentIndex() ==
             VertexDisplayMethodComboBoxIndex::Square) {
    Preferences::get().setVertexDisplayMethod(Vertex::DisplayMethod::Square);
  }
}

void PreferencesWindow::saveEdgeType() {
  if (ui->comboBox_edgeType->currentIndex() == EdgeTypeComboBoxIndex::Solid) {
    Preferences::get().setEdgeType(Edge::Type::Solid);
  } else if (ui->comboBox_edgeType->currentIndex() ==
             EdgeTypeComboBoxIndex::Dashed) {
    Preferences::get().setEdgeType(Edge::Type::Dashed);
  }
}

void PreferencesWindow::saveBackgroundColor() {
  QColor color = ui->colorPushButton_backgroundColor->getColor();
  Preferences::get().setBackgroundColor(color);
}
void PreferencesWindow::loadBackgroundColor() {
  QColor color = Preferences::get().getBackgroundColor();
  ui->colorPushButton_backgroundColor->updateData(color);
}
void PreferencesWindow::saveVertexColor() {
  QColor color = ui->colorPushButton_vertexColor->getColor();
  Preferences::get().setVertexColor(color);
}
void PreferencesWindow::saveCameraSpeed() {
  int cameraSpeed = ui->spinBox_cameraSpeed->value();
  Preferences::get().setCameraSpeed(cameraSpeed);
}

void PreferencesWindow::saveNearPlane() {
  int nearPlane = ui->spinBox_nearPlane->value();
  Preferences::get().setNearPlane(nearPlane);
}

void PreferencesWindow::saveFarPlane() {
  int farPlane = ui->spinBox_farPlane->value();
  Preferences::get().setFarPlane(farPlane);
}

void PreferencesWindow::loadVertexColor() {
  QColor color = Preferences::get().getVertexColor();
  ui->colorPushButton_vertexColor->updateData(color);
}
void PreferencesWindow::saveEdgeColor() {
  QColor color = ui->colorPushButton_edgeColor->getColor();
  Preferences::get().setEdgeColor(color);
}
void PreferencesWindow::loadEdgeColor() {
  QColor color = Preferences::get().getEdgeColor();
  ui->colorPushButton_edgeColor->updateData(color);
}

void PreferencesWindow::saveVertexSize() {
  Preferences::get().setVertexSize(ui->spinBox_vertexSize->value());
}

void PreferencesWindow::saveEdgeSize() {
  Preferences::get().setEdgeSize(ui->spinBox_edgeSize->value());
}

void PreferencesWindow::loadSettings() {
  loadBackgroundColor();
  loadCameraSpeed();
  loadNearPlane();
  loadFarPlane();

  loadVertexSize();
  loadVertexDisplayMethodSettings();
  loadVertexColor();

  loadEdgeSize();
  loadEdgeTypeSettings();
  loadEdgeColor();
}

void PreferencesWindow::saveSettings() {
  saveBackgroundColor();
  saveCameraSpeed();
  saveNearPlane();
  saveFarPlane();

  saveVertexSize();
  saveVertexDisplayMethod();
  saveVertexColor();

  saveEdgeSize();
  saveEdgeType();
  saveEdgeColor();

  Preferences::get().save();
}

void PreferencesWindow::handleApplyButtonClick() { saveSettings(); }

void PreferencesWindow::handleCancelButtonClick() { closeWindow(); }
void PreferencesWindow::handleOkButtonClick() {
  saveSettings();
  closeWindow();
}

void PreferencesWindow::handleResetSettingsButtonClick() {
  QMessageBox::StandardButton reply = QMessageBox::question(
      this, "Reset settings", "Are you sure you want to reset all settings?",
      QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

  if (reply == QMessageBox::Yes) {
    Preferences::get().m_settings->clear();
    Preferences::get().load();

    openPreferencesWindow();
    saveSettings();
  }
}

void PreferencesWindow::closeWindow() { close(); }
