//
// Created by Kamin Fay on 4/10/18.
//
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>
#include <string>
#include <vector>
#include "fileManipulation.h"


class window {
public:
    window(std::string windowName);
    bool windowNotCLosed();
    void render();
    void renderObject();
    void settingsPane();
    void leftViewPane();
    void topViewPane();
    void frontViewPane();
    void objectViewPane();
    void closeWindow();

    void error_callback(int error, const char *description);

    ~window();

    GLfloat mRotationX = 0.0f;
    GLfloat mRotationY = 0.0f;

private:
    GLFWwindow* mWindow;
    int mScreenWidth, mScreenHeight, mGapSize, mWindowWidth, mWindowHeight;
    float spW, spH, vpW, vpH;


    bool mWindowClosed = true;

    int numVerts = 4;
    GLfloat testVerts[12] = {
            0, 100, 0,
            100, 100, 0,
            100, 0, 0,
            0, 0, 0,
    };

    std::string mWindowName;
    ImVec4 clear_color = ImColor(114, 144, 154);

    bool mCheckFiles = true;
    stringvec v;
    charvec vc;

};

