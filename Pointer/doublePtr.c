#include <stdio.h>
#include <stdlib.h>

void func(char **pptr, int size) //반환값 없음, char 이중 포인터 매개변수 지정
{
	*pptr = malloc(size); //char **pptr을 역참조하여 char *pptr에 메모리 할당
}

int main(int argc, char **argv)
{
	char *ptr;

	//단일 포인터 char *ptr의 메모리 주소는, char **과 같음, 할당할 크기도 넣음
	func(&ptr, sizeof(char));

	*ptr = 's';
	printf( "%c\n", *ptr );

	free(ptr); //동적 메모리 해제

	return 0;
}
