
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "imgui.h"

#ifndef CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_BLOCK_HPP
#define CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_BLOCK_HPP



class block {
public:
    block();
    void setBlockSize(int newWidth, int newHeight, int newLength);
    void setBlockPos(int x, int y, int z);
    void setBlockVerts();
    GLfloat getHeight();
    GLfloat getWidth();
    GLfloat getLength();
    void setLength(float length);
    void setWidth(float width);
    void setHeight(float height);
    void setBlockName(std::string blockName);
    void setLeftMinMax(ImVec2 min, ImVec2 max);
    void setFrontMinMax(ImVec2 min, ImVec2 max);
    void setTopMinMax(ImVec2 min, ImVec2 max);
    void addDrill(ImVec2 location, int face);
    GLfloat *getFrontVerts();
    GLfloat* getSideVerts();
    GLfloat* getTopVerts();
    GLfloat* getTDVerts();
    int getSideDrillC();
    int getTopDrillC();
    int getFrontDrillC();
    std::string getBlockName();
    int withinBlock(int face, ImVec2 mousePosition);
    std::string getOneDrill(int counter, int face);
    ImVec2 getOneDrillActual(int counter, int face);



    enum blockFace{
        LEFT = 1,
        TOP = 2,
        FRONT = 3
    };


private:

    GLfloat x;
    GLfloat y;
    GLfloat z;

    GLfloat mHeight;
    GLfloat mLength;
    GLfloat mWidth;

    GLfloat frontVerts[8];
    GLfloat sideVerts[8];
    GLfloat topVerts[8];
    GLfloat TDVerts[24];


    ImVec2 minimumXYBlockLeft, minimumXYBlockTop, minimumXYBlockFront;
    ImVec2 maximumXYBlockLeft, maximumXYBlockTop, maximumXYBlockFront;

    std::vector<ImVec2> drillSpotsLeft;
    std::vector<ImVec2> drillSpotsTop;
    std::vector<ImVec2> drillSpotsFront;

    int drillLeftC = 0;
    int drillTopC = 0;
    int drillFrontC = 0;

    std::string mBlockName;

};


#endif //CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_BLOCK_HPP
