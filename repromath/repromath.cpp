#include "repromath.h"

#include <algorithm>
#include <numeric>

auto repromath::ddot(int n, double const *x, double const *y) -> double
{
    return std::inner_product(x, x + n, y, 0.);
}

auto repromath::dsum(int n, double const *x) -> double
{
    return std::accumulate(x, x + n, 0.);
}
