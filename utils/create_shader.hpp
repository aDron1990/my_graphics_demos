#pragma once

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <cstdint>

constexpr const size_t INFO_LOG_SIZE = 1024;

uint32_t create_shader(const std::string& vertex_code, const std::string& fragment_code)
{
    char info_log[INFO_LOG_SIZE];
    int success;

    uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_code_cstr = vertex_code.c_str();
    glShaderSource(vertex, 1, &vertex_code_cstr, nullptr);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, INFO_LOG_SIZE, nullptr, info_log);
        std::cerr << "Failed to compile vertex shader" << std::endl;
        std::cerr << info_log << std::endl;
        return 0;
    }

    uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_code_cstr = fragment_code.c_str();
    glShaderSource(fragment, 1, &fragment_code_cstr, nullptr);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, INFO_LOG_SIZE, nullptr, info_log);
        std::cerr << "Failed to compile fragment shader" << std::endl;
        std::cerr << info_log << std::endl;
        return 0;
    }

    uint32_t program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, INFO_LOG_SIZE, nullptr, info_log);
        std::cerr << "Failed to link shader program" << std::endl;
        std::cerr << info_log << std::endl;
        return 0;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return program;
}