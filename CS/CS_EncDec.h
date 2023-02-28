/* CS_EncDec.h */
#ifndef _CS_ENCDEC_H_
#define _CS_ENCDEC_H_

#define CS_MAX_INO		50
#define CS_LOGIN_ID_LEN	12
#define CS_LOGIN_PW_LEN	15
#define CS_NAME_LEN		20
#define CS_COMPANY_LEN	20
#define CS_MOBILE_LEN	11
#define CS_TEL_LEN		11
#define CS_TEAM_LEN		30
#define CS_EMAIL_LEN	64

#define CS_FIELD_MASK_LOGIN		(CS_TAG_RESULT_CODE|CS_TAG_SESSON_ID)
#define CS_FIELD_MASK_CREATE	(CS_TAG_RESULT_CODE|CS_TAG_CARD_ID)
#define CS_FIELD_MASK_SEARCH	(CS_TAG_RESULT_CODE|CS_TAG_TOTAL_CNT|CS_TAG_CNT|CS_TAG_CARD_ID|CS_TAG_NAME| \
        						 CS_TAG_COMPANY|CS_TAG_TEAM|CS_TAG_POSITION|CS_TAG_MOBILE|CS_TAG_EMAIL)
								//CS_TAG_TITLE, CS_TAG_TEL - optional
#define CS_FIELD_MASK_DELETE	(CS_TAG_RESULT_CODE|CS_TAG_TOTAL_CNT|CS_TAG_CNT|CS_TAG_CARD_ID|CS_TAG_NAME| \
								 CS_TAG_COMPNAY|CS_TAG_TEL)

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
    CS_RC_SUCC                 = 0x00,
    CS_RC_FAIL                 = 0x01
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

typedef struct
{
	unsigned int    unCnt;
	unsigned int    unCardId;
	char            szName[CS_NAME_LEN + 1];
	char            szCompany[CS_COMPANY_LEN + 1];
	char            szTeam[CS_TEAM_LEN + 1];
	unsigned char   ucPosition;
	unsigned char   ucTitle;
	char            szMobile[CS_MOBILE_LEN + 1];
	char            szTel[CS_TEL_LEN + 1];
	char            szEmail[CS_EMAIL_LEN + 1];
} CS_DetailInfo_t;

typedef struct
{
	unsigned int    unCnt;
	unsigned int    unCardId;
	char            szName[NAME_LEN + 1];
	char            szCompany[COMPANY_LEN + 1];
	char            szMobile[MOBILE_LEN + 1];
} CS_SimpleInfo_t;

/**************************************************/
/*                     HEADER                     */
/**************************************************/
typedef struct
{
	unsigned char   ucMsgType;
	unsigned int    unBodyLen;
} CS_Header_t;

/*************************************************/
/*                    REQUEST                    */
/*************************************************/
typedef struct
{
	char            szLoginId[CS_LOGIN_ID_LEN + 1];
	char            szLoginPw[CS_LOGIN_PW_LEN + 1];
} CS_LoginReq_t;

typedef struct
{
	char            szName[CS_NAME_LEN + 1];
	char            szCompany[CS_COMPANY_LEN + 1];
	char            szTeam[CS_TEAM_LEN + 1];
	unsigned char   ucPosition;
	unsigned char   ucTitle;
	char            szMobile[CS_MOBILE_LEN + 1];
	char            szTel[CS_TEL_LEN + 1];
	char            szEmail[CS_EMAIL_LEN + 1];
} CS_CreateReq_t;

typedef struct
{
	char            szName[CS_NAME_LEN + 1];
	char            szCompany[CS_COMPANY_LEN + 1];
	unsigned int    unCardId;
} CS_SearchReq_t;

typedef struct
{
	char            szName[CS_NAME_LEN + 1];
	char            szCompany[CS_COMPANY_LEN + 1];
	unsigned int    unCardId;
} CS_DeleteReq_t;

/**************************************************/
/*                    RESPONSE                    */
/**************************************************/
typedef struct
{
	unsigned short   usTotalCnt;
	CS_DetailInfo_t  tDetailInfo[CS_MAX_INFO];
} CS_SearchRes_t;

typedef struct
{
	unsigned short   usTotalCnt;
	CS_SimpleInfo_t  tSimpleInfo[CS_MAX_INFO];
} CS_DeleteRes_t;

typedef struct
{
	unsigned char ucResultCode;
	union
	{
		unsigned char	ucErrCode;
		unsigned long	ulSessionId; //LoginRes
		unsigned int 	unCardId;    //CreateRes
		CS_SearchRes_t	tSearchRes;
		CS_DeleteRes_t	tDeleteRes;
	} u;
} CS_Res_t;

