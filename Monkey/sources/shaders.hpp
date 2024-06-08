#pragma once

const char vertex_code[] = R"(
#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec3 fragColor;

layout (std140, binding = 0) uniform PerFrameData
{
    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform int isWireframe;
};

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    fragColor = isWireframe > 0 ? vec3(0.2) : color;
}

)";

const char fragment_code[] = R"(
#version 460 core

in vec3 fragColor;

out vec4 outColor;

void main()
{
    outColor = vec4(fragColor, 1.0);
}

)";