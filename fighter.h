#include <stdlib.h>
#include <glm/glm.hpp>

struct fighter {
	//position
	glm::vec2 position;
	glm::vec2 dimensions;
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

	fighter(glm::vec2 startingPos, glm::vec2 dimAnal) : position(startingPos), dimensions(dimAnal) {};

	void move() {
		position += velocity;
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