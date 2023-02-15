/*
 *	[예제 3-1]의 이미 선언된 함수를 사용하는 main 함수: 정의는 별도의 소스 파일에 있음
 */
int max(int, int);
int max_3(int, int, int);

int a = 5;
int b = 10;

int main(int argc, char** argv)
{
	int m1 = max(a, b);
	int m2 = max_3(5, 8, -1);
	return 0;
}
