#include "stdafx.h"
#define A 4
#define Z 13

#define SQR(x) (x)*(x)
#define MAX(y,z) ((y)>(z))?(y):(z)
#define MIN(y,z) ((y)<(z))?(y):(z)
#define ABS(x) ((x)<0)?(x)*(-1):(x)

#define OUTPUT(w) puts ("control output"); \
	printf(#w"=%d\n",w)

#define RESULT(w) puts ("result: "); \
	printf(#w"=%f\n", (float)w)

int _tmain(int argc, _TCHAR* argv[])
{
	int w, 
		x, 
		min, 
		max, 
		abs,
		maxSquared;

	#if 5<A<10
		
		puts("Input x value:");
		scanf("%d", &x);
		OUTPUT(x);

		min = MIN(A, Z);
		OUTPUT(min);

		max = MAX(x + Z, x*Z);
		OUTPUT(max);

		w = min * max;
		RESULT(w);

	#elif A<=5 && Z>=10

		puts("Input x value:");
		scanf("%d", &x);
		OUTPUT(x);

		abs = ABS(x - Z);
		OUTPUT(abs);

		max = MAX(abs, Z);
		OUTPUT(max);

		w = SQR(max);
		RESULT(w);

	#else

		puts("A and Z not match any cases above");

	#endif

	_getch();

	return 0;
}

