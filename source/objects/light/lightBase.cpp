
#include "lightBase.hpp"

float lightBase::s_ambient = 0.2f;

lightBase::lightBase(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : m_ambient(ambient), m_diffuse(diffuse), m_specular(specular) { }

void lightBase::setForShader(const shader& sh, const std::string& structShName) const
{
    sh.use();
    sh.set3f(structShName + ".ambient", m_ambient);
    sh.set3f(structShName + ".diffuse", m_diffuse);
    sh.set3f(structShName + "light.specular", m_specular);
}
