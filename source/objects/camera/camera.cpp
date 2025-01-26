
#include "camera.hpp"

cameraBase* cameraBase::currentCamera = nullptr;
float cameraBase::lastX = 400;
float cameraBase::lastY = 300;

void cameraBase::setCurrent(window& window)
{
    currentCamera = this;
    
    double xpos, ypos;
    glfwGetCursorPos(window.handle, &xpos, &ypos);
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);
    
    glfwSetCursorPosCallback(window.handle, nullptr);
    glfwSetScrollCallback(window.handle, nullptr);
}

void cameraBase::setForShader(
    const shader& sh, 
    const std::string& nameView, 
    const std::string& nameProj) const
{
    sh.use();
    sh.set3f("viewPos", pos.x, pos.y, pos.z);
    if(ortho) {
        sh.setMatrix4fv(nameProj, glm::ortho(-1.5f, 1.5f, -1.5f, 1.5f, 0.0f, 100.0f));
    }
    else {
        sh.setMatrix4fv(nameProj, glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f));
    }
    sh.setMatrix4fv(nameView, glm::lookAt(pos, pos + front, up));
}
