//
// Created by Kamin Fay on 4/10/18.
//

#include "window.h"
#include <imgui_internal.h>


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
        //std::cout << mWindowWidth << "-----" << mWindowHeight << std::endl;
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
        ImGui::Begin("Settings");
        {
            ImGui::SetWindowSize(ImVec2(spW, spH));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::Separator();
            if (ImGui::CollapsingHeader("File Modifications")) {
                if (ImGui::TreeNode("Saving")) {
//                    static char buf[32];
//                    ImGui::InputText("input", buf, IM_ARRAYSIZE(buf));
                    if (ImGui::Button("Open File"))
                        ImGui::OpenPopup("savePopup");
                    ImGui::SetNextWindowPos(ImVec2((2* mGapSize) + spW, mGapSize));
                    if (ImGui::BeginPopupModal("savePopup")) {

                        ImGui::SetWindowSize(ImVec2(vpW, vpH));

                        int numberOfFiles = 0;

                        std::string fileName;

                            stringvec vNum;
                            numberOfFiles = getNumberOfFiles("../templates/", vNum);
                            vNum.clear();
                            char *fileListTemp[numberOfFiles];
                            read_directory("../templates/", v, vc, fileListTemp);
                            mCheckFiles = false;

                        ImGui::Columns(3, "FileBrowser", false);
                        ImGui::Separator();
                        for(int i = 0; i < numberOfFiles; i++){
                            //ImGui::Text("%s", v[i].c_str());
                            char labelBuff[32];
                            sprintf(labelBuff, vc[i], i);
                            if(ImGui::Selectable(labelBuff)){

                                fileName = labelBuff;
                                std::cout << labelBuff << std::endl;
                                readFile(fileName);
                            }
                            ImGui::NextColumn();
                        }

                        //TODO implement list boxes to allow for file selection

//                        static int current_item = 1;
////                        if(ImGui::ListBox("##", &current_item, vector_string_items_getter, &v, v.size(), 10)){
////
////                        }


                        if (ImGui::Button("Close"))
                            ImGui::CloseCurrentPopup();
                        ImGui::EndPopup();
                        clearVectors(v, vc);
                    }

                    ImGui::TextWrapped(
                            "The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded. You can also call ImGui::LogText() to output directly to the log without a visual output.");
                    ImGui::TreePop();
                }
            }

            ImGui::Separator();

            if (ImGui::CollapsingHeader("Tools")) {

            }

            ImGui::Separator();

            if (ImGui::CollapsingHeader("Help")) {

            }
        }
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
        std::vector<std::string> test = {"test", "Test 2", "Test 3"};
        for(int i = 0; i < 3; i++){
            ImGui::Text(test[i].c_str());
        }
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

