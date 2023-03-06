/* CS_EncDec.h */
#ifndef _CS_ENCDEC_H_
#define _CS_ENCDEC_H_

#define CS_REQ_BUF_LEN			512
#define CS_RES_HEADER_BUF_LEN	5
#define CS_RES_BODY_BUF_LEN		512

#define CS_SPACE				' '
#define CS_ASTERISK				'*'
#define CS_MAX_INFO				50

#define CS_LEN_LOGIN_ID			12
#define CS_LEN_LOGIN_PW			15
#define CS_LEN_SESSION_ID		8
#define CS_LEN_CARD_ID			4
#define CS_LEN_NAME				20
#define CS_LEN_COMPANY			20
#define CS_LEN_MOBILE			11
#define CS_LEN_TEL				11
#define CS_LEN_TEAM				30
#define CS_LEN_TOTAL_CNT		2
#define CS_LEN_CNT				1
#define CS_LEN_EMAIL			64
#define CS_LEN_RESULT_CODE		1
#define CS_LEN_ERR_CODE			1

/* Field Mask */
typedef enum _CS_FieldMask_e
{
	CS_FIELD_MASK_RESULT_CODE	= 0x01,
	CS_FIELD_MASK_ERR_CODE		= 0x02,
	CS_FIELD_MASK_SESSION_ID	= 0x04,
	CS_FIELD_MASK_CARD_ID		= 0x08,
	CS_FIELD_MASK_NAME			= 0x10,		//0000 0001 0000
	CS_FIELD_MASK_COMPANY		= 0x20,		//0000 0010 0000
	CS_FIELD_MASK_MOBILE		= 0x40,		//0000 0100 0000
	CS_FIELD_MASK_TEL			= 0x80,		//0000 1000 0000
	CS_FIELD_MASK_TEAM			= 0x100,	//0001 0000 0000
	CS_FIELD_MASK_POSITION		= 0x200,	//0010 0000 0000
	CS_FIELD_MASK_TITLE			= 0x400,	//0100 0000 0000
	CS_FIELD_MASK_EMAIL			= 0x800,	//1000 0000 0000
	CS_FIELD_MASK_TOTAL_CNT		= 0x1000,
	CS_FIELD_MASK_CNT			= 0x2000
} CS_FieldMask_e;

#define SET_MASK( p_mask, _data_mask, _data ) \
	do { \
		if ( EMPTY_INPUT != strlen(_data) ) \
		{ \
			*(p_mask) |= (_data_mask); \
		} \
	} while ( 0 );

#define SET_MASK_( p_mask, _data_mask, _data ) \
	do { \
		if ( EMPTY_INPUT != (_data) ) \
		{ \
			*(p_mask) |= (_data_mask); \
		} \
	} while ( 0 );

#define SET_MASK_CREATE_REQ( p_mask, _data ) \
	do { \
		SET_MASK( p_mask, CS_FIELD_MASK_NAME, (_data).szName ); \
		SET_MASK( p_mask, CS_FIELD_MASK_COMPANY, (_data).szCompany ); \
		SET_MASK( p_mask, CS_FIELD_MASK_TEAM, (_data).szTeam ); \
		SET_MASK_( p_mask, CS_FIELD_MASK_POSITION, (_data).ucPosition ); \
		SET_MASK_( p_mask, CS_FIELD_MASK_TITLE, (_data).ucTitle ); \
		SET_MASK( p_mask, CS_FIELD_MASK_MOBILE, (_data).szMobile ); \
		SET_MASK( p_mask, CS_FIELD_MASK_TEL, (_data).szTel ); \
		SET_MASK( p_mask, CS_FIELD_MASK_EMAIL, (_data).szEmail ); \
	} while ( 0 );

#define SET_MASK_SEARCH_DELETE_REQ( p_mask, _data ) \
	do { \
		SET_MASK( p_mask, CS_FIELD_MASK_NAME, (_data).szName ); \
		SET_MASK( p_mask, CS_FIELD_MASK_COMPANY, (_data).szCompany ); \
		SET_MASK_( p_mask, CS_FIELD_MASK_CARD_ID, (_data).unCardId ); \
	} while ( 0 );

