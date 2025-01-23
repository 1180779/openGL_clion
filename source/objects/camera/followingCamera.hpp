
#ifndef U1180779_FOLLOWING_CAMERA_H
#define U1180779_FOLLOWING_CAMERA_H

#include "camera.hpp"
#include "../models/objectShape.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class followingCamera : public cameraBase 
{
    public:
    explicit followingCamera(objectShape& obj) : obj(obj) { }
    ~followingCamera() override = default;

    [[nodiscard]] std::unique_ptr<cameraBase> clone() const override
        { return std::make_unique<followingCamera>(*this); }

    void update(float dt) override;

    glm::vec3 relPos = glm::vec3(4.0f, 4.0f, 4.0f); /* position relative to the object */
    objectShape& obj; /* obj being followed */
};

#endif