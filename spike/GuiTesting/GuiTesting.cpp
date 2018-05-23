// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR)/sizeof(*_ARR)))

std::string testDepth() {
//    std::cout << "Test Depth function called!" << std::endl;
    return "Test Depth function called";
}

void getWidthHeight() {
    std::cout << "getWidthHeight function called!" << std::endl;
}

static void error_callback(int error, const char *description) {
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void multiply(int x, int y) {
    std::cout << x * y << std::endl;
}

GLuint renderToWidget(){
    float vertices[] = {
            // positions         // colors
            0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
            0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };

//create a vao,vbo
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

// color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    GLuint fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

    // Enables the vertex array for writing and rendering

    glEnableClientState(GL_VERTEX_ARRAY);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    //Defines an array of vertext data
    // Param 1: 3 for the number of coordinates for each vertext (x, y, z)
    // Param 2: GL_Float for the data type
    // Param 3: 0 for no byte offset between consecutive vertices
    // Param 4: the verticies themselves
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    //Render primitives from array data
    // Param 1: Mode
    // Param 2: first index of array
    // Param 3: number of indicies to render
    glDrawArrays(GL_QUADS, 0, 24);

    // Closes the client state
    glDisableClientState(GL_VERTEX_ARRAY);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    return fbo;
}

int main(int, char **) {
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "There was an error initializing glfw please fix!!" << std::endl;
        return -1;
    }
    //glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    ImGui_ImplGlfwGL3_Init(window, true); //ImGui Bindings for GLFW3


    GLuint renderedTexture;
    glGenTextures(1, &renderedTexture);
    glBindTexture(GL_TEXTURE_2D, renderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    renderedTexture= renderToWidget();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glClear(GL_CLEAR_BUFFER);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //When complete

    //glViewport(0, 0, 500, 500);

    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
    std::string responseString;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplGlfwGL3_NewFrame();

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        ImGui::SetNextWindowPos(ImVec2(10,10));
        {
            ImGui::Begin("Debug Panel");
            ImGui::SetWindowSize(ImVec2(100,100));
            static float f = 0.0f;
            static char buf[32] = "input Text";
            ImGui::Text("Hello, world!");
            ImGui::Button("Test BUtton");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(10,100));
        {
            ImGui::Begin("Data Collector");
            if (ImGui::Button("Get depth information")) {
                responseString = testDepth();
            }
            ImGui::SameLine();
            ImGui::Text(responseString.c_str());

            if (ImGui::Button("Get length and width of block")) {
                getWidthHeight();
            }
            ImGui::End();
        }

        ImGui::SetNextWindowPos(ImVec2(300, 10));
        {
            ImGui::Begin("Game rendering");
            {
                    // Get the current cursor position (where your window is)
                    ImVec2 pos = ImGui::GetCursorScreenPos();

                    // Ask ImGui to draw it as an image:
                    // Under OpenGL the ImGUI image type is GLuint
                    // So make sure to use "(void *)tex" but not "&tex"
                    ImGui::GetWindowDrawList()->AddImage(
                            (void *)renderedTexture, ImVec2(ImGui::GetItemRectMin().x + pos.x,
                                                            ImGui::GetItemRectMin().y + pos.y),
                            ImVec2(pos.x + 640 / 2, pos.y + 600 / 2), ImVec2(0, 1), ImVec2(1, 0));

            }
            ImGui::End();

            glBindFramebuffer(GL_FRAMEBUFFER, 0);

        }

        // Rendering
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui::Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Closing up
    glDeleteFramebuffers(1, &renderedTexture);

    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}