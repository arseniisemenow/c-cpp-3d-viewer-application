#include "DockWidgetSettings.h"

DockWidgetSettings::DockWidgetSettings(QWidget *parent)
    : QDockWidget(parent), m_isRightDockButtonChecked(false) {
  m_centralWidget = new QWidget(this);
  this->setWidget(m_centralWidget);

  this->setFeatures(QDockWidget::QDockWidget::NoDockWidgetFeatures);

  setFixedHeight(23);

  m_cameraIconLabel = new QLabel();
  setCameraIconLabel();

  m_projectionTypeComboBox = new QComboBox();
  setProjectionTypeComboBox();

  m_cameraModeComboBox = new QComboBox();
  setCameraModeComboBox();

  m_hideRightDockButton = new QPushButton();
  setHideDockButton();

  m_layout = new QHBoxLayout(m_centralWidget);
  setLayoutForWidget();

  connect(&EventHandler::get(),
          &EventHandler::eventToggledDockWidgetModelEditor, this,
          &DockWidgetSettings::updateDockWidgetModelEditorButtonStatus);

  connect(m_projectionTypeComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::handleProjectionTypeChanged);

  connect(m_cameraModeComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::handleCameraModeChanged);

  connect(&EventHandler::get(), &EventHandler::eventResetSettings, this,
          &DockWidgetSettings::updateDockWidget);

  connect(this, &DockWidgetSettings::eventProjectionTypeChanged,
          &EventHandler::get(), &EventHandler::projectionTypeChanged);
  connect(this, &DockWidgetSettings::eventCameraModeChanged,
          &EventHandler::get(), &EventHandler::cameraModeChanged);

  connect(m_projectionTypeComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::handleProjectionTypeChanged);
  connect(m_cameraModeComboBox,
          QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &DockWidgetSettings::handleCameraModeChanged);

  loadProjectionTypeSettings();
  loadCameraModeSettings();

  emit cameraModeChanged();
  emit projectionTypeChanged();

  updateHideRightDockWidgetButtonStyle();
}

void DockWidgetSettings::updateDockWidget() {
  loadCameraModeSettings();
  loadProjectionTypeSettings();
}

void DockWidgetSettings::updateStyles() {
  this->setStyleSheet(getStylesFromFile(PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE));
  m_centralWidget->setStyleSheet(
      getStylesFromFile(PATH_DOCK_WIDGET_SETTINGS_STYLES_FILE));
}

void DockWidgetSettings::handleProjectionTypeChanged(int index) {
  saveProjectionTypeSettings();

  if (index == ProjectionTypeComboBoxIndex::Parallel) {
    m_cameraModeComboBox->setItemData(CameraModeComboBoxIndex::Fly,
                                      QVariant(Qt::ItemIsEnabled),
                                      Qt::UserRole - 1);
    m_cameraModeComboBox->setCurrentIndex(CameraModeComboBoxIndex::Turnable);
  } else {
    m_cameraModeComboBox->setItemData(
        CameraModeComboBoxIndex::Fly,
        QVariant(Qt::ItemIsEnabled | Qt::ItemIsSelectable), Qt::UserRole - 1);
  }
  emit projectionTypeChanged();
}

void DockWidgetSettings::handleCameraModeChanged(int index) {
  saveCameraModeSettings();
  emit cameraModeChanged();
}

void DockWidgetSettings::updateDockWidgetModelEditorButtonStatus() {
  toggleChecked();
  updateHideRightDockWidgetButtonStyle();
}

void DockWidgetSettings::toggleChecked() {
  m_isRightDockButtonChecked = !m_isRightDockButtonChecked;
}

void DockWidgetSettings::setCameraIconLabel() {
  m_cameraIconLabel->setFixedSize(
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);
  m_cameraIconLabel->setIndent(5);
  m_cameraIconLabel->setObjectName(OBJECT_NAME_CAMERA_ICON_LABEL);
}

