
#include "uploadData.h"



void pushBlockData(std::string blockName, int blockLength, int blockWidth, int blockHeight){
    std::string phpCommand;
    phpCommand = "curl https://thecarpentrytutor.000webhostapp.com/pushBlockName.php/\\?blockName\\=" + blockName +
              "\\&blockLength\\=" + std::to_string(blockLength) +
              "\\&blockWidth\\=" + std::to_string(blockWidth) +
              "\\&blockHeight\\=" + std::to_string(blockHeight);

    const char *command = phpCommand.c_str();
   system(command);
}

//void pushCutData(std::string blockName, int cutType, float x, float y){
//    std::string phpCommand;
//    phpCommand = "curl https://thecarpentrytutor.000webhostapp.com/pushCuts.php/\\?blockName\\=" + blockName +
//                 "\\&blockFace\\=" + std::to_string(cutType) +
//                 "\\&cutX\\=" + std::to_string(x) +
//                 "\\&cutY\\=" + std::to_string(y);
//
//    const char *command = phpCommand.c_str();
//    system(command);
//}