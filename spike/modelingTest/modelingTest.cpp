#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>

#define SCREEN_WIDTH  1920
#define SCREEN_HEIGHT  1080
#define TOTAL_DEPTH 500

struct centerPosition {
    GLfloat x = SCREEN_WIDTH / 2.0f;
    GLfloat y = SCREEN_HEIGHT / 2.0f;
    GLfloat z = -(TOTAL_DEPTH);
} blockPos;

struct centerPositionFilled {
    GLfloat x = SCREEN_WIDTH / 4.0f;
    GLfloat y = SCREEN_HEIGHT / 4.0f;
    GLfloat z = -(TOTAL_DEPTH);
} blockPosFilled;

struct dimensions {
    GLfloat depth;
    GLfloat length;
    GLfloat width;
} block;



void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

void renderBlock(centerPosition bPos, dimensions block);
void renderBlockFilled(centerPositionFilled bPos, dimensions block);
void DrawCircle(float cx, float cy, float r, int num_segments);


GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;

int main() {
    std::cout << "Input the blocks depth" << std::endl;
    std::cin >> block.depth;
    std::cout << "Input the blocks width" << std::endl;
    std::cin >> block.width;
    std::cout << "input the blocks length" << std::endl;
    std::cin >> block.length;

    GLFWwindow *window;
    if (!glfwInit()) {
        std::cerr << " There was an issue initializing GLFW" << std::endl;
        return -1;
    }

    //Window creation
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Model Testing", nullptr, nullptr);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // The section of the window openGL will display to
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Sets the matrix mode to projection which is used for camera manipulation; from what I can tell
    glMatrixMode(GL_PROJECTION);
    // Loads the matrix with the identity matrxi
    glLoadIdentity();
    // Sets up the camera info
    // Param 1: left clipping plane
    // Param 2: Right clipping plane
    // Param 3: Bottom clipping plane
    // Param 4; top clipping plane
    // Param 5 depth clipping plane
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000);

    glMatrixMode(
            GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world
    glLoadIdentity(); // same as above comment

    // While window open
    while (!glfwWindowShouldClose(window)) {
        // Clears the buffer to the preset values
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, -500);
        glRotatef(rotationX, 1, 0, 0);
        glRotatef(rotationY, 0, 1, 0);
        glTranslatef(-(SCREEN_WIDTH / 2), -(SCREEN_HEIGHT / 2), 500);

        //Calls Draw blocks to calculate and render the block
        //Param 1: block position struct
        // Param 2: Block dimensions struct
        //renderBlock(blockPos, block);

        DrawCircle(500, 500, 300, 22);

        //renderBlockFilled(blockPosFilled, block);

        glPopMatrix();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        //Events bullshit
        glfwPollEvents();
    }
    //Cleanup
    glfwTerminate();
    return 0;
}


void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    const GLfloat rotationSpeed = 20;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch (key) {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                break;
        }
    }
}

void renderBlock(centerPosition bPos, dimensions block) {


    GLfloat vertices[] = {
            //Front face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left

            //Back face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Left

            //Left face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top left
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left

            //Right face
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Left

            //Top face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left

            //back face
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left
    };

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
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    //Render primitives from array data
    // Param 1: Mode
    // Param 2: first index of array
    // Param 3: number of indicies to render
    glDrawArrays(GL_QUADS, 0, 24);

    // Closes the client state
    glDisableClientState(GL_VERTEX_ARRAY);

}

void DrawCircle(GLfloat centerX, GLfloat centerY, GLfloat radius, int num_segments)
{
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    float PI = 3.14159;
    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // center of circle
    for(i = 0; i <= triangleAmount;i++) {
        glVertex2f(
                centerX + (radius * cos(i *  twicePi / num_segments)),
                centerY + (radius * sin(i * twicePi / num_segments))
        );
    }
    glEnd();
}


void renderBlockFilled(centerPositionFilled bPos, dimensions block) {
    GLfloat vertices[] = {
            //Front face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left

            //Back face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Left

            //Left face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top left
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left

            //Right face
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Bot Left

            //Top face
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y + (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left

            //back face
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top left
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z - (0.5f * block.depth), // Top Right
            bPos.x + (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Right
            bPos.x - (0.5f * block.length), bPos.y - (0.5f * block.width), bPos.z + (0.5f * block.depth), // Bot Left
    };

    // Front and Back is for front and back facing polygons
    // GL_LINE is how the polygons are rastarized
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Enables the vertex array for writing and rendering
    glEnableClientState(GL_VERTEX_ARRAY);

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

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

}
