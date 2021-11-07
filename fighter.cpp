#include "fighter.h"

fighter::fighter(glm::vec2 position, bool facingLeft) :
	position(position), facingLeft(facingLeft) {};

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
			setAnim(getAnimations().at("run")); //@ TODO reverse
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
		if (facingLeft)
		{
			hitbox.position.x -= 150;
			hurtbox.position.x -= 90;

			hitbox.dimensions.x = 230;
			hitbox.dimensions.y = 100;
			hurtbox.dimensions.x = 170;
		}
		else
		{
			hitbox.dimensions.x = 230;
			hitbox.dimensions.y = 100;
			hurtbox.dimensions.x = 170;
		}

		setAnim(getAnimations().at("attack2"));
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
		hitbox = box(glm::vec2(160.0f, 145.0f), glm::vec2(0.0f));
		hurtbox = box(glm::vec2(160.0f, 145.0f), glm::vec2(80.0f, 100.0f));
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