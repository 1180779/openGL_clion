
#ifndef U1180779_LIGHT_MANAGER_H
#define U1180779_LIGHT_MANAGER_H

#include "lightDirectional.hpp"
#include "lightPoint.hpp"
#include "lightSpotlight.hpp"

#include "../camera/camera.hpp"
#include <vector>
#include <string>

class lightManager 
{
public:
    void addPointLight(const lightPoint& light);
    void addSpotlight(const lightSpotlight& light);
    void addDirectionalLight(const lightDirectional& light);

    void setForShader(const shader& sh) const;
    void update(float dt);
    void render(const cameraBase& cam) const;

    bool fog = true;
    glm::vec3 fogColor = glm::vec3(0.5f, 0.5f, 0.5f);
    float fogDensity = 0.10f;

    bool day = true;
    std::vector<std::unique_ptr<lightPoint>> m_pointLights;
    std::vector<std::unique_ptr<lightSpotlight>> m_spotlights;
    std::vector<std::unique_ptr<lightDirectional>> m_directionalLights;
};

#endif
