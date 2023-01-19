/*
 *	제네릭 포인터를 역참조하면 컴파일 오류가 생성됨
 */

#include <stdio.h>

int main(int argc, char** argv)
{
	int var = 9;
	int* ptr = &var;
	void* gptr = ptr;

	printf( "%d\n", *gptr );

	return 0;
}
