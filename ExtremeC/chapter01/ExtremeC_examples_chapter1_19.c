/*
 *	다른 함수 여러 개를 호출하는 하나의 함수 포인터 예
 */
#include <stdio.h>

int sum(int a , int b)
{
	return a + b;
}

int subtract(int a, int b)
{
	return a - b;
}

int main()
{
	int result = 0;
	int (*func_ptr)(int, int);
	func_ptr = NULL;

	func_ptr = &sum;
	result = func_ptr(5, 4);
	printf( "Sum: %d\n", result );

	func_ptr = &subtract;
	result = func_ptr(5, 4);
	printf( "Subtract: %d\n", result );

	return 0;
}
