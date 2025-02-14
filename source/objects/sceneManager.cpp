
#include "sceneManager.hpp"
#include "camera/movingCamera.hpp"
#include "camera/followingCamera.hpp"
#include "camera/followingRotatableCamera.hpp"

#include "light/lightSpotlightFollowing.hpp"

#include "models/sphereShape.hpp"

void sceneManager::addObjects()
{
    /* objects */
    glm::vec3 cubePositions[10] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    float angle = 50.f;
    for (auto cubePosition : cubePositions) {
        angle += 50.f;
        objectShape* obj = new cubeShape();
        obj->material = material::copper;
        obj->pos = cubePosition;
        list.addObject(obj);
    }

    auto s = new sphereShape();
    s->material = material::cyanPlastic;
    s->pos = glm::vec3(-5.0f, 0.0f, 0.0f);
    list.addObject(s);

    auto s2 = new sphereShape(10, 6);
    s2->material = material::ruby;
    s2->pos = glm::vec3(3.0f, 7.0f, 0.0f);
    list.addObject(s2);

    auto b = new bezierShape();
    b->pos = glm::vec3(0.0f, 2.0f, 0.0f);
    b->material = material::jade;
    list.m_bezier = b;

    /* lights */

    lightSpotlight spotlight;
    spotlight.setPos(glm::vec3(0.0f, 0.0f, 3.0f));
    spotlight.m_direction = glm::vec3(0.0f, 0.0f, -1.0f);
    lightMan.addSpotlight(spotlight);

    lightDirectional lightDir;
    lightDir.m_direction = glm::vec3(0.0f, -1.0f, 0.0f);
    lightMan.addDirectionalLight(lightDir);

    lightPoint pointLight;
    pointLight.setPos(glm::vec3(-3.8f, -4.0f, -12.3f));
    lightMan.addPointLight(pointLight);

    pointLight.setPos(list.m_objs[5]->pos + glm::vec3(0.0f, 2.0f, 0.0f));
    lightMan.addPointLight(pointLight);

    lightSpotlightFollowing spotF(*list.m_objs[2]);
    spotF.relPos = glm::vec3(0.0f, 0.0f, 2.0f);
    spotF.relDirection = glm::normalize(-spotF.relPos);
    lightMan.addSpotlight(spotF);

    /* cameras */

    movingCamera c;
    c.pos = glm::vec3(10.0f, 10.0f, 10.0f);
    cameraMan.addCamera(c);

    cameraMan.nextCamera();
    std::unique_ptr<lightSpotlightFollowing> flashlight =
        std::make_unique<lightSpotlightFollowing>(cameraMan.getCamera());
    flashlight->relPos = glm::vec3(0.0f, 0.0f, 0.0f);
    lightMan.addFlashlight(flashlight);

    cameraMan.addCamera(cameraBase());

    followingCamera fc(*list.m_objs[2]);
    fc.relPos = glm::vec3(0.0f, 4.0f, 4.0f);
    cameraMan.addCamera(fc);

    followingRotatableCamera frc(*list.m_objs[2]);
    frc.relPos = glm::vec3(0.0f, 4.0f, 4.0f);
    cameraMan.addCamera(frc);

    followingRotatableCamera frc2(*list.m_objs[4]);
    frc2.relPos = glm::vec3(0.0f, 4.0f, 4.0f);
    cameraMan.addCamera(frc2);
}

void sceneManager::update(float dt)
{
    list.update(dt);
    lightMan.update(dt);
    cameraMan.update(dt);
}

void sceneManager::render() const
{
    const cameraBase& cam = cameraMan.getCamera();
    list.render(cam, lightMan);
    lightMan.render(cam);
}
