/*
 *	세그멘테이션 오류 상황 만들기
 */
#include <stdio.h>

int* create_an_integer(int default_value)
{
	int var = default_value;
	return &var;
}

int main()
{
	int* ptr = NULL;
	ptr = create_an_integer(10);
	printf( "%d\n", *ptr );
	return 0;
}
