
#include "lightManager.hpp"

void lightManager::addPointLight(const lightPoint& light)
{
    m_pointLights.push_back(light.clone());
    m_pointLights[m_pointLights.size() - 1]->m_shape.scale = glm::vec3(0.1f, 0.1f, 0.1f);
}

void lightManager::addSpotlight(const lightSpotlight& light)
{
    m_spotlights.push_back(light.clone());
    m_spotlights[m_spotlights.size() - 1]->m_shape.scale = glm::vec3(0.1f, 0.1f, 0.1f);
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

    sh.set1i("lightSCount",
        static_cast<int>(m_spotlights.size()));
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
    for (auto& light : m_pointLights)
        light->update();
    for (auto& light : m_spotlights)
        light->update();
    for (auto& light : m_directionalLights)
        light->update();
}
