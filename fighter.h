#ifndef FIGHTER_H
#define FIGHTER_H

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

	bool shift = false;
	
	bool isHit = false;

	//combat states
	bool attacking = false;
	bool blocking = false;
	bool parrying = false;
	bool grabbing = false;

	unsigned int stopFrames = 0;

	fighter(glm::vec2 position);

	void move(glm::vec2 vel);

	void attack();

	void block();

	void draw(int flags);

	void update();

	void setAnim(animSequence* animS);
};
#endif