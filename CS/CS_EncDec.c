/* CS_EncDec.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

/*
 *	Encoding
 */

int ENCDEC_EncodingHeader( unsigned char *pucBuf, int nBufLen, CS_Header_t *ptHeader )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptHeader );
	CHECK_OVERFLOW( (int)sizeof(CS_Header_t), nBufLen, CS_rErrOverflow );

	CS_Header_t *ptTemp;
	
	ptTemp = (CS_Header_t *)pucBuf;
	*ptTemp = *ptHeader;

	ptTemp->ucMsgType = ptHeader->ucMsgType;
	ptTemp->unBodyLen = 0x00;

	return sizeof(CS_Header_t);
}

int ENCDEC_EncodingLoginBody( unsigned char *pucBuf, int nBufLen, CS_LoginReqData_t *ptLoginReqData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptLoginReqData );
	CHECK_OVERFLOW( (int)sizeof(CS_LoginReqData_t), nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* 1. Login ID */
	nRC = ENCDEC_EncodingTLVString( pucBuf, nBufLen, CS_TAG_LOGIN_ID, (unsigned short)CS_LEN_LOGIN_ID, ptLoginReqData->szLoginId, CS_SPACE );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* 2. Login PW */
	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_LOGIN_PW, (unsigned short)CS_LEN_LOGIN_PW, ptLoginReqData->szLoginPw, CS_SPACE );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	return nPos;
}

