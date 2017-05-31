TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    additional_functions.cpp


win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux
OPCV_VER = 310

linux {
    OPENCV_LIB_PATH = /usr/local/lib
    LIBS += -L$$OPENCV_LIB_PATH \
         -lopencv_aruco \
         -lopencv_bgsegm \
         -lopencv_bioinspired \
         -lopencv_calib3d \
         -lopencv_ccalib \
         -lopencv_core \
         -lopencv_datasets \
         -lopencv_dnn \
         -lopencv_dpm \
         -lopencv_face \
         -lopencv_features2d \
         -lopencv_flann \
         -lopencv_fuzzy \
         -lopencv_highgui \
         -lopencv_imgcodecs \
         -lopencv_imgproc \
         -lopencv_line_descriptor \
         -lopencv_ml \
         -lopencv_objdetect \
         -lopencv_optflow \
         -lopencv_photo \
         -lopencv_plot \
         -lopencv_reg \
         -lopencv_rgbd \
         -lopencv_saliency \
         -lopencv_shape \
         -lopencv_stereo \
         -lopencv_stitching \
         -lopencv_structured_light \
         -lopencv_superres \
         -lopencv_surface_matching \
         -lopencv_text \
         -lopencv_tracking \
         -lopencv_video \
         -lopencv_videoio \
         -lopencv_videostab \
         -lopencv_xfeatures2d \
         -lopencv_ximgproc \
         -lopencv_xobjdetect
}
win32 {
#    OPENCV_LIB_PATH = D:\opencv\build\install\x86\mingw\bin
#    INCLUDEPATH += D:\opencv\build\install\include
## В переменных окружения системы должны быть определены
##     OPENCV_INC - путь к заголовкам
##     OPENCV_DIR - путь к бинарникам
    INCLUDEPATH += $$(OPENCV_INC)
    LIBS += -L $$(OPENCV_DIR)\bin \
        -lopencv_aruco$$OPCV_VER \
        -lopencv_bgsegm$$OPCV_VER \
        -lopencv_bioinspired$$OPCV_VER \
        -lopencv_calib3d$$OPCV_VER \
        -lopencv_ccalib$$OPCV_VER \
        -lopencv_core$$OPCV_VER \
        -lopencv_datasets$$OPCV_VER \
        -lopencv_dnn$$OPCV_VER \
        -lopencv_dpm$$OPCV_VER \
        -lopencv_face$$OPCV_VER \
        -lopencv_features2d$$OPCV_VER \
        -lopencv_flann$$OPCV_VER \
        -lopencv_fuzzy$$OPCV_VER \
        -lopencv_highgui$$OPCV_VER \
        -lopencv_imgcodecs$$OPCV_VER \
        -lopencv_imgproc$$OPCV_VER \
        -lopencv_line_descriptor$$OPCV_VER \
        -lopencv_ml$$OPCV_VER \
        -lopencv_objdetect$$OPCV_VER \
        -lopencv_optflow$$OPCV_VER \
        -lopencv_photo$$OPCV_VER \
        -lopencv_plot$$OPCV_VER \
        -lopencv_reg$$OPCV_VER \
        -lopencv_rgbd$$OPCV_VER \
        -lopencv_saliency$$OPCV_VER \
        -lopencv_shape$$OPCV_VER \
        -lopencv_stereo$$OPCV_VER \
        -lopencv_stitching$$OPCV_VER \
        -lopencv_structured_light$$OPCV_VER \
        -lopencv_superres$$OPCV_VER \
        -lopencv_surface_matching$$OPCV_VER \
        -lopencv_text$$OPCV_VER \
        -lopencv_tracking$$OPCV_VER \
        -lopencv_video$$OPCV_VER \
        -lopencv_videoio$$OPCV_VER \
        -lopencv_videostab$$OPCV_VER \
        -lopencv_xfeatures2d$$OPCV_VER \
        -lopencv_ximgproc$$OPCV_VER \
        -lopencv_xobjdetect$$OPCV_VER \
        -lopencv_xphoto$$OPCV_VER  \
}
