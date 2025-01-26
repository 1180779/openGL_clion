//
// Created by rdkgs on 1/24/2025.
//

#include "lightSpotlightFollowing.hpp"

void lightSpotlightFollowing::update()
{
    glm::mat4 t = glm::mat4(1.0f);
    t = glm::rotate(t, glm::radians(m_obj.getPitch()), glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, glm::radians(m_obj.getYaw()), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::rotate(t, glm::radians(m_obj.getRoll()), glm::vec3(0.0f, 0.0f, 1.0f));

    m_shape.pitch = m_obj.getPitch();
    m_shape.yaw = m_obj.getYaw();
    m_shape.roll = m_obj.getRoll();

    m_shape.pos = m_obj.getPos() + glm::vec3(t * glm::vec4(relPos, 0.0f));

    m_direction = glm::normalize(glm::vec3(t * glm::vec4(relDirection, 0.0f)));

    /* TODO: find a way to remove this (fix working with cameras) */
    auto cam = dynamic_cast<cameraBase*>(&m_obj);
    if (cam) {
        m_direction = cam->direction;
    }
}