int ENCDEC_EncodingCreateBody( unsigned char *pucBuf, int nBufLen, CS_CreateReqData_t *ptCreateReqData, unsigned short usBitmask )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptCreateReqData );
	CHECK_OVERFLOW( (int)sizeof(CS_CreateReqData_t), nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* 1. Session ID */
	nRC = ENCDEC_EncodingTLVLong( pucBuf, nBufLen, CS_TAG_SESSION_ID, (unsigned short)CS_LEN_SESSION_ID, g_tEnv.ulSessionId );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingTLVLong fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* 2. Name */
	if ( CS_FIELD_MASK_NAME == (CS_FIELD_MASK_NAME & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_NAME, (unsigned short)CS_LEN_NAME, ptCreateReqData->szName, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 3. Company */
	if ( CS_FIELD_MASK_COMPANY == (CS_FIELD_MASK_COMPANY & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_COMPANY, (unsigned short)CS_LEN_COMPANY, ptCreateReqData->szCompany, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 4. Team */
	if ( CS_FIELD_MASK_TEAM == (CS_FIELD_MASK_TEAM & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_TEAM, (unsigned short)CS_LEN_TEAM, ptCreateReqData->szTeam, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 5. Position */
	if ( CS_FIELD_MASK_POSITION == (CS_FIELD_MASK_POSITION & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &pucBuf[nPos], nBufLen - nPos, CS_TAG_POSITION, 1, ptCreateReqData->ucPosition );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVOneByte fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 6. Title */
	if ( CS_FIELD_MASK_TITLE == (CS_FIELD_MASK_TITLE & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &pucBuf[nPos], nBufLen - nPos, CS_TAG_TITLE, 1, ptCreateReqData->ucTitle );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVOneByte fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 7. Mobile */
	if ( CS_FIELD_MASK_MOBILE == (CS_FIELD_MASK_MOBILE & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_MOBILE, (unsigned short)CS_LEN_MOBILE, ptCreateReqData->szMobile, 0 );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 8. Tel */
	if ( CS_FIELD_MASK_TEL == (CS_FIELD_MASK_TEL & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_TEL, (unsigned short)CS_LEN_TEL, ptCreateReqData->szTel, CS_SPACE );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 9. Email */
	if ( CS_FIELD_MASK_EMAIL == (CS_FIELD_MASK_EMAIL & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_EMAIL, (unsigned short)CS_LEN_EMAIL, ptCreateReqData->szEmail, CS_SPACE );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	return nPos;
}

int ENCDEC_EncodingSearchBody( unsigned char *pucBuf, int nBufLen, CS_SearchReqData_t *ptSearchReqData, unsigned short usBitmask )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptSearchReqData );
	CHECK_OVERFLOW( (int)sizeof(CS_SearchReqData_t), nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* 1. Session ID */
	nRC = ENCDEC_EncodingTLVLong( pucBuf, nBufLen, CS_TAG_SESSION_ID, (unsigned short)CS_LEN_SESSION_ID, g_tEnv.ulSessionId );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingTLVLong fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* 2. Name */
	if ( CS_FIELD_MASK_NAME == (CS_FIELD_MASK_NAME & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_NAME, (unsigned short)CS_LEN_NAME, ptSearchReqData->szName, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 3. Company */
	if ( CS_FIELD_MASK_COMPANY == (CS_FIELD_MASK_COMPANY & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_COMPANY, (unsigned short)CS_LEN_COMPANY, ptSearchReqData->szCompany, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 4. Card Id */
	if ( CS_FIELD_MASK_CARD_ID == (CS_FIELD_MASK_CARD_ID & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVInt( &pucBuf[nPos], nBufLen - nPos, CS_TAG_CARD_ID, (unsigned short)CS_LEN_CARD_ID, ptSearchReqData->unCardId );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVInt fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	return nPos;
}

int ENCDEC_EncodingDeleteBody( unsigned char *pucBuf, int nBufLen, CS_DeleteReqData_t *ptDeleteReqData, unsigned short usBitmask )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptDeleteReqData );
	CHECK_OVERFLOW( (int)sizeof(CS_DeleteReqData_t), nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* 1. Session ID */
	nRC = ENCDEC_EncodingTLVLong( pucBuf, nBufLen, CS_TAG_SESSION_ID, (unsigned short)CS_LEN_SESSION_ID, g_tEnv.ulSessionId );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "ENCDEC_EncodingTLVLong fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* 2. Name */
	if ( CS_FIELD_MASK_NAME == (CS_FIELD_MASK_NAME & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_NAME, (unsigned short)CS_LEN_NAME, ptDeleteReqData->szName, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 3. Company */
	if ( CS_FIELD_MASK_COMPANY == (CS_FIELD_MASK_COMPANY & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nBufLen - nPos, CS_TAG_COMPANY, (unsigned short)CS_LEN_COMPANY, ptDeleteReqData->szCompany, CS_ASTERISK );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVString fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	/* 4. Card Id */
	if ( CS_FIELD_MASK_CARD_ID == (CS_FIELD_MASK_CARD_ID & usBitmask) )
	{
		nRC = ENCDEC_EncodingTLVInt( &pucBuf[nPos], nBufLen - nPos, CS_TAG_CARD_ID, (unsigned short)CS_LEN_CARD_ID, ptDeleteReqData->unCardId );
		if ( 0 > nRC )
		{
			LOG_ERR_F( "ENCDEC_EncodingTLVInt fail <%d>", nRC );
			return nRC;
		}
		else
		{
			nPos += nRC;
			CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
		}
	}

	return nPos;
}

void encdec_SetBodyLen( unsigned char *pucBuf, unsigned int unLen )
{
	CS_Header_t *ptTemp;
	ptTemp = (CS_Header_t *)pucBuf;
	ptTemp->unBodyLen = ntohl(unLen);
}

int ENCDEC_EncodingTLVString( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, char *pszValue, char cFillChar )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pszValue );
	CHECK_OVERFLOW( (int)usLength + 1, nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* Tag */
	pucBuf[nPos] = ucTag;
	nPos++;

	/* Length */
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, usLength );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* Value(string) */
	nRC = encdec_EncodingString( &pucBuf[nPos], nBufLen - nPos, pszValue, usLength, cFillChar );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingString fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	return sizeof(unsigned char) + sizeof(unsigned short) + usLength;
}

int ENCDEC_EncodingTLVOneByte( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned char ucValue )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( (int)usLength + 1, nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* Tag */
	pucBuf[nPos] = ucTag;
	nPos++;

	/* Length */
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, usLength );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* Value(one byte) */
	nRC = encdec_EncodingOneByte( &pucBuf[nPos], nBufLen - nPos, ucValue );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingOneByte fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	return sizeof(unsigned char) + sizeof(unsigned short) + sizeof(unsigned char);
}

int ENCDEC_EncodingTLVInt( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned int unValue )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( (int)usLength + 1, nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* Tag */
	pucBuf[nPos] = ucTag;
	nPos++;

	/* Length */
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, usLength );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* Value(int) */
	nRC = encdec_EncodingInt( &pucBuf[nPos], nBufLen - nPos, unValue );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingInt fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	return sizeof(unsigned char) + sizeof(unsigned short) + sizeof(unsigned int);
}

int ENCDEC_EncodingTLVShort( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned short usValue )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( (int)usLength + 1, nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* Tag */
	pucBuf[nPos] = ucTag;
	nPos++;

	/* Length */
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, usLength );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* Value(short) */
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, usValue );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	return sizeof(unsigned char) + sizeof(unsigned short) + sizeof(unsigned short);
}

int ENCDEC_EncodingTLVLong( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned long ulValue )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( (int)usLength + 1, nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;

	/* Tag */
	pucBuf[nPos] = ucTag;
	nPos++;

	/* Length */
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, usLength );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	/* Value(long) */
	nRC = encdec_EncodingLong( &pucBuf[nPos], nBufLen - nPos, ulValue );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingLong fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	return sizeof(unsigned char) + sizeof(unsigned short) + sizeof(unsigned long);
}

int encdec_EncodingString( unsigned char *pucBuf, int nBufLen, char *pszData, int nStrMaxLen, char cChar )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pszData );
	CHECK_OVERFLOW( nStrMaxLen, nBufLen, CS_rErrOverflow );

	int i = 0;

	/* 필드의 사용되지 않는 부분 채우기 */
	if ( strlen(pszData) < nStrMaxLen )
	{
		for ( i = strlen(pszData); i < nStrMaxLen; i++ )
		{
			pszData[i] = cChar;
		}
	}

	for ( i = 0; i < nStrMaxLen; i++ )
	{
		pucBuf[i] = pszData[i];
	}

	return nStrMaxLen;
}

int encdec_EncodingOneByte( unsigned char *pucBuf, int nBufLen, unsigned char ucData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned char), nBufLen, CS_rErrOverflow );

	unsigned char *pucTemp;
	pucTemp = (unsigned char *)pucBuf;
	*pucTemp = ucData;

	return sizeof(unsigned char);
}

int encdec_EncodingShort( unsigned char *pucBuf, int nBufLen, unsigned short usData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned short), nBufLen, CS_rErrOverflow );

	unsigned short *pusTemp;
	pusTemp = (unsigned short *)pucBuf;
	*pusTemp = htons(usData);

	return sizeof(unsigned short);
}

int encdec_EncodingInt( unsigned char *pucBuf, int nBufLen, unsigned int unData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned int), nBufLen, CS_rErrOverflow );

	unsigned int *punTemp;
	punTemp = (unsigned int *)pucBuf;
	*punTemp = htonl(unData);

	return sizeof(unsigned int);
}

int encdec_EncodingLong( unsigned char *pucBuf, int nBufLen, unsigned long ulData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned long), nBufLen, CS_rErrOverflow );

	unsigned long *pulTemp;
	pulTemp = (unsigned long *)pucBuf;
	*pulTemp = htonl(ulData);

	return sizeof(unsigned long);
}

/*
 *	Decoding
 */

int ENCDEC_DecodingHeader( unsigned char *pucBuf, CS_Header_t *ptHeader )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptHeader );

	CS_Header_t *ptTemp;
	ptTemp = (CS_Header_t *)pucBuf;

	ptHeader->ucMsgType = ptTemp->ucMsgType;
	ptHeader->unBodyLen = ntohl(ptTemp->unBodyLen);

	return CS_rOk;
}

