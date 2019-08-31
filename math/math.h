// Copyright 2019 Roman Skabin
// 
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#pragma once

typedef __int8  s8;
typedef __int16 s16;
typedef __int32 s32;
typedef __int64 s64;

typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef float  f32;
typedef double f64;

#define _abs(x) ((x) < 0 ? (-(x)) : (x))

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

#ifdef __cplusplus
extern "C" {
#endif

s32 __vectorcall __ceil(f64 value);
s32 __vectorcall __floor(f64 value);
s32 __vectorcall __round(f64 value);

f64 __cdecl      __exp(f64 power);
f64 __cdecl      __pow(f64 base, f64 power);
f64 __vectorcall __sqrt(f64 base);
f64 __cdecl      __root(f64 base, f64 root);

f64 __cdecl __cos(f64 x);
f64 __cdecl __sin(f64 x);
f64 __cdecl __tan(f64 x);
f64 __cdecl __ctan(f64 x);

f64 __cdecl __acos(f64 x);
f64 __cdecl __asin(f64 x);
f64 __cdecl __atan(f64 x);
f64 __cdecl __actan(f64 x);

f64 __cdecl __cosh(f64 x);
f64 __cdecl __sinh(f64 x);
f64 __cdecl __tanh(f64 x);
f64 __cdecl __ctanh(f64 x);

f64 __cdecl __acosh(f64 x);
f64 __cdecl __asinh(f64 x);
f64 __cdecl __atanh(f64 x);
f64 __cdecl __actanh(f64 x);

f64 __cdecl __log(f64 x);
f64 __cdecl __log2(f64 x);
f64 __cdecl __log10(f64 x);

#ifdef __cplusplus
}
#endif

#define f64_E        2.718281828459045  // e
#define f64_LOG2E    1.4426950408889634 // log2(e)
#define f64_LOG10E   0.4342944819032518 // log10(e)
#define f64_LN2      0.6931471805599453 // ln(2)
#define f64_LN10     2.302585092994045  // ln(10)
#define f64_PI       3.141592653589793  // pi
#define f64_PI_2     1.570796326794896  // pi/2
#define f64_PI_4     0.7853981633974483 // pi/4
#define f64_1_PI     0.3183098861837906 // 1/pi
#define f64_2_PI     0.6366197723675813 // 2/pi
#define f64_2_SQRTPI 1.128379167095512  // 2/sqrt(pi)
#define f64_SQRT2    1.414213562373095  // sqrt(2)
#define f64_1_SQRT2  0.7071067811865475 // 1/sqrt(2)

#define f32_E        2.7182818f  // e
#define f32_LOG2E    1.44269504f // log2(e)
#define f32_LOG10E   0.43429448f // log10(e)
#define f32_LN2      0.69314718f // ln(2)
#define f32_LN10     2.3025850f  // ln(10)
#define f32_PI       3.1415926f  // pi
#define f32_PI_2     1.5707963f  // pi/2
#define f32_PI_4     0.78539816f // pi/4
#define f32_1_PI     0.31830988f // 1/pi
#define f32_2_PI     0.63661977f // 2/pi
#define f32_2_SQRTPI 1.1283791f  // 2/sqrt(pi)
#define f32_SQRT2    1.4142135f  // sqrt(2)
#define f32_1_SQRT2  0.70710678f // 1/sqrt(2)
