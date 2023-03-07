/* CS_Util.c */
#include "CS_Inc.h"

int UTIL_IsBigEndian()
{
	union {
		uint32_t i;
		char c[4];
	} e = { 0x01000000 };

	return e.c[0];
}

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

void UTIL_ClearLine()
{
	while ( getchar() != '\n' );
}

void UTIL_PrtBuf( const char *pszBuf, int nBufLen )
{
	int i = 0;

	for ( i = 0; i < nBufLen; i++ )
	{
		if ( (i != 0) && (i % 50 == 0) )
		{
			PRT_LF;
		}

		printf( "%02x ", pszBuf[i] );
	}
}

int UTIL_InputData( const char *pszPrt, char *pszBuf, int nBufLen )
{
	CHECK_PARAM_RC( pszPrt );
	CHECK_PARAM_RC( pszBuf );

	printf( "%s: ", pszPrt );

	char *pszTemp;
	pszTemp = pszBuf;
	
	fgets( pszTemp, nBufLen, stdin );
	UTIL_ClearStdin( pszTemp );

	return CS_rOk;
}
