//
// Created by Kamin Fay on 4/10/18.
//

#include "window.h"





window::window(std::string windowName) {
    std::cout << "Window being created..." << std::endl;
    mWindowName = windowName;

    if (!glfwInit()) {
        std::cerr << " There was an issue initializing GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mScreenWidth = 1920;
    mScreenHeight = 1080;
    mWindowHeight = mScreenHeight;
    mWindowWidth = mScreenWidth;
    mGapSize = 10;

    mWindow = glfwCreateWindow(mScreenWidth, mWindowHeight, mWindowName.c_str(), NULL, NULL);
    glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, 1);

    glfwMakeContextCurrent(mWindow);
    glewExperimental = GL_TRUE;
    glewInit();
    if(glewInit() != GLEW_OK){
        std::cout << "glew was not initiated properly" << std::endl;
    }

    glfwGetFramebufferSize(mWindow, &mScreenWidth, &mScreenHeight);

    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(mWindow, true);

    if (!mWindow) {
        std::cout << "Window not setup Properly" << std::endl;
        glfwTerminate();
        return;
    }

    mWindowClosed = false;


    std::cout << "Window done being created..." << std::endl;

}

bool window::windowNotCLosed(){
    if(!mWindowClosed){
        return false;
    }else{
        return true;
    }
}

void window::render(){
    std::cout << "Entering Render" << std::endl;

    glViewport(0.0f, 0.0f, mWindowWidth, mWindowHeight);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0, mWindowHeight, 0, mWindowHeight, 0, 1000);

    glMatrixMode( GL_MODELVIEW);

    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT);


    while(!glfwWindowShouldClose(mWindow)){
        ImGui_ImplGlfwGL3_NewFrame();
        glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
        std::cout << mWindowWidth << "-----" << mWindowHeight << std::endl;
        spW = ((mWindowWidth * .25) - (1.5 * mGapSize));
        spH = ((mWindowHeight) - (2 * mGapSize));
        vpW = (((mWindowWidth * .75) / 2) - mGapSize);
        vpH = ((mWindowHeight * .5) - (1.5 * mGapSize));

        settingsPane();
        leftViewPane();
        topViewPane();
        frontViewPane();
        objectViewPane();

        glPushMatrix();
        glTranslatef(mWindowWidth / 2, mWindowHeight / 2, -500);
        glRotatef(mRotationX, 1, 0, 0);
        glRotatef(mRotationY, 0, 1, 0);
        glTranslatef(-(mWindowWidth / 2), -(mWindowHeight / 2), 500);
        glPopMatrix();

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        ImGui::Render();
//        renderObject();

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

void window::settingsPane(){
    mWindowWidth = 1920;
    mWindowHeight = 1080;
    {
        ImGui::SetNextWindowPos(ImVec2(mGapSize, mGapSize));
        ImGui::Begin("SettingsPane");
        ImGui::SetWindowSize(ImVec2(spW, spH));
        ImGui::Text("First Test panel");
        ImGui::End();
    }
}

void window::leftViewPane(){
    {
        ImGui::SetNextWindowPos(ImVec2((2* mGapSize) + spW, mGapSize));
        ImGui::Begin("Left View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImGui::Text("First Test panel");
        ImGui::End();
    }
}

void window::topViewPane(){
    {
        ImGui::SetNextWindowPos(ImVec2((3 * mGapSize) + spW + vpW, mGapSize));
        ImGui::Begin("Top View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImGui::Text("First Test panel");
        ImGui::End();
    }
}

void window::frontViewPane(){
    {
        ImGui::SetNextWindowPos(ImVec2((2 * mGapSize) + spW, (2 * mGapSize) + vpH));
        ImGui::Begin("Front View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImGui::Text("First Test panel");
        ImGui::End();
    }
}

void window::objectViewPane(){
    {
        ImGui::SetNextWindowPos(ImVec2((3 * mGapSize) + spW + vpW, (2 * mGapSize) + vpH));
        ImGui::Begin("3D View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImGui::Text("First Test panel");
        ImGui::End();
    }
}

void window::closeWindow(){
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();
    mWindowClosed = true;
}

window::~window() {
    glfwTerminate();
}

void window::error_callback(int error, const char *description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

