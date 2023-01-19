/*
 *	[예제 2-1]의 main 함수
 */
#include <stdio.h>
#include "ExtremeC_examples_chapter2_1.h"

int main( int argc, char** argv )
{
	double average = 0;

	//배열 선언
	int array[5];

	//배열 채우기
	array[0] = 10;
	array[1] = 3;
	array[2] = 5;
	array[3] = -8;
	array[4] = 9;

	//'avg' 함수로 평균 계산하기
	average = avg( array, 5, NORMAL );
	printf( "The average: %f\n", average );

	average = avg( array, 5, SQUARED );
	printf( "The squared average: %f\n", average );

	return 0;
}
