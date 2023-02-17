/* BCP_EncDec.c */
#include "BCP_Inc.h"

int ENCDEC_EncodingHeader( unsigned char *pucBuf, int nBufLen, BCP_Header_t *ptHeader )
{
	BCP_Header_t *ptHD;

	if ( nBufLen < (int)sizeof(BCP_Header_t) )
	{
		printf( "buf length(%d) is smaller than size of BCP_Header_t(%d)\n", nBufLen, (int)sizeof(BCP_Header_t) );
		return BCP_rErrInvalidParam;
	}

	ptHD = (BCP_Header_t *)pucBuf;
	*ptHD = *ptHeader;

	ptHD->ucMsgType = ptHeader->ucMsgType;
	ptHD->unBodyLength = 0x00; //Encoding 완료 후 재설정

	return sizeof(BCP_Header_t);
}

