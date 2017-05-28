TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    additional_functions.cpp


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
    OPENCV_LIB_PATH = D:\opencv\build\install\x86\mingw\bin
    INCLUDEPATH += D:\opencv\build\install\include
    LIBS += -L$$OPENCV_LIB_PATH \
        -lopencv_aruco320 \
        -lopencv_bgsegm320 \
        -lopencv_bioinspired320 \
        -lopencv_calib3d320 \
        -lopencv_ccalib320 \
        -lopencv_core320 \
        -lopencv_datasets320 \
        -lopencv_dnn320 \
        -lopencv_dpm320 \
        -lopencv_face320 \
        -lopencv_features2d320 \
        -lopencv_flann320 \
        -lopencv_fuzzy320 \
        -lopencv_highgui320 \
        -lopencv_imgcodecs320 \
        -lopencv_imgproc320 \
        -lopencv_line_descriptor320 \
        -lopencv_ml320 \
        -lopencv_objdetect320 \
        -lopencv_optflow320 \
        -lopencv_photo320 \
        -lopencv_plot320 \
        -lopencv_reg320 \
        -lopencv_rgbd320 \
        -lopencv_saliency320 \
        -lopencv_shape320 \
        -lopencv_stereo320 \
        -lopencv_stitching320 \
        -lopencv_structured_light320 \
        -lopencv_superres320 \
        -lopencv_surface_matching320 \
        -lopencv_text320 \
        -lopencv_tracking320 \
        -lopencv_video320 \
        -lopencv_videoio320 \
        -lopencv_videostab320 \
        -lopencv_xfeatures2d320 \
        -lopencv_ximgproc320 \
        -lopencv_xobjdetect320 \
        -lopencv_xphoto320  \
}
