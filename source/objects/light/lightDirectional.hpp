
#ifndef U1180779_LIGHT_DIRECTIONAL_H
#define U1180779_LIGHT_DIRECTIONAL_H

#include "lightBase.hpp"

class lightDirectional : public lightBase, public IClonable<lightDirectional>
{
public:
    explicit lightDirectional(glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f))
        : lightBase(color, color, color) { }

    [[nodiscard]] std::unique_ptr<lightDirectional> clone() const override
        { return std::make_unique<lightDirectional>(*this); }

    glm::vec3 m_direction = glm::normalize(glm::vec3(-0.2f, -0.2f, -0.2f));
    float m_constant = 1.0f;
    float m_linear = 0.09f;
    float m_quadratic = 0.032f;

    void setForShader(
        const shader& sh, 
        const std::string& structShName) const override;
    void render(const cameraBase& cam) const override { } /* render is empty */
};

#endif