int ENCDEC_DecodingBody( unsigned char *pucBuf, CS_Header_t tHeader, CS_ResBody_t *ptResBody )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptResBody );

	int nRC = 0;

	switch( tHeader.ucMsgType )
	{
		case CS_MSG_LOGIN_RES:
		{
			nRC = ENCDEC_DecodingLoginBody( pucBuf, (int)tHeader.unBodyLen, ptResBody );
			if ( CS_rOk != nRC )
			{
				LOG_ERR_F( "ENCDEC_DecodingLoginBody fail <%d>", nRC );
				return CS_rErrDecodingFail;
			}
		}
			break;
		case CS_MSG_CREATE_RES:
		{
			nRC = ENCDEC_DecodingCreateBody( pucBuf, (int)tHeader.unBodyLen, ptResBody );
			if ( CS_rOk != nRC )
			{
				LOG_ERR_F( "ENCDEC_DecodingCreateBody fail <%d>", nRC );
				return CS_rErrDecodingFail;
			}
		}
			break;
		case CS_MSG_SEARCH_RES:
		{
			nRC = ENCDEC_DecodingSearchBody( pucBuf, (int)tHeader.unBodyLen, ptResBody );
			if ( CS_rOk != nRC )
			{
				LOG_ERR_F( "ENCDEC_DecodingSearchBody fail <%d>", nRC );
				return CS_rErrDecodingFail;
			}
		}
			break;
		case CS_MSG_DELETE_RES:
		{
			nRC = ENCDEC_DecodingDeleteBody( pucBuf, (int)tHeader.unBodyLen, ptResBody );
			if ( CS_rOk != nRC )
			{
				LOG_ERR_F( "ENCDEC_DecodingDeleteBody fail <%d>", nRC );
				return CS_rErrDecodingFail;
			}
		}
			break;
		case CS_MSG_LOGOUT_RES:
		{
			nRC = ENCDEC_DecodingLogoutBody( pucBuf, (int)tHeader.unBodyLen, ptResBody );
			if ( CS_rOk != nRC )
			{
				LOG_ERR_F( "ENCDEC_DecodingLogoutBody fail <%d>", nRC );
				return CS_rErrDecodingFail;
			}
		}
			break;
	}

	return CS_rOk;
}

