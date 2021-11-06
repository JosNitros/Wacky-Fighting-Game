#include "text.h"

#include <map>
#include <iostream>

bool inited = false;
unsigned int textVAO, textVBO;

FT_Library ft;

std::map<GLchar, Char> loadFont(const char* font)
{
	std::map<GLchar, Char> Chars;
		
	if (!inited)
	{
		if (FT_Init_FreeType(&ft))
		{
			std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
			return Chars;
		}
	}

	FT_Face face;
	if (FT_New_Face(ft, font, 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return Chars;
	}
	FT_Set_Pixel_Sizes(face, 0, 128);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 128; c++)
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			return Chars;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_COMPRESSED_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// now store character for later use
		Char character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Chars.insert(std::pair<char, Char>(c, character));
	}
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	
	if (!inited)
	{
		glGenVertexArrays(1, &textVAO);
		glGenBuffers(1, &textVBO);
		glBindVertexArray(textVAO);
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		inited = true;
	}

	return Chars;
}

void renderText(std::map<GLchar, Char>& font, shader& shade, std::string text, double x, double y, unsigned int screenHeight, unsigned int screenWidth, double scale, glm::vec3 color, bool center)
{
	y *= screenHeight;
	const double xscale = scale * 0.5;
	const double yscale = scale * 0.5;
	// activate corresponding render state
	shade.use();
	shade.setVec3("textColor", color);

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);

	std::string::const_iterator c;

	if (center)
	{
		for (c = text.begin(); c != text.end(); c++)
		{
			Char ch = font[*c];
			x -= ((ch.Advance >> 6) * xscale) / screenWidth * 0.5;
		}
	}

	for (c = text.begin(); c != text.end(); c++)
	{
		Char ch = font[*c];

		float xpos = (x + (ch.Bearing.x / screenWidth) * xscale);
		float ypos = (y - (ch.Size.y - ch.Bearing.y) * yscale) / screenHeight;

		float w = (ch.Size.x * xscale) / screenWidth;
		float h = (ch.Size.y * yscale) / screenHeight;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};

		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 6 * 4 * sizeof(float), vertices);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += ((ch.Advance >> 6) * xscale) / screenWidth; // bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(textVAO);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void renderText(std::map<GLchar, Char>& font, shader& shade, std::string text, int x, int y, unsigned int screenHeight, unsigned int screenWidth, double scale, glm::vec3 color, bool center)
{
	double newX = x * (1.0 / screenWidth * 2) - 1.0;
	double newY = -y * (1.0 / screenHeight * 2) + 1.0;

	renderText(font, shade, text, newX, newY, screenHeight, screenWidth, scale, color, center);
}