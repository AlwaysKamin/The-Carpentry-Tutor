

#include "block.hpp"

block::block(){

}

GLfloat block::getHeight(){
    return mHeight;
}

GLfloat block::getWidth(){
    return mWidth;
}
GLfloat block::getLength(){
    return mLength;
}

void block::setLength(float length){
    mLength = length;
}

void block::setWidth(float width){
    mWidth = width;
}

void block::setHeight(float height){
    mHeight = height;
}

void block::setBlockName(std::string blockName) {
    mBlockName = blockName;
}

void block::setLeftMinMax(ImVec2 min, ImVec2 max) {
    minimumXYBlockLeft = min;
    maximumXYBlockLeft = max;
}

void block::setFrontMinMax(ImVec2 min, ImVec2 max) {
    minimumXYBlockFront = min;
    maximumXYBlockFront = max;
}

void block::setTopMinMax(ImVec2 min, ImVec2 max) {
    minimumXYBlockTop = min;
    maximumXYBlockTop = max;
}

std::string block::getBlockName(){
    return mBlockName;
}

GLfloat* block::getFrontVerts(){
    return frontVerts;
}

GLfloat* block::getTopVerts(){
    return topVerts;
}

GLfloat* block::getSideVerts(){
    return sideVerts;
}

GLfloat* block::getTDVerts(){
    return TDVerts;
}

int block::getSideDrillC(){
    return drillLeftC;
}
int block::getTopDrillC(){
    return drillTopC;
}
int block::getFrontDrillC(){
    return drillFrontC;
}

std::string block::getOneDrill(int counter, int face){
    std::string temp;
    // Grabs the location of the ddrill spots and returns the x, y cooridnate in string format
    switch(face){
        case LEFT:
            temp = "X: " + std::to_string(drillSpotsLeft[counter].x) + " Y: " + std::to_string(drillSpotsLeft[counter].y);
            break;
        case TOP:
            temp = "X: " + std::to_string(drillSpotsTop[counter].x) + " Y: " + std::to_string(drillSpotsTop[counter].y);
            break;
        case FRONT:
            temp = "X: " + std::to_string(drillSpotsFront[counter].x) + " Y: " + std::to_string(drillSpotsFront[counter].y);
            break;
        default:
            break;
    }

    return temp;
}

ImVec2 block::getOneDrillActual(int counter, int face){
    ImVec2 test;
    // Does the same as the above but returns an ImVec2 variable with the x, y coordiantes in it
    switch(face){
            case LEFT:
                return drillSpotsLeft[counter];
            case TOP:
                return drillSpotsTop[counter];
            case FRONT:
                return drillSpotsFront[counter];
            default:
                break;
    }

    return test;
}


void block::addDrill(ImVec2 location, int face){
    ImVec2 actualPosition;

    // Depending on which face the block is in it will calculate the actual x, y position on the block itself
    // It is then pushed into a list of drill holes depended on the block itself
    switch(face){
        case LEFT:
            std::cout << "Screen XY --- X: " << location.x << " Y: " << location.y << std::endl;
            actualPosition.x = location.x - minimumXYBlockLeft.x;
            actualPosition.y = location.y - minimumXYBlockLeft.y;
            std::cout << "Actual XY --- X: " << actualPosition.x << " Y: " << actualPosition.y << std::endl;
            drillSpotsLeft.push_back(actualPosition);
            drillLeftC++;
            break;
        case TOP:
            std::cout << "Screen XY --- X: " << location.x << " Y: " << location.y << std::endl;
            actualPosition.x = location.x - minimumXYBlockTop.x;
            actualPosition.y = location.y - minimumXYBlockTop.y;
            std::cout << "Actual XY --- X: " << actualPosition.x << " Y: " << actualPosition.y << std::endl;
            drillSpotsTop.push_back(actualPosition);
            drillTopC++;
            break;
        case FRONT:
            std::cout << "Screen XY --- X: " << location.x << " Y: " << location.y << std::endl;
            actualPosition.x = location.x - minimumXYBlockFront.x;
            actualPosition.y = location.y - minimumXYBlockFront.y;
            std::cout << "Actual XY --- X: " << actualPosition.x << " Y: " << actualPosition.y << std::endl;
            drillSpotsFront.push_back(actualPosition);
            drillFrontC++;
            break;
        default:
            break;
    }
}
//TODO move the render to widget, it doesnt belong here


