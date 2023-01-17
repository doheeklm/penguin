/*
 *	값에 의한 전달 함수 호출의 예
 */
#include <stdio.h>

void func(int a)
{
	a = 5;
}

int main(int argc, char** argv)
{
	int x = 3;

	printf( "Before function call: %d\n", x );

	func( x );
	
	printf( "After function call: %d\n", x );

	return 0;
}
