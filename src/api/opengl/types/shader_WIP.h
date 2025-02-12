#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>
#include <vector>

struct ShaderModule {
public:
    ShaderModule(const std::string& filename);
    int GetHandle();
    bool CompilationFailed();
    std::string& GetFilename();
    std::string& GetErrors();
    std::vector<std::string>& GetLineMap();
private:
    int m_handle = -1;
    std::string m_filename = "";
    std::string m_errors = "";
    std::vector<std::string> m_lineMap;
};

struct Shader {
public:
    Shader(std::vector<std::string> shaderPaths);
    void use();
    bool load(std::vector<std::string> shaderPaths);
    void setInt(const std::string& name, int value);
    void setBool(const std::string& name, bool value);
    void setFloat(const std::string& name, float value);
    void setMat2x2(const std::string& name, const glm::mat2& mat);
    void setMat3x3(const std::string& name, const glm::mat3& mat);
    void setMat4x4(const std::string& name, glm::mat4 value);
    void setVec2(const std::string& name, const glm::vec2& value);
    void setVec4(const std::string& name, const glm::vec4& value);
    void setVec3(const std::string& name, const glm::vec3& value);
    void setVec2(const std::string& name, float x, float y);
    void setVec3(const std::string& name, float x, float y, float z);
    void setVec4(const std::string& name, float x, float y, float z, float w);
    int getHandle();
private:
    std::unordered_map<std::string, int> m_uniformLocations;
    int m_handle = -1;
};