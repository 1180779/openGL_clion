
#include "lightSpotlight.hpp"

void lightSpotlight::setForShader(
    const shader& sh, 
    const std::string& structShName) const
{
    lightSource::setForShader(sh, structShName);
    sh.set3f(structShName + ".direction", -m_direction);
    sh.set1f(structShName + ".cutoff", glm::cos(glm::radians(m_cutoff)));
    sh.set1f(structShName + ".outerCutoff", glm::cos(glm::radians(m_outerCutoff)));
}