int ENCDEC_DecodingLoginBody( unsigned char *pucBuf, int nBufLen, CS_ResBody_t *ptResBody )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptResBody );

	int nRC = 0, nPos = 0;
	unsigned short usLength = 0;
	unsigned short usBitmask = 0;

	while ( nPos < nBufLen )
	{
		/* 1. Result Code */
		if ( CS_TAG_RESULT_CODE == pucBuf[nPos] )
		{
			nPos++;

			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_RESULT_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->ucResultCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		
			usBitmask |= CS_FIELD_MASK_RESULT_CODE;
		}
		/* 2. Err Code */
		else if ( CS_TAG_ERR_CODE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_ERR_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.ucErrCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_ERR_CODE;
		}
		/* 3. Session Id */
		else if ( CS_TAG_SESSION_ID == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_SESSION_ID, usLength );

			nRC = encdec_DecodingLong( &pucBuf[nPos], &(ptResBody->u.ulSessionId) ); 
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingLong fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_SESSION_ID;
		}
		else
		{
			LOG_ERR_F( "system fail <(invalid tag)/(too small bodylen)/(too large bodylen)>" );
			return CS_rErrSystemFail;
		}
	}

	if ( (CS_FIELD_MASK_FAIL_RES != usBitmask) && (CS_FIELD_MASK_LOGIN_RES != usBitmask) )
	{
		LOG_ERR_F( "wrong response message <(missing tag)/(or tag all included)>" );
		return CS_rErrWrongResponse;
	}
	return CS_rOk;
}

