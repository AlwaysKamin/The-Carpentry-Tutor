
#include "window.h"
#include <imgui_internal.h>
#include "uploadData.h"
#include <mysql/mysql.h>

window::window(std::string windowName) {
    std::cout << "Window being created..." << std::endl;
    mWindowName = windowName;

    if (!glfwInit()) {
        std::cerr << " There was an issue initializing GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
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





GLuint window::renderObjectToWidget(ImVec2 pos, GLfloat frontVerts[], GLfloat height, GLfloat width, bool ThreeDimensional){


//create a vao,vbo
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(frontVerts), frontVerts, GL_STATIC_DRAW);

// position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

// color attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    //glEnableVertexAttribArray(1);



    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 200, 200, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    // Enables the vertex array for writing and rendering

    glEnableClientState(GL_VERTEX_ARRAY);


    //Defines an array of vertext data
    // Param 1: 3 for the number of coordinates for each vertext (x, y, z)
    // Param 2: GL_Float for the data type
    // Param 3: 0 for no byte offset between consecutive vertices
    // Param 4: the verticies themselves
    glVertexPointer(3, GL_FLOAT, 0, frontVerts);

    //Render primitives from array data
    // Param 1: Mode
    // Param 2: first index of array
    // Param 3: number of indicies to render
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if(ThreeDimensional == true){
        glDrawArrays(GL_QUADS, 0, 24);
    }else{
        glDrawArrays(GL_QUADS, 0, 8);
    }


    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Closes the client state
    glDisableClientState(GL_VERTEX_ARRAY);
    GLuint mRenderedTexture;


    glGenTextures(1, &mRenderedTexture);
    glBindTexture(GL_TEXTURE_2D, mRenderedTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    mRenderedTexture = fbo;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Ask ImGui to draw it as an image:
    // Under OpenGL the ImGUI image type is GLuint
    // So make sure to use "(void *)tex" but not "&tex"
    ImGui::GetWindowDrawList()->AddImage(
            (void *)mRenderedTexture,
            ImVec2(ImGui::GetItemRectMin().x + pos.x , ImGui::GetItemRectMin().y + pos.y),
            ImVec2(pos.x + width , pos.y + height ), ImVec2(0, 1), ImVec2(1, 0));


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);

    glLoadIdentity();
    return fbo;
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

    double xPos = 0;
    double yPos = 0;

    while(!glfwWindowShouldClose(mWindow)){
        ImGui_ImplGlfwGL3_NewFrame();
        glfwGetWindowSize(mWindow, &mWindowWidth, &mWindowHeight);
        //std::cout << mWindowWidth << "-----" << mWindowHeight << std::endl;
        spW = ((mWindowWidth * .25) - (1.5 * mGapSize));
        spH = ((mWindowHeight) - (2 * mGapSize));
        vpW = (((mWindowWidth * .75) / 2) - mGapSize);
        vpH = ((mWindowHeight * .5) - (1.5 * mGapSize));

        mousePosition = ImGui::GetMousePos();

        settingsPane();
        leftViewPane();
        topViewPane();
        frontViewPane();
        objectViewPane();

        if(ImGui::IsMouseClicked(0)){
            int testReturn = whichPanel(mousePosition);
            int test = block.withinBlock(1, mousePosition);
            if(clickBlock == true && test != 0){
                block.addDrill(mousePosition, test);
                clickBlock = false;
                upload(test);
            }
        }

        glPushMatrix();
        glTranslatef(mWindowWidth / 2, mWindowHeight / 2, -500);
        glRotatef(mRotationX, 1, 0, 0);
        glRotatef(mRotationY, 0, 1, 0);
        glTranslatef(-(mWindowWidth / 2), -(mWindowHeight / 2), 500);
        glPopMatrix();

        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();

        // Swap front and back buffers
        glfwSwapBuffers(mWindow);

        //Events bullshit
        glfwPollEvents();
    }

}





void window::settingsPane(){
    mWindowWidth = 1920;
    mWindowHeight = 1080;
    {
        ImGui::SetNextWindowPos(ImVec2(mGapSize, mGapSize));
        ImGui::Begin("Settings");
        {
            ImGui::GetIO().Framerate = 120;
            ImGui::SetWindowSize(ImVec2(spW, spH));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::Separator();
            if (ImGui::CollapsingHeader("File Modifications")) {

                static char fileNameInput[128] = "";
                ImGui::InputText("", fileNameInput, IM_ARRAYSIZE(fileNameInput));
                ImGui::SameLine();
                    if(ImGui::Button("New File")){
                        //TODO content here for creating a new file
                        newOrOpen = false;
                        std::cout << fileNameInput;
                        newFile(fileNameInput, block);
                    }

                    if (ImGui::Button("Open File")){
                        block.setBlockPos(0,0,0);
                        block.setBlockVerts();
                        ImGui::OpenPopup("openPopUp");
                    }

                    std::string fileName;
                    char labelBuff[32];

                ImGui::SetNextWindowPos(ImVec2((2* mGapSize) + spW, mGapSize));
                    if (ImGui::BeginPopupModal("openPopUp")) {

                        ImGui::SetWindowSize(ImVec2(vpW, vpH));

                        int numberOfFiles = 0;

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
                            sprintf(labelBuff, vc[i], i);
                            if(ImGui::Selectable(labelBuff)){

                                mFileName = labelBuff;
                                readFile((mFileName), block);
                                block.setBlockName(mFileName);
                                block.setBlockPos(0,0,0);
                                block.setBlockVerts();
                                blockIsLoaded = true;
                                std::cout << labelBuff << std::endl;
                                //readFile(fileName);
                            }
                            ImGui::NextColumn();
                        }

                        //TODO implement list boxes to allow for file selection

                        if (ImGui::Button("Close"))
                            ImGui::CloseCurrentPopup();
                        ImGui::EndPopup();
                        clearVectors(v, vc);
                    }

                if (ImGui::Button("Save File")){
                    //TODO contents here for saving a file
                    std::cout << fileNameInput;
                    std::cout << "Saving: " << mFileName << std::endl;
                    saveFile(mFileName, block);
                    pushBlockData(block.getBlockName(), block.getLength(), block.getWidth(), block.getHeight());
                    blockIsLoaded = false;
                    newOrOpen = true;
                }
            }
            ImGui::Separator();

            if (ImGui::CollapsingHeader("Camera")) {
                camera camera;
                ImGui::Button("Reload Camera");
                ImGui::SameLine();
                ImGui::Button("Close Camera");
                if(ImGui::Button("Grab Color Frame")){
                    camera.getColorFrame();
                }
                ImGui::SameLine();
                ImGui::Button("Grab Depth Frame");
            }
            ImGui::Separator();

            if (ImGui::CollapsingHeader("Tools")) {
                float tempLength = block.getLength();
                float tempWidth = block.getWidth();
                float tempHeight = block.getHeight();
                ImGui::Text("Block Size Modification");
                ImGui::SliderFloat("Length", &tempLength, 0.0f, 1000.0f);
                block.setLength(tempLength);
                ImGui::SliderFloat("Width", &tempWidth, 0.0f, 1000.0f);
                block.setWidth(tempWidth);
                ImGui::SliderFloat("Height", &tempHeight, 0.0f, 1000.0f);
                block.setHeight(tempHeight);

                ImGui::Separator();
                if(ImGui::Button("Place Drill Hole")){
                    clickBlock = true;
                }
            }
            ImGui::Separator();

            if (ImGui::CollapsingHeader("Help")) {
                std::string xPositionText = "X: ";
                xPositionText = xPositionText + std::to_string(mousePosition.x);

                std::string yPositionText = "Y: ";
                yPositionText = yPositionText + std::to_string(mousePosition.y);
                ImGui::Text(xPositionText.c_str());
                ImGui::Text(yPositionText.c_str());
            }
        }
        ImGui::End();
    }
}

