

#ifndef U1180779_KEY_BINDS_H
#define U1180779_KEY_BINDS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct keyBinds {
    int forward = GLFW_KEY_W;
    int backward = GLFW_KEY_S;
    int left = GLFW_KEY_A;
    int right = GLFW_KEY_D;
    int up = GLFW_KEY_Z;
    int down = GLFW_KEY_X;

    int cameraNext = GLFW_KEY_N;
    int cameraPrev = GLFW_KEY_M;
};

#endif