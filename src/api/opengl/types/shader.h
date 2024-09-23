#pragma once

#include "../../common.h"
#include <fstream>
#include <sstream>

class Shader {
    private:
        uint32_t ID;

    public:
        Shader(std::string& name) {
            std::string vertPath = ROOT_DIR + "res/shaders/" + name + ".vert";
            std::string fragPath = ROOT_DIR + "res/shaders/" + name + ".frag";
            std::ifstream vShaderFile, fShaderFile;
            std::stringstream vertCode, fragCode;

            vShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
            fShaderFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

            try {
                vShaderFile.open(vertPath);
                fShaderFile.open(fragPath);
                vertCode << vShaderFile.rdbuf();
                fragCode << fShaderFile.rdbuf();
                vShaderFile.close();
                fShaderFile.close();
            }
            catch (std::ifstream::failure& e) {
                std::cout << "Shader File not successfully read: " << e.what() << std::endl;
            }

            uint32_t vertex, fragment;
            const char* vertexCode = vertCode.str().c_str();
            const char* fragmentCode = fragCode.str().c_str();

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vertexCode, NULL);
            glCompileShader(vertex);
            // todo: call check compile errors

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1,  &fragmentCode, NULL);
            glCompileShader(fragment);
            // todo: call check compile errors

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        void use() {
            glUseProgram(ID);
        }
        uint32_t getID() {
            return ID;
        }

        void setInt(std::string& name, int value) {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setFloat(std::string& name, float value) {
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setBool(std::string& name, bool value) {
            glUniform1i(glGetUniformLocation(ID, name.c_str()), ( int )value);
        }

        void setVec3(std::string& name, glm::vec3& value) {
            glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
        }
};