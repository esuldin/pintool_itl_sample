#pragma once

#include "api_defines.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

double API builtin_constant();
double API viete_formula(unsigned iter_num);
double API wallis_formula(unsigned iter_num);

#ifdef __cplusplus
};
#endif // __cplusplus