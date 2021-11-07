#include "fighter.h"

fighter::fighter(glm::vec2 position) :
	position(position) {};

void fighter::move(glm::vec2 vel)
{
	if (stopFrames == 0)
	{
		velocity = vel;
		if (vel.x > 0)
		{
			setAnim(getAnimations().at("run"));
		}
		else if (vel.x < 0)
		{
			setAnim(getAnimations().at("run"));
		}
		else
		{
			setAnim(getAnimations().at("idle"));
		}
	}
}

void fighter::attack()
{
	if (stopFrames == 0)
	{
		attacking = true;
		velocity.x = 0.0f;
		setAnim(getAnimations().at("attack1"));
		stopFrames = 8 * 4;
	}
}

void fighter::block()
{
	if (stopFrames == 0)
	{
		blocking = true;
		velocity.x = 0.0f;
		setAnim(getAnimations().at("death"));
		stopFrames = 8 * 4;
	}
}

void fighter::draw(int flags)
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

void fighter::update() {
	position += velocity;
	if (stopFrames > 1)
	{
		stopFrames--;
	}
	else if (stopFrames == 1)
	{
		stopFrames = 0;
		setAnim(getAnimations().at("idle"));
		attacking = false;
		blocking = false;
	}
}

void fighter::setAnim(animSequence* animS)
{
	anim = animS;
	af = 0;
}