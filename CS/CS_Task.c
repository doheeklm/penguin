/* CS_Task.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int TASK_Login()
{
	int nRC = 0, nPos = 0;

	/* Request  */
	CS_Header_t tReqHeader;
	CS_LoginReqData_t tLoginReqData;
	unsigned char ucReqBuf[CS_REQ_BUF_LEN];

	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( &tLoginReqData, 0x00, sizeof(tLoginReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );

	/* Response */
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN];
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN];
	CS_Header_t tResHeader;
	CS_ResBody_t tResBody;
	
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	/**************/
	/* Input Data */
	/**************/
	PRT_TITLE( "Login" );	
	do
	{
		nRC = UTIL_InputData( "ID", tLoginReqData.szLoginId, sizeof(tLoginReqData.szLoginId) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( NULL != strchr(tLoginReqData.szLoginId, CS_SPACE) ||
			  EMPTY_INPUT == strlen(tLoginReqData.szLoginId) );

	if ( 0 == strcmp( tLoginReqData.szLoginId, "exit" ) )
	{
		PRT_EXIT;
		return CS_rExitProgram;
	}

	do {
		nRC = UTIL_InputData( "PW", tLoginReqData.szLoginPw, sizeof(tLoginReqData.szLoginPw) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
		
	} while ( NULL != strchr(tLoginReqData.szLoginPw, CS_SPACE) ||
			  EMPTY_INPUT == strlen(tLoginReqData.szLoginPw) );

	printf( "\n%s/%s\n", tLoginReqData.szLoginId, tLoginReqData.szLoginPw ); 

	/*******************/
	/* Request Message */
	/*******************/
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
	PRT_TITLE( "Login Request" )
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

	/********************/
	/* Response Message */
	/********************/
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

	PRT_TITLE( "Login Response" );
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
			PRT_TITLE( "Success" );
			printf( "Session ID = %ld\n", g_tEnv.ulSessionId );

			//TODO Session ID byteordering
		}
			break;
		case CS_RC_FAIL:
		{
			PRT_TITLE( "Fail" );
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

	//RES_FIELD_MASK TODO

	return CS_rOk;
}

int TASK_Menu()
{
	int nSelect = 0, nRC = 0;
	
	while ( 1 )
	{
		PRT_MENU;
		printf( "Input: " );
		scanf( "%d", &nSelect );
		UTIL_ClearLine();
		
		if ( TASK_MENU(nSelect) )
		{
			switch( nSelect )
			{
				case MENU_CREATE:
				{
					PRT_TITLE( "Create" );

					nRC = MENU_Create();
					if ( CS_rOk != nRC )
					{
						LOG_ERR_F( "MENU_Create fail <%d>", nRC );
						return nRC;
					}
				}
					break;
				case MENU_SEARCH:
				{
					PRT_TITLE( "Search" );
				
					nRC = MENU_Search();
					if ( CS_rOk != nRC )
					{
						LOG_ERR_F( "MENU_Search fail <%d>", nRC );
						return nRC;
					}
				}
					break;
				case MENU_DELETE:
				{
					PRT_TITLE( "Delete" );

					nRC = MENU_Delete();
					if ( CS_rOk != nRC )
					{
						LOG_ERR_F( "MENU_Delete fail <%d>", nRC );
						return nRC;
					}
				}
					break;
				case MENU_LOGOUT:
				{
					PRT_TITLE( "Logout" );
				}
					break;
				case MENU_ADMIN:
				{
					return CS_rExitProgram;
				}
					break;
				default:
					return CS_rErrClientServerFail;
					break;
			}
		} 
	}
	
	return CS_rOk;
}
