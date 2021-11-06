#include "texture.h"

#include <iostream>

#include <stb_image.h>

texture2D::texture2D()
    : Width(0), Height(0), Internal_Format(GL_COMPRESSED_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_NEAREST), Filter_Max(GL_NEAREST)
{
    glGenTextures(1, &this->ID);
}

void texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;
    // create Texture
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->Internal_Format, width, height, 0, this->Image_Format, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->Wrap_S);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->Wrap_T);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->Filter_Min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->Filter_Max);
    // unbind texture?
}

void texture2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}

texture2D loadTextureFromFile(const char* file, bool alpha)
{
    stbi_set_flip_vertically_on_load(true);
    // create texture object
    texture2D texture;
    if (alpha)
    {
        texture.Internal_Format = GL_COMPRESSED_RGBA;
        texture.Image_Format = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, width);
    glPixelStorei(GL_UNPACK_IMAGE_HEIGHT, height);

    glBindTexture(GL_TEXTURE_2D, 0);
    // free image data
    stbi_image_free(data);

    return texture;
}

std::map<std::string, texture2D> textures;
void loadTextures()
{
    // @TODO
}

std::map<std::string, texture2D>* getTextures()
{
    return &textures;
}