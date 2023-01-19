/*
 *	루프를 모방한 가변 인자 매크로 사용하기
 */

#include <stdio.h>

#define LOOP_3(X, ...) \
	printf( "%s\n", #X );

#define LOOP_2(X, ...) \
	printf( "%s\n", #X ); \
	LOOP_3( __VA_ARGS__ )

#define LOOP_1(X, ...) \
	printf( "%s\n", #X ); \
	LOOP_2( __VA_ARGS__ )

#define LOOP(X, ...) \
	LOOP_1( __VA_ARGS__ )

int main(int argc, char** argv)
{
	LOOP(copy paste cut)
	//단어 사이에 쉼표를 넣지 않고 copy paste cut을 통과시켰다.
	//전처리기는 이를 하나의 입력으로 받아들였고 모방된 루프는 한번만 반복됐다.

	LOOP(copy, paste, cut)
	//이 입력값들은 통과된 뒤 쉼표에 의해 단어가 분리되었다.
	//전처리기는 이들을 3개의 다른 인수로 처리했다.
	//따라서 모방된 루프는 세 번 반복된다.

	LOOP(copy, paste, cut, select)
	//copy, paste, cut, select라는 총 4개의 값을 통과시켰다.
	//하지만 이들 중 3개만이 처리되었다.
	//이 루프 매크로는 리스트의 요소를 3개까지만 처리할 수 있기 때문에
	//3번재 이후의 요소부터는 무시된다.

	return 0;
}
