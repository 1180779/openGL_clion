
#ifndef U1180779_OBJECTLIST_H
#define U1180779_OBJECTLIST_H

#include "../shader.hpp"
#include "objectShape.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "../camera/camera.hpp"
#include "../light/lightBase.hpp"

#include "../light/lightManager.hpp"

#include "bezierShape.hpp"

class objectList 
{
public:
    explicit objectList(shader& sh, shader& shBezier);
    virtual ~objectList();

    objectList& addObject(objectShape* obj);

    void reset() { m_trans = glm::mat4(1.0f); }
    virtual objectList& translate(const glm::vec3& v);
    virtual objectList& rotate(float angle, const glm::vec3& v);
    virtual objectList& scale(const glm::vec3& v);

    void update(float dt);

    void render(
        const cameraBase& cam, 
        const lightManager& lightMan, 
        const std::string& name = "model") const;

    shader& m_sh;
    std::vector<objectShape*> m_objs;

    shader& m_shBezier;
    bezierShape* m_bezier = nullptr;

    glm::mat4 m_trans = glm::mat4(1.0f);
};

#endif