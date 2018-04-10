//
// Created by Kamin Fay on 3/31/18.
//
#include <librealsense2/rs.hpp>
#include <librealsense2/rsutil.h>
#include "example.hpp"


int main(){

    rs2::context context;
    auto list = context.query_devices();
    if(list.size() == 0){
        throw std::runtime_error("No device detected.... Shit");
    }
    rs2::device device = list.front();

    rs2::pipeline p;
    p.start();

    rs2::frameset frames = p.wait_for_frames();
    rs2::depth_frame depth = frames.get_depth_frame();

    float cameraWidth = depth.get_width();
    float cameraHeight = depth.get_height();

    float dist_to_center = depth.get_distance(cameraWidth / 2, cameraHeight / 2);

    std::cout << "The object is " << dist_to_center << " Meteres away " << std::endl;


    return 0;
}