#include "game.h"
#include "fighter.h"

fighter* fighter1 = new fighter(glm::vec2(10.0f, 10.0f), glm::vec2(10.0f, 10.0f));

fighter* fighter2 = new fighter(glm::vec2(10.0f, 10.0f), glm::vec2(10.0f, 10.0f));


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {

    case GLFW_KEY_A:
        if (fighter1->shift) {
            //faster running velocity; goes left
            fighter1->velocity = glm::vec2(10.0f, 0.0f);
            fighter1->setAllFalse();
            fighter1->shift = true;
            fighter1->run = true;
            
        }
        else {
            //slower walking velocity; goes left
            fighter1->velocity = glm::vec2(10.0f, 0.0f);
            fighter1->setAllFalse();
            fighter1->walk = true;
        }

        break;

    case GLFW_KEY_D:
        if (fighter1->shift) {
            //faster running velocity; goes right
            fighter1->velocity = glm::vec2(10.0f, 0.0f);
            fighter1->setAllFalse();
            fighter1->shift = true;
            fighter1->run = true;

        }
        else {
            //slower walking velocity; goes right
            fighter1->velocity = glm::vec2(10.0f, 0.0f);
            fighter1->setAllFalse();
            fighter1->walk = true;
        }
        break;

    case GLFW_KEY_J:
        if (fighter2->shift) {
            //faster running velocity; goes left
            fighter2->velocity = glm::vec2(10.0f, 0.0f);
            fighter2->setAllFalse();
            fighter2->shift = true;
            fighter2->run = true;

        }
        else {
            //slower walking velocity; goes left
            fighter2->velocity = glm::vec2(10.0f, 0.0f);
            fighter2->setAllFalse();
            fighter2->walk = true;
        }
        break;

    case GLFW_KEY_L:
        if (fighter2->shift) {
            //faster running velocity; goes right
            fighter2->velocity = glm::vec2(10.0f, 0.0f);
            fighter2->setAllFalse();
            fighter2->shift = true;
            fighter2->run = true;

        }
        else {
            //slower walking velocity; goes right
            fighter2->velocity = glm::vec2(10.0f, 0.0f);
            fighter2->setAllFalse();
            fighter2->walk = true;
        }
        break;


    case GLFW_KEY_S:
        fighter1->velocity = glm::vec2(0.0f, 0.0f);
        fighter1->setAllFalse();
        fighter1->blocking = true;
        
        break;

    case GLFW_KEY_K:
        fighter2->velocity = glm::vec2(0.0f, 0.0f);
        fighter2->setAllFalse();
        fighter2->blocking = true;

        break;

    case GLFW_KEY_W:
        fighter1->velocity = glm::vec2(0.0f, 0.0f);
        fighter1->setAllFalse();
        fighter1->attacking = true;

        break;

    case GLFW_KEY_I:
        fighter2->velocity = glm::vec2(0.0f, 0.0f);
        fighter2->setAllFalse();
        fighter2->attacking = true;

        break;
    }


}

void doGameTick(double dt)
{

}