int ENCDEC_DecodingCreateBody( unsigned char *pucBuf, int nBufLen, CS_ResBody_t *ptResBody )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptResBody );

	int nRC = 0, nPos = 0;
	unsigned short usLength = 0;
	unsigned short usBitmask = 0;

	while ( nPos < nBufLen )
	{
		/* 1. Result Code */
		if ( CS_TAG_RESULT_CODE == pucBuf[nPos] )
		{
			nPos++;

			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_RESULT_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->ucResultCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		
			usBitmask |= CS_FIELD_MASK_RESULT_CODE;
		}
		/* 2. Err Code */
		else if ( CS_TAG_ERR_CODE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_ERR_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.ucErrCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_ERR_CODE;
		}
		/* 3. Card Id */
		else if ( CS_TAG_CARD_ID == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_CARD_ID, usLength );

			nRC = encdec_DecodingInt( &pucBuf[nPos], &(ptResBody->u.unCardId) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingInt fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_CARD_ID;
		}
		else
		{
			LOG_ERR_F( "system fail <(invalid tag)/(too small bodylen)/(too large bodylen)>" );
			return CS_rErrSystemFail;
		}
	}

	if ( (CS_FIELD_MASK_FAIL_RES != usBitmask) && (CS_FIELD_MASK_CREATE_RES != usBitmask) )
	{
		LOG_ERR_F( "wrong response message <(missing tag)/(or tag all included)>" );
		return CS_rErrWrongResponse;
	}

	return CS_rOk;
}

int ENCDEC_DecodingSearchBody( unsigned char *pucBuf, int nBufLen, CS_ResBody_t *ptResBody )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptResBody );

	int nRC = 0, nPos = 0, nCnt = -1, i = 0;
	unsigned short usLength = 0;
	unsigned short usBitmask = 0;
	unsigned short ausBitmask[CS_MAX_INFO];
	memset( ausBitmask, 0x00, sizeof(ausBitmask) );
	
	while ( nPos < nBufLen )
	{
		/* 1. Result Code */
		if ( CS_TAG_RESULT_CODE == pucBuf[nPos] )
		{
			nPos++;

			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_RESULT_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->ucResultCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		
			usBitmask |= CS_FIELD_MASK_RESULT_CODE;
		}
		/* 2. Err Code */
		else if ( CS_TAG_ERR_CODE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_ERR_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.ucErrCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_ERR_CODE;
		}
		/* 3. Total Cnt */
		else if ( CS_TAG_TOTAL_CNT == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_TOTAL_CNT, usLength );

			nRC = encdec_DecodingShort( &pucBuf[nPos], &(ptResBody->u.tSearchResData.usTotalCnt) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_TOTAL_CNT;
		}
		/* 4. Cnt */
		else if ( CS_TAG_CNT == pucBuf[nPos] )
		{
			nCnt++;
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_CNT, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.tSearchResData.tDetailInfo[nCnt].ucCnt) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		
			ausBitmask[nCnt] |= CS_FIELD_MASK_CNT;
		}
		/* 5. Card Id */
		else if ( CS_TAG_CARD_ID == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_CARD_ID, usLength );

			nRC = encdec_DecodingInt( &pucBuf[nPos], &(ptResBody->u.tSearchResData.tDetailInfo[nCnt].unCardId) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingInt fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_CARD_ID;
		}
		/* 6. Name */
		else if ( CS_TAG_NAME == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_NAME, usLength );
			
			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tSearchResData.tDetailInfo[nCnt].szName, CS_LEN_NAME );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_NAME;
		}
		/* 7. Company */
		else if ( CS_TAG_COMPANY == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_COMPANY, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tSearchResData.tDetailInfo[nCnt].szCompany, CS_LEN_COMPANY );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_COMPANY;
		}
		/* 8. Team */
		else if ( CS_TAG_TEAM == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_TEAM, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tSearchResData.tDetailInfo[nCnt].szTeam, CS_LEN_TEAM );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_TEAM;
		}
		/* 9. Position */
		else if ( CS_TAG_POSITION == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_POSITION, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.tSearchResData.tDetailInfo[nCnt].ucPosition) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_POSITION;
		}
		/* 10. Title (Optional - No bit check) */
		else if ( CS_TAG_TITLE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_TITLE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.tSearchResData.tDetailInfo[nCnt].ucTitle) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		}
		/* 11. Mobile */
		else if ( CS_TAG_MOBILE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_MOBILE, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tSearchResData.tDetailInfo[nCnt].szMobile, CS_LEN_MOBILE );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_MOBILE;
		}
		/* 12. Tel (Optional - No bit check) */
		else if ( CS_TAG_TEL == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_TEL, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tSearchResData.tDetailInfo[nCnt].szTel, CS_LEN_TEL );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		}
		/* 13. Email */
		else if ( CS_TAG_EMAIL == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_EMAIL, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tSearchResData.tDetailInfo[nCnt].szEmail, CS_LEN_EMAIL );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_EMAIL;
		}
		else
		{
			LOG_ERR_F( "system fail <(invalid tag)/(too small bodylen)/(too large bodylen)>" );
			return CS_rErrSystemFail;
		}
	}

	nCnt += 1;
	if ( nCnt != ptResBody->u.tSearchResData.usTotalCnt )
	{
		LOG_ERR_F( "nCnt(%d) != usTotalCnt(%d)", nCnt, ptResBody->u.tSearchResData.usTotalCnt );
		return CS_rErrSystemFail;
	}

	if ( CS_FIELD_MASK_FAIL_RES != usBitmask && CS_FIELD_MASK_TOTAL_CNT_RES != usBitmask )
	{
		LOG_ERR_F( "response message does not contains 'result code+err code' nor 'result code+total cnt'" );
		return CS_rErrSystemFail;
	}

	for ( i = 0; i < ptResBody->u.tSearchResData.usTotalCnt; i++ )
	{
		if ( CS_FIELD_MASK_DETAIL_INFO != ausBitmask[i] )
		{
			LOG_ERR_F( "wrong response message info[%d] <(missing tag)/(or tag all included)>", i );
			return CS_rErrWrongResponse;
		}
	}

	return CS_rOk;
}

