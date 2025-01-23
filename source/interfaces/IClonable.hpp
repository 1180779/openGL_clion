
#ifndef U1180779_I_CLONABLE_H
#define U1180779_I_CLONABLE_H

#include <memory>

template <typename BaseClassT>
class IClonable 
{
public:
    virtual ~IClonable() = default;

    virtual std::unique_ptr<BaseClassT> clone() const = 0;
};

#endif