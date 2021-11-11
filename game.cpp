#include "game.h"

#define WALKSPEED 5.0
#define RUNSPEED 7.0

fighter* fighter1 = new fighter(glm::vec2(-100.0f, 385.0f), false);
fighter* fighter2 = new fighter(glm::vec2(975.0f, 385.0f), true);
double timer = 99;
bool over = false;

inline bool detect_hit1(fighter* fighter1, fighter* fighter2) {
    return (fighter1->position.x + fighter1->hitbox.position.x + fighter1->hitbox.dimensions.x >= fighter2->position.x + fighter2->hurtbox.position.x
        && fighter1->hitbox.dimensions.y > 0);
}

inline bool detect_hit2(fighter* fighter1, fighter* fighter2) {
    return (fighter2->position.x + fighter2->hitbox.position.x <= fighter1->position.x + fighter1->hurtbox.position.x + fighter1->hurtbox.dimensions.x 
        && fighter2->hitbox.dimensions.y > 0);
}

bool debug = false;
void toggleDebug()
{
    debug = !debug;
};

bool conTroll = false;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS && key == GLFW_KEY_LEFT_CONTROL)
    {
        conTroll = true;
        return;
    }
    else if (action == GLFW_PRESS && key == GLFW_KEY_R && conTroll)
    {
        restart();
        return;
    }
    else if (action == GLFW_PRESS && key == GLFW_KEY_G && conTroll)
    {
        toggleDebug();
        return;
    }

    if (action == GLFW_RELEASE && key == GLFW_KEY_LEFT_CONTROL)
    {
        conTroll = false;
        return;
    }

    if (action == GLFW_PRESS && !over)
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

            case GLFW_KEY_E:
                fighter1->grab();
                break;

            case GLFW_KEY_O:
                fighter2->grab();
                break;
        }
    }
    else if (action == GLFW_RELEASE && !over)
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

            case GLFW_KEY_S:
                fighter1->blocking = false;
                break;

            case GLFW_KEY_K:
                fighter2->blocking = false;
                break;
        }
    }
}

int sframes = 0;
void restart()
{
    sframes = 0;
    delete fighter1;
    delete fighter2;
    fighter1 = new fighter(glm::vec2(-100.0f, 385.0f), false);
    fighter2 = new fighter(glm::vec2(975.0f, 385.0f), true);
    timer = 99;
    over = false;
}

void doGameTick()
{
    if (sframes > 0) sframes--;

    if (over)
    {
        if (fighter1->health <= 0.0)
        {
            if (fighter1->af == (4 * 6) - 1)
            {
                fighter1->af = (4 * 6) - 2;
            }
        }

        if (fighter2->health <= 0.0)
        {
            if (fighter2->af == (4 * 6) - 1)
            {
                fighter2->af = (4 * 6) - 2;
            }
        }
        return;
    }

    timer -= 1.0 / 60.0;

    fighter1->update();
    fighter2->update();

    if (fighter1->blocking) {
        fighter1->stopFrames = 2;
    }
    if (fighter2->blocking) {
        fighter2->stopFrames = 2;
    }

    if (fighter1->blockedATK)
    {
        if (fighter1->af == 3 * 4)
        {
            fighter1->setAnim(getAnimations().at("idle"));
        }
    }

    if (fighter2->blockedATK)
    {
        if (fighter2->af == 3 * 4)
        {
            fighter2->setAnim(getAnimations().at("idle"));
        }
    }


    bool hit2 = detect_hit1(fighter1, fighter2) && (fighter1->attacking ||fighter1->grabbing) ;
    bool hit1 = detect_hit2(fighter1, fighter2) && (fighter2->attacking ||fighter2->grabbing) ;

    if (hit2 && !fighter2->blocking && !fighter2->parrying)
    {
        sframes = 8;
        fighter2->hit();
    }

    if (hit1 && !fighter1->blocking && !fighter1->parrying)
    {
        sframes = 8;
        fighter1->hit();
    }

    if (hit2 && fighter2->blocking && !fighter1->grabbing)
    {
        fighter2->blockedAttack();
    }

    if (hit1 && fighter1->blocking && !fighter2->grabbing)
    {
        fighter1->blockedAttack();
    }
    if (hit1 && fighter2->grabbing)
    {
        fighter1->hit();
    }
    if (hit2 && fighter1->grabbing)
    {
        fighter2->hit();
    }


    if (fighter1->position.x < -160) {
        fighter1->position.x = -160;
    }
    if (fighter2->position.x > 1040) {
        fighter2->position.x = 1040;
    }
    if (fighter1->position.x + 55 > fighter2-> position.x) {
        sframes = 8;
        fighter1->bump();
        fighter2->bump();
    }


    if (fighter1->health <= 0.0 || fighter2->health <= 0.0 || timer <= 0.0)
    {
        timer = -1.0;

        if (fighter1->health <= 0.0)
        {
            fighter1->setAnim(getAnimations().at("death"));
        }
        else
        {
            fighter1->setAnim(getAnimations().at("idle"));
        }

        if (fighter2->health <= 0.0)
        {
            fighter2->setAnim(getAnimations().at("death"));
        }
        else
        {
            fighter2->setAnim(getAnimations().at("idle"));
        }

        over = true;
    }
}

int getShakeFrames()
{
    return sframes;
}

double getTimer()
{
    return timer;
}

bool getOver()
{
    return over;
}

bool getDebug()
{
    return debug;
}

fighter* getPlayer1()
{
    return fighter1;
}

fighter* getPlayer2()
{
    return fighter2;
}