#include <Windows.h>
#include <libloaderapi.h>
#include <stdio.h>

template <auto Fn> static void perr(char const *banner, FILE *fp)
{
    LPSTR msg = nullptr;
    auto n = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            NULL, Fn(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msg, 0, NULL);
    fprintf(fp, "%s: %.*s\n", banner, int(n), msg);
    LocalFree(msg);
}

int main()
{
    double x[] = {1., 2., 3.};
    double y[] = {4., -5., 6.};
    auto handle = ::LoadLibraryW(L"repromath.dll");
    // error handling
    if (handle == INVALID_HANDLE_VALUE)
    {
        perr<GetLastError>("main", stderr);
        return 1;
    }
    typedef auto ddot_t(int, double const *, double const *) -> double;
    auto ddot = (ddot_t *)::GetProcAddress(handle, "?ddot@repromath@@YANHPEBN0@Z");

    printf("result = %g\n", ddot(3, x, y));
    ::FreeLibrary(handle);
}