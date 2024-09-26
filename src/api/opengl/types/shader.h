#pragma once

#include "../../../common.h"
#include <fstream>
#include <sstream>
#include <unordered_map>

void checkCompileErrors();

struct Shader {
    private:
        uint32_t m_ID;
        std::unordered_map<std::string, int> uniformLocs;

    public:
        void load(const std::string& name) {
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

            int temp_ID = glCreateProgram();
            glAttachShader(temp_ID, vertex);
            glAttachShader(temp_ID, fragment);
            glLinkProgram(temp_ID);
            // todo: call check compile errors

            if (m_ID != -1) {
                glDeleteProgram(m_ID);
            }

            m_ID = temp_ID;

            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        void use() {
            glUseProgram(m_ID);
        }
        uint32_t getID() {
            return m_ID;
        }

        void setInt(const std::string& name, int value) {
            if (uniformLocs.find(name) == uniformLocs.end()) {
                uniformLocs[name] = glGetUniformLocation(m_ID, name.c_str());
            }
            glUniform1i(uniformLocs[name], value);
        }

        void setFloat(const std::string& name, float value) {
            if (uniformLocs.find(name) == uniformLocs.end()) {
                uniformLocs[name] = glGetUniformLocation(m_ID, name.c_str());
            }
            glUniform1f(uniformLocs[name], value);
        }

        void setBool(const std::string& name, bool value) {
            if (uniformLocs.find(name) == uniformLocs.end()) {
                uniformLocs[name] = glGetUniformLocation(m_ID, name.c_str());
            }
            glUniform1i(uniformLocs[name], ( int )value);
        }

        void setVec3(const std::string& name, glm::vec3& value) {
            if (uniformLocs.find(name) == uniformLocs.end()) {
                uniformLocs[name] = glGetUniformLocation(m_ID, name.c_str());
            }
            glUniform3fv(uniformLocs[name], 1, &value[0]);
        }
};