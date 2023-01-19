/*
 *	[예제 2-1]의 헤더 파일
 */
#ifndef EXTREMEC_EXAMPLES_CHAPTER_2_1_H
#define EXTREMEC_EXAMPLES_CHAPTER_2_1_H

typedef enum
{
	NONE,
	NORMAL,
	SQUARED
} average_type_t;

//함수 선언
double avg( int*, int, average_type_t );

#endif
