#include "render.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaders.h"
#include "texture.h"
#include "text.h"
#include "animation.h"

#include "game.h"

const float vertices[] = {
	0.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,

	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f
};

unsigned int VAO, VBO, FBO;
unsigned int FBOtexture;

std::map<GLchar, Char> font;
void initRenderer()
{
	font = loadFont("assets/fonts/Lato/Lato-Black.ttf");

	compileShaders();
	loadTextures();
	loadAnimations();

	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	glGenTextures(1, &FBOtexture);
	glBindTexture(GL_TEXTURE_2D, FBOtexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1280, 720, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FBOtexture, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void drawBox(box& obj, glm::vec4 color)
{
	auto shader = getShaders()->at("box");

	shader.use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(obj.position, 0.0f));
	model = glm::scale(model, glm::vec3(obj.dimensions, 1.0f));

	shader.setMat4("model", model);

	shader.setVec4("color", color);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawBG()
{
	auto bg = getTextures()->at("background");
	auto shdr = getShaders()->at("image");

	shdr.use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1280.0f, 720, 1.0f));

	shdr.setMat4("model", model);
	
	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, bg.ID);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void drawGame()
{
	auto shaders = getShaders();
	auto textures = getTextures();
	auto animations = getAnimations();
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(1.0f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawBG();

	fighter* p1 = getPlayer1();
	fighter* p2 = getPlayer2();

	//renderText(font, shaders->at("text"), "Cool pile", 300, 300, 1280, 720, 2.0, glm::vec3(1.0f));

	renderText(font, shaders->at("text"), std::to_string((int)(getTimer())), 363, 100, 1280, 720, 2.5, glm::vec3(0.9f));

	glBindVertexArray(VAO);
	p1->draw(0);
	p2->draw(3);
	
	
	box tmp = box(p1->hitbox.position + p1->position, p1->hitbox.dimensions);
	drawBox(tmp, glm::vec4(1.0, 0.0, 0.0, 0.5));
	tmp = box(p2->hitbox.position + p2->position, p2->hitbox.dimensions);
	drawBox(tmp, glm::vec4(1.0, 0.0, 0.0, 0.5));

	tmp = box(p1->hurtbox.position + p1->position, p1->hurtbox.dimensions);
	drawBox(tmp, glm::vec4(0.0, 1.0, 0.0, 0.5));
	tmp = box(p2->hurtbox.position + p2->position, p2->hurtbox.dimensions);
	drawBox(tmp, glm::vec4(0.0, 1.0, 0.0, 0.5));
	

	tmp = box(glm::vec2(0.0f), glm::vec2(500.0f * (p1->health / 100.0f), 75.0f));
	drawBox(tmp, glm::vec4(1.0, 0.0, 0.0, 1.0));

	tmp = box(glm::vec2(1280.0f - 500.0f * (p2->health / 100.0f), 0.0f), glm::vec2(500.0f * (p2->health / 100.0f), 75.0f));
	drawBox(tmp, glm::vec4(1.0, 0.0, 0.0, 1.0));

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glFinish();
}

void render()
{
	auto shaders = getShaders();
	shaders->at("box").use();
	shaders->at("box").setFloat("time", glfwGetTime());
	drawGame();

	glClearColor(0.5f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaders->at("screen").use();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(1280.0f, 720, 1.0f));

	shaders->at("screen").setMat4("model", model);

	glBindVertexArray(VAO);
	glBindTexture(GL_TEXTURE_2D, FBOtexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}