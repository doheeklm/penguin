/* BCP_Err.h */
#ifndef _BCP_ERR_H_
#define _BCP_ERR_H_

typedef enum
{
	BCP_rOk = 1000,
	
	BCP_rErrFail,
	BCP_rErrInvalidParam,
	BCP_rErrSocketInit,
	
	BCP_rExitProgram
} ReturnCode_e;

#endif /* _BCP_ERR_H_ */
