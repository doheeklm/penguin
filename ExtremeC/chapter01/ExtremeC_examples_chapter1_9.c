/*
 *	C에서 포인터 변수를 선언하고 사용하는 방법
 */

int main(int argc, char** argv)
{
	int var = 100;
	int *ptr = 0;
	ptr = &var;
	*ptr = 200;

	return 0;
}
