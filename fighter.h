#include <stdlib.h>
#include <glm/glm.hpp>

#include "animation.h"

struct box {
	glm::vec2 position;
	glm::vec2 dimensions;
	box(glm::vec2 pos, glm::vec2 dim) : position(pos), dimensions(dim) {};
};

struct fighter {
	//position
	glm::vec2 position;
	box hitbox = box(glm::vec2(0.0f), glm::vec2(0.0f));
	box hurtbox = box(glm::vec2(160.0f, 145.0f), glm::vec2(80.0f, 100.0f));
	glm::vec2 velocity = glm::vec2(0.0f);

	unsigned int af = 0;
	animSequence* anim = nullptr;
	
	//states
	bool idle = true;

	bool walk = false;

	//states for running
	bool run = false;
	bool shift = false;
	
	bool isHit = false;

	//combat states
	bool attacking = false;
	bool blocking = false;
	bool parrying = false;
	bool grabbing = false;

	fighter(glm::vec2 position) : position(position) {};

	void draw(int flags)
	{
		if (anim)
		{
			anim->draw(af, position, glm::vec2(400.0f), flags);
		}
		else
		{
			anim = getAnimations().at("idle");
		}
	}

	void move() {
		position += velocity;
	}

	void setAllFalse() {
		idle = false;
		walk = false;
		run = false;
		
		isHit = false;
		attacking = false;
		blocking = false;
		parrying = false;
		grabbing = false;
	}

	void reverseDirection() {
		velocity *= -1;
	}

};