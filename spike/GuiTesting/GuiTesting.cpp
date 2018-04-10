// ImGui - standalone example application for Glfw + OpenGL 3, using programmable pipeline
// If you are new to ImGui, see examples/README.txt and documentation at the top of imgui.cpp.

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw_gl3.h>

#define IM_ARRAYSIZE(_ARR) ((int)(sizeof(_ARR)/sizeof(*_ARR)))

std::string testDepth(){
//    std::cout << "Test Depth function called!" << std::endl;
    return "Test Depth function called";
}

void getWidthHeight(){
    std::cout << "getWidthHeight function called!" << std::endl;
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}

void multiply(int x, int y){
    std::cout << x * y << std::endl;
}

int main(int, char**)
{
    // Setup window
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()){
        std::cerr << "There was an error initializing glfw please fix!!" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui OpenGL3 example", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    ImGui_ImplGlfwGL3_Init(window, true); //ImGui Bindings for GLFW3
    glViewport(0, 0, 500, 500);

    bool show_test_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImColor(114, 144, 154);
    std::string responseString;

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplGlfwGL3_NewFrame();

        // 1. Show a simple window
        // Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
        {
            static float f = 0.0f;
            static char buf[32] = "input Text";
            ImGui::Text("Hello, world!");
            ImGui::Button("Test BUtton");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        {
            ImGui::Begin("Data Collector");
            if(ImGui::Button("Get depth information")){
                responseString = testDepth();
            }
            ImGui::SameLine();
            ImGui::Text(responseString.c_str());

            if(ImGui::Button("Get length and width of block")){
                getWidthHeight();
            }
            ImGui::End();
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
    ImGui_ImplGlfwGL3_Shutdown();
    glfwTerminate();

    return 0;
}