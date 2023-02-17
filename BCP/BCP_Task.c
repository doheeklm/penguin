/* BCP_Task.c */
#include "BCP_Inc.h"

int TASK_Login()
{
	int					nRC = 0;
	int					nCurPos = 0;
	unsigned char		ucBuf[32];
	BCP_TLV_t			tTLV[2];	
	BCP_LoginReqData_t	tLoginReqData;
	BCP_ReqMsg_t		tReqMsg;

	memset( ucBuf, 0x00, sizeof(ucBuf) );
	memset( &tTLV, 0x00, sizeof(tTLV) );
	memset( &tLoginReqData, 0x00, sizeof(tLoginReqData) );

	do
	{
		printf( "\n...Login...\n" );
		printf( "ID : " );
		fgets( tLoginReqData.szLoginId, sizeof(tLoginReqData.szLoginId), stdin );
		ClearStdin( tLoginReqData.szLoginId );	
	
		if ( 0 == strcmp( tLoginReqData.szLoginId, "exit" ) )
		{
			printf( "Exit Program\n" );
			return BCP_rExitProgram;
		}

		printf( "PW : " );
		fgets( tLoginReqData.szLoginPw, sizeof(tLoginReqData.szLoginPw), stdin );
		ClearStdin( tLoginReqData.szLoginPw );	
		
	} while ( NULL != strchr(tLoginReqData.szLoginId, ' ') ||
			  NULL != strchr(tLoginReqData.szLoginPw, ' ') );

//	tReqMsg.tHeader.ucMsgType = LOGIN_REQ;

	nRC = ENCDEC_EncodingHeader( ucBuf, sizeof(ucBuf), &tReqMsg.tHeader );
	nCurPos += nRC;

	printf( "nCurPos = %d\n", nCurPos );

	tTLV[0].ucTag = BCP_TAG_LOGIN_ID;
	tTLV[0].usLength = (unsigned short)BCP_LOGIN_ID_LEN;
	
	strncpy( tTLV[0].acValue, tLoginReqData.szLoginId, strlen(tLoginReqData.szLoginId) );
	tTLV[0].acValue[ strlen(tTLV[0].acValue) ] = '\0';
	
	tTLV[1].ucTag = BCP_TAG_LOGIN_PW;
	tTLV[1].usLength = (unsigned short)BCP_LOGIN_PW_LEN;
	strncpy( tTLV[1].acValue, tLoginReqData.szLoginPw, strlen(tLoginReqData.szLoginPw) );
	tTLV[1].acValue[ strlen(tTLV[1].acValue) ] = '\0';
	
	int i = 0;
	for ( i = 0; i < 2; i++ )
	{
		printf( "%x", tTLV[i].ucTag );
		printf( "%d", tTLV[i].usLength );
		printf( "%s", tTLV[i].acValue );
	}
		
/*	ucBuf[0] = BCP_TAG_LOGIN_ID;
	unsigned short usLength = htons(BCP_LOGINID_LEN);
	ucBuf[1] = usLength & 0xff;
	ucBuf[2] = (usLength >> 8) & 0xff;
*/
	//0112HappyLoginxx0215passwordxxxxxxx

	return BCP_rOk;
}
