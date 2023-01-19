/*
 *	조건부 컴파일 예
 */

#define CONDITION

int main(int argc, char** argv)
{
#ifdef CONDITION
	int i = 0;
	i++;
#endif

	int j = 0;
	return 0;
}