#define CS_FIELD_MASK_FAIL_RES		(CS_FIELD_MASK_RESULT_CODE|CS_FIELD_MASK_ERR_CODE)
#define CS_FIELD_MASK_LOGIN_RES		(CS_FIELD_MASK_RESULT_CODE|CS_FIELD_MASK_SESSION_ID)
#define CS_FIELD_MASK_CREATE_RES	(CS_FIELD_MASK_RESULT_CODE|CS_FIELD_MASK_CARD_ID)
#define CS_FIELD_MASK_SEARCH_RES	(CS_FIELD_MASK_RESULT_CODE|CS_FIELD_MASK_TOTAL_CNT| \
									 CS_FIELD_MASK_CNT|CS_FIELD_MASK_CARD_ID|CS_FIELD_MASK_NAME| \
									 CS_FIELD_MASK_COMPANY|CS_FIELD_MASK_TEAM|CS_FIELD_MASK_POSITION| \
									 CS_FIELD_MASK_MOBILE|CS_FIELD_MASK_EMAIL)
									//Optional: CS_FIELD_MASK_TITLE, CS_FIELD_MASK_TEL
#define CS_FIELD_MASK_DELETE_RES	(CS_FIELD_MASK_RESULT_CODE|CS_FIELD_MASK_TOTAL_CNT| \
									 CS_FIELD_MASK_CNT|CS_FIELD_MASK_CARD_ID| \
									 CS_FIELD_MASK_NAME|CS_FIED_MASK_COMPNAY|CS_FIELD_MASK_TEL)
/* Message Type */
typedef enum _CS_MsgType_e
{
    CS_MSG_LOGIN_REQ           = 0x01,
    CS_MSG_CREATE_REQ          = 0x02,
    CS_MSG_SEARCH_REQ          = 0x03,
    CS_MSG_DELETE_REQ          = 0x04,
    CS_MSG_LOGOUT_REQ          = 0x05,
    CS_MSG_LOGIN_RES           = 0x11,
    CS_MSG_CREATE_RES          = 0x12,
    CS_MSG_SEARCH_RES          = 0x13,
    CS_MSG_DELETE_RES          = 0x14,
    CS_MSG_LOGOUT_RES          = 0x15
} CS_MsgType_e;

/* Position */
typedef enum _CS_Position_e
{
    CS_P_EMPLOYEE              = 0x01,
    CS_P_ASSISTANT_MANAGER     = 0x02,
    CS_P_MANAGER               = 0x03,
    CS_P_DEPUTY_GENERAL_MANAGER= 0x04,
    CS_P_GENERAL_MANAGER       = 0x05,
    CS_P_ASSISTANT             = 0x06,
    CS_P_JUNIOR                = 0x07,
    CS_P_SENIOR                = 0x08,
    CS_P_PRINCIPAL             = 0x09,
    CS_P_DIRECTOR              = 0x0A,
    CS_P_MANAGING_DIRECTOR     = 0x0B,
    CS_P_SENIOR_MANAGING_DIRECTOR = 0x0C,
    CS_P_CEO                   = 0x0D,
    CS_P_CHAIRMAN              = 0x0E
} CS_Position_e;

/* Title */
typedef enum _CS_Title_e
{
    CS_T_STAFF                 = 0x01,
    CS_T_CHEIF_OF_STAFF        = 0x02,
    CS_T_HEAD_OF_DEPARTMENT    = 0x03,
    CS_T_HEAD_OF_DEVISION      = 0x04,
    CS_T_DIRECTOR              = 0x05,
    CS_T_GROUP_LEADER          = 0x06,
    CS_T_MANAGER_OF_DEPARMENT  = 0x07,
    CS_T_CTO                   = 0x08,
    CS_T_CEO                   = 0x09
} CS_Title_e;

/* Return Code */
typedef enum _CS_ReturnCode_e
{
    CS_RC_SUCCESS              = 0x00,
    CS_RC_FAIL                 = 0x01,
} CS_ReturnCode_e;

