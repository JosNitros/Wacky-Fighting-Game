#ifndef ANIMATION_H
#define ANIMATION_H

#include "texture.h"

#include <glm/glm.hpp>

#include <vector>
#include <map>

struct frame
{
	texture2D* image;
	unsigned int cframe;
	unsigned int frames;

	frame(texture2D* image, unsigned int cframe, unsigned int frames);

	void draw(glm::vec2 pos, glm::vec2 scale, int flags = 0);
};

struct animSequence
{
	std::vector<frame*> sequence;

	void update(unsigned int& curFrame);

	void draw(unsigned int& curFrame, glm::vec2 pos, glm::vec2 scale, int flags = 0);
};

void loadAnimations();

std::map<std::string, animSequence*>& getAnimations();

#endif