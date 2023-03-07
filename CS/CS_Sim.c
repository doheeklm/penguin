/* CS_Sim.c */
#include "CS_Inc.h"

void SIM_Login( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, n = 0;

	a[0] = CS_MSG_LOGIN_RES;
	a[1] = 0x00;
	a[2] = 0x00;
	a[3] = 0x00;
	a[4] = 0x0f; //fail:0x08, success:0x0f(15)

	b[n++] = CS_TAG_RESULT_CODE;
	b[n++] = 0x00;
	b[n++] = CS_LEN_RESULT_CODE;
	b[n++] = CS_RC_SUCCESS;

	unsigned char Result = CS_RC_SUCCESS;

	if ( CS_RC_SUCCESS == Result )
	{
		b[n++] = CS_TAG_SESSION_ID;
		b[n++] = 0x00;
		b[n++] = CS_LEN_SESSION_ID;
		b[n++] = 0x01;
		b[n++] = 0x02;
		b[n++] = 0x03;
		b[n++] = 0x04;
		b[n++] = 0x05;
		b[n++] = 0x06;
		b[n++] = 0x07;
		b[n++] = 0x08;
/*
		unsigned long SID_Value = 1004; //0x03ec //11 1110 1100
		nRC = encdec_EncodingLong( &b[n], CS_RES_BODY_BUF_LEN - n, SID_Value );
		n += nRC;*/
	}
	else if ( CS_RC_FAIL == Result )
	{
		b[n++] = CS_TAG_ERR_CODE;
		b[n++] = 0x00;
		b[n++] = CS_LEN_ERR_CODE;
		b[n++] = CS_EC_UNDEFINED_ERR;
	}
	
	b[n] = '\0';
}

void SIM_Create( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;
	int nRC = 0, n = 0;

	a = pucHeader;
	b = pucBody;

	a[0] = CS_MSG_CREATE_RES;
	a[1] = 0x00;
	a[2] = 0x00;
	a[3] = 0x00;
	a[4] = 0x0b; //fail:0x08, success:0x0b (11)

	b[n++] = CS_TAG_RESULT_CODE;
	b[n++] = 0x00;
	b[n++] = CS_LEN_RESULT_CODE;
	b[n++] = CS_RC_SUCCESS;

	unsigned char Result = CS_RC_SUCCESS;

	if ( CS_RC_SUCCESS == Result )
	{
		b[n++] = CS_TAG_CARD_ID;
		b[n++] = 0x00;
		b[n++] = 0x04;
		b[n++] = 0x00;
		b[n++] = 0x00;
		b[n++] = 0x01;
		b[n++] = 0x4d;
	}
	else if ( CS_RC_FAIL == Result )
	{
		b[n++] = CS_TAG_ERR_CODE;
		b[n++] = 0x00;
		b[n++] = CS_LEN_ERR_CODE;
		b[n++] = CS_EC_UNDEFINED_ERR;
	}
	
	b[n] = '\0';
}

void SIM_Search( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, n = 0;

	a[0] = CS_MSG_SEARCH_RES;
	a[1] = 0x00;
	a[2] = 0x00;
	a[3] = 0x00;
	a[4] = 0x09; //fail:0x08, success:0x0b

	b[n++] = CS_TAG_RESULT_CODE;
	b[n++] = 0x00;
	b[n++] = CS_LEN_RESULT_CODE;
	b[n++] = CS_RC_SUCCESS;

	unsigned char Result = CS_RC_SUCCESS;

	if ( CS_RC_SUCCESS == Result )
	{
		b[n++] = CS_TAG_TOTAL_CNT;
		b[n++] = 0x00;
		b[n++] = CS_LEN_TOTAL_CNT;
		b[n++] = 0x00;
		b[n++] = 0x01;
		b[n++] = CS_TAG_CNT;
		b[n++] = 0x00;
		b[n++] = CS_LEN_CNT;
		b[n++] = 0x01;
		b[n++] = CS_TAG_NAME;
		b[n++] = 0x00;
		b[n++] = CS_LEN_NAME;
		int i = 0;
		for ( i = n; i < CS_LEN_NAME; i++ )
			b[i] = 0x2a;
		n++;
	}
	else if ( CS_RC_FAIL == Result )
	{
		b[n++] = CS_TAG_ERR_CODE;
		b[n++] = 0x00;
		b[n++] = CS_LEN_ERR_CODE;
		b[n++] = CS_EC_UNDEFINED_ERR;
	}
	
	b[n] = '\0';
}

void SIM_Delete( unsigned char *pucHeader, unsigned char *pucBody )
{
}

void SIM_Logout( unsigned char *pucHeader, unsigned char *pucBody )
{
	unsigned char *a;
	unsigned char *b;

	a = pucHeader;
	b = pucBody;

	int nRC = 0, n = 0;

	a[0] = CS_MSG_LOGOUT_RES;
	a[1] = 0x00;
	a[2] = 0x00;
	a[3] = 0x00;
	a[4] = 0x04; //fail:0x08, success:0x04

	b[n++] = CS_TAG_RESULT_CODE;
	b[n++] = 0x00;
	b[n++] = CS_LEN_RESULT_CODE;
	b[n++] = CS_RC_SUCCESS;

	unsigned char Result = CS_RC_SUCCESS;

	if ( CS_RC_SUCCESS == Result )
	{
	}
	else if ( CS_RC_FAIL == Result )
	{
		b[n++] = CS_TAG_ERR_CODE;
		b[n++] = 0x00;
		b[n++] = CS_LEN_ERR_CODE;
		b[n++] = CS_EC_UNDEFINED_ERR;
	}
	
	b[n] = '\0';
}
