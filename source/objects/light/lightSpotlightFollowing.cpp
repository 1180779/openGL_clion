//
// Created by rdkgs on 1/24/2025.
//

#include "lightSpotlightFollowing.hpp"

void lightSpotlightFollowing::update()
{
    glm::mat4 t = glm::mat4(1.0f);
    t = glm::rotate(t, glm::radians(m_obj.pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, glm::radians(m_obj.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::rotate(t, glm::radians(m_obj.roll), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 rel2 = t * glm::vec4(relPos, 0.0f);
    m_shape.pos = m_obj.pos + rel2;

    glm::mat4 t2 = glm::translate(glm::mat4(1.0f), relPos);
    t2 = t2 * t;
    t2 = glm::translate(t2, -relPos);

    m_direction = glm::normalize(t2 * glm::vec4(relDirection, 0.0f));
}
