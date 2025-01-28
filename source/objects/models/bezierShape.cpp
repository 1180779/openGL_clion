//
// Created by rdkgs on 1/25/2025.
//

#include "bezierShape.hpp"

#include "glad/glad.h"

int bezierShape::s_count = 0;
GLuint bezierShape::s_VBO = 0;
GLuint bezierShape::s_EBO = 0;
GLuint bezierShape::s_VAO = 0;

float bezierShape::s_vertices[16 * 5] = {
    -0.77f,     -0.52f,      0.1f,      0.0f,   0.0f,
    -1.f,       -0.09f,      0.0f,      0.33f,  0.0f,
    -0.77f,      0.15f,      0.12f,     0.66f,  0.0f,
    -0.77f,      0.5f,       0.31f,     1.0f,   0.0f,
    -0.35f,     -0.45f,     -0.20f,     0.0f,   0.33f,
    -0.26f,     -0.2f,       0.03f,     0.33f,  0.33f,
    -0.26f,      0.18f,      0.13f,     0.66f,  0.33f,
    -0.26f,      0.56f,     -0.03f,     1.0f,   0.33f,
    0.22f,      -0.56f,     -0.26f,     0.0f,   0.66f,
    0.26f,      -0.21f,      0.21f,     0.33f,  0.66f,
    0.26f,       0.19f,      0.01f,     0.66f,  0.66f,
    0.22f,       0.55f,      0.0f,      1.0f,   0.66f,
    0.77f,      -0.54f,     -0.32f,     0.0f,   1.0f,
    0.77f,      -0.18f,      0.29f,     0.33f,  1.0f,
    0.77f,       0.18f,      0.15f,     0.66f,  1.0f,
    0.91f,       0.6f,      -0.01f,     1.0f,   1.0f
};

unsigned int bezierShape::s_indices[6 * 3 * 3] = {
    0, 1, 4,
    4, 5, 1,
    1, 2, 5,
    5, 6, 2,
    2, 3, 6,
    6, 7, 3,

    4, 5, 8,
    8, 9, 5,
    5, 6, 9,
    9, 10, 6,
    6, 7, 10,
    10, 11, 7,

    8, 9, 12,
    12, 13, 9,
    9, 10, 13,
    13, 14, 10,
    10, 11, 14,
    14, 15, 11
};

bezierShape::bezierShape()
{
    ++s_count;
    if (s_count > 1)
        return;

    glGenVertexArrays(1, &s_VAO);
    glBindVertexArray(s_VAO);

    glGenBuffers(1, &s_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(s_indices), s_indices, GL_STATIC_DRAW);

    glGenBuffers(1, &s_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(s_vertices), s_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(4*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(2);

    glPatchParameteri(GL_PATCH_VERTICES, 16);
}

bezierShape::~bezierShape()
{
    --s_count;
    if (s_count > 0)
        return;
    glDeleteVertexArrays(1, &s_VAO);
    glDeleteBuffers(1, &s_VBO);
    glDeleteBuffers(1, &s_EBO);
}

void bezierShape::render(shader &sh) const
{
    objectShape::render(sh);
    glBindVertexArray(s_VAO);
    glDrawArrays(GL_PATCHES, 0, 16);
}
