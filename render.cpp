#include "render.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shaders.h"
#include "texture.h"
#include "text.h"
#include "animation.h"

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

unsigned int tf1 = 0;
unsigned int tf2 = 0;
void drawGame()
{
	auto shaders = getShaders();
	auto textures = getTextures();
	auto animations = getAnimations();
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	glClearColor(1.0f, 0.5f, 0.5f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//@ TODO

	renderText(font, shaders->at("text"), "Cum", 300, 300, 1280, 720, 2.0, glm::vec3(1.0));

	glBindVertexArray(VAO);
	animations.at("attack2")->draw(tf1, glm::vec2(100.0f, 100.0f), glm::vec2(400.0f, 400.0f), 2);
	animations.at("attack2")->draw(tf2, glm::vec2(100.0f, 300.0f), glm::vec2(400.0f, 400.0f), 1);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glFinish();
}

void render()
{
	auto shaders = getShaders();
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