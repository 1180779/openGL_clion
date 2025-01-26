
#ifndef U1180779_LIGHT_MANAGER_H
#define U1180779_LIGHT_MANAGER_H

#include <random>

#include "lightDirectional.hpp"
#include "lightPoint.hpp"
#include "lightSpotlight.hpp"

#include "../camera/camera.hpp"
#include <vector>
#include <string>

#include "lightSpotlightFollowing.hpp"

class lightManager 
{
public:
    void addPointLight(const lightPoint& light);
    void addSpotlight(const lightSpotlight& light);
    void addDirectionalLight(const lightDirectional& light);

    void setForShader(const shader& sh) const;
    void update(float dt);
    void render(const cameraBase& cam) const;

    void addFlashlight(std::unique_ptr<lightSpotlightFollowing>& light)
        { m_flashLight = std::move(light); }

    void clearFlashlight() { m_flashLight.reset(nullptr); }

    bool fog = true;
    glm::vec3 fogColor = glm::vec3(0.5f, 0.5f, 0.5f);
    float fogDensity = 0.10f;

    std::unique_ptr<lightSpotlightFollowing> m_flashLight;
    bool flashLightOn = false;

    bool day = true;
    std::vector<std::unique_ptr<lightPoint>> m_pointLights;
    std::vector<std::unique_ptr<lightSpotlight>> m_spotlights;
    std::vector<std::unique_ptr<lightDirectional>> m_directionalLights;
};

#endif
