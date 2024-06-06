const char vertex_code[] = R"(
#version 460 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 color;

out vec3 fragColor;

void main()
{
    gl_Position = vec4(pos, 0.0, 1.0);
    fragColor = color;
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