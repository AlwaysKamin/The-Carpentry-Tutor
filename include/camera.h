
#include <iostream>
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>
#include <librealsense2/rs_advanced_mode.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>


#ifndef CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_CAMERA_H
#define CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_CAMERA_H

class camera{
public:

    camera();
    void getColorFrame();
    void getDepthFrame();

private:
    rs2::context cameraContext;
    rs2::device cameras;
    rs2::config cameraConfig;
    rs2::pipeline cameraPipeline;
    rs2::frameset mFrames;
    rs2::frame colorFrame;

};

#endif //CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_CAMERA_H
