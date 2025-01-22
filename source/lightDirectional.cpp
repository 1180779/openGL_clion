#include "lightDirectional.hpp"

void lightDirectional::setForShader(
    const shader& sh, 
    const std::string& structShName) const
{
    lightBase::setForShader(sh, structShName);
    sh.set3f(structShName + ".direction", -m_direction);
}

