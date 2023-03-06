/* CS_Menu.c */
#include "CS_Inc.h"

int MENU_Create()
{
	int nRC = 0, nPos = 0;
	
	/* Request */
	unsigned short usBitmask = 0x00;
	CS_Header_t tReqHeader;
	CS_CreateReqData_t tCreateReqData;
	unsigned char ucReqBuf[CS_REQ_BUF_LEN];
	char szPosition[5];
	char szTitle[5];

	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( &tCreateReqData, 0x00, sizeof(tCreateReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( &szPosition, 0x00, sizeof(szPosition) );
	memset( &szTitle, 0x00, sizeof(szTitle) );
	
	/* Response */
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN];
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN];
	CS_Header_t tResHeader;
	CS_ResBody_t tResBody;

	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	/*********************/
	/* Input Create Data */
	/*********************/
	do
	{
		nRC = UTIL_InputData( "(M) Name", tCreateReqData.szName, sizeof(tCreateReqData.szName) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( EMPTY_INPUT == strlen(tCreateReqData.szName) );

	do
	{
		nRC = UTIL_InputData( "(M) Company", tCreateReqData.szCompany, sizeof(tCreateReqData.szCompany) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( EMPTY_INPUT == strlen(tCreateReqData.szCompany) );

	do
	{
		nRC = UTIL_InputData( "(M) Team", tCreateReqData.szTeam, sizeof(tCreateReqData.szTeam) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( EMPTY_INPUT == strlen(tCreateReqData.szTeam) );

	do
	{
		nRC = UTIL_InputData( "(M 0x01~0x0E) Position", szPosition, sizeof(szPosition) );
		if ( CS_rOk != nRC )
		{
			LOG_ERR_F( "UTIL_InputData fail <%d>", nRC );
			return CS_rErrClientServerFail;
		}
	} while ( EMPTY_INPUT == strlen(szPosition) ||
			  EMPTY_INPUT == strtol(szPosition, NULL, 0) );

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
	} while ( EMPTY_INPUT == strlen(tCreateReqData.szEmail) );
	
	printf( "\n(M)%s/(M)%s/(M)%s/(M)%02x/(O)%02x/(M)%s/(O)%s/(M)%s\n",
			tCreateReqData.szName, tCreateReqData.szCompany,
			tCreateReqData.szTeam, tCreateReqData.ucPosition,
			tCreateReqData.ucTitle, tCreateReqData.szMobile,
			tCreateReqData.szTel, tCreateReqData.szEmail );

	SET_MASK_CREATE_REQ( &usBitmask, tCreateReqData ); //0000 1111 1111 0000

	/**************************/
	/* Create Request Message */
	/**************************/
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

#ifdef DEBUG
	PRT_TITLE( "Create Request" )
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
#endif
	
#ifdef SIM
	//TODO
	//SIM_Create( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/***************************/
	/* Create Response Message */
	/***************************/
	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( 0 > nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return CS_rErrReadFail;
	}
#endif

	//TODO Decoding Header, Read Body, Decoding Body 

	return CS_rOk;
}

int MENU_Search()
{
	int nRC = 0, nPos = 0;
	
	/* Request */
	unsigned short usBitmask = 0x00;
	CS_Header_t tReqHeader;
	CS_SearchReqData_t tSearchReqData;
	unsigned char ucReqBuf[CS_REQ_BUF_LEN];
	char szCardId[CS_LEN_CARD_ID + 1];

	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( &tSearchReqData, 0x00, sizeof(tSearchReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( szCardId, 0x00, sizeof(szCardId) );
	
	/* Response */
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN];
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN];
	CS_Header_t tResHeader;
	CS_ResBody_t tResBody;

	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	/*********************/
	/* Input Search Data */
	/*********************/
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

	SET_MASK_SEARCH_DELETE_REQ( &usBitmask, tSearchReqData ); //0000 0000 0011 1000

	/**************************/
	/* Search Request Message */
	/**************************/
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

#ifdef DEBUG
	PRT_TITLE( "Search Request" )
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
#endif
	
#ifdef SIM
	//TODO
	//SIM_Search( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/***************************/
	/* Search Response Message */
	/***************************/
	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( 0 > nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return CS_rErrReadFail;
	}
#endif

	//TODO Decoding Header, Read Body, Decoding Body 

	return CS_rOk;
}

int MENU_Delete()
{
	int nRC = 0, nPos = 0;
	
	/* Request */
	unsigned short usBitmask = 0x00;
	CS_Header_t tReqHeader;
	CS_DeleteReqData_t tDeleteReqData;
	unsigned char ucReqBuf[CS_REQ_BUF_LEN];
	char szCardId[CS_LEN_CARD_ID + 1];

	memset( &tReqHeader, 0x00, sizeof(tReqHeader) );
	memset( &tDeleteReqData, 0x00, sizeof(tDeleteReqData) );
	memset( ucReqBuf, 0x00, sizeof(ucReqBuf) );
	memset( szCardId, 0x00, sizeof(szCardId) );
	
	/* Response */
	unsigned char ucResHeaderBuf[CS_RES_HEADER_BUF_LEN];
	unsigned char ucResBodyBuf[CS_RES_BODY_BUF_LEN];
	CS_Header_t tResHeader;
	CS_ResBody_t tResBody;

	memset( ucResHeaderBuf, 0x00, sizeof(ucResHeaderBuf) );
	memset( ucResBodyBuf, 0x00, sizeof(ucResBodyBuf) );
	memset( &tResHeader, 0x00, sizeof(tResHeader) );
	memset( &tResBody, 0x00, sizeof(tResBody) );

	/*********************/
	/* Input Delete Data */
	/*********************/
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
		
		SET_MASK_SEARCH_DELETE_REQ( &usBitmask, tDeleteReqData ); //0000 0000 0011 1000

	} while ( 0 == (0x00 | usBitmask) );
	
	printf( "\n(C)%s/(C)%s/(C)%d\n",
			tDeleteReqData.szName, tDeleteReqData.szCompany, tDeleteReqData.unCardId );

	/**************************/
	/* Delete Request Message */
	/**************************/
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

#ifdef DEBUG
	PRT_TITLE( "Delete Request" )
	UTIL_PrtBuf( ucReqBuf, CS_REQ_BUF_LEN );
	PRT_LF;
#endif
	
#ifdef SIM
	//TODO
	//SIM_Delete( ucResHeaderBuf, ucResBodyBuf );
#endif

#ifdef RUN
	nRC = SOCK_Write( ucReqBuf, strlen(ucReqBuf) + 1 );
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_Write fail <%d>", nRC );
		return CS_rErrWriteFail;
	}

	/***************************/
	/* Delete Response Message */
	/***************************/
	nRC = SOCK_Read( ucResHeaderBuf, sizeof(ucResHeaderBuf) );
	if ( 0 > nRC )
	{
		LOG_ERR_F ( "SOCK_Read fail <%d>", nRC );
		return CS_rErrReadFail;
	}
#endif

	//TODO Decoding Header, Read Body, Decoding Body 

	return CS_rOk;

}

int MENU_Logout()
{
}
