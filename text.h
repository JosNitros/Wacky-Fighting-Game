#ifndef SNDXTEXT_H
#define SNDXTEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <map>

#include "shaders.h"


struct Char {
	unsigned int TextureID;  // ID handle of the glyph texture
	glm::ivec2   Size;       // Size of glyph
	glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
	unsigned int Advance;    // Offset to advance to next glyph
};

std::map<GLchar, Char> loadFont(const char* font);

void renderText(std::map<GLchar, Char>& font, shader& shade, std::string text, int x, int y, unsigned int screenHeight, unsigned int screenWidth, double scale, glm::vec3 color, bool center = true);
#endif