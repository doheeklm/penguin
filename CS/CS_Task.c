/* CS_Task.c */
#include "CS_Inc.h"

int TASK_Login()
{
	int					nRC = 0;
	int					nCurPos = 0;
	unsigned char		ucBuf[32];
	memset( ucBuf, 0x00, sizeof(ucBuf) );

	do
	{
		printf( "\n...Login...\n" );
		printf( "ID : " );
		fgets( tLoginReqData.szLoginId, sizeof(tLoginReqData.szLoginId), stdin );
		ClearStdin( tLoginReqData.szLoginId );	
	
		if ( 0 == strcmp( tLoginReqData.szLoginId, "exit" ) )
		{
			printf( "Exit Program\n" );
			return CS_rExitProgram;
		}

		printf( "PW : " );
		fgets( tLoginReqData.szLoginPw, sizeof(tLoginReqData.szLoginPw), stdin );
		ClearStdin( tLoginReqData.szLoginPw );	
		
	} while ( NULL != strchr(tLoginReqData.szLoginId, ' ') ||
			  NULL != strchr(tLoginReqData.szLoginPw, ' ') );

	//nRC = ENCDEC_EncodingHeader( ucBuf, sizeof(ucBuf), &tReqMsg.tHeader );

	return CS_rOk;
}
