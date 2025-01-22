
#include "deltaTime.hpp"

void deltaTime::measure()
{
    currFrame = static_cast<float>(glfwGetTime());
    dt = currFrame - lastFrame;
    lastFrame = currFrame;
}
