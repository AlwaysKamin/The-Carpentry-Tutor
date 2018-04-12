//
// Created by Kamin Fay on 3/31/18.
//
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>
#include <librealsense2/rs_advanced_mode.hpp>
#include "example.hpp"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
void getColorFrame(rs2::pipeline p, rs2::frameset frames);
void getDepthFrame(rs2::pipeline p, rs2::frameset frames);

int main(){

    rs2::context context;
    auto list = context.query_devices();
    if(list.size() == 0){
        throw std::runtime_error("No device detected.... Shit");
    }
    rs2::device device = list.front();

    rs2::config config;
    config.enable_stream(RS2_STREAM_COLOR, 1920, 1080, RS2_FORMAT_BGR8, 6);
    config.enable_stream(RS2_STREAM_DEPTH);
    rs2::pipeline p;
    p.start(config);
    rs2::frameset frames;
    rs2::frame colorFrame;

    getDepthFrame(p, frames);
    getColorFrame(p, frames);

    return EXIT_SUCCESS;
}

void getDepthFrame(rs2::pipeline p, rs2::frameset frames){

    frames = p.wait_for_frames();
    rs2::depth_frame depth = frames.get_depth_frame();

    float cameraWidth = depth.get_width();
    float cameraHeight = depth.get_height();

    float dist_to_center = depth.get_distance(cameraWidth / 2, cameraHeight / 2);

    std::cout << "The object is " << dist_to_center << " Meteres away " << std::endl;

}

void getColorFrame(rs2::pipeline p, rs2::frameset frames){
    rs2::frame colorFrame;

    for(int i = 0; i < 20; i++){
        frames = p.wait_for_frames();
        colorFrame = frames.get_color_frame();
    }

    cv::Mat colorImage(cv::Size(1920, 1080), CV_8UC3, (void*)colorFrame.get_data(), cv::Mat::AUTO_STEP);
    //colorImage.data = (uchar*) reinterpret_cast<const uint8_t *>(colorFrame);
    cv::cvtColor(colorImage, colorImage, CV_RGB2BGR);

    cv::imshow("cameraData", colorImage);
    cv::waitKey(-1);
}