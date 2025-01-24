
#ifndef U1180779_LIGHT_POINT_H
#define U1180779_LIGHT_POINT_H

#include "lightSource.hpp"

class lightPoint : public lightSource, public IClonable<lightPoint>
{
public:
    void setForShader(
        const shader& sh, 
        const std::string& structShName) const override;
    // virtual void render(camera& cam) const {} /* same as in lightSource */

    [[nodiscard]] std::unique_ptr<lightPoint> clone() const override
        { return std::make_unique<lightPoint>(*this); }

    /* atteniuation */
    float m_constant = 1.0f;
    float m_linear = 0.09f;
    float m_quadratic = 0.032f;
};

#endif
