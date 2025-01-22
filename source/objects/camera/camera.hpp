
#ifndef U1180779_CAMERA_H
#define U1180779_CAMERA_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "../shader.hpp"
#include <glm/glm.hpp>

#include "../../window.hpp"
#include "../../interfaces/IClonable.hpp"

class cameraBase : IClonable<cameraBase>
{
public:
    cameraBase() { }

    std::unique_ptr<cameraBase> clone() const override
        { return std::make_unique<cameraBase>(*this); }

    /* set mouse movement to modify this cameras yaw and pitch */
    virtual void setCurrent(window& window);

    /* update pos */
    virtual void update(float dt) { }

    inline glm::vec3 getPos() const { return pos; }

    /* process input */
    virtual void processInput(GLFWwindow* window, float dt) { }

    /* set 4f matrix with name in the shader */
    void setForShader(const shader& sh, 
        const std::string& nameView = "view", 
        const std::string& nameProj = "projection") const;

    float speed = 2.0f;
    float yaw = -90.0f;

    float pitch = 0.0f;
    float pitchMax = 89.0f;
    float pitchMin = -89.0f;

    float fov = 45.0f;
    float fovMax = 45.0f;
    float fovMin = 1.0f;

    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 3.0f);

    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f);
    glm::vec3 direction = glm::normalize(glm::vec3(1.0f, 1.0f, 1.0f));

    static cameraBase* currentCamera;
    static float lastX, lastY;
};

using staticCamera = cameraBase;



#endif