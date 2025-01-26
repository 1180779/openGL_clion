//
// Created by rdkgs on 1/24/2025.
//

#ifndef LIGHTDIRECTIONALFOLLOWING_HPP
#define LIGHTDIRECTIONALFOLLOWING_HPP

#include "lightSpotlight.hpp"
#include "../models/objectShape.hpp"
#include "../../interfaces/IFollowable.hpp"

class lightSpotlightFollowing : public lightSpotlight {
public:
    explicit lightSpotlightFollowing(IFollowable& obj) : m_obj(obj) { }

    [[nodiscard]] std::unique_ptr<lightSpotlight> clone() const override
        { return std::make_unique<lightSpotlightFollowing>(*this); }

    void update() override;

    glm::vec3 relDirection = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 relPos = glm::vec3(0, 0, 0);

private:
    IFollowable& m_obj;
};



#endif //LIGHTDIRECTIONALFOLLOWING_HPP
