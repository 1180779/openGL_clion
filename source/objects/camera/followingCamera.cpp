
#include "followingCamera.hpp"

void followingCamera::update(float dt)
{
    glm::mat4 t = glm::mat4(1.0f);
    t = glm::rotate(t, glm::radians(obj.pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, glm::radians(obj.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::rotate(t, glm::radians(obj.roll), glm::vec3(0.0f, 0.0f, 1.0f));

    glm::vec3 rel2 = t * glm::vec4(relPos, 0.0f);
    pos = obj.pos + rel2;
    glm::vec3 objDir = glm::normalize(-rel2);

    direction = objDir;


    front = glm::normalize(objDir);
    up = glm::normalize(t * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f));
}
