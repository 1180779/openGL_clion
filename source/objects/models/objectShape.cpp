
#include "objectShape.hpp"

const glm::mat4 objectShape::s_model = glm::mat4(1.0f);

/* unified shader names */

const char* objectShape::s_colorShaderName = "objectColor";

/* methods */

void objectShape::render(shader& sh) const
{
    sh.use();
    sh.set3f("material.ambient", material.ambient);
    sh.set3f("material.diffuse", material.diffuse);
    sh.set3f("material.specular", material.specular);
    sh.set1f("material.shininess", material.shininess);
}

glm::mat4 objectShape::model() const
{
    auto t = s_model;
    t = glm::scale(t, scale);
    t = glm::translate(t, pos);
    t = glm::rotate(t, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::rotate(t, glm::radians(roll), glm::vec3(0.0f, 0.0f, 1.0f));
    return t;
}

glm::mat4 objectShape::normalMatrix() const
{
    auto t = s_model;
    t = glm::scale(t, scale);
    return glm::transpose(glm::inverse(t));
}

