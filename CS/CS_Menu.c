/* CS_Menu.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int MENU_Create()
{
	int nRC = 0, nPos = 0;
	
	char szPosition[30]; //Position을 문자열로 받음
	char szTitle[30]; //Title을 문자열로 받음
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
		nRC = UTIL_InputData( "이름", tCreateReqData.szName, sizeof(tCreateReqData.szName) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szName) );

	do
	{
		nRC = UTIL_InputData( "회사명", tCreateReqData.szCompany, sizeof(tCreateReqData.szCompany) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szCompany) );

	do
	{
		nRC = UTIL_InputData( "부서", tCreateReqData.szTeam, sizeof(tCreateReqData.szTeam) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szTeam) );

	do
	{
		nRC = UTIL_InputData( "* { 사원, 대리, 과장, 차장, 부장, 주임, 선임, 책임, 수석, 이사, 상무 이사, 전무 이사, 사장, 회장 } 중에 입력해주세요\n"
							  "* 잘 못 입력한 경우 다시 입력 받습니다.\n"
							  "직위", szPosition, sizeof(szPosition) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( (CS_EMPTY_INPUT == strlen(szPosition)) ||
			( 0 > UTIL_MappingStrToPosition( szPosition, &(tCreateReqData.ucPosition), sizeof(szPosition) ) ) );

	do
	{
		nRC = UTIL_InputData( "* { 팀원, 파트장, 부서장, 실장, 본부장, 그룹장, 부문장, CTO, CEO } 중에 입력해주세요\n"
							  "* 입력하지 않으면 다음으로 넘어갑니다.\n"
							  "* 입력 했지만 잘 못 입력한 경우 다시 입력 받습니다.\n"
							  "직책", szTitle, sizeof(szTitle) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( 0 > UTIL_MappingStrToTitle( szTitle, &(tCreateReqData.ucTitle), sizeof(szTitle) ) );

	do
	{
		nRC = UTIL_InputData( "* 반드시 11자리로 입력해주세요\n"
							  "휴대전화 번호", tCreateReqData.szMobile, sizeof(tCreateReqData.szMobile) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_LEN_MOBILE != strlen(tCreateReqData.szMobile) );

	nRC = UTIL_InputData( "* 입력하지 않으면 다음으로 넘어갑니다.\n"
						  "유선전화 번호", tCreateReqData.szTel, sizeof(tCreateReqData.szTel) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	do
	{
		nRC = UTIL_InputData( "이메일", tCreateReqData.szEmail, sizeof(tCreateReqData.szEmail) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( CS_EMPTY_INPUT == strlen(tCreateReqData.szEmail) );
	
	printf( "\n%s / %s / %s / %02x / %02x / %s / %s / %s\n",
			tCreateReqData.szName, tCreateReqData.szCompany,
			tCreateReqData.szTeam, tCreateReqData.ucPosition,
			tCreateReqData.ucTitle, tCreateReqData.szMobile,
			tCreateReqData.szTel, tCreateReqData.szEmail );

	CS_SET_MASK_CREATE_REQ( &usBitmask, tCreateReqData ); //FULL INPUT : 0000 1111 1111 0000

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

	PRT_TITLE( "Request" )
	UTIL_PrtBuf( ucReqBuf, nPos );
	PRT_LF;

	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return nRC;
	}

	//SIM_Create( ucResHeaderBuf, ucResBodyBuf );

	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return nRC;
	}

	nRC = ENCDEC_DecodingHeader( ucResHeaderBuf, &tResHeader );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "ENCDEC_DecodingHeader fail <%d>", nRC );
		return nRC;
	}

	nRC = SOCK_Read( ucResBodyBuf, tResHeader.unBodyLen );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return nRC;
	}

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
			return CS_rErrFromServer;
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
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN];//CS_RES_BODY_BUF_LEN]; //Response 메시지 바디 버퍼
	char *pucNewResBodyBuf = NULL; //응답받은 bodylen이 내가 정한 바디버퍼보다 클 경우 malloc용
	CS_ResBody_t tResBody; //Response 메시지 바디 저장할 구조체

	memset( szCardId, 0x00, sizeof(szCardId) );
	memset( &tSearchReqData, 0x00, sizeof(tSearchReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	nRC = UTIL_InputData( "* 모두 입력 안 된 경우, 모든 명함 정보를 조회합니다.\n"
						  "이름", tSearchReqData.szName, sizeof(tSearchReqData.szName) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	nRC = UTIL_InputData( "회사명", tSearchReqData.szCompany, sizeof(tSearchReqData.szCompany) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
		return CS_rErrClientServerFail;
	}

	do
	{
		nRC = UTIL_InputData( "* 문자가 포함되면 다시 입력 받습니다. 범위(0~4,294,967,295) \n" 
							  "명함 ID", szCardId, sizeof(szCardId) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( 0 > UTIL_ValidInputCardId( szCardId, &(tSearchReqData.unCardId) ) );

	tSearchReqData.unCardId = atoi(szCardId);

	printf( "\n%s / %s / %d\n", tSearchReqData.szName, tSearchReqData.szCompany, tSearchReqData.unCardId );

	CS_SET_MASK_SEARCH_DELETE_REQ( &usBitmask, tSearchReqData ); //FULL INPUT : 0000 0000 0011 1000

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
	
	PRT_TITLE( "Request" )
	UTIL_PrtBuf( ucReqBuf, nPos );
	PRT_LF;

	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return nRC;
	}
	
	//SIM_Search( ucResHeaderBuf, ucResBodyBuf );
	//SIM_Search( ucResHeaderBuf, pucNewResBodyBuf ); //사용하려면 pucNewResBodyBuf malloc 해야함	

	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return nRC;
	}

	nRC = ENCDEC_DecodingHeader( ucResHeaderBuf, &tResHeader );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "ENCDEC_DecodingHeader fail <%d>", nRC );
		return nRC;
	}

	if ( tResHeader.unBodyLen > CS_RES_BODY_BUF_LEN )
	{
		pucNewResBodyBuf = (char *)malloc( sizeof(char *) * tResHeader.unBodyLen );
		if ( NULL == pucNewResBodyBuf )
		{
			fprintf( stderr, "malloc fail <%d:%s>", errno, strerror(errno) );
			return CS_rErrMallocFail;
		}

		nRC = SOCK_Read( pucNewResBodyBuf, tResHeader.unBodyLen );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
			goto exit_failure;
		}

		PRT_TITLE( "Response" );
		UTIL_PrtBuf( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
		UTIL_PrtBuf( pucNewResBodyBuf, tResHeader.unBodyLen );

		nRC = ENCDEC_DecodingBody( pucNewResBodyBuf, tResHeader, &tResBody );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "ENCDEC_DecodingBody fail <%d>", nRC );
			goto exit_failure;
		}
	}
	else
	{
		nRC = SOCK_Read( ucResBodyBuf, tResHeader.unBodyLen );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
			return nRC;
		}

		PRT_TITLE( "Response" );
		UTIL_PrtBuf( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
		UTIL_PrtBuf( ucResBodyBuf, tResHeader.unBodyLen );

		nRC = ENCDEC_DecodingBody( ucResBodyBuf, tResHeader, &tResBody );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "ENCDEC_DecodingBody fail <%d>", nRC );
			return nRC;
		}
	}

	switch ( tResBody.ucResultCode )
	{
		case CS_RC_SUCCESS:
		{
			printf( "\n\n조회된 명함 정보 개수 %d\n", tResBody.u.tSearchResData.usTotalCnt );

			for ( nIndex = 0; nIndex < tResBody.u.tSearchResData.usTotalCnt; nIndex++ )
			{
				PRT_DETAIL_INFO( tResBody.u.tSearchResData.tDetailInfo[nIndex],
						UTIL_MappingPositionToStr(tResBody.u.tSearchResData.tDetailInfo[nIndex].ucPosition),
						UTIL_MappingTitleToStr(tResBody.u.tSearchResData.tDetailInfo[nIndex].ucTitle) );
			}
		}
			break;
		case CS_RC_FAIL:
		{
			printf( "\nError Code = %02x\n", tResBody.u.ucErrCode );
			nRC = CS_rErrFromServer;
			goto exit_failure;
		}
			break;
		default:
		{
			LOG_ERR_F( "wrong result code (%02x)", tResBody.ucResultCode );
			nRC = CS_rErrSystemFail;
			goto exit_failure;
		}
			break;
	}

	FREE( pucNewResBodyBuf );
	return CS_rOk;

exit_failure:
	FREE( pucNewResBodyBuf );
	return nRC;
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
	char *pucNewResBodyBuf = NULL; //응답받은 bodylen이 내가 정한 바디버퍼보다 클 경우 malloc용
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

		nRC = UTIL_InputData( "* 이름, 회사명, 명함 ID 중 한 개는 반드시 포함되어야 합니다.\n"
							  "이름", tDeleteReqData.szName, sizeof(tDeleteReqData.szName) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}

		nRC = UTIL_InputData( "회사", tDeleteReqData.szCompany, sizeof(tDeleteReqData.szCompany) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}

		do
		{
			nRC = UTIL_InputData( "* 문자가 포함되면 다시 입력 받습니다. 범위(0~4,294,967,295)\n"
								  "명함 ID", szCardId, sizeof(szCardId) );
			if ( CS_rOk != nRC )
			{
				LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
				return CS_rErrClientServerFail;
			}
		} while ( 0 > UTIL_ValidInputCardId( szCardId, &(tDeleteReqData.unCardId) ) );

		tDeleteReqData.unCardId = atoi(szCardId);

		CS_SET_MASK_SEARCH_DELETE_REQ( &usBitmask, tDeleteReqData ); //FULL INPUT : 0000 0000 0011 1000

	} while ( 0 == (0x00 | usBitmask) );
	
	printf( "\n%s / %s / %d\n", tDeleteReqData.szName, tDeleteReqData.szCompany, tDeleteReqData.unCardId );

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

	PRT_TITLE( "Request" )
	UTIL_PrtBuf( ucReqBuf, nPos );
	PRT_LF;

	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return nRC;
	}

	//SIM_Delete( ucResHeaderBuf, ucResBodyBuf );
	//SIM_Delete( ucResHeaderBuf, pucNewResBodyBuf ); //사용하려면 pucNewResBodyBuf malloc 해야함

	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return nRC;
	}

	nRC = ENCDEC_DecodingHeader( ucResHeaderBuf, &tResHeader );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "ENCDEC_DecodingHeader fail <%d>", nRC );
		return nRC;
	}

	if ( tResHeader.unBodyLen >  CS_RES_BODY_BUF_LEN )
	{
		pucNewResBodyBuf = (char *)malloc( sizeof(char *) * tResHeader.unBodyLen );
		if ( NULL == pucNewResBodyBuf )
		{
			fprintf( stderr, "malloc fail <%d:%s>", errno, strerror(errno) );
			return CS_rErrMallocFail;
		}

		nRC = SOCK_Read( pucNewResBodyBuf, tResHeader.unBodyLen );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
			goto exit_failure;
		}

		PRT_TITLE( "Response" );
		UTIL_PrtBuf( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
		UTIL_PrtBuf( pucNewResBodyBuf, tResHeader.unBodyLen );

		nRC = ENCDEC_DecodingBody( pucNewResBodyBuf, tResHeader, &tResBody );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "ENCDEC_DecodingBody fail <%d>", nRC );
			goto exit_failure;
		}
	}
	else
	{
		nRC = SOCK_Read( ucResBodyBuf, tResHeader.unBodyLen );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
			return nRC;
		}

		PRT_TITLE( "Response" );
		UTIL_PrtBuf( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
		UTIL_PrtBuf( ucResBodyBuf, tResHeader.unBodyLen );

		nRC = ENCDEC_DecodingBody( ucResBodyBuf, tResHeader, &tResBody );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "ENCDEC_DecodingBody fail <%d>", nRC );
			return nRC;
		}
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
			nRC = CS_rErrFromServer;
			goto exit_failure;
		}
			break;
		default:
		{
			LOG_ERR_F( "wrong result code (%02x)", tResBody.ucResultCode );
			nRC = CS_rErrSystemFail;
			goto exit_failure;
		}
	}

	FREE( pucNewResBodyBuf );
	return CS_rOk;

exit_failure:
	FREE( pucNewResBodyBuf );
	return nRC;
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

	PRT_TITLE( "Request" );
	UTIL_PrtBuf( ucReqBuf, nPos );
	PRT_LF;

	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return nRC;
	}

	//SIM_Logout( ucResHeaderBuf, ucResBodyBuf );

	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return nRC;
	}

	nRC = ENCDEC_DecodingHeader( ucResHeaderBuf, &tResHeader );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "ENCDEC_DecodingHeader fail <%d>", nRC );
		return nRC;
	}

	nRC = SOCK_Read( ucResBodyBuf, tResHeader.unBodyLen );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return nRC;
	}

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
			return CS_rErrFromServer;
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
