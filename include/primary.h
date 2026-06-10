#ifndef SMATH_PRIMARY_H
#define SMATH_PRIMARY_H

#include "defs/typedef.h"
#include "defs/constdef.h"

/* the result of sm_sign */
#define SM_PLUS 1
#define SM_ZERO 0
#define SM_MINUS -1

/* the result of sm_cmp */
#define SM_EQ 0 /* equal */
#define SM_GT 1 /* greater than */
#define SM_LT 2 /* lower than */

#ifdef __cplusplus
#define NOEXC noexcept
extern "C" 
{
#else
#define NOEXC
#endif

Num sm_abs(Num) NOEXC;
Num sm_neg(Num) NOEXC;
i8 sm_sign(Num) NOEXC;

Num sm_ceil(i16, Num) NOEXC;
Num sm_floor(i16, Num) NOEXC;
Num sm_round(i16, Num) NOEXC;


i8 sm_cmp(Num, Num) NOEXC;
Num sm_min(Num, Num) NOEXC;
Num sm_max(Num, Num) NOEXC;
Num sm_clamp(Num, Num, Num) NOEXC;
Num sm_avr(Num, Num) NOEXC;
Num sm_mod(Num, Num) NOEXC;

#ifdef __cplusplus
}
#endif

#endif
