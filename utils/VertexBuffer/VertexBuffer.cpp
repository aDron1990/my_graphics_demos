#include "VertexBuffer.hpp"

#include <glad/glad.h>

#include <stdexcept>
#include <iterator>
#include <cstddef>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices_)
{
    std::copy(vertices_.begin(), vertices_.end(), std::back_inserter(vertices));
    updateBuffers();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

VertexBuffer::VertexBuffer(VertexBuffer&& rhs) noexcept
{
    vao = rhs.vao;
    vbo = rhs.vbo;
    rhs.vao = 0;
    rhs.vbo = 0;
}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& rhs) noexcept
{
    vao = rhs.vao;
    vbo = rhs.vbo;
    rhs.vao = 0;
    rhs.vbo = 0;
    return *this;
}

void VertexBuffer::updateBuffers()
{
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, decltype(Vertex::position)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, decltype(Vertex::color)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, decltype(Vertex::uv)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}

void VertexBuffer::bind()
{
    glBindVertexArray(vao);
}

size_t VertexBuffer::size()
{
    return vertices.size();
}