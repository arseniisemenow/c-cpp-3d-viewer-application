#include "EventHandler.h"

void EventHandler::openPreferencesWindow() {
  emit eventOpenPreferencesWindow();
}

void EventHandler::closePreferencesWindow() {
  emit eventClosePreferencesWindow();
}

void EventHandler::openAboutWindow() { emit eventOpenAboutWindow(); }

void EventHandler::closeAboutWindow() { emit eventCloseAboutWindow(); }

void EventHandler::closeMainWindow() { emit eventCloseMainWindow(); }

void EventHandler::recentFilesChanged() { emit eventRecentFilesChanged(); }

void EventHandler::updateFileMenu() { emit eventUpdateFileMenu(); }

void EventHandler::openFileDialog() { emit eventOpenFileDialog(); }

void EventHandler::closeFile() { emit eventCloseFile(); }

void EventHandler::applySettings() { emit eventApplySettings(); }

void EventHandler::cancelSettings() { emit eventCancelSettings(); }

void EventHandler::okSettings() { emit eventOkSettings(); }

void EventHandler::resetSettings() { emit eventResetSettings(); }

void EventHandler::fileDialogCloseWindow() {
  emit eventFileDialogCloseWindow();
}

void EventHandler::fileDialogUpdateSelectedPath(const QModelIndex &index) {
  emit eventFileDialogUpdateSelectedPath(index);
}
