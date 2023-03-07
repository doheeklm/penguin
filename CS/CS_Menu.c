/* CS_Menu.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int MENU_Create()
{
	int nRC = 0, nPos = 0;
	
	char szPosition[5]; //Position을 문자열로 받음
	char szTitle[5]; //Title을 문자열로 받음
	CS_CreateReqData_t tCreateReqData; //Client에게 입력받은 데이터
	unsigned short usBitmask = 0x00; //Client에게 입력받은 데이터 확인용
	CS_Header_t tReqHeader; //Request 메시지 헤더
	unsigned char ucReqBuf[CS_REQ_BUF_LEN]; //Request 메시지 총 버퍼
	
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN]; //Response 메시지 헤더 버퍼
	CS_Header_t tResHeader; //Response 메시지 헤더 저장할 구조체
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN]; //Response 메시지 바디 버퍼
	CS_ResBody_t tResBody; //Response 메시지 바디 저장할 구조체

	memset( &szPosition, 0x00, sizeof(szPosition) );
	memset( &szTitle, 0x00, sizeof(szTitle) );
	memset( &tCreateReqData, 0x00, sizeof(tCreateReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	do
	{
		nRC = UTIL_InputData( "(M) Name", tCreateReqData.szName, sizeof(tCreateReqData.szName) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szName) );

	do
	{
		nRC = UTIL_InputData( "(M) Company", tCreateReqData.szCompany, sizeof(tCreateReqData.szCompany) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szCompany) );

	do
	{
		nRC = UTIL_InputData( "(M) Team", tCreateReqData.szTeam, sizeof(tCreateReqData.szTeam) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szTeam) );

	do
	{
		nRC = UTIL_InputData( "(M 0x01~0x0E) Position", szPosition, sizeof(szPosition) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(szPosition) ||
			  CS_EMPTY_INPUT == strtol(szPosition, NULL, 0) );

	tCreateReqData.ucPosition = (unsigned char)strtol(szPosition, NULL, 0);

	nRC = UTIL_InputData( "(O 0x01~0x09) Title", szTitle, sizeof(szTitle) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	tCreateReqData.ucTitle = (unsigned char)strtol(szTitle, NULL, 0);
	
	do
	{
		nRC = UTIL_InputData( "(M 11bytes) Mobile", tCreateReqData.szMobile, sizeof(tCreateReqData.szMobile) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_LEN_MOBILE != strlen(tCreateReqData.szMobile) );

	nRC = UTIL_InputData( "(O) Tel", tCreateReqData.szTel, sizeof(tCreateReqData.szTel) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	do
	{
		nRC = UTIL_InputData( "(M) Email", tCreateReqData.szEmail, sizeof(tCreateReqData.szEmail) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szEmail) );
	
	printf( "\n(M)%s/(M)%s/(M)%s/(M)%02x/(O)%02x/(M)%s/(O)%s/(M)%s\n",
			tCreateReqData.szName, tCreateReqData.szCompany,
			tCreateReqData.szTeam, tCreateReqData.ucPosition,
			tCreateReqData.ucTitle, tCreateReqData.szMobile,
			tCreateReqData.szTel, tCreateReqData.szEmail );

	CS_SET_MASK_CREATE_REQ( &usBitmask, tCreateReqData ); //FULL INPUT : 0000 1111 1111 0000

	/*
	 *	Request Message for 'Create'
	 */

	tReqHeader.ucMsgType = CS_MSG_CREATE_REQ;

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
	
	nRC = ENCDEC_EncodingCreateBody( &ucReqBuf[nPos], sizeof(ucReqBuf) - nPos, &tCreateReqData, usBitmask );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingCreateBody fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, sizeof(ucReqBuf), CS_rErrOverflow );
	}

	encdec_SetBodyLen( ucReqBuf, nPos - CS_RES_HEADER_BUF_LEN );	
	ucReqBuf[ strlen(ucReqBuf) ] = '\0';

	PRT_TITLE( "Request" )
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
	