/* Error Code */
typedef enum _CS_ErrCode_e
{
    CS_EC_USER_NOT_EXIST       = 0x01,
    CS_EC_WRONG_PASSWORD       = 0x02,
    CS_EC_INVALID_SESSION_ID   = 0x03,
    CS_EC_FULL_INFO            = 0x04,
    CS_EC_EMPTY_INFO           = 0x05,
    CS_EC_INFO_NOT_EXIST       = 0x06,
    CS_EC_SYSTEM_FAIL          = 0x07,
    CS_EC_DUPLICATE_LOGIN      = 0x08,
    CS_EC_MISSING_FIELD        = 0x09,
    CS_EC_UNDEFINED_ERR        = 0x0A
} CS_ErrCode_e;

/* Tag */
typedef enum _CS_Tag_e
{
    CS_TAG_LOGIN_ID            = 0x01,
    CS_TAG_LOGIN_PW            = 0x02,
    CS_TAG_SESSION_ID          = 0x03,
    CS_TAG_CARD_ID             = 0x10,
    CS_TAG_NAME                = 0x11,
    CS_TAG_COMPANY             = 0x12,
    CS_TAG_MOBILE              = 0x13,
    CS_TAG_TEL                 = 0x14,
    CS_TAG_TEAM                = 0x15,
    CS_TAG_POSITION            = 0x16,
    CS_TAG_TITLE               = 0x17,
    CS_TAG_EMAIL               = 0x18,
    CS_TAG_TOTAL_CNT           = 0x20,
    CS_TAG_CNT                 = 0x21,
    CS_TAG_RESULT_CODE         = 0x30,
    CS_TAG_ERR_CODE            = 0x31
} CS_Tag_e;

#pragma pack(push, 1)

typedef struct
{
	unsigned int			unCnt;
	unsigned int			unCardId;
	char					szName[CS_LEN_NAME + 1];
	char					szCompany[CS_LEN_COMPANY + 1];
	char					szTeam[CS_LEN_TEAM + 1];
	unsigned char			ucPosition;
	unsigned char			ucTitle;
	char					szMobile[CS_LEN_MOBILE + 1];
	char					szTel[CS_LEN_TEL + 1];
	char					szEmail[CS_LEN_EMAIL + 1];
} CS_DetailInfo_t;

typedef struct
{
	unsigned int			unCnt;
	unsigned int			unCardId;
	char					szName[CS_LEN_NAME + 1];
	char					szCompany[CS_LEN_COMPANY + 1];
	char					szMobile[CS_LEN_MOBILE + 1];
} CS_SimpleInfo_t;

/**************************************************/
/*                     HEADER                     */
/**************************************************/
typedef struct
{
	unsigned char			ucMsgType;
	unsigned int			unBodyLen;
} CS_Header_t;

/*************************************************/
/*                    REQUEST                    */
/*************************************************/
typedef struct
{
	char					szLoginId[CS_LEN_LOGIN_ID + 1];
	char					szLoginPw[CS_LEN_LOGIN_PW + 1];
} CS_LoginReqData_t;

typedef struct
{
	char					szName[CS_LEN_NAME + 1];
	char					szCompany[CS_LEN_COMPANY + 1];
	char					szTeam[CS_LEN_TEAM + 1];
	unsigned char			ucPosition;
	unsigned char			ucTitle;
	char					szMobile[CS_LEN_MOBILE + 1];
	char					szTel[CS_LEN_TEL + 1];
	char					szEmail[CS_LEN_EMAIL + 1];
} CS_CreateReqData_t;

typedef struct
{
	char					szName[CS_LEN_NAME + 1];
	char					szCompany[CS_LEN_COMPANY + 1];
	unsigned int			unCardId;
} CS_SearchReqData_t, CS_DeleteReqData_t;

/**************************************************/
/*                    RESPONSE                    */
/**************************************************/
typedef struct
{
	unsigned short			usTotalCnt;
	CS_DetailInfo_t			tDetailInfo[CS_MAX_INFO];
} CS_SearchResData_t;

typedef struct
{
	unsigned short			usTotalCnt;
	CS_SimpleInfo_t			tSimpleInfo[CS_MAX_INFO];
} CS_DeleteResData_t;

