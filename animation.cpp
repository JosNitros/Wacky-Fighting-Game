#include "animation.h"

#include "shaders.h"

#include <glm/gtc/matrix_transform.hpp>

frame::frame(texture2D* image, unsigned int cframe, unsigned int frames) :
	image(image), cframe(cframe), frames(frames) {}

void frame::draw(glm::vec2 pos, glm::vec2 scale)
{
	auto shader = getShaders()->at("animation");
	shader.use();

	glm::mat2 dframe = { {1.0f / frames, 0.0}, {0.0, 1.0f} };
	shader.setMat2("frameM", dframe);

	float df = (float)(cframe) / (float)(frames);
	shader.setFloat("frame", df);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(pos, 0.0f));
	model = glm::scale(model, glm::vec3(scale, 1.0f));

	shader.setMat4("model", model);
	
	glBindTexture(GL_TEXTURE_2D, image->ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void animSequence::update(unsigned int& curFrame)
{
	++curFrame %= sequence.size() * 4;
}

void animSequence::draw(unsigned int& curFrame, glm::vec2 pos, glm::vec2 scale)
{
	sequence[floor(curFrame / 4.0)]->draw(pos, scale);
	update(curFrame);
}

std::map<std::string, animSequence*> animations;
void loadAnimations()
{
	auto textures = getTextures();
	auto attack1 = &textures->at("attack1");
	animSequence* tmpA = new animSequence();
	frame* tmp = new frame(attack1, 0, 6);
	tmpA->sequence.push_back(tmp);
	tmp = new frame(attack1, 1, 6);
	tmpA->sequence.push_back(tmp);
	tmp = new frame(attack1, 2, 6);
	tmpA->sequence.push_back(tmp);
	tmp = new frame(attack1, 3, 6);
	tmpA->sequence.push_back(tmp);
	tmp = new frame(attack1, 4, 6);
	tmpA->sequence.push_back(tmp);
	tmp = new frame(attack1, 5, 6);
	tmpA->sequence.push_back(tmp);
	animations.insert(std::pair<std::string, animSequence*>("attack1", tmpA));
}

std::map<std::string, animSequence*>& getAnimations()
{
	return animations;
}