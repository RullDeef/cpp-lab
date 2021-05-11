#include "Vector.hpp"
#include <cmath>

double Vector::getLength() const
{
    return hypot(hypot(x, y), z);
}
