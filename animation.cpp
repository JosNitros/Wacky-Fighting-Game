#include "animation.h"

#include "shaders.h"

#include <glm/gtc/matrix_transform.hpp>

frame::frame(texture2D* image, unsigned int cframe, unsigned int frames) :
	image(image), cframe(cframe), frames(frames) {}

void frame::draw(glm::vec2 pos, glm::vec2 scale, int flags)
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
	shader.setInt("flags", flags);
	
	glBindTexture(GL_TEXTURE_2D, image->ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void animSequence::update(unsigned int& curFrame)
{
	++curFrame %= sequence.size() << 2;
}

void animSequence::draw(unsigned int& curFrame, glm::vec2 pos, glm::vec2 scale, int flags)
{
	sequence[curFrame >> 2]->draw(pos, scale, flags);
	update(curFrame);
}

#define ATTACK1_FRAMES 6
#define ATTACK2_FRAMES 6
#define DEATH_FRAMES 6
#define FALL_FRAMES 2
#define IDLE_FRAMES 8
#define JUMP_FRAMES 2
#define RUN_FRAMES 8
#define TAKEHIT_FRAMES 4
#define TAKEHITW_FRAMES 4
std::map<std::string, animSequence*> animations;
void loadAnimations()
{
	auto textures = getTextures();

	texture2D* anim = &textures->at("attack1");
	animSequence* tmpA = new animSequence();
	frame* tmp;
	for (unsigned int i = 0; i < ATTACK1_FRAMES; i++)
	{
		tmp = new frame(anim, i, ATTACK1_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("attack1", tmpA));

	anim = &textures->at("attack2");
	tmpA = new animSequence();
	for (unsigned int i = 0; i < ATTACK2_FRAMES; i++)
	{
		tmp = new frame(anim, i, ATTACK2_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("attack2", tmpA));

	anim = &textures->at("death");
	tmpA = new animSequence();
	for (unsigned int i = 0; i < DEATH_FRAMES; i++)
	{
		tmp = new frame(anim, i, DEATH_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("death", tmpA));

	anim = &textures->at("idle");
	tmpA = new animSequence();
	for (unsigned int i = 0; i < IDLE_FRAMES; i++)
	{
		tmp = new frame(anim, i, IDLE_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("idle", tmpA));

	anim = &textures->at("run");
	tmpA = new animSequence();
	for (unsigned int i = 0; i < RUN_FRAMES; i++)
	{
		tmp = new frame(anim, i, RUN_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("run", tmpA));

	anim = &textures->at("takehit");
	tmpA = new animSequence();
	for (unsigned int i = 0; i < TAKEHIT_FRAMES; i++)
	{
		tmp = new frame(anim, i, TAKEHIT_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("takehit", tmpA));

	anim = &textures->at("takehitW");
	tmpA = new animSequence();
	for (unsigned int i = 0; i < TAKEHITW_FRAMES; i++)
	{
		tmp = new frame(anim, i, TAKEHITW_FRAMES);
		tmpA->sequence.push_back(tmp);
	}
	animations.insert(std::pair<std::string, animSequence*>("takehitW", tmpA));

}

std::map<std::string, animSequence*>& getAnimations()
{
	return animations;
}