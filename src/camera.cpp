
#include "camera.h"

camera::camera(){
    auto list = cameraContext.query_devices();
    if(list.size() == 0){
        std::cerr << "No device detected.... Shit";

    }else{
        cameras = list.front();
        cameraConfig.enable_stream(RS2_STREAM_COLOR, 1920, 1080, RS2_FORMAT_BGR8, 6);
        cameraConfig.enable_stream(RS2_STREAM_DEPTH);
        cameraPipeline.start(cameraConfig);
    }
}

void camera::getDepthFrame(){

    mFrames = cameraPipeline.wait_for_frames();
    rs2::depth_frame depth = mFrames.get_depth_frame();

    float cameraWidth = depth.get_width();
    float cameraHeight = depth.get_height();

    float dist_to_center = depth.get_distance(cameraWidth / 2, cameraHeight / 2);

    std::cout << "The object is " << dist_to_center << " Meteres away " << std::endl;

}

void camera::getColorFrame(){

    for(int i = 0; i < 20; i++){
        mFrames = cameraPipeline.wait_for_frames();
        colorFrame = mFrames.get_color_frame();
    }

    cv::Mat colorImage(cv::Size(1920, 1080), CV_8UC3, (void*)colorFrame.get_data(), cv::Mat::AUTO_STEP);
    //colorImage.data = (uchar*) reinterpret_cast<const uint8_t *>(colorFrame);
    cv::cvtColor(colorImage, colorImage, CV_RGB2BGR);

    cv::imshow("cameraData", colorImage);
    cv::waitKey(-1);
}