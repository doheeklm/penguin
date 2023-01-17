/*
 *	참조에 의한 전달이 아닌 포인터에 의한 함수 호출의 예
 */
#include <stdio.h>

void func(int* a)
{
	int b = 9;
	*a = 5;
	a = &b;

	printf( "\na = %p\n", a );
	printf( "&b = %p\n\n", &b );
}

int main(int argc, char** argv)
{
	int x = 3;
	int* xptr = &x;

	printf( "Value before call: %d\n", x ); //3
	printf( "Pointer before function call: %p\n", (void *)xptr );

	func( xptr );

	printf( "Value after call: %d\n", x ); //5
	printf( "Pointer after function call: %p\n", (void *)xptr );

	return 0;
}
