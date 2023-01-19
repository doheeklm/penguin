/*
 *	유사 함수 매크로 정의하기
 */

#define ADD(a, b) a + b

int main(int argc, char** argv)
{
	int x = 2;
	int y = 3;
	int z = ADD(x, y); // x + y;

	return 0;
}
