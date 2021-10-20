#include <repromath.h>
#include <stdio.h>

int main()
{
    double x[] = {1., 2., 3.};
    double y[] = {4., -5., 6.};

    printf("address prior to use: %p\n", repromath::ddot);
    printf("result = %g\n", repromath::ddot(3, x, y));
    printf("address after using:  %p\n", repromath::ddot);
}
