#include "pi.h"

#include <math.h>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

static double builtin_constant()
{
    return 3.14159265358979323846;
}

double viete_formula(unsigned iter_num)
{
    double r = 1;
    for (unsigned i = 0; i < iter_num; ++i)
    {
        double a = sqrt(2.);
        for (unsigned j = 0; j < i; ++j)
        {
            a = sqrt(2 + a);
        }
        r *= a / 2;
    }

    return 2 / r;
}

double wallis_formula(unsigned iter_num)
{
    double n = 2;
    double d = 1;
    double r = 1;

    for (unsigned i = 0; i < iter_num; ++i)
    {
        double double_i = 2. * (i + 1);
        r *= double_i * double_i / ((double_i - 1) * (double_i + 1));
    }

    return 2 * r;
}
