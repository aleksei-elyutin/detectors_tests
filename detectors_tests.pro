TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp


win32: OS_SUFFIX = win32
linux-g++: OS_SUFFIX = linux

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
         -lopencv_xobjdetect \
}
win32 {
    OPENCV_LIB_PATH = C:\opencv-build\install\x86\mingw\bin
    INCLUDEPATH += C:\opencv-build\install\include
    LIBS += -L$$OPENCV_LIB_PATH \
        -lopencv_aruco310 \
        -lopencv_bgsegm310 \
        -lopencv_bioinspired310 \
        -lopencv_calib3d310 \
        -lopencv_ccalib310 \
        -lopencv_core310 \
        -lopencv_datasets310 \
        -lopencv_dnn310 \
        -lopencv_dpm310 \
        -lopencv_face310 \
        -lopencv_features2d310 \
        -lopencv_flann310 \
        -lopencv_fuzzy310 \
        -lopencv_highgui310 \
        -lopencv_imgcodecs310 \
        -lopencv_imgproc310 \
        -lopencv_line_descriptor310 \
        -lopencv_ml310 \
        -lopencv_objdetect310 \
        -lopencv_optflow310 \
        -lopencv_photo310 \
        -lopencv_plot310 \
        -lopencv_reg310 \
        -lopencv_rgbd310 \
        -lopencv_saliency310 \
        -lopencv_shape310 \
        -lopencv_stereo310 \
        -lopencv_stitching310 \
        -lopencv_structured_light310 \
        -lopencv_superres310 \
        -lopencv_surface_matching310 \
        -lopencv_text310 \
        -lopencv_tracking310 \
        -lopencv_video310 \
        -lopencv_videoio310 \
        -lopencv_videostab310 \
        -lopencv_xfeatures2d310 \
        -lopencv_ximgproc310 \
        -lopencv_xobjdetect310 \
        -lopencv_xphoto310  \
#        $$OPENCV_LIB_PATH\opencv_ffmpeg310.dll \
}
