#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
    GLuint ID;

    Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode, fragmentCode;
        std::ifstream vFile, fFile;

        vFile.open(vertexPath);
        fFile.open(fragmentPath);

        std::stringstream vStream, fStream;

        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();

        vFile.close();
        fFile.close();

        vertexCode = vStream.str();
        fragmentCode = fStream.str();

        const char* vCode = vertexCode.c_str();
        const char* fCode = fragmentCode.c_str();

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vCode, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fCode, NULL);
        glCompileShader(fs);

        ID = glCreateProgram();
        glAttachShader(ID, vs);
        glAttachShader(ID, fs);
        glLinkProgram(ID);

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void use() {
        glUseProgram(ID);
    }

    void setVec4(const char* name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(ID, name), x, y, z, w);
    }

    void setMat4(const char* name, glm::mat4 mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(mat));
    }
};