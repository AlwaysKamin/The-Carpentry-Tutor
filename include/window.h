//
// Created by Kamin Fay on 4/10/18.
//

#ifndef CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_WINDOW_H
#define CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>



class window {
public:
    window(std::string windowName);
    bool windowNotCLosed();
    void render();
    void renderObject();
    void closeWindow();

    void error_callback(int error, const char *description);

    ~window();

    GLfloat mRotationX = 0.0f;
    GLfloat mRotationY = 0.0f;

private:
    GLFWwindow* mWindow;
    int mScreenWidth, mScreenHeight;


    bool mWindowClosed = true;

    int numVerts = 4;
    GLfloat testVerts[12] = {
            0, 100, 0,
            100, 100, 0,
            100, 0, 0,
            0, 0, 0,
    };

    std::string mWindowName;


};


#endif //CMAKE_BUILD_DEBUG_CARPENTRYTUTOR_WINDOW_H
