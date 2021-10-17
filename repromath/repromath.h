#pragma once

#include "repromath_export.h"

namespace repromath
{
REPROMATH_EXPORT auto ddot(int n, double const *x, double const *y) -> double;
REPROMATH_EXPORT auto dsum(int n, double const *x) -> double;
}