void window::leftViewPane(){

    {
        minimumXYLeftView = ImVec2((2 * mGapSize) + spW, mGapSize);
        maximumXYLeftView = ImVec2(minimumXYLeftView.x + vpW, minimumXYLeftView.y + vpH);

        ImGui::SetNextWindowPos(minimumXYLeftView);
        ImGui::Begin("Left View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImVec2 maxPos = ImVec2(pos.x + block.getLength(), pos.y + block.getHeight());
        block.setLeftMinMax(pos, maxPos);

        if(blockIsLoaded){
            renderObjectToWidget(pos, block.getSideVerts(), block.getHeight(), block.getLength(), false);
        }

        ImGui::End();
    }
}

void window::topViewPane(){
    {
        minimumXYTopView = ImVec2((3 * mGapSize) + spW + vpW, mGapSize);
        maximumXYTopView = ImVec2(minimumXYTopView.x + vpW, minimumXYTopView.y + vpH);

        ImGui::SetNextWindowPos(minimumXYTopView);
        ImGui::Begin("Top View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImVec2 maxPos = ImVec2(pos.x + block.getWidth(), pos.y + block.getLength());
        block.setTopMinMax(pos, maxPos);

        if(blockIsLoaded){
            renderObjectToWidget(pos, block.getTopVerts(), block.getLength(), block.getWidth(), false);
        }
        ImGui::End();
    }
}

void window::frontViewPane(){
    {
        minimumXYFrontView = ImVec2((2 * mGapSize) + spW, (2 * mGapSize) + vpH);
        maximumXYFrontView = ImVec2(minimumXYFrontView.x + vpW, minimumXYFrontView.y + vpH);

        ImGui::SetNextWindowPos(minimumXYFrontView);
        ImGui::Begin("Front View");
        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImVec2 maxPos = ImVec2(pos.x + block.getWidth(), pos.y + block.getHeight());
        block.setFrontMinMax(pos, maxPos);

        if(blockIsLoaded){
            renderObjectToWidget(pos, block.getFrontVerts(), block.getHeight(), block.getWidth(), false);
        }
        ImGui::End();
    }
}

void window::objectViewPane(){
    {
        ImGui::SetNextWindowPos(ImVec2((3 * mGapSize) + spW + vpW, (2 * mGapSize) + vpH));
        ImGui::Begin("Information Pane");

        ImGui::SetWindowSize(ImVec2(vpW, vpH));
        ImGui::Text("Block Name: ");
        ImGui::Text("Block Length: ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(block.getLength()).c_str());
        ImGui::Text("Block Width: " );
        ImGui::SameLine();
        ImGui::Text(std::to_string(block.getWidth()).c_str());
        ImGui::Text("Block Height: ");
        ImGui::SameLine();
        ImGui::Text(std::to_string(block.getHeight()).c_str());

        ImGui::Separator();

        ImGui::Columns(3, NULL, true);
        ImGui::Text("Drill slots on Side View:");
        ImGui::NextColumn();
        ImGui::Text("Drill slots on Top View:");
        ImGui::NextColumn();
        ImGui::Text("Drill slots on Front View:");
        ImGui::NextColumn();



        for(int i = 0; i < block.getSideDrillC(); i++){
            std::string tempLeft = block.getOneDrill(i, block.LEFT);
            ImGui::Text(tempLeft.c_str());
        }

        ImGui::NextColumn();
        for(int i = 0; i < block.getTopDrillC(); i++){
            std::string tempTop = block.getOneDrill(i, block.TOP);
            ImGui::Text(tempTop.c_str());
        }

        ImGui::NextColumn();
        for(int i = 0; i < block.getFrontDrillC(); i++){
            std::string tempFront = block.getOneDrill(i, block.FRONT);
            ImGui::Text(tempFront.c_str());
        }
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

void window::upload(int face){
    ImVec2 temp;
    switch(face){
        case 1:
            for(int i = 0; i < block.getSideDrillC(); i++){
                temp = block.getOneDrillActual(i, block.LEFT);
                pushCutData(mFileName, face, temp.x, temp.y);
                }
            break;
        case 2:
            for(int i = 0; i < block.getTopDrillC(); i++){
                temp = block.getOneDrillActual(i, block.TOP);
                pushCutData(mFileName, face, temp.x, temp.y);
                }
            break;
        case 3:
            for(int i = 0; i < block.getFrontDrillC(); i++){
                temp = block.getOneDrillActual(i, block.FRONT);
                pushCutData(mFileName,face, temp.x, temp.y);
                }
            break;
        default:
            break;
    }

}

int window::whichPanel(ImVec2 mousePosition){
    if(mousePosition.x > minimumXYLeftView.x && mousePosition.y > minimumXYLeftView.y &&
       mousePosition.x < maximumXYLeftView.x && mousePosition.y < maximumXYLeftView.y){
        std::cout << "Mouse is clicked within the left view panel." << std::endl;
        return 1;
    }else if(mousePosition.x > minimumXYTopView.x && mousePosition.y > minimumXYTopView.y &&
             mousePosition.x < maximumXYTopView.x && mousePosition.y < maximumXYTopView.y){
        std::cout << "Mouse is clicked within the top view panel." << std::endl;
        return 2;
    }else if(mousePosition.x > minimumXYFrontView.x && mousePosition.y > minimumXYFrontView.y &&
             mousePosition.x < maximumXYFrontView.x && mousePosition.y < maximumXYFrontView.y){
        std::cout << "Mouse is clicked within the front view panel." << std::endl;
        return 3;
    }else {
        std::cout << "Not clicked within object panels" << std::endl;
        return 0;
    }
}