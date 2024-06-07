#pragma once

#include "Vertex.hpp"

#include <cstdint>
#include <vector>

class VertexBuffer
{
public:

    VertexBuffer(const std::vector<Vertex>& vertices);
    ~VertexBuffer();
    VertexBuffer(VertexBuffer&&) noexcept;
    VertexBuffer& operator=(VertexBuffer&&) noexcept;

    void bind();
    size_t size();

    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

private:

    void updateBuffers();

private:

    uint32_t vbo, vao;
    std::vector<Vertex> vertices;

};