/* CS_Err.h */
#ifndef _CS_ERR_H_
#define _CS_ERR_H_

typedef enum
{
	CS_rOk = 1000,
	
	CS_rErrFail,
	CS_rErrInvalidParam,
	CS_rErrSocketInit,
	
	CS_rExitProgram
} ReturnCode_e;

#endif /* _CS_ERR_H_ */
