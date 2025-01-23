
#include "cameraManager.hpp"

void cameraManager::update(float dt)
{
    for (const auto & m_camera : m_cameras)
        m_camera->update(dt);
}

void cameraManager::prevCamera()
{
    --m_curr;
    if (m_curr < 0)
        m_curr = static_cast<int>(m_cameras.size() - 1);
    getCamera().setCurrent(m_window);
}

void cameraManager::nextCamera()
{
    ++m_curr;
    if (m_curr >= m_cameras.size())
        m_curr = 0;
    getCamera().setCurrent(m_window);
}

void cameraManager::addCamera(const cameraBase& cam)
{
    m_cameras.push_back(cam.clone());
}
