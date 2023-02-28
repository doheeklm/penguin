/* CS_Sock.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int SOCK_Init()
{
	int nRC = 0;
	int nFd = 0;
	struct sockaddr_in tSockAddr;
	memset( &tSockAddr, 0, sizeof(tSockAddr) );
	
	g_tEnv.nFd = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( -1 == g_tEnv.nFd )
	{
		fprintf( stderr, "%s:: socket fail <%d:%s>\n", __func__, errno, strerror(errno) );
		return CS_rErrSocketInit;
	}

	printf( "%s:: socket fd[%d] created\n", __func__, g_tEnv.nFd );

	tSockAddr.sin_family = AF_INET;
	tSockAddr.sin_port = htons( g_tEnv.nPort );
	if ( -1 == tSockAddr.sin_port )
	{
		fprintf( stderr, "%s:: htons fail <%d:%s>\n", __func__, errno, strerror(errno) );
		goto end_of_function;
	}

	tSockAddr.sin_addr.s_addr = inet_addr( g_tEnv.szIp ); //서버 주소
	if ( INADDR_NONE == tSockAddr.sin_addr.s_addr )
	{
		fprintf( stderr, "%s:: inet_addr fail <%d:%s>\n", __func__, errno, strerror(errno) );
		goto end_of_function;
	}

	nRC = connect( g_tEnv.nFd, (struct sockaddr*)&tSockAddr, sizeof(tSockAddr) );	
	if ( -1 == nRC );
	{
		fprintf( stderr, "%s:: connect fail <%d:%s>\n", __func__, errno, strerror(errno) );
		goto end_of_function;
	}

	return CS_rOk;

end_of_function:
	FD_CLOSE( g_tEnv.nFd );
	return CS_rErrSocketInit;
}

