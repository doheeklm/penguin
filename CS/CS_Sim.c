/* CS_Sim.c */
#include "CS_Inc.h"

void SIM_SetBodyLen( unsigned char *pucBuf, int unBodyLen )
{	
	int *punTemp;
	punTemp = (int *)pucBuf;
	*punTemp = htonl(unBodyLen);
}

int SIM_SetDetailInfo( unsigned char *pucBuf, int nLen, int cnt, int card_id, char *name, char *company, char *team, char position, char title, char *mobile, char *tel, char *email )
{
	int nRC = 0, nPos = 0;

	nRC = ENCDEC_EncodingTLVOneByte( pucBuf, nLen, CS_TAG_CNT, CS_LEN_CNT, cnt );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVInt( &pucBuf[nPos], nLen - nPos, CS_TAG_CARD_ID, CS_LEN_CARD_ID, card_id );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_NAME, CS_LEN_NAME, name, CS_ASTERISK );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_COMPANY, CS_LEN_COMPANY, company, CS_ASTERISK );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_TEAM, CS_LEN_TEAM, team, CS_ASTERISK );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVOneByte( &pucBuf[nPos], nLen - nPos, CS_TAG_POSITION, CS_LEN_POSITION, position );
	nPos += nRC;

	if ( title != 0 )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &pucBuf[nPos], nLen - nPos, CS_TAG_TITLE, CS_LEN_TITLE, title );
		nPos += nRC;
	}

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_MOBILE, CS_LEN_MOBILE, mobile, 0 );
	nPos += nRC;

	if ( tel != NULL )
	{
		nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_TEL, CS_LEN_TEL, tel, CS_SPACE );
		nPos += nRC;
	}

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_EMAIL, CS_LEN_EMAIL, email, CS_SPACE );
	nPos += nRC;

	return nPos;
}

int SIM_SetSimpleInfo( unsigned char *pucBuf, int nLen, int cnt, int card_id, char *name, char *company, char *mobile )
{
	int nRC = 0, nPos = 0;

	nRC = ENCDEC_EncodingTLVOneByte( pucBuf, nLen, CS_TAG_CNT, CS_LEN_CNT, cnt );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVInt( &pucBuf[nPos], nLen - nPos, CS_TAG_CARD_ID, CS_LEN_CARD_ID, card_id );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_NAME, CS_LEN_NAME, name, CS_ASTERISK );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_COMPANY, CS_LEN_COMPANY, company, CS_ASTERISK );
	nPos += nRC;

	nRC = ENCDEC_EncodingTLVString( &pucBuf[nPos], nLen - nPos, CS_TAG_MOBILE, CS_LEN_MOBILE, mobile, 0 );
	nPos += nRC;

	return nPos;
}

void SIM_Login( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, nPos = 0;

	unsigned char Result = CS_RC_SUCCESS;
	
	nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_RESULT_CODE, CS_LEN_RESULT_CODE, Result );
	nPos += nRC;

	if ( CS_RC_SUCCESS == Result )
	{
		nRC = ENCDEC_EncodingTLVLong( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_SESSION_ID, CS_LEN_SESSION_ID, 1004 );
		nPos += nRC;
	}
	else if ( CS_RC_FAIL == Result )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_ERR_CODE, CS_LEN_ERR_CODE, CS_EC_UNDEFINED_ERR );
		nPos += nRC;
	}
	
	b[nPos] = '\0';

	a[0] = CS_MSG_LOGIN_RES;
	SIM_SetBodyLen( &a[1], nPos );
}

void SIM_Create( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;
	int nRC = 0, nPos = 0;

	a = pucHeader;
	b = pucBody;

	unsigned char Result = CS_RC_SUCCESS;
		
	nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_RESULT_CODE, CS_LEN_RESULT_CODE, Result );
	nPos += nRC;

	if ( CS_RC_SUCCESS == Result )
	{
		nRC = ENCDEC_EncodingTLVInt( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_CARD_ID, CS_LEN_CARD_ID, 777  );
		nPos += nRC;
	}
	else if ( CS_RC_FAIL == Result )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_ERR_CODE, CS_LEN_ERR_CODE, CS_EC_UNDEFINED_ERR );
		nPos += nRC;
	}
	
	b[nPos] = '\0';
	
	a[0] = CS_MSG_CREATE_RES;
	SIM_SetBodyLen( &a[1], nPos );
}

