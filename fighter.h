#include <stdlib.h>
#include <glm/glm.hpp>

class fighter {
public:
	//position
	glm::vec2 position;
	glm::vec2 velocity;

	//states
	bool idle;
	bool walk;
	bool run;
	bool isHit;
};
