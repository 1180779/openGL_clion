//
// Created by rdkgs on 1/25/2025.
//

#ifndef U1180779_BEZIER_SHAPE_HPP
#define U1180779_BEZIER_SHAPE_HPP

#include "objectShape.hpp"

class bezierShape : public objectShape
{
public:
    bezierShape();
    ~bezierShape() override;

    void render(shader& sh) const override;

private:
    static int s_count;
    static GLuint s_VBO;
    static GLuint s_EBO;
    static GLuint s_VAO;

    static float s_vertices[16 * 5];
    static unsigned int s_indices[6 * 3 * 3];
};



#endif //U1180779_BEZIER_SHAPE_HPP
