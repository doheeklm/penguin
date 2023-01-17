/*
 *	포인터 연산으로 배열 반복하기
 */
#include <stdio.h>

#define SIZE 5

int main(int argc, char** argv)
{
	int arr[SIZE];

	arr[0] = 9;
	arr[1] = 22;
	arr[2] = 30;
	arr[3] = 23;
	arr[4] = 18;

//	int* ptr = &arr[0];
	int* ptr = arr;

	while( 1 )
	{
		printf( "%d\n", *ptr );
		if ( ptr == &arr[SIZE - 1] )
		{
			break;
		}

		ptr++;
	}

	return 0;
}
