#pragma once
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/mat2x2.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

struct shader
{
    unsigned int ID;

    shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    // activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value);

    void setInt(const std::string& name, int value);

    void setFloat(const std::string& name, float value);

    void setVec2(const std::string& name, const glm::vec2& value);

    void setVec2(const std::string& name, float x, float y);

    void setVec3(const std::string& name, const glm::vec3& value);

    void setVec3(const std::string& name, float x, float y, float z);

    void setVec4(const std::string& name, const glm::vec4& value);

    void setVec4(const std::string& name, float x, float y, float z, float w);

    void setMat2(const std::string& name, const glm::mat2& mat);
 
    void setMat3(const std::string& name, const glm::mat3& mat);

    void setMat4(const std::string& name, const glm::mat4& mat);
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shdr, std::string type);
};

bool compileShaders();

std::map<std::string, shader>* getShaders();
#endif