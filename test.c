#include "math/math.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>

#define profile_func_s32(func, ...)                           \
{                                                             \
	u64 last = __rdtsc();                                     \
	s32 a    = func(__VA_ARGS__);                             \
	u64 cur  = __rdtsc();                                     \
	                                                          \
	printf("%I32d = "#func" cycles: %I64d\n", a, cur - last); \
}

#define profile_func(func, ...)                             \
{                                                           \
	u64 last = __rdtsc();                                   \
	f64 a    = func(__VA_ARGS__);                           \
	u64 cur  = __rdtsc();                                   \
	                                                        \
	printf("%lf = "#func" cycles: %I64d\n", a, cur - last); \
}

void profile_math()
{
	profile_func_s32(__ceil, 2.3);
	profile_func_s32(__floor, 2.7);
	profile_func_s32(__round, 2.5);

	profile_func(__exp, 3.7);
	profile_func(__pow, 2.5, 6.3);
	profile_func(__sqrt, 25.0);
	profile_func(__root, 16.0, 4.0);

	profile_func(__cos, f64_PI);
	profile_func(__sin, f64_PI_2);
	profile_func(__tan, f64_PI_4);
	profile_func(__ctan, f64_PI_4);

	profile_func(__acos, 1);
	profile_func(__asin, -1);
	profile_func(__atan, 3);
	profile_func(__actan, 3);

	profile_func(__cosh, 6.3);
	profile_func(__sinh, 2.5);
	profile_func(__tanh, 1.98);
	profile_func(__ctanh, 7.3);

	profile_func(__acosh, 2.7);
	profile_func(__asinh, 3.5);
	profile_func(__atanh, 0.6);
	profile_func(__actanh, -5.3);

	profile_func(__log, 15.2);
	profile_func(__log2, 175.3);
	profile_func(__log10, 82.4);

	getchar();
}

int main()
{
	f64 rad  = 90 * f64_TO_RAD;
	f64 grad = f64_PI_2 * f64_TO_GRAD;
//	profile_math();
	return 0;
}
