#include "lightPoint.hpp"

void lightPoint::setForShader(
    const shader& sh, 
    const std::string& structShName) const
{
    lightSource::setForShader(sh, structShName);
    sh.set1f(structShName + ".constant", m_constant);
    sh.set1f(structShName + ".linear", m_linear);
    sh.set1f(structShName + ".quadratic", m_quadratic);
}
