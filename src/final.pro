QT += core gui opengl

LIBS += -L"$$_PRO_FILE_PWD_/glew/lib" -lGLEW 

CONFIG += c++11

unix:!macx {
    QMAKE_CXXFLAGS += -std=c++11
}

TARGET = final
TEMPLATE = app

# If you add your own folders, add them to INCLUDEPATH and DEPENDPATH, e.g.

CONFIG -= depend_includepath

INCLUDEPATH += "glew/include"
# DEPENDPATH += folder1 folder2

SOURCES += main.cpp \
    mainwindow.cpp \
    view.cpp \
    scene.cpp \
    camera.cpp \
    light.cpp \
    mesh.cpp \
    material.cpp \
    sceneobject.cpp \
    scenenode.cpp \
    drawcontext.cpp \
    geometry.cpp

HEADERS += mainwindow.h \
    view.h \
    geometry.h \
    common.h \
    scene.h \
    camera.h \
    light.h \
    mesh.h \
    material.h \
    sceneobject.h \
    scenenode.h \
    drawcontext.h

DEFINES += QT_COORD_TYPE=float

FORMS += mainwindow.ui
