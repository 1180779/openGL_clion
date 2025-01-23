
#ifndef U1180779_MOVING_CAMERA_H
#define U1180779_MOVING_CAMERA_H

#include "camera.hpp"
#include "../../window.hpp"

class movingCamera : public cameraBase 
{
    [[nodiscard]] std::unique_ptr<cameraBase> clone() const override
        { return std::make_unique<movingCamera>(*this); }

    void setCurrent(window& window) override;
    void processInput(GLFWwindow* window, const keyBinds& keys, float dt) override;

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};

#endif