void block::setBlockPos(int x, int y, int z){
    block::x = x;
    block::y = y;
    block::z = z;
}

void block::setBlockSize(int newWidth, int newHeight, int newLength){
    std::cout << "L: " << newLength << " W: " << newWidth << " H: " << newHeight << std::endl;
    mWidth = newWidth;
    mHeight = newHeight;
    mLength = newLength;
}

void block::setBlockVerts(){
    frontVerts[0] = x - (0.5f * mWidth);
    frontVerts[1] = y + (0.5f * mHeight); //Top Left
    frontVerts[2] = x - (0.5f * mWidth);
    frontVerts[3] = y - (0.5f * mHeight);//Bot Left
    frontVerts[4] = x + (0.5f * mWidth);
    frontVerts[5] = y - (0.5f * mHeight);//Bot Right
    frontVerts[6] = x + (0.5f * mWidth);
    frontVerts[7] = y + (0.5f * mHeight); //Top Right

    sideVerts[0] = x - (0.5f * mLength);
    sideVerts[1] = y + (0.5f * mHeight);
    sideVerts[2] = x - (0.5f * mLength);
    sideVerts[3] = y - (0.5f * mHeight);
    sideVerts[4] = x + (0.5f * mLength);
    sideVerts[5] = y - (0.5f * mHeight);
    sideVerts[6] = x + (0.5f * mLength);
    sideVerts[7] = y + (0.5f * mHeight);

    topVerts[0] = x - (0.5f * mWidth);
    topVerts[1] = y + (0.5f * mLength);
    topVerts[2] = x - (0.5f * mWidth);
    topVerts[3] = y - (0.5f * mLength);
    topVerts[4] = x + (0.5f * mWidth);
    topVerts[5] = y - (0.5f * mLength);
    topVerts[6] = x + (0.5f * mWidth);
    topVerts[7] = y + (0.5f * mLength);

    for(int i = 0; i < 8; i++){
        TDVerts[i] = frontVerts[i];
        TDVerts[i+8] = sideVerts[i];
        TDVerts[i+16] = topVerts[i];
    }
    std::cout << "Front Verts" << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << frontVerts[i] << "-";
    }
    std::cout << std::endl;
    std::cout << "Side Verts" << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << sideVerts[i] << "-";
    }
    std::cout << std::endl;
    std::cout << "Top Verts" << std::endl;
    for(int i = 0; i < 8; i++){
        std::cout << topVerts[i] << "-";
    }
    std::cout << std::endl;
    std::cout << "ThreeD Verts" << std::endl;
    for(int i = 0; i < 24; i++){
        std::cout << TDVerts[i] << "-";
    }
}

int block::withinBlock(int test, ImVec2 mousePosition){
    // Similar to the function in the window and panes. Just simply checks to see if the mouse is within the parameters of the block
    if(mousePosition.x > minimumXYBlockLeft.x && mousePosition.y > minimumXYBlockLeft.y &&
       mousePosition.x < maximumXYBlockLeft.x && mousePosition.y < maximumXYBlockLeft.y){
        std::cout << "Mouse is within the left face of the block" << std::endl;
        return 1;
    }else if(mousePosition.x > minimumXYBlockTop.x && mousePosition.y > minimumXYBlockTop.y &&
             mousePosition.x < maximumXYBlockTop.x && mousePosition.y < maximumXYBlockTop.y){
        std::cout << "Mouse is clicked within the top face of the block." << std::endl;
        return 2;
    }else if(mousePosition.x > minimumXYBlockFront.x && mousePosition.y > minimumXYBlockFront.y &&
             mousePosition.x < maximumXYBlockFront.x && mousePosition.y < maximumXYBlockFront.y){
        std::cout << "Mouse is clicked within the front face of the block." << std::endl;
        return 3;
    }else {
        std::cout << "Not clicked within object panels" << std::endl;
        return 0;
    }
}