#ifdef SIM
	SIM_Create( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/*
	 *	Response Message for 'Create'
	 */

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

	PRT_TITLE( "Response" );
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
			printf( "\nCard Id = %02x\n", tResBody.u.unCardId );
		}
			break;
		case CS_RC_FAIL:
		{
			printf( "\nError Code = %02x\n", tResBody.u.ucErrCode );
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

int MENU_Search()
{
	int nRC = 0, nPos = 0, nIndex = 0;
	
	char szCardId[CS_LEN_CARD_ID + 1]; //Card Id를 문자열로 받음
	CS_SearchReqData_t tSearchReqData; //Client에게 입력받은 데이터
	unsigned short usBitmask = 0x00; //Client게 입력받은 데이터 확인용
	CS_Header_t tReqHeader; //Request 메시지 헤더
	unsigned char ucReqBuf[CS_REQ_BUF_LEN]; //Request 메시지 총 버퍼

	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN]; //Response 메시지 헤더 버퍼
	CS_Header_t tResHeader; //Response 메시지 헤더 저장할 구조체
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN]; //Response 메시지 바디 버퍼
	CS_ResBody_t tResBody; //Response 메시지 바디 저장할 구조체

	memset( szCardId, 0x00, sizeof(szCardId) );
	memset( &tSearchReqData, 0x00, sizeof(tSearchReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	nRC = UTIL_InputData( "(O) Name", tSearchReqData.szName, sizeof(tSearchReqData.szName) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	nRC = UTIL_InputData( "(O) Company", tSearchReqData.szCompany, sizeof(tSearchReqData.szCompany) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	nRC = UTIL_InputData( "(O) Card Id", szCardId, sizeof(szCardId) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	STR_TO_INT( szCardId, tSearchReqData.unCardId );
	
	printf( "\n(O)%s/(O)%s/(O)%d\n",
			tSearchReqData.szName, tSearchReqData.szCompany,
			tSearchReqData.unCardId );

	CS_SET_MASK_SEARCH_DELETE_REQ( &usBitmask, tSearchReqData ); //FULL INPUT : 0000 0000 0011 1000

	/*
	 *	Request Message for 'Search'
	 */

	tReqHeader.ucMsgType = CS_MSG_SEARCH_REQ;

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
	
	nRC = ENCDEC_EncodingSearchBody( &ucReqBuf[nPos], sizeof(ucReqBuf) - nPos, &tSearchReqData, usBitmask );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingSearchBody fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, sizeof(ucReqBuf), CS_rErrOverflow );
	}

	encdec_SetBodyLen( ucReqBuf, nPos - CS_RES_HEADER_BUF_LEN );	
	ucReqBuf[ strlen(ucReqBuf) ] = '\0';

	PRT_TITLE( "Request" )
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
	
#ifdef SIM
	SIM_Search( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/*
	 *	Response Message for 'Search'
	 */

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

	PRT_TITLE( "Response" );
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
			printf( "\n조회된 명함 정보 개수 %d\n", tResBody.u.tSearchResData.usTotalCnt );

			for ( nIndex = 0; nIndex < tResBody.u.tSearchResData.usTotalCnt; nIndex++ )
			{
				PRT_DETAIL_INFO( tResBody.u.tSearchResData.tDetailInfo[nIndex] );
			}
		}
			break;
		case CS_RC_FAIL:
		{
			printf( "\nError Code = %02x\n", tResBody.u.ucErrCode );
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

int MENU_Delete()
{
	int nRC = 0, nPos = 0, nIndex = 0;
	
	char szCardId[CS_LEN_CARD_ID + 1]; //Card Id를 문자열로 받음
	CS_DeleteReqData_t tDeleteReqData; //Client에게 입력받은 데이터
	unsigned short usBitmask = 0x00; //Client에게 입력받은 데이터 확인용
	CS_Header_t tReqHeader; //Request 메시지 헤더
	unsigned char ucReqBuf[CS_REQ_BUF_LEN]; //Request 메시지 총 버퍼

	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN]; //Response 메시지 헤더 버퍼
	CS_Header_t tResHeader; //Response 메시지 헤더 저장할 구조체
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN]; //Response 메시지 바디 버퍼
	CS_ResBody_t tResBody; //Response 메시지 바디 저장할 구조체

	memset( szCardId, 0x00, sizeof(szCardId) );
	memset( &tDeleteReqData, 0x00, sizeof(tDeleteReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	do
	{
		usBitmask = 0x00;

		nRC = UTIL_InputData( "(C) Name", tDeleteReqData.szName, sizeof(tDeleteReqData.szName) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}

		nRC = UTIL_InputData( "(C) Company", tDeleteReqData.szCompany, sizeof(tDeleteReqData.szCompany) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}

		nRC = UTIL_InputData( "(C) Card Id", szCardId, sizeof(szCardId) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
		STR_TO_INT( szCardId, tDeleteReqData.unCardId );
		
		CS_SET_MASK_SEARCH_DELETE_REQ( &usBitmask, tDeleteReqData ); //FULL INPUT : 0000 0000 0011 1000

	} while ( 0 == (0x00 | usBitmask) );
	
	printf( "\n(C)%s/(C)%s/(C)%d\n",
			tDeleteReqData.szName, tDeleteReqData.szCompany, tDeleteReqData.unCardId );

	/*
	 *	Request Message for 'Delete'
	 */

	tReqHeader.ucMsgType = CS_MSG_DELETE_REQ;

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
	
	nRC = ENCDEC_EncodingDeleteBody( &ucReqBuf[nPos], sizeof(ucReqBuf) - nPos, &tDeleteReqData, usBitmask );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingDeleteBody fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, sizeof(ucReqBuf), CS_rErrOverflow );
	}

	encdec_SetBodyLen( ucReqBuf, nPos - CS_RES_HEADER_BUF_LEN );	
	ucReqBuf[ strlen(ucReqBuf) ] = '\0';

	PRT_TITLE( "Request" )
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
	
#ifdef SIM
	SIM_Delete( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/*
	 *	Response Message for 'Delete'
	 */

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

	PRT_TITLE( "Response" );
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
			printf( "\n삭제된 명함 정보 개수 %d\n", tResBody.u.tDeleteResData.usTotalCnt );

			for ( nIndex = 0; nIndex < tResBody.u.tDeleteResData.usTotalCnt; nIndex++ )
			{
				PRT_SIMPLE_INFO( tResBody.u.tDeleteResData.tSimpleInfo[nIndex] );
			}
		}
			break;
		case CS_RC_FAIL:
		{
			printf( "\nError Code = %02x\n", tResBody.u.ucErrCode );
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

int MENU_Logout()
{
	int nRC = 0, nPos = 0;

	CS_Header_t tReqHeader; //Request 메시지 헤더
	unsigned char ucReqBuf[CS_REQ_BUF_LEN]; //Request 메시지 총 버퍼
	
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN]; //Response 메시지 헤더 버퍼
	CS_Header_t tResHeader; //Response 메시지 헤더 저장할 구조체
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN]; //Response 메시지 바디 버퍼
	CS_ResBody_t tResBody; //Response 메시지 바디 저장할 구조체

	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	/*
	 *	Request Message for 'Logout'
	 */

	tReqHeader.ucMsgType = CS_MSG_LOGOUT_REQ;

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

	nRC = ENCDEC_EncodingTLVLong( &ucReqBuf[nPos], sizeof(ucReqBuf) - nPos, CS_TAG_SESSION_ID, (unsigned short)CS_LEN_SESSION_ID, g_tEnv.ulSessionId );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingTLVLong fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, sizeof(ucReqBuf) - nPos, CS_rErrOverflow );
	}

	encdec_SetBodyLen( ucReqBuf, nPos - CS_RES_HEADER_BUF_LEN );	
	ucReqBuf[ strlen(ucReqBuf) ] = '\0';

	PRT_TITLE( "Request" )
		UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;

#ifdef SIM
	SIM_Logout( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/*
	 *	Response Message for 'Logout'
	 */

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

	PRT_TITLE( "Response" );
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
			PRT_LF;
		}
			break;
		case CS_RC_FAIL:
		{
			printf( "\nError Code = %02x\n", tResBody.u.ucErrCode );
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
