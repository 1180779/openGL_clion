
#ifndef U1180779_SPHERE_SHAPE_H
#define U1180779_SPHERE_SHAPE_H

#include "objectShape.hpp"
#include "../sphere/Sphere.h"

#include "glad/glad.h"

#include <memory>
#include <map>

// TODO:    add counter of sphere instances 
//          and free resources when last spehere is destroyed

struct key
{
    key(int sectors, int stacks)
    {
        setSectors(sectors);
        setStacks(stacks);
    }

    int getSectors() const { return sectorCount; }
    int setSectors(int s) { 
        return sectorCount = std::max(s_minSectors, std::min(s_maxSectors, s));
    }
    int getStacks() const { return stackCount; }
    int setStacks(int s) {
        return stackCount = std::max(s_minStacks, std::min(s_maxStacks, s));
    }

    static constexpr int s_maxSectors = 1024;
    static constexpr int s_minSectors = 2;
    static constexpr int s_maxStacks = 1024;
    static constexpr int s_minStacks = 2;

private:
    int sectorCount;
    int stackCount;
};

struct keyCompare
{
    bool operator()(const key& lhs, const key& rhs) const
    {
        int l = key::s_maxSectors * lhs.getSectors() + lhs.getStacks();
        int r = key::s_maxSectors * rhs.getSectors() + rhs.getStacks();
        return l < r;
    }
};

struct value
{
    int triangleCount;
    GLuint VBO;
    GLuint EBO;
    GLuint VAO;

    value(Sphere s);
    void render() const;
    ~value();
};

class sphereShape : public objectShape 
{
public:
    sphereShape(int sectors = 36, int stacks = 18);
    void render(shader& sh) const override;

private:
    key m_key;
    static std::map<key, std::unique_ptr<value>, keyCompare> s_spheresMap;
};

#endif