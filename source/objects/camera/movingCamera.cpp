
#include "movingCamera.hpp"

#include "../../keyBinds.hpp"

void movingCamera::setCurrent(window& window)
{
    cameraBase::setCurrent(window);
    glfwSetCursorPosCallback(window.handle, mouseCallback);
    glfwSetScrollCallback(window.handle, scrollCallback);
}

void movingCamera::processInput(GLFWwindow* window, const keyBinds& keys, float dt)
{
    float speed = this->speed * dt;
    if (glfwGetKey(window, keys.forward) == GLFW_PRESS) {
        pos += speed * front;
    }
    if (glfwGetKey(window, keys.backward) == GLFW_PRESS) {
        pos -= speed * front;
    }

    if (glfwGetKey(window, keys.right) == GLFW_PRESS) {
        pos += speed * glm::normalize(glm::cross(front, up));
    }
    if (glfwGetKey(window, keys.left) == GLFW_PRESS) {
        pos -= speed * glm::normalize(glm::cross(front, up));
    }

    if (glfwGetKey(window, keys.up) == GLFW_PRESS) {
        pos += speed * up;
    }
    if (glfwGetKey(window, keys.down) == GLFW_PRESS) {
        pos -= speed * up;
    }
}

void movingCamera::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    float xoffset = static_cast<float>(xpos - lastX);
    float yoffset = static_cast<float>(lastY - ypos); // reversed since y-coordinates range from bottom to top
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);

    if (!currentCamera)
        return;

    constexpr float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    currentCamera->yaw += xoffset;
    currentCamera->pitch += yoffset;

    /* limit pitch */
    if (currentCamera->pitch > 89.0f)
        currentCamera->pitch = 89.0f;
    if (currentCamera->pitch < -89.0f)
        currentCamera->pitch = -89.0f;

    currentCamera->direction.x = static_cast<float>(
        cos(glm::radians(currentCamera->yaw)) * cos(glm::radians(currentCamera->pitch)));
    currentCamera->direction.y = static_cast<float>(
        sin(glm::radians(currentCamera->pitch)));
    currentCamera->direction.z = static_cast<float>(
        sin(glm::radians(currentCamera->yaw)) * cos(glm::radians(currentCamera->pitch)));
    currentCamera->front = glm::normalize(currentCamera->direction);
}

void movingCamera::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (!currentCamera)
        return;
    currentCamera->fov -= static_cast<float>(yoffset);
    if (currentCamera->fov < currentCamera->fovMin)
        currentCamera->fov = currentCamera->fovMin;
    if (currentCamera->fov > currentCamera->fovMax)
        currentCamera->fov = currentCamera->fovMax;
}
