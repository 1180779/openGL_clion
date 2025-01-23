//
// Created by rdkgs on 1/23/2025.
//

#include "followingRotatableCamera.hpp"

void followingRotatableCamera::update(float dt)
{
    pos = obj.pos + relPos;
    const glm::vec3 objDir = glm::normalize(-relPos);

    direction = objDir;

    glm::mat4 t = glm::mat4(1.0f);
    t = glm::rotate(t, glm::radians(obj.pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    t = glm::rotate(t, glm::radians(obj.yaw), glm::vec3(0.0f, 1.0f, 0.0f));
    t = glm::rotate(t, glm::radians(obj.roll), glm::vec3(0.0f, 0.0f, 1.0f));

    front = glm::normalize(objDir);
    up = t * glm::vec4(up, 1.0f);
}

void followingRotatableCamera::setCurrent(window& window)
{
    cameraBase::setCurrent(window);
    glfwSetCursorPosCallback(window.handle, mouseCallback);
    glfwSetScrollCallback(window.handle, scrollCallback);
}

void followingRotatableCamera::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // reversed since y-coordinates range from bottom to top
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    if (!currentCamera) return;
    followingRotatableCamera* c = dynamic_cast<followingRotatableCamera*>(currentCamera);
    if(!c) return;

    constexpr float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    glm::mat4 t = glm::mat4(1.0f);
    glm::vec3 axis = glm::normalize(
        glm::cross(-c->relPos, c->up));
    t = glm::rotate(t, glm::radians(yoffset), axis);
    t = glm::rotate(t, glm::radians(-xoffset), glm::vec3(0.0f ,1.0f, 0.0f));

    c->relPos = t * glm::vec4(c->relPos, 1.0f);
}

void followingRotatableCamera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (!currentCamera)
        return;
    currentCamera->fov -= static_cast<float>(yoffset);
    if (currentCamera->fov < currentCamera->fovMin)
        currentCamera->fov = currentCamera->fovMin;
    if (currentCamera->fov > currentCamera->fovMax)
        currentCamera->fov = currentCamera->fovMax;
}
