
#ifndef _1180779_TEXTURE_H_
#define _1180779_TEXTURE_H_

#include <string>
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class texture 
{
public:
    [[nodiscard]] int width() const { return m_width; }
    [[nodiscard]] int height() const { return m_height; }
    [[nodiscard]] int nrChanngels() const { return m_nrChannels; }

    void use(int i = 0);

    explicit texture(std::string source, GLenum format = GL_RGB);

private:
    int m_width;
    int m_height;
    int m_nrChannels;
    unsigned char* m_data;
    GLuint m_texture;
};

#endif