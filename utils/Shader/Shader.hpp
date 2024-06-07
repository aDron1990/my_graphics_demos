#pragma once

#include <cstdint>
#include <string>
#include <glm/glm.hpp>

class Shader
{
public:

    Shader(const std::string& vertexCode, const std::string& fragmentCode);
    ~Shader();
    Shader(Shader&&) noexcept;
    Shader& operator=(Shader&&) noexcept;

    void bind() const noexcept;
    template<class T>
    void setUniform(const std::string& uniformName, const T& uniformValue) noexcept;

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

private:
    
    uint32_t compileShader(const int type, const std::string& shaderCode);
    uint32_t linkProgram(const uint32_t vertex, const uint32_t fragment);

private:

    uint32_t program;

};