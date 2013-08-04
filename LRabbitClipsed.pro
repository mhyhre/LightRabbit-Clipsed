# LRabbit Qt project file

QT += core gui
QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LRabbitClipsed
TEMPLATE = app

SOURCES += \
    src/Engine/Camera2D.cpp \
    src/Engine/DefaultShaders.cpp \
    src/Engine/DrawableEntity.cpp \
    src/Engine/EntityObject.cpp \
    src/Engine/GLWidget.cpp \
    src/Engine/Line.cpp \
    src/Engine/Rect.cpp \
    src/Engine/Scene.cpp \
    src/Engine/SceneObject.cpp \
    src/Engine/Sprite.cpp \
    src/Engine/SpriteBatch.cpp \
    src/Engine/TextureAtlas.cpp \
    src/Engine/TextureRegion.cpp \
    src/Engine/VertexBufferManager.cpp \
    src/FormAbout.cpp \
    src/FormNewClip.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/MainWindow2.cpp

HEADERS  += \
    headers/FormAbout.h \
    headers/FormNewClip.h \
    headers/ListWidgetItems.h \
    headers/MainWindow.h \
    headers/Engine/Camera2D.h \
    headers/Engine/DefaultShaders.h \
    headers/Engine/DrawableEntity.h \
    headers/Engine/EntityObject.h \
    headers/Engine/GLWidget.h \
    headers/Engine/Line.h \
    headers/Engine/Rect.h \
    headers/Engine/Scene.h \
    headers/Engine/SceneObject.h \
    headers/Engine/Sprite.h \
    headers/Engine/SpriteBatch.h \
    headers/Engine/TextureAtlas.h \
    headers/Engine/TextureRegion.h \
    headers/Engine/VertexBufferManager.h \
    headers/Engine/VertexTypes.h

INCLUDEPATH += headers \
    headers/Engine

FORMS    += \
    FormAbout.ui \
    MainWindow.ui \
    FormNewClip.ui

OTHER_FILES += \
    README.md

RESOURCES += \
    Shaders.qrc \
    Icons.qrc

QMAKE_CXXFLAGS += -std=c++11
