/*
 *	두 포인터의 산술연산 간격
 */

#include <stdio.h>

int main(int argc, char** argv)
{
	int var = 1;

	int* int_ptr = NULL;
	int_ptr = &var;

	char* char_ptr = NULL;
	char_ptr = (char*)&var;

	printf( "Before arithmetic: int_ptr: %u, char_ptr: %u\n",
			(unsigned int)int_ptr, (unsigned int)char_ptr );

	int_ptr++;
	char_ptr++;

	printf( "After arithmetic: int_ptr: %u, char_ptr: %u\n",
			(unsigned int)int_ptr, (unsigned int)char_ptr );

	return 0;
}
