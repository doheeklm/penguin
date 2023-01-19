/*
 *	메모리에서 동일한 바이트 주소를 가리키는 세 가지 자료형으로부터 얻은 3개의 포인터
 */
#include <stdio.h>

typedef struct
{
	int x;
	int y;
} point_t;

typedef struct
{
	point_t center;
	int radius;
} circle_t;

int main(int argc, char** argv)
{
	circle_t c;
	
	circle_t* p1 = &c;

	point_t* p2 = (point_t *)&c;

	int* p3 = (int*)&c;

	printf( "p1: %p\n", (void*)p1 );
	printf( "p2: %p\n", (void*)p2 );
	printf( "p3: %p\n", (void*)p3 );

	return 0;
}
