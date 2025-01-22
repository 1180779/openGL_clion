
#ifndef U1180779_MATERIAL_H
#define U1180779_MATERIAL_H

#include <glm/glm.hpp>

struct material {
    material() 
        :   ambient(glm::vec3(0.0f, 0.0f, 0.0f)), 
            diffuse(glm::vec3(0.0f, 0.0f, 0.0f)), 
            specular(glm::vec3(0.0f, 0.0f, 0.0f)), 
            shininess(1.0f) { }
    material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
        :   ambient(ambient), 
            diffuse(diffuse), 
            specular(specular), 
            shininess(shininess) { }

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    
    static const material emerald;
    static const material jade;
    static const material obsidian;
    static const material pearl;
    static const material ruby;
    static const material turquoise;
    static const material brass;
    static const material bronze;
    static const material chrome;
    static const material copper;
    static const material gold;
    static const material silver;
    static const material blackPlastic;
    static const material cyanPlastic;
    static const material greenPlastic;
    static const material redPlastic;
    static const material whitePlastic;
    static const material yellowPlastic;
    static const material blackRubber;
    static const material cyanRubber;
    static const material greenRubber;
    static const material redRubber;
    static const material whiteRubber;
    static const material yellowRubber;
};

#endif