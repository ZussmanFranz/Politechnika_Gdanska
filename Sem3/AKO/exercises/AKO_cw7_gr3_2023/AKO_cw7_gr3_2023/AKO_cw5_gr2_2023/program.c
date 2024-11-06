#include <stdio.h>
#include <xmmintrin.h>

extern  void wyswietl_RAX(__m128);

//messagebox(hwnd,off,off,uint)

void main()
{
	__m128 a;
	a.m128_u64[0]= 0xfffffffffffffffe;
	a.m128_u64[1] =	0xffffffffffffffff;
	
	wyswietl_RAX(a);
}