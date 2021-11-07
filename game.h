#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "fighter.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

void doGameTick(double dt);

double getTimer();

bool getOver();

fighter* getPlayer1();
fighter* getPlayer2();

#endif