int ENCDEC_EncodingHeader		( unsigned char *pucBuf, int nBufMaxLen, CS_Header_t *ptHeader );
int ENCDEC_EncodingLoginBody	( unsigned char *pucBuf, int nBufMaxLen, CS_LoginReq_t *ptLoginReq );
int ENCDEC_EncodingCreateBody	( unsigned char *pucBuf, int nBufMaxLen, CS_CreateReq_t *ptCreateReq, unsigned char ucBitmask );
int ENCDEC_EncodingSearchBody	( unsigned char *pucBuf, int nBufMaxLen, CS_SearchReq_t *ptSearchReq, unsigned char ucBitmask );
int ENCDEC_EncodingDeleteBody	( unsigned char *pucBuf, int nBufMaxLen, CS_DeleteReq_t *ptDeleteReq, unsigned char ucBitmask );
int ENCDEC_EncodingLogoutBody	( unsigned char *pucBuf, int nBufMaxLen );

int encdec_EncodingLoginId		( unsigned char *pucBuf, int nBufMaxLen, char *pszLoginId );
int encdec_EncodingLoginPw		( unsigned char *pucBuf, int nBufMaxLen, char *pszLoginPw );
int encdec_EncodingSessionId	( unsigned char *pucBuf, int nBufMaxLen, unsigned long ulSessionId );
int encdec_EncodingName			( unsigned char *pucBuf, int nBufMaxLen, const char *pszName );
int encdec_EncodingCompany		( unsigned char *pucBuf, int nBufMaxLen, const char *pszCompany );
int encdec_EncodingTeam			( unsigned char *pucBuf, int nBufMaxLen, const char *pszTeam );
int encdec_EncodingPosition		( unsigned char *pucBuf, int nBufMaxLen, unsigned char char ucPosition );
int encdec_EncodingTitle		( unsigned char *pucBuf, int nBufMaxLen, unsigned char ucTitle );
int encdec_EncodingMobile		( unsigned char *pucBuf, int nBufMaxLen, const char *pszMobile );
int encdec_EncodingTel			( unsigned char *pucBuf, int nBufMaxLen, const char *pszTel );
int encdec_EncodingEmail		( unsigned char *pucBuf, int nBufMaxLen, const char *pszEmail );
int encdec_EncodingCardId		( unsigned char *pucBuf, int nBufMaxLen, unsigned int unCardId );

int encdec_EncodingOneByte		( unsigned char *pucBuf, int nBufMaxLen, unsigned char ucData );
int encdec_EncodingShort		( unsigned char *pucBuf, int nBufMaxLen, unsigned short usData );
int encdec_EncodingInt			( unsigned char *pucBuf, int nBufMaxLen, unsigned int unData );
int encdec_EncodingLong			( unsigned char *pucBuf, int nBufMaxLen, unsigned long ulData );
int encdec_EncodingString		( unsigned char *pucBuf, int nBufLen, const char *pszData, int nStrMaxLen, char cChar );

int ENCDEC_DecodingHeader		( unsigned char *pucHeaderBuf, int nBufMaxLen, CS_Header_t *ptHeader );
int ENCDEC_DecodingBody			( unsigned char *pucBodyBuf, int nBufMaxLen, unsigned char ucMsgType, CS_Res_t *ptRes );
int ENCDEC_DecodingLoginBody	( unsigned char *pucBodyBuf, int nBufMaxLen, Res_t *ptRes );
int ENCDEC_DecodingCreateBody	( unsigned char *pucBodyBuf, int nBufMaxLen, Res_t *ptRes );
int ENCDEC_DecodingSearchBody	( unsigned char *pucBodyBuf, int nBufMaxLen, Res_t *ptRes );
int ENCDEC_DecodingDeleteBody	( unsigned char *pucBodyBuf, int nBufMaxLen, Res_t *ptRes );
int ENCDEC_DecodingLogoutBody	( unsigned char *pucBodyBuf, int nBufMaxLen, Res_t *ptRes );

int encdec_DecodingOneByte		( unsigned char *pucBodyBuf, unsigned char *pucData ); 
int encdec_DecodingShort		( unsigned char *pucBodyBuf, unsigned short *pusData );
int encdec_DecodingInt			( unsigned char *pucBodyBuf, unsigned int *punData );
int encdec_DecodingLong			( unsigned char *pucBodyBuf, unsigned long *pulData );
int encdec_DecodingString		( unsigned char *pucBodyBuf, char *pszData );

#endif /* _CS_ENCDEC_H_ */
