#include "shader.hpp"

#include <iostream>

// loading shaders from files
#include <string>
#include <fstream>

GLuint compileShader(const char* source, GLenum shaderType);
GLuint linkProgram(
    GLuint vertexShader,
    GLuint fragmentShader,
    GLuint geometryShader = -1,
    GLuint tesselationControlShader = -1,
    GLuint tesselationEvaluationShader = -1);

shader::shader(
    const char* vertexShaderC,
    const char* fragmentShaderC,
    const char* geometryShaderC,
    const char* tesselationControlShaderC,
    const char* tesselationEvaluationShaderC)
{
    this->vertexShaderC = vertexShaderC;
    this->fragmentShaderC = fragmentShaderC;
    this->geometryShaderC = geometryShaderC;
    this->tesselationControlShaderC = tesselationControlShaderC;
    this->tesselationEvaluationShaderC = tesselationEvaluationShaderC;

    m_vertexShader = ::compileShader(vertexShaderC, GL_VERTEX_SHADER);
    m_fragmentShader = ::compileShader(fragmentShaderC, GL_FRAGMENT_SHADER);
    m_geometryShader = -1;
    m_tesselationControlShader = -1;
    m_tesselationEvaluationShader = -1;
    if (geometryShaderC != nullptr)
        m_geometryShader = ::compileShader(
            geometryShaderC,
            GL_GEOMETRY_SHADER);
    if (tesselationControlShaderC != nullptr)
        m_tesselationControlShader = ::compileShader(
            tesselationControlShaderC,
            GL_TESS_CONTROL_SHADER);
    if (tesselationEvaluationShaderC != nullptr)
        m_tesselationEvaluationShader = ::compileShader(
            tesselationEvaluationShaderC,
            GL_TESS_EVALUATION_SHADER);

    m_program = ::linkProgram(
        m_vertexShader,
        m_fragmentShader,
        m_geometryShader,
        m_tesselationControlShader,
        m_tesselationEvaluationShader);

    glDeleteShader(m_vertexShader);
    glDeleteShader(m_fragmentShader);
    if (m_geometryShader != -1)
        glDeleteShader(m_geometryShader);
    if (m_tesselationControlShader != -1)
        glDeleteShader(m_tesselationControlShader);
    if (m_tesselationEvaluationShader != -1)
        glDeleteShader(m_tesselationEvaluationShader);
}

shader::~shader()
{
    glDeleteProgram(m_program);
}

void shader::use() const
{
    glUseProgram(m_program);
}

void shader::setb(const std::string& name, bool b) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()),
        static_cast<int>(b));
}

void shader::set1i(const std::string& name, int v) const
{
    glUniform1i(glGetUniformLocation(m_program, name.c_str()), v);
}

void shader::set1f(const std::string& name, float v) const
{
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), v);
}

void shader::set3f(const std::string& name, float v0, float v1, float v2) const
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), v0, v1, v2);
}

void shader::set3f(const std::string& name, const glm::vec3& v) const
{
    glUniform3f(glGetUniformLocation(m_program, name.c_str()), v.x, v.y, v.z);
}

void shader::set4f(const std::string& name, float v0, float v1, float v2, float v3) const
{
    glUniform4f(glGetUniformLocation(m_program, name.c_str()), v0, v1, v2, v3);
}

void shader::setMatrix4fv(const std::string& name, const glm::mat4& trans) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}

// ------------------------------------------------
// implementation

GLuint compileShader(const char* source, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    // Check for compilation errors
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Shader Compilation Failed:\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint linkProgram(
    GLuint vertexShader,
    GLuint fragmentShader,
    GLuint geometryShader,
    GLuint tesselationControlShader,
    GLuint tesselationEvaluationShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    if (geometryShader != -1)
        glAttachShader(program, geometryShader);
    if (tesselationControlShader != -1)
        glAttachShader(program, tesselationControlShader);
    if (tesselationEvaluationShader != -1)
        glAttachShader(program, tesselationEvaluationShader);
    glLinkProgram(program);

    // Check for linking errors
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cerr << "Program Linking Failed:\n" << infoLog << std::endl;
    }

    return program;
}