
#ifndef U1180779_LIGHT_BASE_H
#define U1180779_LIGHT_BASE_H

#include "../shader.hpp"
#include "../camera/camera.hpp"

class lightBase 
{
public:
    lightBase(glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f),
        glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f), 
        glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f));
    
    virtual void setForShader(
        const shader& sh, 
        const std::string& structShName) const;

    /* implement down in hierarchy */
    virtual void render(const cameraBase& cam) const { } 

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    static float s_ambient;
};

#endif
