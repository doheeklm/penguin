/*
 *	매크로에서 #와 ## 연산자 사용하기
 */

#include <stdio.h>
#include <string.h>

#define CMD(NAME) \
	char NAME ## _cmd[256] = ""; \
	strcpy(NAME ## _cmd, #NAME);

int main(int argc, char** argv)
{
	CMD(copy);
	CMD(paste);
	CMD(cut);

	char cmd[256];
	scanf("%s", cmd);
	
	if ( strcmp(cmd, copy_cmd) == 0 )
	{
		printf( "copy_cmd\n" );	
	}

	if ( strcmp(cmd, paste_cmd) == 0 )
	{
		printf( "paste_cmd\n" );	
	}

	if ( strcmp(cmd, cut_cmd) == 0 )
	{
		printf( "cut_cmd\n" );	
	}

	return 0;
}
