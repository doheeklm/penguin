/* BCP_Inc.h */
#ifndef _BCP_INC_H_
#define _BCP_INC_H_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio_ext.h>

#include "BCP_Macro.h"
#include "BCP_Errmsg.h"
#include "BCP_Util.h"
#include "BCP_Sock.h"
#include "BCP_EncDec.h"
#include "BCP_Task.h"

typedef struct
{
	char szIp[16];
	int nPort;
	int nFd;
} BCP_Env_t;

#endif /* _BCP_INC_H_ */
