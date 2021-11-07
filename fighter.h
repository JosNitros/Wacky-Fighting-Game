#include <stdlib.h>
#include <glm/glm.hpp>

struct box {
	glm::vec2 positions;
	glm::vec2 dimensions;
	box(glm::vec2 startingPos, glm::vec2 dim) : positions(startingPos), dimensions(dim) {};
};

struct fighter {
	//position
	glm::vec2 startingposition;
	box hitbox = box(startingposition, glm::vec2(0.0f, 0.0f));
	box hurtbox = box(startingposition, glm::vec2(10.0f, 10.0f));
	glm::vec2 velocity = glm::vec2(10.0f, 10.0f);


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

	fighter(glm::vec2 startingposition) : startingposition(startingposition){};

	void move() {
		hitbox.positions += velocity;
		hurtbox.positions += velocity;
	}

	void setAllFalse() {
		idle = false;
		walk = false;
		run = false;
		shift = false;
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