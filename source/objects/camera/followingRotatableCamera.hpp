//
// Created by rdkgs on 1/23/2025.
//

#ifndef U1180779_FOLLOWING_ROTATABLE_CAMERA_HPP
#define U1180779_FOLLOWING_ROTATABLE_CAMERA_HPP

#include "camera.hpp"
#include "followingCamera.hpp"

class followingRotatableCamera : public followingCamera {
public:
    explicit followingRotatableCamera(objectShape& obj) : followingCamera(obj) { }

    void update(float dt) override;

    [[nodiscard]] std::unique_ptr<cameraBase> clone() const override
    { return std::make_unique<followingRotatableCamera>(*this); }

    void setCurrent(window& window) override;

    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

};



#endif //U1180779_FOLLOWING_ROTATABLE_CAMERA_HPP