int ENCDEC_DecodingDeleteBody( unsigned char *pucBuf, int nBufLen, CS_ResBody_t *ptResBody )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptResBody );

	int nRC = 0, nPos = 0, nCnt = -1, i = 0;
	unsigned short usLength = 0;
	unsigned short usBitmask = 0;
	unsigned short ausBitmask[CS_MAX_INFO];
	memset( ausBitmask, 0x00, sizeof(ausBitmask) );
	
	while ( nPos < nBufLen )
	{
		/* 1. Result Code */
		if ( CS_TAG_RESULT_CODE == pucBuf[nPos] )
		{
			nPos++;

			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_RESULT_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->ucResultCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		
			usBitmask |= CS_FIELD_MASK_RESULT_CODE;
		}
		/* 2. Err Code */
		else if ( CS_TAG_ERR_CODE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_ERR_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.ucErrCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_ERR_CODE;
		}
		/* 3. Total Cnt */
		else if ( CS_TAG_TOTAL_CNT == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_TOTAL_CNT, usLength );

			nRC = encdec_DecodingShort( &pucBuf[nPos], &(ptResBody->u.tDeleteResData.usTotalCnt) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_TOTAL_CNT;
		}
		/* 4. Cnt */
		else if ( CS_TAG_CNT == pucBuf[nPos] )
		{
			nCnt++;
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_CNT, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.tDeleteResData.tSimpleInfo[nCnt].ucCnt) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_CNT;
		}
		/* 5. Card Id */
		else if ( CS_TAG_CARD_ID == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_CARD_ID, usLength );

			nRC = encdec_DecodingInt( &pucBuf[nPos], &(ptResBody->u.tDeleteResData.tSimpleInfo[nCnt].unCardId) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingInt fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_CARD_ID;
		}
		/* 6. Name */
		else if ( CS_TAG_NAME == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_NAME, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tDeleteResData.tSimpleInfo[nCnt].szName, CS_LEN_NAME );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_NAME;
		}
		/* 7. Company */
		else if ( CS_TAG_COMPANY == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_COMPANY, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tDeleteResData.tSimpleInfo[nCnt].szCompany, CS_LEN_COMPANY );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_COMPANY;
		}
		/* 8. Mobile */
		else if ( CS_TAG_MOBILE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			CHECK_TLV_LENGTH( CS_LEN_MOBILE, usLength );

			nRC = encdec_DecodingString( &pucBuf[nPos], ptResBody->u.tDeleteResData.tSimpleInfo[nCnt].szMobile, CS_LEN_MOBILE );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingString fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			ausBitmask[nCnt] |= CS_FIELD_MASK_MOBILE;
		}
		else
		{
			LOG_ERR_F( "system fail <(invalid tag)/(too small bodylen)/(too large bodylen)>" );
			return CS_rErrSystemFail;
		}
	}
	
	nCnt += 1;
	if ( nCnt != ptResBody->u.tDeleteResData.usTotalCnt )
	{
		LOG_ERR_F( "nCnt(%d) != usTotalCnt(%d)", nCnt, ptResBody->u.tDeleteResData.usTotalCnt );
		return CS_rErrSystemFail;
	}

	if ( CS_FIELD_MASK_FAIL_RES != usBitmask && CS_FIELD_MASK_TOTAL_CNT_RES != usBitmask )
	{
		LOG_ERR_F( "response message does not contains 'result code+err code' nor 'result code+total cnt'" );
		return CS_rErrSystemFail;
	}

	for ( i = 0; i < ptResBody->u.tDeleteResData.usTotalCnt; i++ )
	{
		if ( CS_FIELD_MASK_SIMPLE_INFO != ausBitmask[i] )
		{
			LOG_ERR_F( "wrong response message info[%d] <(missing tag)/(or tag all included)>", i );
			return CS_rErrWrongResponse;
		}
	}

	return CS_rOk;
}