typedef struct
{
	unsigned char			ucResultCode;
	union
	{
		unsigned char		ucErrCode;
		unsigned long		ulSessionId;
		unsigned int 		unCardId;
		CS_SearchResData_t	tSearchResData;
		CS_DeleteResData_t	tDeleteResData;
	} u;
} CS_ResBody_t;

#pragma pack(pop)

/**************************************************/
/*                    ENCODING                    */
/**************************************************/
int ENCDEC_EncodingHeader( unsigned char *pucBuf, int nBufLen, CS_Header_t *ptHeader );
int ENCDEC_EncodingLoginBody( unsigned char *pucBuf, int nBufLen, CS_LoginReqData_t *ptLoginReqData );
int ENCDEC_EncodingCreateBody( unsigned char *pucBuf, int nBufLen, CS_CreateReqData_t *ptCreateReqData, unsigned short usBitmask );
int ENCDEC_EncodingSearchBody( unsigned char *pucBuf, int nBufLen, CS_SearchReqData_t *ptSearchReqData, unsigned short usBitmask );
int ENCDEC_EncodingDeleteBody( unsigned char *pucBuf, int nBufLen, CS_DeleteReqData_t *ptDeleteReqData, unsigned short usBitmask );
int ENCDEC_EncodingLogoutBody( unsigned char *pucBuf, int nBufLen );

void encdec_SetBodyLen( unsigned char *pucBuf, unsigned int unLen );

int ENCDEC_EncodingTLVString( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, char *pszValue, char cFillChar ); 
int ENCDEC_EncodingTLVOneByte( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned char ucValue );
int ENCDEC_EncodingTLVInt( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned int unValue );
int ENCDEC_EncodingTLVLong( unsigned char *pucBuf, int nBufLen, unsigned char ucTag, unsigned short usLength, unsigned long ulValue );

int encdec_EncodingString( unsigned char *pucBuf, int nBufLen, char *pszData, int nStrMaxLen, char cChar );
int encdec_EncodingOneByte( unsigned char *pucBuf, int nBufLen, unsigned char ucData );
int encdec_EncodingShort( unsigned char *pucBuf, int nBufLen, unsigned short usData );
int encdec_EncodingInt( unsigned char *pucBuf, int nBufLen, unsigned int unData );
int encdec_EncodingLong( unsigned char *pucBuf, int nBufLen, unsigned long ulData );

/**************************************************/
/*                    DECODING                    */
/**************************************************/
int ENCDEC_DecodingHeader( unsigned char *pucBuf, CS_Header_t *ptHeader );
int ENCDEC_DecodingBody( unsigned char *pucBuf, CS_Header_t tHeader, CS_ResBody_t *ptResBody );

int ENCDEC_DecodingLoginBody( unsigned char *pucBuf, int nBufLen, CS_ResBody_t *ptResBody );

int encdec_DecodingOneByte( unsigned char *pucBuf, unsigned char *pucData ); 
int encdec_DecodingShort( unsigned char *pucBuf, unsigned short *pusData );
int encdec_DecodingLong( unsigned char *pucBuf, unsigned long *pulData );
int encdec_DecodingString( unsigned char *pucBuf, char *pszData, int nStrMaxLen );

/*

int ENCDEC_DecodingCreateBody	( unsigned char *pucBodyBuf, int nBufLen, Res_t *ptRes );
int ENCDEC_DecodingSearchBody	( unsigned char *pucBodyBuf, int nBufLen, Res_t *ptRes );
int ENCDEC_DecodingDeleteBody	( unsigned char *pucBodyBuf, int nBufLen, Res_t *ptRes );
int ENCDEC_DecodingLogoutBody	( unsigned char *pucBodyBuf, int nBufLen, Res_t *ptRes );

int encdec_DecodingInt			( unsigned char *pucBodyBuf, unsigned int *punData );
int encdec_DecodingString		( unsigned char *pucBodyBuf, char *pszData );
int encdec_DecodingLong( unsigned char *pucBuf, unsigned long *pulData );
*/

#endif /* _CS_ENCDEC_H_ */
