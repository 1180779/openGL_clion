

#ifndef U1180779_SCENE_MANAGER_H
#define U1180779_SCENE_MANAGER_H

#include "shader.hpp"
#include "shadersC.hpp"
#include "models/objectList.hpp"

#include "camera/camera.hpp"

#include "light/lightManager.hpp"
#include "camera/cameraManager.hpp"

class sceneManager 
{
public:
    explicit sceneManager(window& win) : cameraMan(win) { }

    void addObjects();
    void update(float dt);
    void render() const;

    shader sh = shader(vertexSS, fragmentSSCombined);
    shader shBezier = shader(
        vertexSBSS,
        fragmentSSCombined,
        nullptr,
        tesselacionControlSBSS,
        tesselationEvaluationSBSS);
    objectList list = objectList(sh, shBezier);
    lightManager lightMan;
    cameraManager cameraMan;
};

#endif