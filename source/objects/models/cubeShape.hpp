
#ifndef U1180779_CUBE_H
#define U1180779_CUBE_H

#include "objectShape.hpp"

class cubeShape : public objectShape
{
public:
    explicit cubeShape(glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f));
    cubeShape(const cubeShape& other);
    ~cubeShape() override;

    void render(shader& sh) const override;

    glm::vec3 m_color;

private:
    static int s_count;
    static GLuint s_VBO;
    static GLuint s_VAO;

    static float s_vertices[36 * 6]; /* vertices and normal vectors */
};

#endif