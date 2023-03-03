/* CS_Util.c */
#include "CS_Inc.h"

void UTIL_ClearStdin( char *pszBuf )
{
	if ( NULL == pszBuf )
	{
		return;
	}

	if ( pszBuf[strlen(pszBuf) - 1] == '\n' )
	{
		pszBuf[strlen(pszBuf) - 1] = '\0';
	}

	__fpurge(stdin);
}

void UTIL_PrtBuf( const char *pszBuf, int nBufLen )
{
	int i = 0;

	for ( i = 0; i < nBufLen; i++ )
	{
		if ( i % 20 == 0 )
		{
			printf( "\n" );
		}
		printf( "%02x ", pszBuf[i] );
	}
}

