/* CS_Util.c */
#include "CS_Inc.h"

void ClearStdin( char *pStr )
{
	if ( NULL == pStr )
	{
		return;
	}

	if ( pStr[strlen(pStr) - 1] == '\n' )
	{
		pStr[strlen(pStr) - 1] = '\0';
	}

	__fpurge(stdin);
}
