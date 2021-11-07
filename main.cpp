#include <iostream>
#include <thread>



#include "game.h"
#include "render.h"

#define TARGET_FPS 60

GLFWwindow* window;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "TEST", NULL, NULL);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW windows" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetKeyCallback(window, key_callback);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    initRenderer();

    int frames = 0;
    int fps = 0;

    double gameTime = glfwGetTime();
    double frameTimer = gameTime;
    double nowTime = gameTime;

    double dt = 0;
    const float dtMod = 1.0f;
    while (!glfwWindowShouldClose(window))
    {

        nowTime = glfwGetTime();

        dt = (nowTime - gameTime);
        dt *= dtMod;
        if (dt > 1)
            dt = 1; //this limit prevents teleporting through walls
        gameTime = nowTime;

        if (nowTime - frameTimer >= 1)
        {
            frameTimer += 1;
            fps = frames;

            std::cout << fps << '\n';

            frames = 0;
        }

        doGameTick(dt);
        render();

        glfwSwapBuffers(window);

        double expectedFrame = (nowTime - frameTimer) * TARGET_FPS;
        if (frames > expectedFrame)
        {
            long fix = floor((frames - expectedFrame) * (1000.0 / TARGET_FPS));
            std::this_thread::sleep_for(std::chrono::milliseconds(fix));
        }

        glfwPollEvents();

        frames++;
    }

    glfwTerminate();
	return 0;
}