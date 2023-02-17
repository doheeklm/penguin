/* BCP_EncDec.h */
#ifndef _BCP_ENCDEC_H_
#define _BCP_ENCDEC_H_

#define BCP_LOGINID_LEN	12
#define BCP_LOGINPW_LEN	15
#define BCP_NAME_LEN	20
#define BCP_COMPANY_LEN	20
#define BCP_MOBILE_LEN	11
#define BCP_TEL_LEN		11
#define BCP_TEAM_LEN	30
#define BCP_EMAIL_LEN	64

/* Message Type */
typedef enum _BCP_MsgType_e
{
	LOGIN_REQ	= 0x01,
	CREATE_REQ	= 0x02,
	SEARCH_REQ	= 0x03,
	DELETE_REQ	= 0x04,
	LOGOUT_REQ	= 0x05,
	LOGIN_RES	= 0x11,
	CREATE_RES	= 0x12,
	SEARCH_RES	= 0x13,
	DELETE_RES	= 0x14,
	LOGOUT_RES	= 0x15
} BCP_MsgType_e;

/* Position */
typedef enum _BCP_Position_e
{
	BCP_P_Employee					= 0x01,
	BCP_P_AssistantManager			= 0x02,
	BCP_P_Manager					= 0x03,
	BCP_P_DeputyGeneralManager		= 0x04,
	BCP_P_GeneralManager			= 0x05,
	BCP_P_Assistant					= 0x06,
	BCP_P_Junior					= 0x07,
	BCP_P_Senior					= 0x08,
	BCP_P_Principal					= 0x09,
	BCP_P_Director					= 0x0A,
	BCP_P_ManagingDirector			= 0x0B,
	BCP_P_SeniorManagingDirector	= 0x0C,
	BCP_P_CEO						= 0x0D,
	BCP_P_Chairman					= 0x0E
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
	BCP_RC_SUCC	= 0x00,
	BPC_RC_FAIL = 0x01
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

typedef struct _BCP_LoginReq_s
{
	char szLoginId[BCP_LOGINID_LEN + 1];
	char szLoginPw[BCP_LOGINPW_LEN + 1];
} BCP_LoginReq_t;

typedef struct _BCP_LoginRes_s
{
	char			ucReturnCode;
	char			ucErrCode;

	unsigned long	ulSessionId; //if success
} BCP_LoginRes_t;

typedef struct _BCP_InsertReq_s
{
	unsigned long	ulSessionId;
	char			szName[BCP_NAME_LEN + 1];
	char			szCompany[BCP_COMPANY_LEN + 1];
	unsigned char	ucPosition;
	unsigned char	ucTitle; //O
	char			szMobile[BCP_MOBILE_LEN + 1];
	char			szTel[BCP_TEL_LEN + 1]; //O
	char			szEmail[BCP_EMAIL_LEN + 1];
} BCP_InsertReq_t;

typedef struct _BCP_InsertRes_s
{
	char			ucReturncode;
	char			ucErrCode;
	unsigned int	unBCId; //if success
} BCP_InsertRes_t;

typedef struct _BCP_SelectReq_s
{
	unsigned long	ulSessionId;
	char			szName[BCP_NAME_LEN + 1]; //O
	char			szCompany[BCP_COMPANY_LEN + 1]; //O
	unsigned int	unBCId;	//O
} BCP_SelectReq_t;

typedef struct _BCP_SelectRes_s
{
	char			ucReturncode;
	char			ucErrCode;
	/* if success */	
	unsigned short	usBCTotal;
	unsigned int	unBCCnt;
	unsigned int	unBCId;
	char			szName[BCP_NAME_LEN + 1];
	char			szCompany[BCP_COMPANY_LEN + 1];
	unsigned char	ucPosition; 
	unsigned char	ucTitle; //O
	char			szMobile[BCP_MOBILE_LEN + 1];
	char			szTel[BCP_TEL_LEN + 1]; //O
	char			szEmail[BCP_EMAIL_LEN + 1];
} BCP_SelectRes_t;

typedef BCP_SelectReq_t BCP_DeleteReq_t;

typedef struct _BCP_DeleteRes_s
{
	char			ucReturncode;
	char			ucErrCode;
	/* if success */	
	unsigned short	usBCTotal;
	unsigned int	unBCCnt;
	unsigned int	unBCId;
	char			szName[BCP_NAME_LEN + 1];
	char			szCompany[BCP_COMPANY_LEN + 1];
	char			szMobile[BCP_MOBILE_LEN + 1];
} BCP_DeleteRes_t;

typedef struct _BCP_LogoutReq_s
{
	unsigned long	ulSessionId;
} BCP_LogoutReq_t;

typedef struct _BCP_LogoutRes_s
{
	char			ucReturncode;
	char			ucErrCode;
} BCP_LogoutRes_t;

typedef struct _BCP_Req_s
{
	BCP_Header_t	tHeader;
	BCP_TLV_t		tTLV;	
//TODO TVL 여러개?
	/*
	  union
	{
		BCP_LoginReq_t	tLoginReq;
		BCP_InsReq_t	tInsReq;
		BCP_SelReq_t	tSelReq;
		BCP_DelReq_t	tDelReq;
		BCP_LogoutReq_t	tLogoutReq;
	} u;*/
} BCP_Req_t;

//TODO _BCP_Res_s

#endif /* _BCP_ENCDEC_H_ */
