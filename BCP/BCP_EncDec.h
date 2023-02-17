/* BCP_EncDec.h */
#ifndef _BCP_ENCDEC_H_
#define _BCP_ENCDEC_H_

#define BCP_LOGIN_ID_LEN		12
#define BCP_LOGIN_PW_LEN		15
#define BCP_NAME_LEN			20
#define BCP_COMPANY_LEN			20
#define BCP_MOBILE_LEN			11
#define BCP_TEL_LEN				11
#define BCP_TEAM_LEN			30
#define BCP_EMAIL_LEN			64

/* Message Type */
typedef enum _BCP_MsgType_e
{
	LOGIN_REQ					= 0x01,
	CREATE_REQ					= 0x02,
	SEARCH_REQ					= 0x03,
	DELETE_REQ					= 0x04,
	LOGOUT_REQ					= 0x05,
	LOGIN_RES					= 0x11,
	CREATE_RES					= 0x12,
	SEARCH_RES					= 0x13,
	DELETE_RES					= 0x14,
	LOGOUT_RES					= 0x15
} BCP_MsgType_e;

/* Position */
typedef enum _BCP_Position_e
{
	BCP_P_Employee				= 0x01,
	BCP_P_AssistantManager		= 0x02,
	BCP_P_Manager				= 0x03,
	BCP_P_DeputyGeneralManager	= 0x04,
	BCP_P_GeneralManager		= 0x05,
	BCP_P_Assistant				= 0x06,
	BCP_P_Junior				= 0x07,
	BCP_P_Senior				= 0x08,
	BCP_P_Principal				= 0x09,
	BCP_P_Director				= 0x0A,
	BCP_P_ManagingDirector		= 0x0B,
	BCP_P_SeniorManagingDirector= 0x0C,
	BCP_P_CEO					= 0x0D,
	BCP_P_Chairman				= 0x0E
} BCP_Position_e;

/* Title */
typedef enum _BCP_Title_e
{
	BCP_T_Staff					= 0x01,
	BCP_T_ChiefOfStaff			= 0x02,
	BCP_T_HeadOfDepartment		= 0x03,
	BCP_T_HeadOfDevision		= 0x04,
	BCP_T_Director				= 0x05,
	BCP_T_GroupLeader			= 0x06,
	BCP_T_ManagerOfDepartment	= 0x07,
	BCP_T_CTO					= 0x08,
	BCP_T_CEO					= 0x09
} BCP_Title_e;

/* Return Code */
typedef enum _BCP_ReturnCode_e
{
	BCP_RC_SUCC					= 0x00,
	BPC_RC_FAIL					= 0x01
} BCP_ReturnCode_e;

/* Error Code */
typedef enum _BCP_ErrCode_e
{
	BCP_EC_USER_NOT_EXIST		= 0x01,
	BCP_EC_WRONG_PASSWORD		= 0x02,
	BCP_EC_INVALID_SESSION_ID	= 0x03,
	BCP_EC_FULL_INFO			= 0x04,
	BCP_EC_EMPTY_INFO			= 0x05,
	BCP_EC_INFO_NOT_EXIST		= 0x06,
	BCP_EC_SYSTEM_FAIL			= 0x07,
	BCP_EC_DUPLICATE_LOGIN		= 0x08,
	BCP_EC_MISSING_FIELD		= 0x09,
	BCP_EC_UNDEFINED_ERR		= 0x0A
} BCP_ErrCode_e;

/* Tag */
typedef enum _BCP_Tag_e
{
	BCP_TAG_LOGIN_ID			= 0x01,
	BCP_TAG_LOGIN_PW			= 0x02,
	BCP_TAG_SESSION_ID			= 0x03,
	BCP_TAG_BC_ID				= 0x10,
	BCP_TAG_NAME				= 0x11,
	BCP_TAG_COMPANY				= 0x12,
	BCP_TAG_MOBILE				= 0x13,
	BCP_TAG_TEL					= 0x14,
	BCP_TAG_TEAM				= 0x15,
	BCP_TAG_POSITION			= 0x16,
	BCP_TAG_TITLE				= 0x17,
	BCP_TAG_EMAIL				= 0x18,
	BCP_TAG_BC_TOTAL			= 0x20,
	BCP_TAG_BC_CNT				= 0x21,
	BCP_TAG_RESULT_CODE			= 0x30,
	BCP_TAG_ERR_CODE			= 0x31
} BCP_Tag_e;

typedef struct _BCP_LoginReqData_s
{
	char			szLoginId[BCP_LOGIN_ID_LEN + 1];
	char			szLoginPw[BCP_LOGIN_PW_LEN + 1];
} BCP_LoginReqData_t;

typedef struct _BCP_Header_s
{
	unsigned char	ucMsgType;
	unsigned int	unBodyLength;
} BCP_Header_t;

typedef struct _BCP_TLV_s
{
	unsigned char	ucTag;
	unsigned short	usLength;
	char			acValue[];
} BCP_TLV_t;

typedef struct _BCP_ReqMsg_s
{
	//bitmask
	BCP_Header_t	tHeader;
	char			acBody[]; //malloc
} BCP_ReqMsg_t;

int ENCDEC_EncodingHeader( unsigned char *pucBuf, int nBufLen, BCP_Header_t *ptHeader );

/*
	char			szLoginId[BCP_LOGINID_LEN + 1];
	char			szLoginPw[BCP_LOGINPW_LEN + 1];
	unsigned long	ulSessionId;
	unsigned int	unBCId;
	char			szName[BCP_NAME_LEN + 1];
	char			szCompany[BCP_COMPANY_LEN + 1];
	char			szMobile[BCP_MOBILE_LEN + 1];
	char			szTel[BCP_TEL_LEN + 1];
	char			szTeam[BCP_TEAM_LEN + 1];
	unsigned char	ucPosition;
	unsigned char	ucTitle;
	char			szEmail[BCP_EMAIL_LEN + 1];
	unsigned short	usBCTotal;
	unsigned int	unBCCnt;
	char			cReturnCode;
	char			cErrCode;
*/

#endif /* _BCP_ENCDEC_H_ */
