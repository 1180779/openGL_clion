
#include "lightManager.hpp"

void lightManager::addPointLight(const lightPoint& light)
{
    m_pointLights.push_back(light);
    m_pointLights[m_pointLights.size() - 1].m_shape.scale = glm::vec3(0.1f, 0.1f, 0.1f);
}

void lightManager::addSpotlight(const lightSpotlight& light)
{
    m_spotlights.push_back(light);
    m_spotlights[m_spotlights.size() - 1].m_shape.scale = glm::vec3(0.1f, 0.1f, 0.1f);
}

void lightManager::addDirectionalLight(const lightDirectional& light)
{
    m_directionalLights.push_back(light);
}

void lightManager::setForShader(const shader& sh) const
{
    for(int i = 0; i < m_directionalLights.size(); ++i) 
    {
        m_directionalLights[i].setForShader(sh, "lightD[" + std::to_string(i) + ']');
    }

    for (int i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i].setForShader(sh, "lightP[" + std::to_string(i) + ']');
    }

    for (int i = 0; i < m_spotlights.size(); ++i)
    {
        m_spotlights[i].setForShader(sh, "lightS[" + std::to_string(i) + ']');
    }
}

void lightManager::render(const cameraBase& cam) const
{
    for (int i = 0; i < m_directionalLights.size(); ++i)
    {
        m_directionalLights[i].render(cam);
    }

    for (int i = 0; i < m_pointLights.size(); ++i)
    {
        m_pointLights[i].render(cam);
    }

    for (int i = 0; i < m_spotlights.size(); ++i)
    {
        m_spotlights[i].render(cam);
    }
}
