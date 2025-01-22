
#ifndef _1180779_TEXTURE_H_
#define _1180779_TEXTURE_H_

#include <string>
#include "glad/glad.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class texture 
{
public:
    int width() { return m_width; }
    int height() { return m_height; }
    int nrChanngels() { return m_nrChannels; }

    void use(int i = 0);

    texture(std::string source, GLenum format = GL_RGB);

private:
    int m_width;
    int m_height;
    int m_nrChannels;
    unsigned char* m_data;
    GLuint m_texture;
};

#endif