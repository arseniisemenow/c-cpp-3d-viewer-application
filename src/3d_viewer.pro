QT += core gui
QT += opengl
# QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++17


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    frontend/ui/modalWidgets/FileInformationWindow/FileInformationWindow.cpp \
    gif_library/gif.cpp \
    backend/constants.c \
    frontend/opengl/Camera.cpp \
    frontend/opengl/Mesh.cpp \
    frontend/opengl/Renderer.cpp \
    frontend/ui/ColorPushButton/ColorPushButton.cpp \
    frontend/ui/MediaProcessor/MediaProcessor.cpp \
    frontend/ui/SpinBox/SpinBox.cpp \
    frontend/ui/SpinBox/SpinBoxLineEdit.cpp \
    frontend/ui/SpinBox/SpinBoxPushButton.cpp \
    frontend/ui/TitleBar/TitleBar.cpp \
    frontend/ui/TransformWidget/TransformWidget.cpp \
    frontend/ui/dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.cpp \
    frontend/ui/dockWidgets/DockWidgetSettings/DockWidgetSettings.cpp \
    frontend/ui/EventHandler/EventHandler.cpp \
    frontend/ui/StatusBar/StatusBar.cpp \
    frontend/ui/menuBar/MenuFile/MenuFile.cpp \
    frontend/ui/menuBar/MenuMedia/MenuMedia.cpp \
    frontend/ui/Preferences/Preferences.cpp \
    backend/affine_transformations.c \
    backend/arrays.c \
    frontend/ui/styles/styles.cpp \
    main.cpp \
    frontend/ui/MainWindow/MainWindow.cpp \
    frontend/ui/menuBar/MenuBar/MenuBar.cpp \
    frontend/ui/menuBar/MenuViews/MenuViews.cpp \
    frontend/ui/modalWidgets/AboutWindow/AboutWindow.cpp \
    frontend/ui/modalWidgets/FileDialog/FileDialog.cpp \
    frontend/ui/modalWidgets/PreferencesWindow/PreferencesWindow.cpp \
    frontend/opengl/OpenGLWidget/OpenGLWidget.cpp \
    backend/parser/parser.c \
    frontend/ui/userInteractionWidgets/ModelEditor.cpp \
    frontend/ui/userInteractionWidgets/ModelViewer.cpp

HEADERS += \
    frontend/ui/modalWidgets/FileInformationWindow/FileInformationWindow.h \
    gif_library/gif.hpp \
    backend/constants.h \
    backend/error_enums.h \
    backend/mesh_data.h \
    frontend/opengl/Camera.h \
    frontend/opengl/Mesh.h \
    frontend/opengl/OpenGLWidget/Transform.h \
    frontend/opengl/Renderer.h \
    frontend/ui/ColorPushButton/ColorPushButton.h \
    frontend/opengl/Constants.h \
    frontend/ui/MediaProcessor/MediaProcessor.h \
    frontend/ui/SpinBox/SpinBox.h \
    frontend/ui/SpinBox/SpinBoxLineEdit.h \
    frontend/ui/SpinBox/SpinBoxPushButton.h \
    frontend/ui/TitleBar/TitleBar.h \
    frontend/ui/TransformWidget/TransformWidget.h \
    frontend/ui/dockWidgets/DockWidgetModelEditor/DockWidgetModelEditor.h \
    frontend/ui/dockWidgets/DockWidgetSettings/DockWidgetSettings.h \
    frontend/ui/EventHandler/EventHandler.h \
    frontend/ui/FileHandler/FileHandler.h \
    frontend/ui/StatusBar/StatusBar.h \
    frontend/ui/menuBar/MenuFile/MenuFile.h \
    frontend/ui/menuBar/MenuMedia/MenuMedia.h \
    frontend/ui/Preferences/Preferences.h \
    frontend/ui/MainWindow/MainWindow.h \
    frontend/ui/menuBar/MenuViews/MenuViews.h \
    backend/parser/parser.h \
    backend/affine_transformations.h \
    backend/arrays.h \
    frontend/ui/menuBar/MenuBar/MenuBar.h \
    frontend/ui/RecentFile/RecentFile.h \
    frontend/ui/modalWidgets/AboutWindow/AboutWindow.h \
    frontend/ui/modalWidgets/FileDialog/FileDialog.h \
    frontend/ui/modalWidgets/PreferencesWindow/PreferencesWindow.h \
    frontend/opengl/OpenGLWidget/OpenGLWidget.h \
    backend/parser/parser.h \
    frontend/ui/structs.h \
    frontend/ui/styles/globalStyles.h \
    frontend/ui/styles/styles.h \
    frontend/ui/userInteractionWidgets/ModelEditor.h \
    frontend/ui/userInteractionWidgets/ModelViewer.h

FORMS += \
    frontend/ui/modalWidgets/AboutWindow/AboutWindow.ui \
    frontend/ui/modalWidgets/FileInformationWindow/FileInformationWindow.ui \
    frontend/ui/modalWidgets/PreferencesWindow/PreferencesWindow.ui

CONFIG += lrelease
CONFIG += embed_translations

QMAKE_EXTRA_TARGETS += format

format.target = format
format.commands = \
    echo "Start formatting..."; \
    clang-format -i *.c *.h *.cpp; \
    clang-format -i ../*/*.c ../*/*.h ../*/*.cpp; \
    clang-format -i ../*/*/*.c ../*/*/*.h ../*/*/*.cpp; \
    clang-format -i ../*/*/*/*.c ../*/*/*/*.h ../*/*/*/*.cpp; \
    clang-format -i ../*/*/*/*/*.c ../*/*/*/*/*.h ../*/*/*/*/*.cpp; \
    clang-format -i ../*/*/*/*/*/*.c ../*/*/*/*/*/*.h ../*/*/*/*/*/*.cpp; \
    echo "Formatting complete.";

format.depends = FORCE

PRE_TARGETDEPS += format
FORCE:

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    3d_viewer.app/Contents/Info.plist \
    3d_viewer.app/Contents/MacOS/3d_viewer \
    3d_viewer.app/Contents/PkgInfo \
    3d_viewer.app/Contents/Resources/empty.lproj \
    frontend/opengl/fragmentShader.frag \
    frontend/media/custom_hide_icon.png \
    frontend/media/custom_hide_icon_active.png \
    frontend/opengl/vertexShader.vert \
    frontend/ui/styles/DockWidgetSettingsStyles.qss

RESOURCES += \
    frontend/ui/media/media.qrc \
    frontend/opengl/shaders.qrc \
    frontend/ui/styles/styles.qrc
