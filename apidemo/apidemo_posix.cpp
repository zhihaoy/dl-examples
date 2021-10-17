#include <dlfcn.h>
#include <stdio.h>

static void perr(char const *banner, FILE *fp)
{
    fprintf(fp, "%s: %s\n", banner, ::dlerror());
}

int main()
{
    double x[] = {1., 2., 3.};
    double y[] = {4., -5., 6.};
    auto handle = ::dlopen("./librepromath.so", RTLD_LOCAL | RTLD_NOW);
    // error handling
    if (handle == nullptr)
    {
        perr("main", stderr);
        return 1;
    }
    typedef auto ddot_t(int, double const *, double const *) -> double;
    auto ddot = (ddot_t *)::dlsym(handle, "_ZN9repromath4ddotEiPKdS1_");

    printf("result = %g\n", ddot(3, x, y));
    ::dlclose(handle);
}