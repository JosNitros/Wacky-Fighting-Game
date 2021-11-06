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
	bool run = false;
	bool isHit = false;

	fighter(glm::vec2 startingPos, glm::vec2 dimAnal) : position(startingPos), dimensions(dimAnal) {};

	void move() {
		position += velocity;
	}

	void reverseDirection() {
		velocity *= -1;
	}

};