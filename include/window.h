#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "fileManipulation.h"
#include "camera.h"
#include "block.hpp"
#include <opencv2/core/utility.hpp>
#include <opencv/cv.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class window {
public:
    window(std::string windowName);
    GLuint renderObjectToWidget(ImVec2 pos, GLfloat frontVerts[], GLfloat height, GLfloat width, bool ThreeDimensional);
    void render();
    void settingsPane();
    void leftViewPane();
    void topViewPane();
    void frontViewPane();
    void objectViewPane();
    void closeWindow();
    int whichPanel(ImVec2 mousePosition);
    void upload(int face);

    ~window();

    GLfloat mRotationX = 0.0f;
    GLfloat mRotationY = 0.0f;

private:

    GLuint mRenderedTexture;
    GLFWwindow* mWindow;
    int mScreenWidth, mScreenHeight, mGapSize, mWindowWidth, mWindowHeight;
    float spW, spH, vpW, vpH;


    bool mWindowClosed = true;

    std::string mWindowName;
    ImVec4 clear_color = ImColor(165, 173, 104);

    bool mCheckFiles = true;
    stringvec v;
    charvec vc;

    bool blockIsLoaded = false;
    bool clickBlock = false;
    block block;
    ImVec2 mousePosition;


    ImVec2 minimumXYLeftView, minimumXYTopView, minimumXYFrontView;
    ImVec2 maximumXYLeftView, maximumXYTopView, maximumXYFrontView;

    std::string mFileName;

    bool newOrOpen = true; // New = false ///// Open = true

    enum panel{
        left = 1,
        top = 2,
        front = 3
    };
};

