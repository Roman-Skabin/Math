#include "math/math.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <math.h>
#include <intrin.h>

#define test_s32_func(my_func, crt_func, ...)                                                          \
{                                                                                                      \
	u64 my_last = __rdtsc();                                                                           \
	s32 my_res  = my_func(__VA_ARGS__);                                                                \
	u64 my_cur  = __rdtsc();                                                                           \
                                                                                                       \
	u64 crt_last = __rdtsc();                                                                          \
	s32 crt_res  = (s32)crt_func(__VA_ARGS__);                                                         \
	u64 crt_cur  = __rdtsc();                                                                          \
                                                                                                       \
	printf(#my_func"(%s) = %I32d\tcycles: %I64u\n"       , #__VA_ARGS__,  my_res,  my_cur -  my_last); \
	printf("  "#crt_func"(%s) = %I32d\tcycles: %I64u\n\n", #__VA_ARGS__, crt_res, crt_cur - crt_last); \
}

#define test_f64_func(my_func, crt_func, ...)                                                        \
{                                                                                                    \
	u64 my_last = __rdtsc();                                                                         \
	f64 my_res  = my_func(__VA_ARGS__);                                                              \
	u64 my_cur  = __rdtsc();                                                                         \
                                                                                                     \
	u64 crt_last = __rdtsc();                                                                        \
	f64 crt_res  = crt_func(__VA_ARGS__);                                                            \
	u64 crt_cur  = __rdtsc();                                                                        \
                                                                                                     \
	printf(#my_func"(%s) = %lf\tcycles: %I64u\n"       , #__VA_ARGS__,  my_res,  my_cur -  my_last); \
	printf("  "#crt_func"(%s) = %lf\tcycles: %I64u\n\n", #__VA_ARGS__, crt_res, crt_cur - crt_last); \
}

#define test_f32_func(my_func, crt_func, ...)                                                       \
{                                                                                                   \
	u64 my_last = __rdtsc();                                                                        \
	f32 my_res  = my_func(__VA_ARGS__);                                                             \
	u64 my_cur  = __rdtsc();                                                                        \
                                                                                                    \
	u64 crt_last = __rdtsc();                                                                       \
	f32 crt_res  = crt_func(__VA_ARGS__);                                                           \
	u64 crt_cur  = __rdtsc();                                                                       \
                                                                                                    \
	printf(#my_func"(%s) = %f\tcycles: %I64u\n"       , #__VA_ARGS__,  my_res,  my_cur -  my_last); \
	printf("  "#crt_func"(%s) = %f\tcycles: %I64u\n\n", #__VA_ARGS__, crt_res, crt_cur - crt_last); \
}

void test_f64_math()
{
	test_s32_func(__ceil, ceil, 2.3);
	test_s32_func(__floor, floor, 2.7);
	test_s32_func(__round, round, 2.5);

	test_f64_func(__exp, exp, 3.7);
	test_f64_func(__pow, pow, 2.5, 6.3);
	test_f64_func(__sqrt, sqrt, 25.0);
	test_f64_func(__root, __root, 16.0, 4.0);

	test_f64_func(__cos, cos, _PI);
	test_f64_func(__sin, sin, _PI_2);
	test_f64_func(__tan, tan, _PI_4);
	test_f64_func(__ctan, __ctan, _PI_4);

	test_f64_func(__acos, acos, 1);
	test_f64_func(__asin, asin, -1);
	test_f64_func(__atan, atan, 3);
	test_f64_func(__actan, __actan, 3);

	test_f64_func(__cosh, cosh, 6.3);
	test_f64_func(__sinh, sinh, 2.5);
	test_f64_func(__tanh, tanh, 1.98);
	test_f64_func(__ctanh, __ctanh, 7.3);

	test_f64_func(__acosh, acosh, 2.7);
	test_f64_func(__asinh, asinh, 3.5);
	test_f64_func(__atanh, atanh, 0.6);
	test_f64_func(__actanh, __actanh, -5.3);

	test_f64_func(__log, log, 15.2);
	test_f64_func(__log2, log2, 175.3);
	test_f64_func(__log10, log10, 82.4);
}

void test_f32_math()
{
	test_s32_func(__ceilf, ceilf, 2.3f);
	test_s32_func(__floorf, floorf, 2.7f);
	test_s32_func(__roundf, roundf, 2.5f);

	test_f32_func(__expf, expf, 3.7f);
	test_f32_func(__powf, powf, 2.5f, 6.3f);
	test_f32_func(__sqrtf, sqrtf, 25.0f);
	test_f32_func(__rootf, __rootf, 16.0f, 4.0f);

	test_f32_func(__cosf, cosf, _PIf);
	test_f32_func(__sinf, sinf, _PI_2f);
	test_f32_func(__tanf, tanf, _PI_4f);
	test_f32_func(__ctanf, __ctanf, _PI_4f);

	test_f32_func(__acosf, acosf, 1.0f);
	test_f32_func(__asinf, asinf, -1.0f);
	test_f32_func(__atanf, atanf, 3.0f);
	test_f32_func(__actanf, __actanf, 3.0f);

	test_f32_func(__coshf, coshf, 6.3f);
	test_f32_func(__sinhf, sinhf, 2.5f);
	test_f32_func(__tanhf, tanhf, 1.98f);
	test_f32_func(__ctanhf, __ctanhf, 7.3f);

	test_f32_func(__acoshf, acoshf, 2.7f);
	test_f32_func(__asinhf, asinhf, 3.5f);
	test_f32_func(__atanhf, atanhf, 0.6f);
	test_f32_func(__actanhf, __actanhf, -5.3f);

	test_f32_func(__logf, logf, 15.2f);
	test_f32_func(__log2f, log2f, 175.3f);
	test_f32_func(__log10f, log10f, 82.4f);
}

int main()
{
	puts("f64 functions: \n\n");
	test_f64_math();

//	getchar();

	puts("\nf32 functions: \n\n");
	test_f32_math();

	getchar();
	return 0;
}
