//
// Created by Kamin Fay on 4/10/18.
//

#include "window.h"

#define SCREEN_WIDTH = 1920
#define SCREEN_HEIGHT = 1080
#define TOTAL_DEPTH = 1000

void renderObject();


window::window(std::string windowName) {
    std::cout << "Window being created..." << std::endl;
    mWindowName = windowName;

    if (!glfwInit()) {
        std::cerr << " There was an issue initializing GLFW" << std::endl;
        return;
    }
    mScreenWidth = 1920;
    mScreenHeight = 1080;

    mWindow = glfwCreateWindow(mScreenWidth, mScreenHeight, mWindowName.c_str(), NULL, NULL);

    glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, 1);

    glfwGetFramebufferSize(mWindow, &mScreenWidth, &mScreenHeight);
    glfwMakeContextCurrent(mWindow);

    if (!mWindow) {
        std::cout << "Window not setup Properly" << std::endl;
        glfwTerminate();
        return;
    }

    mWindowClosed = false;

    std::cout << "Window done being created..." << std::endl;

}

bool window::windowNotCLosed(){
    if(mWindowClosed == false){
        return false;
    }else{
        return true;
    }
}

void window::render(){
    std::cout << "Entering Render" << std::endl;


    glViewport(0.0f, 0.0f, mScreenWidth, mScreenHeight);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0, mScreenWidth, 0, mScreenHeight, 0, 1000);

    glMatrixMode( GL_MODELVIEW);

    glLoadIdentity();

    while(!glfwWindowShouldClose(mWindow)){

        glClear(GL_COLOR_BUFFER_BIT);


        glPushMatrix();
        glTranslatef(mScreenWidth / 2, mScreenHeight / 2, -500);
        glRotatef(mRotationX, 1, 0, 0);
        glRotatef(mRotationY, 0, 1, 0);
        glTranslatef(-(mScreenWidth / 2), -(mScreenHeight / 2), 500);

        std::cout << "Done with matrix transformations" << std::endl;
        //Calls Draw blocks to calculate and render the block
        //Param 1: block position struct
        // Param 2: Block dimensions struct
        renderObject();
        //renderBlockFilled(blockPosFilled, block);

        glPopMatrix();

        // Swap front and back buffers
        glfwSwapBuffers(mWindow);

        //Events bullshit
        glfwPollEvents();
    }

}



void window::renderObject(){
    std::cout << "Entering render object" << std::endl;
    // Front and Back is for front and back facing polygons
    // GL_LINE is how the polygons are rastarized
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Enables the vertex array for writing and rendering
    glEnableClientState(GL_VERTEX_ARRAY);

    //Defines an array of vertext data
    // Param 1: 3 for the number of coordinates for each vertext (x, y, z)
    // Param 2: GL_Float for the data type
    // Param 3: 0 for no byte offset between consecutive vertices
    // Param 4: the verticies themselves
    glVertexPointer(3, GL_FLOAT, 0, testVerts);

    //Render primitives from array data
    // Param 1: Mode
    // Param 2: first index of array
    // Param 3: number of indicies to render
    glDrawArrays(GL_QUADS, 0, numVerts);

    // Closes the client state
    glDisableClientState(GL_VERTEX_ARRAY);
}

void window::closeWindow(){
    glfwTerminate();
    mWindowClosed = true;
}

window::~window() {
    glfwTerminate();
}

void window::error_callback(int error, const char *description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

