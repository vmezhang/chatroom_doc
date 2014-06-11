TEMPLATE = app
TARGET =
DEPENDPATH += .
INCLUDEPATH += .

INCLUDEPATH += include
INCLUDEPATH += /usr/local/include/opencv
LIBS += -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui \
        -lopencv_ml \
        -lopencv_video \
        -lopencv_features2d \
        -lopencv_calib3d \
        -lopencv_objdetect \
        -lopencv_contrib \
        -lopencv_legacy \
        -lopencv_flann

QT += network
QT += testlib

# Input
HEADERS += include/MainWindow.h \
    include/ChatWidget.h \
    include/OnlineList.h \
    include/ChatWidget.h \
    include/MainWindow.h \
    include/OnlineList.h \
    include/CamareGet.h

SOURCES += src/main.cpp \
    src/MainWindow.cpp \
    src/ChatWidget.cpp \
    src/OnlineList.cpp \
    src/CamareGet.cpp

RESOURCES += resource.qrc
