
#ifndef U1180779_OBJECTLIST_H
#define U1180779_OBJECTLIST_H

#include "shader.hpp"
#include "objectShape.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "camera.hpp"
#include "lightBase.hpp"

#include "lightManager.hpp"

class objectList 
{
public:
    objectList(shader& sh);
    ~objectList();

    objectList& addObject(objectShape* obj);

    void reset() { m_trans = glm::mat4(1.0f); }
    virtual objectList& translate(const glm::vec3& v);
    virtual objectList& rotate(const float angle, const glm::vec3& v);
    virtual objectList& scale(const glm::vec3& v);

    void update(float dt);

    void render(
        const cameraBase& cam, 
        const lightManager& lightMan, 
        const std::string name = "model") const;

    shader& m_sh;
    std::vector<objectShape*> m_objs;
    glm::mat4 m_trans = glm::mat4(1.0f);
};

#endif