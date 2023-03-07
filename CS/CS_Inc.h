/* CS_Inc.h */
#ifndef _CS_INC_H_
#define _CS_INC_H_

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

#include "CS_Conf.h"
#include "CS_Macro.h"
#include "CS_Errmsg.h"
#include "CS_Util.h"
#include "CS_Sock.h"
#include "CS_EncDec.h"
#include "CS_Task.h"
#include "CS_Sim.h"
#include "CS_Menu.h"

typedef struct
{
	char			szIp[16];
	int				nPort;
	int				nClientFd;
	long 	ulSessionId;
} CS_Env_t;

#endif /* _CS_INC_H_ */
