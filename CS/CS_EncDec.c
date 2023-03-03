/* CS_EncDec.c */
#include "CS_Inc.h"

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

	nRC = encdec_EncodingLoginId( pucBuf, nBufLen, ptLoginReqData->szLoginId );
	if ( 0 > nRC )
	{	
		LOG_ERR_F( "encdec_EncodingLoginId fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	nRC = encdec_EncodingLoginPw( &pucBuf[nPos], nBufLen - nPos, ptLoginReqData->szLoginPw );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingLoginPw fail <%d>", nRC );
		return nRC;
	}
	else
	{
		nPos += nRC;
		CHECK_OVERFLOW( nPos, nBufLen, CS_rErrOverflow );
	}

	encdec_SetBodyLen( pucBuf, nPos );

	return nPos;
}

void encdec_SetBodyLen( unsigned char *pucBuf, unsigned int unLen )
{
	CS_Header_t *ptTemp;
	ptTemp = (CS_Header_t *)pucBuf;
	ptTemp->unBodyLen = ntohl(unLen);
}

int encdec_EncodingLoginId( unsigned char *pucBuf, int nBufLen, char *pszLoginId )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pszLoginId );
	CHECK_OVERFLOW( (CS_LOGIN_ID_LEN +1), nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;
	unsigned short usLength = CS_LOGIN_ID_LEN;

	pucBuf[nPos] = CS_TAG_LOGIN_ID;
	nPos++;

	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, &usLength );
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

	nRC = encdec_EncodingString( &pucBuf[nPos], nBufLen - nPos, pszLoginId, CS_LOGIN_ID_LEN, CS_SPACE );
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

	return sizeof(unsigned char) + sizeof(unsigned short) + CS_LOGIN_ID_LEN;
}

int encdec_EncodingLoginPw( unsigned char *pucBuf, int nBufLen, char *pszLoginPw )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pszLoginPw );
	CHECK_OVERFLOW( (CS_LOGIN_PW_LEN +1), nBufLen, CS_rErrOverflow );

	int nRC = 0, nPos = 0;
	unsigned short usLength = CS_LOGIN_PW_LEN;

	pucBuf[nPos] = CS_TAG_LOGIN_PW;
	nPos++;
	
	nRC = encdec_EncodingShort( &pucBuf[nPos], nBufLen - nPos, &usLength );
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

	nRC = encdec_EncodingString( &pucBuf[nPos], nBufLen - nPos, pszLoginPw, CS_LOGIN_PW_LEN, CS_SPACE );
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

	return sizeof(unsigned char) + sizeof(unsigned short) + CS_LOGIN_PW_LEN;
}

int encdec_EncodingOneByte( unsigned char *pucBuf, int nBufLen, unsigned char *pucData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned char), nBufLen, CS_rErrOverflow );

	unsigned char *pucTemp;
	pucTemp = (unsigned char *)pucBuf;
	*pucTemp = *pucData;

	return sizeof(unsigned char);
}

int encdec_EncodingShort( unsigned char *pucBuf, int nBufLen, unsigned short *pusData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned short), nBufLen, CS_rErrOverflow );

	unsigned short *pusTemp;
	pusTemp = (unsigned short *)pucBuf;
	*pusTemp = htons(*pusData);

	return sizeof(unsigned short);
}

int encdec_EncodingLong( unsigned char *pucBuf, int nBufLen, unsigned long *pulData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_OVERFLOW( sizeof(unsigned long), nBufLen, CS_rErrOverflow );

	unsigned long *pulTemp;
	pulTemp = (unsigned long *)pucBuf;
	*pulTemp = htonl(*pulData);

	return sizeof(unsigned long);
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
		}
			break;
		case CS_MSG_SEARCH_RES:
		{
		}
			break;
		case CS_MSG_DELETE_RES:
		{
		}
			break;
		case CS_MSG_LOGOUT_RES:
		{
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
	unsigned short usFieldMask = 0;

	while ( nPos < nBufLen )
	{
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
	
			CHECK_TLV_LENGTH( CS_RESULT_CODE_LEN, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->ucResultCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			
			nPos += nRC;
		
			usFieldMask |= CS_FIELD_MASK_RESULT_CODE;
		}
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
	
			CHECK_TLV_LENGTH( CS_ERR_CODE_LEN, usLength );

			nRC = encdec_DecodingOneByte( &pucBuf[nPos], &(ptResBody->u.ucErrCode) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingOneByte fail <%d>", nRC );
				return nRC;
			}
			
			nPos += nRC;

			usFieldMask |= CS_FIELD_MASK_ERR_CODE;
		}
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

			CHECK_TLV_LENGTH( CS_SESSION_ID_LEN, usLength );

			nRC = encdec_DecodingLong( &pucBuf[nPos], &(ptResBody->u.ulSessionId) );
			if ( 0 > nRC )
			{
				LOG_ERR_F( "encdec_DecodingLong fail <%d>", nRC );
				return nRC;
			}
				
			nPos += nRC;

			usFieldMask |= CS_FIELD_MASK_SESSION_ID;
		}
		else
		{
			LOG_ERR_F( "system fail(invalid tag/too small bodylen/too large bodylen)" );
			return CS_rErrSystemFail;
		}
	}
	
	if ( (CS_FIELD_MASK_FAIL_RES != usFieldMask) &&
		 (CS_FIELD_MASK_LOGIN_RES != usFieldMask) )
	{
		LOG_ERR_F ( "missing tag" );
		return CS_rErrMissingTag;
	}

	return CS_rOk;
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

int encdec_DecodingLong( unsigned char *pucBuf, unsigned long *pulData )
{
	CHECK_PARAM_RC( pucBuf );
	CHECK_PARAM_RC( pulData );

	unsigned long *pulTemp;
	pulTemp = (unsigned long *)pucBuf;
	*pulData = ntohl(*pulTemp);

	return sizeof(unsigned long);
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
