/*
 *	[예제 3-1]의 두 함수의 정의를 포함하는 파일
 */
int max(int a, int b)
{
	return a > b ? a : b;
}

int max_3(int a, int b, int c)
{
	int temp = max(a, b);

	return c > temp ? c : temp;
}
