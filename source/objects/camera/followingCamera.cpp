
#include "followingCamera.hpp"

void followingCamera::update(float dt)
{
    pos = obj.pos + relPos;
    glm::vec3 objDir = glm::normalize(-relPos);

    direction = objDir;

    glm::mat4 t = glm::mat4(1.0f);
    t = glm::rotate(t, glm::radians(obj.pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, glm::radians(obj.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::rotate(t, glm::radians(obj.roll), glm::vec3(0.0f, 0.0f, 1.0f));
    
    front = glm::normalize(objDir);
    up = t * glm::vec4(up, 1.0f);
}
