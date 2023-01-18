#include <stdio.h>

int main()
{
	char* stringp;
	char STRING[] = "archie";
	int* intp;
	int INT[] = { 7, 4, 9 };

	void* voidp;
	stringp = STRING;
	intp = INT;

	printf( "stringp %p\n", stringp );
	printf( "intp %p\n", intp );

	puts( stringp );
	puts( STRING );

	printf( "INT %d %d %d\n", INT[0], INT[1], INT[2] );
	printf( "intp %d %d %d\n", *intp, *(intp + 1), *(intp + 2) );

	voidp = stringp; //voidp = STRING;
	puts( (char *)voidp );
	printf( "(char *)voidp %p\n", (char *)voidp );
	printf( "(char *)voidp %c %c %c %c %c\n",
			*(char *)voidp,
			*((char *)voidp + 1),
			*((char *)voidp + 2),
			*((char *)voidp + 3),
			*((char *)voidp + 4) );

	voidp = intp; //voidp = INT;
	printf( "%d %d %d\n",
			*(int *)voidp,
			*((int *)voidp + 1),
			*((int *)voidp + 2) );

	voidp = STRING;
	for ( ; *(char *)voidp; (char *)voidp++ )
	{
		printf( "%c\n", *(char *)voidp );
	}

	voidp = INT;
	{
		int i;
		for ( i = 0; i < (sizeof(INT)/sizeof(int)); i++ )
		{
			printf( "%d\n", *(int *)voidp );
		}
	}

	return 0;
}
