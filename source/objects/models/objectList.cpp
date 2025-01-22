
#include <glm/gtc/matrix_transform.hpp>
#include "objectList.hpp"
#include "../light/lightManager.hpp"

objectList::objectList(shader& sh) : m_sh(sh) { }

objectList::~objectList()
{
    for (auto o : m_objs) {
        delete o;
    }
}

objectList& objectList::addObject(objectShape* obj)
{
    m_objs.push_back(obj);
    return *this;
}

objectList& objectList::translate(const glm::vec3& v)
{
    m_trans = glm::translate(m_trans, v);
    return *this;
}

objectList& objectList::rotate(const float angle, const glm::vec3& v)
{
    m_trans = glm::rotate(m_trans, glm::radians(angle), glm::normalize(v));
    return *this;
}

objectList& objectList::scale(const glm::vec3& v)
{
    m_trans = glm::scale(m_trans, v);
    return *this;
}

void objectList::update(float dt)
{
    glm::mat4 t = glm::mat4(1.0f);
    t = glm::rotate(t, glm::radians(50.0f * dt), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::vec3 res = t * glm::vec4(m_objs[2]->pos, 1.0f);
    m_objs[2]->pos = res;
}

void objectList::render(
    const cameraBase& cam, 
    const lightManager& lightMan, 
    const std::string modelName) const
{
    cam.setForShader(m_sh);
    lightMan.setForShader(m_sh);
    for (int i = 0; i < m_objs.size(); ++i) {
        m_sh.setMatrix4fv(modelName, m_trans * m_objs[i]->model());
        m_objs[i]->render(m_sh);
    }
}
