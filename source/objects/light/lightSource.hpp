
#ifndef U1180779_LIGHT_BASIC_H
#define U1180779_LIGHT_BASIC_H

#include "lightBase.hpp"

#include "../models/cubeShape.hpp"
#include "../camera/camera.hpp"

class lightSource : public lightBase
{
public:
    lightSource(const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));
    lightSource(const lightSource& other);
    ~lightSource();

    void setForShader(const shader& sh, const std::string& structShName) const override;
    void render(const cameraBase& cam) const override;
    
    inline glm::vec3 color() const { return m_shape.m_color; }

    inline glm::vec3 pos() const { return m_shape.pos; }
    inline void setPos(glm::vec3 pos) { m_shape.pos = pos; }

    cubeShape m_shape;

private:
    static int s_count;
    static shader* s_sh;
};

#endif