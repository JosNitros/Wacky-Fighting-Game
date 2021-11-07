#include "game.h"

#define WALKSPEED 5.0
#define RUNSPEED 7.0

fighter* fighter1 = new fighter(glm::vec2(-100.0f, 385.0f),false);
fighter* fighter2 = new fighter(glm::vec2(975.0f, 385.0f),true);
double timer = 90;

bool detect_hit1(fighter* fighter1, fighter* fighter2) {
    return (fighter1->position.x + fighter1->hitbox.position.x + fighter1->hitbox.dimensions.x >= fighter2->position.x + fighter2->hurtbox.position.x && fighter1->hitbox.dimensions.y > 0);
}

bool detect_hit2(fighter* fighter1, fighter* fighter2) {
    return (fighter2->position.x + fighter2->hitbox.position.x <= fighter1->position.x + fighter1->hurtbox.position.x + fighter1->hurtbox.dimensions.x && fighter2->hitbox.dimensions.y > 0);
}

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
    timer -= 1.0 / 60.0;

    fighter1->update();
    fighter2->update();

    bool hit2 = detect_hit1(fighter1, fighter2) && fighter1->attacking;
    bool hit1 = detect_hit2(fighter1, fighter2) && fighter2->attacking;

    if (hit2)
    {
        fighter2->hit();
    }

    if (hit1)
    {
        fighter1->hit();
    }
}

double getTimer()
{
    return timer;
}

fighter* getPlayer1()
{
    return fighter1;
}


fighter* getPlayer2()
{
    return fighter2;
}