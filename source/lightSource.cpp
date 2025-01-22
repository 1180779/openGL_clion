
#include "lightSource.hpp"

int lightSource::s_count = 0;
shader* lightSource::s_sh = nullptr;

static const char* lightVertexShaderS = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
} 
)";

static const char* lightFragmentShaderS = R"(
#version 330 core
uniform vec3 lightColor;

out vec4 FragColor;

void main()
{
    FragColor = vec4(lightColor, 1.0f); // set transparency to 1.0
}
)";


lightSource::lightSource(const glm::vec3& color) 
    : lightBase(color, color, color), m_shape(color)
{
    m_shape.scale = glm::vec3(0.1f, 0.1f, 0.1f); /* dafault light scale */
    ++s_count;
    if (s_count > 1)
        return;
    
    s_sh = new shader(lightVertexShaderS, lightFragmentShaderS);
}

lightSource::lightSource(const lightSource& other) 
    : m_shape(other.m_shape)
{
    ++s_count;
}

lightSource::~lightSource()
{
    --s_count;
    if (s_count > 0)
        return;

    delete s_sh;
    s_sh = nullptr;
}

void lightSource::setForShader(
    const shader& sh, 
    const std::string& structShName) const
{
    lightBase::setForShader(sh, structShName);
    glm::vec3 p = pos();
    sh.set3f(structShName + ".pos", p.x, p.y, p.z);
}

void lightSource::render(const cameraBase& cam) const
{
    glm::vec3 c = color();

    s_sh->use();
    s_sh->set3f("lightColor", c.x, c.y, c.z);
    cam.setForShader(*s_sh);
    s_sh->setMatrix4fv("model", m_shape.model());
    m_shape.render(*s_sh);
}
