
#include "lightManager.hpp"

void lightManager::addPointLight(const lightPoint& light)
{
    m_pointLights.push_back(light.clone());
}

void lightManager::addSpotlight(const lightSpotlight& light)
{
    m_spotlights.push_back(light.clone());
}

void lightManager::addDirectionalLight(const lightDirectional& light)
{
    m_directionalLights.push_back(light.clone());
}

void lightManager::setForShader(const shader& sh) const
{
    sh.set1f("fogDensity", fog ? fogDensity : 0.0f);
    sh.set3f("fogColor", fogColor);

    if(day) {
        sh.set1i("lightDCount",
            static_cast<int>(m_directionalLights.size()));
        for(int i = 0; i < m_directionalLights.size(); ++i) {
            m_directionalLights[i]->setForShader(sh, "lightD[" + std::to_string(i) + ']');
        }
    }
    else {
        sh.set1i("lightDCount", 0);
    }

    int lightSCount = 0;
    if (flashLightOn) {
        if (m_flashLight) { /* add flashlight to spotlight if set */
            m_flashLight->setForShader(sh, "lightS[" + std::to_string(m_spotlights.size()) + ']');
            lightSCount = static_cast<int>(m_spotlights.size() + 1);
        }
        else {
            lightSCount = static_cast<int>(m_spotlights.size());
        }
    }
    else {
        lightSCount = static_cast<int>(m_spotlights.size());
    }
    sh.set1i("lightSCount", lightSCount);
    for (int i = 0; i < m_spotlights.size(); ++i) {
        m_spotlights[i]->setForShader(sh, "lightS[" + std::to_string(i) + ']');
    }

    sh.set1i("lightPCount",
        static_cast<int>(m_pointLights.size()));
    for (int i = 0; i < m_pointLights.size(); ++i) {
        m_pointLights[i]->setForShader(sh, "lightP[" + std::to_string(i) + ']');
    }
}

void lightManager::render(const cameraBase& cam) const
{
    for (const auto & directionalLight : m_directionalLights) {
        directionalLight->render(cam);
    }

    for (const auto & pointLight : m_pointLights) {
        pointLight->render(cam);
    }

    for (const auto & spotlight : m_spotlights) {
        spotlight->render(cam);
    }
}

void lightManager::update(float dt)
{
    if (flashLightOn) {
        if (m_flashLight)
            m_flashLight->update();
    }

    for (auto& light : m_pointLights)
        light->update();
    for (auto& light : m_spotlights)
        light->update();
    for (auto& light : m_directionalLights)
        light->update();
}
