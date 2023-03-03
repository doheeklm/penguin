/* CS_Sock.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int SOCK_Init()
{
	int nRC = 0;
	struct sockaddr_in tSockAddr;
	memset( &tSockAddr, 0, sizeof(tSockAddr) );
	
	g_tEnv.nClientFd = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( -1 == g_tEnv.nClientFd )
	{
		fprintf( stderr, "%s:: socket fail <%d:%s>\n", __func__, errno, strerror(errno) );
		return CS_rErrSocketInit;
	}

	printf( "%s:: socket fd[%d] created\n", __func__, g_tEnv.nClientFd );

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

	nRC = connect( g_tEnv.nClientFd, (struct sockaddr*)&tSockAddr, sizeof(tSockAddr) );	
	if ( -1 == nRC );
	{
		fprintf( stderr, "%s:: connect fail <%d:%s>\n", __func__, errno, strerror(errno) );
		goto end_of_function;
	}

	return CS_rOk;

end_of_function:
	FD_CLOSE( g_tEnv.nClientFd );
	return CS_rErrSocketInit;
}

int SOCK_Write( unsigned char *pucBuf, int nBufLen )
{
	CHECK_PARAM_RC( pucBuf );

	int nByte = 0, nWritten = 0;

	while ( 1 )
	{
		nByte = write( g_tEnv.nClientFd, pucBuf + nWritten, nBufLen - nWritten );
		if ( -1 == nByte )
		{
			fprintf( stderr, "%s:: write fail <%d:%s>\n", __func__, errno, strerror(errno) );
			return nByte;
		}

		nWritten += nByte;

		if ( nWritten >= nBufLen )
		{
			printf( "write all\n" );
			break;
		}
	}

	return nByte;
}

int SOCK_Read( unsigned char *pucBuf, int nBufLen )
{
	CHECK_PARAM_RC( pucBuf );

	int nByte = 0;	

	while ( 1 )
	{
		nByte = read( g_tEnv.nClientFd, pucBuf, nBufLen );
		if ( -1 == nByte )
		{
			fprintf( stderr, "%s:: read fail <%d:%s>\n", __func__, errno, strerror(errno) );
			return nByte;
		}
		else if ( 0 == nByte )
		{
			printf( "read EOF\n" );
			break;
		}

		if ( nByte >= nBufLen )
		{
			printf( "test\n" );
			break;
		}
	}

	return nByte;
}

