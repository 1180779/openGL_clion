#include "sphereShape.hpp"

std::map<key, std::unique_ptr<value>, keyCompare> sphereShape::s_spheresMap;

sphereShape::sphereShape(int sectors, int stacks) 
    : m_key(sectors, stacks)
{
    auto iterator = s_spheresMap.find(m_key);
    if(iterator == s_spheresMap.end()) 
    {
        /* not found. Construct and add to map */
        Sphere sphere(0.5f, sectors, stacks, true, 2);

        auto res = s_spheresMap.emplace(
            m_key,
            std::make_unique<value>(sphere));
        if (!res.second)
            throw "sphereShape map error";
    }
}

void sphereShape::render(shader& sh) const
{
    objectShape::render(sh);
    auto iterator = s_spheresMap.find(m_key);
    value& value = *iterator->second.get();
    value.render();
}

value::value(Sphere s)
{
    triangleCount = s.getIndexCount();

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, s.getInterleavedVertexSize(), s.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, s.getIndexSize(), s.getIndices(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, s.getInterleavedStride(), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, s.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void value::render() const
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 
        static_cast<unsigned int>(triangleCount), 
        GL_UNSIGNED_INT, 
        nullptr);
}

value::~value()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
