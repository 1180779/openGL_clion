
#ifndef U1180779_DELTA_TIME_H
#define U1180779_DELTA_TIME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct deltaTime
{
    deltaTime() = default;
    float currFrame = 0.0f;
    float lastFrame = 0.0f;
    float dt = 0.0f;

    inline float operator()() const { return dt; }
    void measure();
};

#endif