void SIM_Search( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, nPos = 0;
	unsigned char Result = CS_RC_SUCCESS;

	char name[CS_LEN_NAME + 1] = "dohee";
	char company[CS_LEN_COMPANY + 1] = "telcoware";
	char team[CS_LEN_TEAM + 1] = "infra1";
	char mobile[CS_LEN_MOBILE + 1] = "01077779999";
	char tel[CS_LEN_TEL + 1] = "023335555";
	char email[CS_LEN_EMAIL + 1] = "dhkim@telcoware.com";

	char name1[CS_LEN_NAME + 1] = "heedo";
	char company1[CS_LEN_COMPANY + 1] = "tel";
	char team1[CS_LEN_TEAM + 1] = "data";
	char mobile1[CS_LEN_MOBILE + 1] = "01089219321";
	char tel1[CS_LEN_TEL + 1] = "0315851111";
	char email1[CS_LEN_EMAIL + 1] = "heedo@tel.com";
	
	nRC = ENCDEC_EncodingTLVOneByte( b, CS_RES_BODY_BUF_LEN, CS_TAG_RESULT_CODE, CS_LEN_RESULT_CODE, Result );
	nPos += nRC;
	
	if ( CS_RC_SUCCESS == Result )
	{
		nRC = ENCDEC_EncodingTLVShort( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_TOTAL_CNT, CS_LEN_TOTAL_CNT, 3 );
		nPos += nRC;

		nRC = SIM_SetDetailInfo( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, 0, 1004, name, company, team, 0x0e, 0x09, mobile, tel, email );
		nPos += nRC;

		nRC = SIM_SetDetailInfo( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, 1, 1005, name1, company1, team1, 0x0c, 0x07, mobile1, tel1, email1 );
		nPos += nRC;

		nRC = SIM_SetDetailInfo( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, 2, 1006, name1, company1, team1, 0x03, 0x09, mobile1, tel1, email1 );
		nPos += nRC;
	}
	else if ( CS_RC_FAIL == Result )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_ERR_CODE, CS_LEN_ERR_CODE, CS_EC_UNDEFINED_ERR );
		nPos += nRC;
	}
	
	b[nPos] = '\0';

	a[0] = CS_MSG_SEARCH_RES;
	SIM_SetBodyLen( &a[1], nPos );
}

void SIM_Delete( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, nPos = 0;
	unsigned char Result = CS_RC_SUCCESS;

	char name[CS_LEN_NAME + 1] = "sarah";
	char company[CS_LEN_COMPANY + 1] = "qq";
	char mobile[CS_LEN_MOBILE + 1] = "01029291133";

	char name1[CS_LEN_NAME + 1] = "alex";
	char company1[CS_LEN_COMPANY + 1] = "ee";
	char mobile1[CS_LEN_MOBILE + 1] = "01039516666";
	
	nRC = ENCDEC_EncodingTLVOneByte( b, CS_RES_BODY_BUF_LEN, CS_TAG_RESULT_CODE, CS_LEN_RESULT_CODE, Result );
	nPos += nRC;
	
	if ( CS_RC_SUCCESS == Result )
	{
		nRC = ENCDEC_EncodingTLVShort( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_TOTAL_CNT, CS_LEN_TOTAL_CNT, 2 );
		nPos += nRC;

		nRC = SIM_SetSimpleInfo( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, 0, 1004, name, company, mobile );
		nPos += nRC;

		nRC = SIM_SetSimpleInfo( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, 1, 1005, name1, company1, mobile1 );
		nPos += nRC;
	}
	else if ( CS_RC_FAIL == Result )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_ERR_CODE, CS_LEN_ERR_CODE, CS_EC_UNDEFINED_ERR );
		nPos += nRC;
	}
	
	b[nPos] = '\0';

	a[0] = CS_MSG_DELETE_RES;
	SIM_SetBodyLen( &a[1], nPos );

}

void SIM_Logout( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, nPos = 0;

	unsigned char Result = CS_RC_SUCCESS;

	nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_RESULT_CODE, CS_LEN_RESULT_CODE, Result );
	nPos += nRC;

	if ( CS_RC_SUCCESS == Result )
	{
		/* X */
	}
	else if ( CS_RC_FAIL == Result )
	{
		nRC = ENCDEC_EncodingTLVOneByte( &b[nPos], CS_RES_BODY_BUF_LEN - nPos, CS_TAG_ERR_CODE, CS_LEN_ERR_CODE, CS_EC_UNDEFINED_ERR );
		nPos += nRC;
	}

	b[nPos] = '\0';

	a[0] = CS_MSG_LOGOUT_RES;
	SIM_SetBodyLen( &a[1], nPos );
}
