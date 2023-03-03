/* CS_Err.h */
#ifndef _CS_ERR_H_
#define _CS_ERR_H_

typedef enum
{
	CS_rErrFail = -100,
	CS_rErrInvalidParam,
	CS_rErrOverflow,

	CS_rErrConfigInit,
	CS_rErrSocketInit,
	CS_rErrWriteFail,
	CS_rErrReadFail,
	CS_rErrWrongLength,

	CS_rErrSystemFail, //서버측 에러
	CS_rErrLoginFail, //클라이언트측 에러

	CS_rErrDecodingFail,
	CS_rErrMissingTag,

	CS_rExitProgram,
	CS_rOk = 1000,

} ReturnCode_e;

#endif /* _CS_ERR_H_ */
