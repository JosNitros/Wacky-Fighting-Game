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
		if (facingLeft)
		{
			//hitbox.dimensions.x = 230;
			//hitbox.dimensions.y = 100;
			//hitbox.position.x -= 150;
			hurtbox.position.x -= 90;

			hurtbox.dimensions.x = 170;
		}
		else
		{
			//hitbox.dimensions.x = 230;
			//hitbox.dimensions.y = 100;
			hurtbox.dimensions.x = 170;
		}

		setAnim(getAnimations().at("attack2"));
		stopFrames = 8 * 4;
	}
}

void fighter::grab()
{
	if (stopFrames == 0)
	{
		grabbing = true;
		velocity.x = 0.0f;
		if (facingLeft)
		{
			//hitbox.dimensions.x = 230;
			//hitbox.dimensions.y = 100;
			//hitbox.position.x -= 150;

			hurtbox.position.x -= 90;
			hurtbox.dimensions.x = 170;
		}
		else
		{
			//hitbox.dimensions.x = 230;
			//hitbox.dimensions.y = 100;
			hurtbox.dimensions.x = 170;
		}

		setAnim(getAnimations().at("attack1"));
		stopFrames = 38;
	}
}

void fighter::block()
{
	if (stopFrames == 0)
	{
		blocking = true;
		velocity.x = 0.0f;
		setAnim(getAnimations().at("idle"));
		stopFrames = 5;
	}
}

void fighter::blockedAttack()
{
		velocity.x = 0.0f;
		setAnim(getAnimations().at("takehit"));
		if (!facingLeft) {
			position += glm::vec2(-40.0f, 0.0f);

		}
		else {
			position += glm::vec2(40.0f, 0.0f);
		}
		stopFrames = 13;
		blockedATK = true;
}

void fighter::bump()
{
	if (stopFrames == 0) {
		velocity.x = 0.0f;
		setAnim(getAnimations().at("takehit"));
		if (!facingLeft) {
			position += glm::vec2(-40.0f, 0.0f);
			
		}
		else {
			position += glm::vec2(40.0f, 0.0f);
		}
		stopFrames = 16;
	}
}

void fighter::hit()
{
	if (!isHit)
	{
		if (facingLeft)
		{
			position += glm::vec2(70.0f, 0.0);
			velocity.x = 0.0f;
		}
		else
		{
			position -= glm::vec2(70.0f, 0.0);
			velocity.x = 0.0f;
		}

		isHit = true;
		attacking = false;
		blocking = false;
		parrying = false;
		health -= 10.0f;
		setAnim(getAnimations().at("takehitW"));
		stopFrames = 20;
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
		if (attacking && facingLeft && stopFrames == 20) {
			hitbox.position.x -= 140;
		}

		if (attacking && facingLeft && stopFrames <= 20) {
			hitbox.dimensions.x = 220;
			hitbox.dimensions.y = 100;
		}

		if (attacking && !facingLeft && stopFrames <= 20) {
			hitbox.dimensions.x = 220;
			hitbox.dimensions.y = 100;
		}
		if (attacking && stopFrames <= 15) {
			hitbox = box(glm::vec2(160.0f, 145.0f), glm::vec2(0.0f));
		}

		if (grabbing && facingLeft && stopFrames == 20) {
			hitbox.position.x -= 90;
		}

		if (grabbing && facingLeft && stopFrames <= 20) {
			hitbox.dimensions.x = 170;
			hitbox.dimensions.y = 100;
		}
		if (grabbing && !facingLeft && stopFrames <= 20) {
			hitbox.dimensions.x = 170;
			hitbox.dimensions.y = 100;
		}

		if (grabbing && stopFrames <= 15) {
			hitbox = box(glm::vec2(160.0f, 145.0f), glm::vec2(0.0f));
		}


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
		isHit = false;
		grabbing = false;
		parrying = false;
	}
}

void fighter::setAnim(animSequence* animS)
{
	anim = animS;
	af = 0;
	blockedATK = false;
}