/* CS_Task.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int TASK_Login()
{
	int nRC = 0, nPos = 0;

	CS_Header_t tReqHeader, tResHeader;
	CS_LoginReqData_t tLoginReqData;
	CS_ResBody_t tResBody;
	
	unsigned char ucReqBuf[CS_REQ_BUF_LEN];
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN];
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN];

	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( &tLoginReqData, 0x00, sizeof(tLoginReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );

	do
	{
		printf( "\n... Login ...\n" );
		printf( "ID : " );
		fgets( tLoginReqData.szLoginId, sizeof(tLoginReqData.szLoginId), stdin );
		UTIL_ClearStdin( tLoginReqData.szLoginId );
	
		if ( 0 == strcmp( tLoginReqData.szLoginId, "exit" ) )
		{
			PRT_EXIT;
			return CS_rExitProgram;
		}

		printf( "PW : " );
		fgets( tLoginReqData.szLoginPw, sizeof(tLoginReqData.szLoginPw), stdin );
		UTIL_ClearStdin( tLoginReqData.szLoginPw );
		
	} while ( NULL != strchr(tLoginReqData.szLoginId, ' ') ||
			  NULL != strchr(tLoginReqData.szLoginPw, ' ') );

	printf( "\n%s/%s\n", tLoginReqData.szLoginId, tLoginReqData.szLoginPw ); 

	tReqHeader.ucMsgType = CS_MSG_LOGIN_REQ;

	nRC = ENCDEC_EncodingHeader( ucReqBuf, sizeof(ucReqBuf), &tReqHeader );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingHeader fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, sizeof(ucReqBuf), CS_rErrOverflow );
	}
	
	nRC = ENCDEC_EncodingLoginBody( &ucReqBuf[nPos], sizeof(ucReqBuf) - nPos, &tLoginReqData );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingLoginBody fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, sizeof(ucReqBuf), CS_rErrOverflow );
	}

	encdec_SetBodyLen( ucReqBuf, nPos - CS_RES_HEADER_BUF_LEN );	
	ucReqBuf[ strlen(ucReqBuf) ] = '\0';

#ifdef DEBUG
	PRT_REQ;
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
#endif

#ifdef SIM
	SIM_Login( ucResHeaderBuf, ucResBodyBuf );

#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( 0 > nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return CS_rErrReadFail;
	}
#endif
	nRC = ENCDEC_DecodingHeader( ucResHeaderBuf, &tResHeader );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "ENCDEC_DecodingHeader fail <%d>", nRC );
		return nRC;
	}

#ifdef RUN
	nRC = SOCK_Read( ucResBodyBuf, tResHeader.unBodyLen );
	if ( 0 > nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return CS_rErrReadFail;
	}
#endif
	PRT_RES;
	UTIL_PrtBuf( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	UTIL_PrtBuf( ucResBodyBuf, tResHeader.unBodyLen );

	nRC = ENCDEC_DecodingBody( ucResBodyBuf, tResHeader, &tResBody );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "ENCDEC_DecodingBody fail <%d>", nRC );
		return nRC;
	}

	switch ( tResBody.ucResultCode )
	{
		case CS_RC_SUCCESS:
		{
			g_tEnv.ulSessionId = tResBody.u.ulSessionId;
			PRT_SUCCESS;
			printf( "Session ID = %ld\n", g_tEnv.ulSessionId );
		}
			break;
		case CS_RC_FAIL:
		{
			PRT_FAIL;
			printf( "Error Code = %02x\n", tResBody.u.ucErrCode );
			return CS_rErrLoginFail;
		}
			break;
		default:
		{
			LOG_ERR_F( "wrong result code (%02x)", tResBody.ucResultCode );
			return CS_rErrSystemFail;
		}
			break;
	}

	return CS_rOk;
}

int TASK_Menu()
{
	int nSelect = 0;

	PRT_MENU;

	while ( 1 )
	{
		scanf( "%d", &nSelect );

		if ( TASK_MENU(nSelect) )
		{
			printf( "OK!\n" );
			break;
		}
		else
		{
			printf( "Input: " );
		}
	}

	sleep(10);

	return CS_rOk;
}
