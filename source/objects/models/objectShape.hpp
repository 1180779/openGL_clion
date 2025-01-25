
#ifndef U1180779_OBJECT_H
#define U1180779_OBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../shader.hpp"
#include "material.hpp"

class objectShape
{
public:
    virtual ~objectShape() = default;

    objectShape() = default;
    objectShape(const objectShape& other) = default;

    virtual void render(shader& sh) const;

    [[nodiscard]] glm::mat4 model() const; /* model matrix */
    [[nodiscard]] glm::mat4 normalMatrix() const; /* matrix for normal vectors */

    /* position variables */

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    float pitch = 0.0f;
    float yaw = 0.0f;
    float roll = 0.0f;

    material material = material::copper;

protected:
    static const char* s_colorShaderName;

private:
    static const glm::mat4 s_model;
};

#endif