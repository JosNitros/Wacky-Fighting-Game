#include "game.h"

#define WALKSPEED 5.0
#define RUNSPEED 7.0

fighter* fighter1 = new fighter(glm::vec2(-100.0f, 385.0f));
fighter* fighter2 = new fighter(glm::vec2(975.0f, 385.0f));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto animations = getAnimations();
    if (action == GLFW_PRESS)
    {
        switch (key) {
            case GLFW_KEY_LEFT_SHIFT:
                fighter1->shift = true;
                if (fighter1->velocity.x > 0)
                {
                    fighter1->move(glm::vec2(RUNSPEED, fighter1->velocity.y));
                }
                else if (fighter1->velocity.x < 0)
                {
                    fighter1->move(glm::vec2(-RUNSPEED, fighter1->velocity.y));
                }
                break;
            case GLFW_KEY_A:
                if (fighter1->shift) {
                    fighter1->move(glm::vec2(-RUNSPEED, fighter1->velocity.y));
                }
                else {
                    fighter1->move(glm::vec2(-WALKSPEED, fighter1->velocity.y));
                }
                break;
            case GLFW_KEY_D:
                if (fighter1->shift) {
                    fighter1->move(glm::vec2(RUNSPEED, fighter1->velocity.y));
                }
                else {
                    fighter1->move(glm::vec2(WALKSPEED, fighter1->velocity.y));
                }
                break;
            case GLFW_KEY_RIGHT_SHIFT:
                fighter2->shift = true;
                if (fighter2->velocity.x > 0)
                {
                    fighter2->move(glm::vec2(RUNSPEED, fighter2->velocity.y));
                }
                else if (fighter2->velocity.x < 0)
                {
                    fighter2->move(glm::vec2(-RUNSPEED, fighter2->velocity.y));
                }
                break;
            case GLFW_KEY_J:
                if (fighter2->shift) {
                    fighter2->move(glm::vec2(-RUNSPEED, fighter2->velocity.y));
                }
                else {
                    fighter2->move(glm::vec2(-WALKSPEED, fighter2->velocity.y));
                }
                break;
            case GLFW_KEY_L:
                if (fighter2->shift) {
                    fighter2->move(glm::vec2(RUNSPEED, fighter2->velocity.y));
                }
                else {
                    fighter2->move(glm::vec2(WALKSPEED, fighter2->velocity.y));
                }
                break;
            case GLFW_KEY_S:
                fighter1->block();
                break;

            case GLFW_KEY_K:
                fighter2->block();
                break;

            case GLFW_KEY_W:
                fighter1->attack();
                break;

            case GLFW_KEY_I:
                fighter2->attack();
                break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key) {

            case GLFW_KEY_LEFT_SHIFT:
                fighter1->shift = false;
                if (fighter1->velocity.x > 0)
                {
                    fighter1->move(glm::vec2(WALKSPEED, fighter1->velocity.y));
                }
                else if (fighter1->velocity.x < 0)
                {
                    fighter1->move(glm::vec2(-WALKSPEED, fighter1->velocity.y));
                }
                break;
            case GLFW_KEY_RIGHT_SHIFT:
                fighter2->shift = false;
                if (fighter2->velocity.x > 0)
                {
                    fighter2->move(glm::vec2(WALKSPEED, fighter2->velocity.y));
                }
                else if (fighter2->velocity.x < 0)
                {
                    fighter2->move(glm::vec2(-WALKSPEED, fighter2->velocity.y));
                }
                break;

            case GLFW_KEY_A:
                if (fighter1->velocity.x < 0)
                {
                    fighter1->move(glm::vec2(0.0f, fighter1->velocity.y));
                }
                break;
            case GLFW_KEY_D:
                if (fighter1->velocity.x > 0)
                {
                    fighter1->move(glm::vec2(0.0f, fighter1->velocity.y));
                }
                break;

            case GLFW_KEY_J:
                if (fighter2->velocity.x < 0)
                {
                    fighter2->move(glm::vec2(0.0f, fighter2->velocity.y));
                }
                break;
            case GLFW_KEY_L:
                if (fighter2->velocity.x > 0)
                {
                    fighter2->move(glm::vec2(0.0f, fighter2->velocity.y));
                }
                break;
        }
    }
}

void doGameTick(double dt)
{
    fighter1->update();
    fighter2->update();
}

fighter* getPlayer1()
{
    return fighter1;
}


fighter* getPlayer2()
{
    return fighter2;
}