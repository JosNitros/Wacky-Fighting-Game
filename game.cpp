#include "game.h"

#define WALKSPEED 5.0
#define RUNSPEED 7.0

fighter* fighter1 = new fighter(glm::vec2(-100.0f, 300.0f));
fighter* fighter2 = new fighter(glm::vec2(975.0f, 300.0f));

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto animations = getAnimations();
    if (action == GLFW_PRESS)
    {
        switch (key) {

            case GLFW_KEY_LEFT_SHIFT:
                fighter1->shift = true;
                if (fighter1->velocity.x > 0)
                {
                    fighter1->velocity.x = RUNSPEED;
                    fighter1->anim = animations.at("run");
                    fighter1->af = 0;
                    fighter1->run = true;
                    fighter1->walk = false;
                }
                else if (fighter1->velocity.x < 0)
                {
                    fighter1->velocity.x = -RUNSPEED;
                    fighter1->anim = animations.at("run");
                    fighter1->af = 0;
                    fighter1->run = true;
                    fighter1->walk = false;
                }
                break;
            case GLFW_KEY_A:
                if (fighter1->shift) {
                    //faster running velocity; goes left
                    fighter1->velocity = glm::vec2(-RUNSPEED, 0.0f);
                    fighter1->anim = animations.at("run");
                    fighter1->af = 0;
                    fighter1->setAllFalse();
                    fighter1->shift = true;
                    fighter1->run = true;

                }
                else {
                    //slower walking velocity; goes left
                    fighter1->velocity = glm::vec2(-WALKSPEED, 0.0f);
                    fighter1->anim = animations.at("run");
                    fighter1->af = 0;
                    fighter1->setAllFalse();
                    fighter1->walk = true;
                }
                break;

            case GLFW_KEY_D:
                if (fighter1->shift) {
                    //faster running velocity; goes right
                    fighter1->velocity = glm::vec2(RUNSPEED, 0.0f);
                    fighter1->anim = animations.at("run");
                    fighter1->af = 0;
                    fighter1->setAllFalse();
                    fighter1->shift = true;
                    fighter1->run = true;

                }
                else {
                    //slower walking velocity; goes right
                    fighter1->velocity = glm::vec2(WALKSPEED, 0.0f);
                    fighter1->anim = animations.at("run");
                    fighter1->af = 0;
                    fighter1->setAllFalse();
                    fighter1->walk = true;
                }
                break;

            case GLFW_KEY_RIGHT_SHIFT:
                fighter2->shift = true;
                if (fighter2->velocity.x > 0)
                {
                    fighter2->velocity.x = RUNSPEED;
                    fighter2->anim = animations.at("run");
                    fighter2->af = 0;
                    fighter2->run = true;
                    fighter2->walk = false;
                }
                else if (fighter2->velocity.x < 0)
                {
                    fighter2->velocity.x = -RUNSPEED;
                    fighter2->anim = animations.at("run");
                    fighter2->af = 0;
                    fighter2->run = true;
                    fighter2->walk = false;
                }
                break;
            case GLFW_KEY_J:
                if (fighter2->shift) {
                    //faster running velocity; goes left
                    fighter2->velocity = glm::vec2(-RUNSPEED, 0.0f);
                    fighter2->anim = animations.at("run");
                    fighter2->af = 0;
                    fighter2->setAllFalse();
                    fighter2->shift = true;
                    fighter2->run = true;

                }
                else {
                    //slower walking velocity; goes left
                    fighter2->velocity = glm::vec2(-WALKSPEED, 0.0f);
                    fighter2->anim = animations.at("run");
                    fighter2->af = 0;
                    fighter2->setAllFalse();
                    fighter2->walk = true;
                }
                break;

            case GLFW_KEY_L:
                if (fighter2->shift) {
                    //faster running velocity; goes right
                    fighter2->velocity = glm::vec2(RUNSPEED, 0.0f);
                    fighter2->anim = animations.at("run");
                    fighter2->af = 0;
                    fighter2->setAllFalse();
                    fighter2->shift = true;
                    fighter2->run = true;

                }
                else {
                    //slower walking velocity; goes right
                    fighter2->velocity = glm::vec2(WALKSPEED, 0.0f);
                    fighter2->anim = animations.at("run");
                    fighter2->af = 0;
                    fighter2->setAllFalse();
                    fighter2->walk = true;
                }
                break;


            case GLFW_KEY_S:
                fighter1->velocity = glm::vec2(0.0f, 0.0f);
                fighter1->anim = animations.at("idle");
                fighter1->af = 0;
                fighter1->setAllFalse();
                fighter1->blocking = true;

                break;

            case GLFW_KEY_K:
                fighter2->velocity = glm::vec2(0.0f, 0.0f);
                fighter2->anim = animations.at("idle");
                fighter2->af = 0;
                fighter2->setAllFalse();
                fighter2->blocking = true;

                break;

            case GLFW_KEY_W:
                fighter1->velocity = glm::vec2(0.0f, 0.0f);
                fighter1->anim = animations.at("idle");
                fighter1->af = 0;
                fighter1->setAllFalse();
                fighter1->attacking = true;

                break;

            case GLFW_KEY_I:
                fighter2->velocity = glm::vec2(0.0f, 0.0f);
                fighter2->anim = animations.at("idle");
                fighter2->af = 0;
                fighter2->setAllFalse();
                fighter2->attacking = true;

                break;
        }
    }
    else if (action == GLFW_RELEASE)
    {
        switch (key) {

            case GLFW_KEY_LEFT_SHIFT:
                fighter1->shift = false;
                if (fighter1->run)
                {
                    if (fighter1->velocity.x > 0)
                    {
                        fighter1->velocity.x = WALKSPEED;
                        fighter1->anim = animations.at("run");
                        fighter1->af = 0;
                        fighter1->walk = true;
                        fighter1->run = false;
                    }
                    else if (fighter1->velocity.x < 0)
                    {
                        fighter1->velocity.x = -WALKSPEED;
                        fighter1->anim = animations.at("run");
                        fighter1->af = 0;
                        fighter1->walk = true;
                        fighter1->run = false;
                    }
                }
                break;
            case GLFW_KEY_RIGHT_SHIFT:
                fighter2->shift = false;
                if (fighter2->run)
                {
                    if (fighter2->velocity.x > 0)
                    {
                        fighter2->velocity.x = WALKSPEED;
                        fighter2->anim = animations.at("run");
                        fighter2->af = 0;
                        fighter2->walk = true;
                        fighter2->run = false;
                    }
                    else if (fighter2->velocity.x < 0)
                    {
                        fighter2->velocity.x = -WALKSPEED;
                        fighter2->anim = animations.at("run");
                        fighter2->af = 0;
                        fighter2->walk = true;
                        fighter2->run = false;
                    }
                }
                break;

            case GLFW_KEY_A:
                if (fighter1->velocity.x < 0)
                {
                    fighter1->velocity.x = 0.0;
                    fighter1->anim = animations.at("idle");
                    fighter1->af = 0;
                    fighter1->walk = false;
                    fighter1->run = false;
                }
                break;
            case GLFW_KEY_D:
                if (fighter1->velocity.x > 0)
                {
                    fighter1->velocity.x = 0.0;
                    fighter1->anim = animations.at("idle");
                    fighter1->af = 0;
                    fighter1->walk = false;
                    fighter1->run = false;
                }
                break;

            case GLFW_KEY_J:
                if (fighter2->velocity.x < 0)
                {
                    fighter2->velocity.x = 0.0;
                    fighter2->anim = animations.at("idle");
                    fighter2->af = 0;
                    fighter2->walk = false;
                    fighter2->run = false;
                }
                break;
            case GLFW_KEY_L:
                if (fighter2->velocity.x > 0)
                {
                    fighter2->velocity.x = 0.0;
                    fighter2->anim = animations.at("idle");
                    fighter2->af = 0;
                    fighter2->walk = false;
                    fighter2->run = false;
                }
                break;
        }
    }
}

void doGameTick(double dt)
{
    fighter1->move();
    fighter2->move();
}

fighter* getPlayer1()
{
    return fighter1;
}


fighter* getPlayer2()
{
    return fighter2;
}