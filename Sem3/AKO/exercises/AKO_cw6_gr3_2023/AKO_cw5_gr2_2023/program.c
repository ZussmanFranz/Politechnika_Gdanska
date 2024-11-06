#include <stdio.h>

extern void wyswietl_EAX(unsigned long long);


void main()
{
	unsigned long long a;
	a = 0xfffffffffffffffe;
	wyswietl_EAX(a);

}