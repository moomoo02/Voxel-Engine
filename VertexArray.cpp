#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void VertexArray::bind()
{
    glBindVertexArray(VAO);
}