//
// Created by rdkgs on 1/25/2025.
//

#ifndef IFOLLOWABLE_HPP
#define IFOLLOWABLE_HPP

#include <glm/glm.hpp>

template<typename T, typename PosT>
class IFollowableGeneric {
public:
    virtual ~IFollowableGeneric() = default;

    [[nodiscard]] virtual T getYaw() const = 0;
    [[nodiscard]] virtual T getPitch() const = 0;
    [[nodiscard]] virtual T getRoll() const = 0;
    [[nodiscard]] virtual PosT getPos() const = 0;
};

using IFollowable = IFollowableGeneric<float, glm::vec3>;

#endif //IFOLLOWABLE_HPP
