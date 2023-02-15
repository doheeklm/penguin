/*
 *	[예제 2-5]의 main 함수
 */
#include <stdio.h>

int add( int, int );

int main( int argc, char** argv )
{
	int x = add(5, 6);

	printf( "Result: %d\n", x );

	return 0;
}
