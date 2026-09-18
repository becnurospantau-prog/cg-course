#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

const int WIDTH  = 1280;
const int HEIGHT = 720;

bool whiteBackground = false;
bool spaceWasPressed = false;

void onResize(GLFWwindow*, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    bool spacePressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    if (spacePressed && !spaceWasPressed) {
        whiteBackground = !whiteBackground;
    }
    spaceWasPressed = spacePressed;
}

int main() {

    if (!glfwInit()) {
        std::cerr << "GLFW iske qosylmady\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT,
                                          "Kompyuterlik grafika",
                                          nullptr, nullptr);
    if (!window) {
        std::cerr << "Tereze zhasalmady.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, onResize);
    glfwSwapInterval(0);

    if (gladLoadGL(glfwGetProcAddress) == 0) {
        std::cerr << "GLAD zhuktelmedi\n";
        glfwTerminate();
        return -1;
    }

    std::cout << "OpenGL: " << glGetString(GL_VERSION) << "\n";
    std::cout << "GPU:    " << glGetString(GL_RENDERER) << "\n";

    int frameCount = 0;
    double lastFpsTime = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {

        processInput(window);

        if (whiteBackground) {
            glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        } else {
            float t = (float)glfwGetTime();
            float r = (std::sin(t * 2.0f) + 1.0f) * 0.5f * 0.3f;
            float g = (std::sin(t * 1.3f) + 1.0f) * 0.5f * 0.3f;
            glClearColor(r, g, 0.35f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

        frameCount++;
        double now = glfwGetTime();
        if (now - lastFpsTime >= 1.0) {
            std::cout << "FPS: " << frameCount << "\n";
            frameCount = 0;
            lastFpsTime = now;
        }
    }

    glfwTerminate();
    return 0;
}