int ENCDEC_DecodingLogoutBody( unsigned char *pucBuf, int nBufLen, CS_ResBody_t *ptResBody )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( ptResBody );

	int nRC = 0, nPos = 0;
	unsigned short usLength = 0;
	unsigned short usBitmask = 0;

	while ( nPos < nBufLen )
	{
		/* 1. Result Code */
		if ( CS_TAG_RESULT_CODE == pucBuf[nPos] )
		{
			nPos++;

			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_RESULT_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->ucResultCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
		
			usBitmask |= CS_FIELD_MASK_RESULT_CODE;
		}
		/* 2. Err Code */
		else if ( CS_TAG_ERR_CODE == pucBuf[nPos] )
		{
			nPos++;
			
			nRC = encdec_DecodingShort( &pucBuf[nPos], &usLength );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingShort fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;
	
			CHECK_TLV_LENGTH( CS_LEN_ERR_CODE, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.ucErrCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			nPos += nRC;

			usBitmask |= CS_FIELD_MASK_ERR_CODE;
		}
		else
		{
			LOG_ERR_F( "system fail <(invalid tag)/(too small bodylen)/(too large bodylen)>" );
			return CS_rErrSystemFail;
		}
	}

	if ( (CS_FIELD_MASK_FAIL_RES != usBitmask) && (CS_FIELD_MASK_RESULT_CODE != usBitmask) )
	{
		LOG_ERR_F( "wrong response message <(missing tag)/(or tag all included)>" );
		return CS_rErrWrongResponse;
	}

	return CS_rOk;
}

int encdec_DecodingString( unsigned char *pucBuf, char *pszData, int nStrMaxLen )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pszData );

	int i = 0;

	for ( i = 0; i < nStrMaxLen; i++ )
	{
		pszData[i] = pucBuf[i];
	}

	return nStrMaxLen;
}

int encdec_DecodingOneByte( unsigned char *pucBuf, unsigned char *pucData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pucData );

	unsigned char *pucTemp;
	pucTemp = pucBuf;
	*pucData = *pucBuf;

	return sizeof(unsigned char);
}

int encdec_DecodingShort( unsigned char *pucBuf, unsigned short *pusData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pusData );

	unsigned short *pusTemp;
	pusTemp = (unsigned short *)pucBuf;
	*pusData = ntohs(*pusTemp);

	return sizeof(unsigned short);
}

int encdec_DecodingInt( unsigned char *pucBuf, unsigned int *punData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( punData );

	unsigned int *punTemp;
	punTemp = (unsigned int *)pucBuf;
	*punData = ntohl(*punTemp);

	return sizeof(unsigned int);
}

int encdec_DecodingLong( unsigned char *pucBuf, unsigned long *pulData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pulData );

	int i = 0;
	unsigned long *pulTemp;
	pulTemp = (unsigned long *)pucBuf;
	*pulData = ntohl(*pulTemp);

	return sizeof(unsigned long);
}
