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
	a[4] = 0x0f; //fail:0x08, success:0x0f

	unsigned char RC_Tag = CS_TAG_RESULT_CODE;
	unsigned short RC_Length = sizeof(unsigned char);
	unsigned char RC_Value = CS_RC_SUCCESS;
	
	b[n] = RC_Tag;
	n++;
	nRC = encdec_EncodingShort( &b[n], CS_RES_BODY_BUF_LEN - n, RC_Length );
	if ( 0 > nRC )
	{
		LOG_ERR_F( "encdec_EncodingShort fail <%d>", nRC );
	}
	n += nRC;
	b[n] = RC_Value;
	n++;

	if ( CS_RC_SUCCESS == RC_Value )
	{
		unsigned char SID_Tag = CS_TAG_SESSION_ID;
		unsigned short SID_Length = sizeof(unsigned long);
		unsigned long SID_Value = 1004; //0x03ec //11 1110 1100
		
		b[n] = SID_Tag;
		n++;
		nRC = encdec_EncodingShort( &b[n], CS_RES_BODY_BUF_LEN - n, SID_Length );
		n += nRC;
		nRC = encdec_EncodingLong( &b[n], CS_RES_BODY_BUF_LEN - n, SID_Value );
		n += nRC;
	}
	else if ( CS_RC_FAIL == RC_Value )
	{
		unsigned char EC_Tag = CS_TAG_ERR_CODE;
		unsigned short EC_Length = sizeof(unsigned char);
		unsigned char EC_Value = CS_EC_UNDEFINED_ERR;

		b[n] = EC_Tag;
		n++;
		nRC = encdec_EncodingShort( &b[n], CS_RES_BODY_BUF_LEN - n, EC_Length );
		n += nRC;
		b[n] = EC_Value;
		n++;
	}
	
	b[n] = '\0';
}