void DockWidgetSettings::setProjectionTypeComboBox() {
  m_projectionTypeComboBox->addItem(PROJECTION_TYPE_PERSPECTIVE_STRING);
  m_projectionTypeComboBox->addItem(PROJECTION_TYPE_PARALLEL_STRING);
  m_projectionTypeComboBox->setFixedSize(
      FIXED_WIDTH_COMBOBOX_SETTINGS_DOCKWIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);
}

void DockWidgetSettings::setHideDockButton() {
  m_hideRightDockButton->setFixedSize(
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);

  connect(m_hideRightDockButton, &QPushButton::clicked, &EventHandler::get(),
          &EventHandler::toggleDockWidgetModelEditor);
}

void DockWidgetSettings::setLayoutForWidget() {
  m_layout->addWidget(m_cameraIconLabel);
  m_layout->addWidget(m_projectionTypeComboBox);

  m_layout->addItem(
      new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));

  m_layout->addWidget(m_cameraModeComboBox);
  m_layout->addWidget(m_hideRightDockButton);

  m_layout->setContentsMargins(DOCK_WIDGET_MARGIN_VALUE, 0,
                               DOCK_WIDGET_MARGIN_VALUE, 0);
}

void DockWidgetSettings::updateHideRightDockWidgetButtonStyle() {
  if (m_isRightDockButtonChecked) {
    m_hideRightDockButton->setObjectName(
        OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_CHECKED);
  } else {
    m_hideRightDockButton->setObjectName(
        OBJECT_NAME_HIDE_RIGHT_DOCK_WIDGET_DEFAULT);
  }
  updateStyles();
}

void DockWidgetSettings::setCameraModeComboBox() {
  m_cameraModeComboBox->addItem(CAMERA_MODE_FLY_STRING);
  m_cameraModeComboBox->addItem(CAMERA_MODE_TURNABLE_STRING);
  m_cameraModeComboBox->setFixedSize(
      FIXED_WIDTH_COMBOBOX_SETTINGS_DOCKWIDGET,
      FIXED_HEIGHT_FOR_ELEMENTS_IN_SETTINGS_DOCK_WIDGET);
}

void DockWidgetSettings::saveProjectionTypeSettings() {
  if (m_projectionTypeComboBox->currentIndex() ==
      ProjectionTypeComboBoxIndex::Perspective) {
    Preferences::get().setProjectionType(Projection::Type::Perspective);
  } else if (m_projectionTypeComboBox->currentIndex() ==
             ProjectionTypeComboBoxIndex::Parallel) {
    Preferences::get().setProjectionType(Projection::Type::Parallel);
  }
  Preferences::get().save();
}

void DockWidgetSettings::loadProjectionTypeSettings() {
  if (Preferences::get().getProjectionType() == Projection::Type::Perspective) {
    m_projectionTypeComboBox->setCurrentIndex(
        ProjectionTypeComboBoxIndex::Perspective);
  } else if (Preferences::get().getProjectionType() ==
             Projection::Type::Parallel) {
    m_projectionTypeComboBox->setCurrentIndex(
        ProjectionTypeComboBoxIndex::Parallel);
  }
}

void DockWidgetSettings::saveCameraModeSettings() {
  if (m_cameraModeComboBox->currentIndex() == CameraModeComboBoxIndex::Fly) {
    Preferences::get().setCameraMode(CameraMode::Fly);
  } else if (m_cameraModeComboBox->currentIndex() ==
             CameraModeComboBoxIndex::Turnable) {
    Preferences::get().setCameraMode(CameraMode::Turnable);
  }
  Preferences::get().save();
}

void DockWidgetSettings::loadCameraModeSettings() {
  if (Preferences::get().getCameraMode() == CameraMode::Fly) {
    m_cameraModeComboBox->setCurrentIndex(CameraModeComboBoxIndex::Fly);
  } else if (Preferences::get().getCameraMode() == CameraMode::Turnable) {
    m_cameraModeComboBox->setCurrentIndex(CameraModeComboBoxIndex::Turnable);
  }
}
