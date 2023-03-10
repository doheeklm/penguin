/* CS_Sock.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int SOCK_Init()
{
	int nRC = 0;
	struct sockaddr_in tSockAddr;
	memset( &tSockAddr, 0, sizeof(tSockAddr) );
	
	g_tEnv.nClientFd = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP ); //Blocking 모드
	if ( -1 == g_tEnv.nClientFd )
	{
		fprintf( stderr, "%s:: socket fail <%d:%s>\n", __func__, errno, strerror(errno) );
		return CS_rErrSocketFail;
	}

	printf( "%s:: socket fd[%d] created\n", __func__, g_tEnv.nClientFd );

	tSockAddr.sin_family = AF_INET;
	tSockAddr.sin_port = htons( g_tEnv.nPort );
	if ( -1 == tSockAddr.sin_port )
	{
		fprintf( stderr, "%s:: htons fail <%d:%s>\n", __func__, errno, strerror(errno) );
		return CS_rErrFail;
	}

	tSockAddr.sin_addr.s_addr = inet_addr( g_tEnv.szIp ); //서버 주소
	if ( INADDR_NONE == tSockAddr.sin_addr.s_addr )
	{
		fprintf( stderr, "%s:: inet_addr fail <%d:%s>\n", __func__, errno, strerror(errno) );
		return CS_rErrFail;
	}

	nRC = connect( g_tEnv.nClientFd, (struct sockaddr*)&tSockAddr, sizeof(tSockAddr) );	
	if ( -1 == nRC );
	{
		fprintf( stderr, "%s:: connect fail <%d:%s>\n", __func__, errno, strerror(errno) );
		return CS_rErrFail;
	}

	return CS_rOk;
}

int SOCK_SetFd()
{
	int nRC = 0;

	g_tEnv.tTime.tv_sec = 60;
	g_tEnv.tTime.tv_usec = 0;

	FD_ZERO( &(g_tEnv.tReadFdSet) );
	FD_SET( g_tEnv.nClientFd, &(g_tEnv.tReadFdSet) );

	return CS_rOk;
}
	
int SOCK_Write( unsigned char *pucBuf, int nBufLen )
{
	CHECK_PARAM_RC( pucBuf );

	int nByte = 0, nCurrent = 0;

	while ( 1 )
	{
		nByte = write( g_tEnv.nClientFd, pucBuf + nCurrent, nBufLen - nCurrent );
		if ( -1 == nByte )
		{
			if ( EINTR == errno )
			{
				//NOTE siganl이 interrupt한 경우에 요청한 byte를 다 쓰기 전에 return 될 수 있음
				//따라서 호출한 시스템 콜(write)을 errno가 EINTR이 아닐 때까지 다시 호출해야함
				continue;
			}

			fprintf( stderr, "%s:: write fail <%d:%s>\n", __func__, errno, strerror(errno) );
			return CS_rErrWriteFail;
		}
		else if ( 0 == nByte )
		{
			printf( "오류가 발생하지는 않았지만, 파일에 write 되지 않음\n" );
			return CS_rErrWriteFail;
		}

		nCurrent += nByte;

		if ( nCurrent >= nBufLen )
		{
			printf( "write all\n" );
			break;
		}
	}

	return CS_rOk;
}

int SOCK_Read( unsigned char *pucBuf, int nBufLen )
{
	CHECK_PARAM_RC( pucBuf );

	int nByte = 0, nCurrent = 0, nRC = 0;

	while ( 1 )
	{
		//NOTE blocking mode 소켓은 데이터가 올 때까지 무한 대기함
		//데이터가 언제 올지 모르기 때문에 fd에 데이터가 있는지 확인하기 위해 select를 사용함
		//60초 기다리고 데이터가 없으면 에러 리턴
#ifdef RUN
		nRC = select( g_tEnv.nClientFd, &(g_tEnv.tReadFdSet), NULL, NULL, &(g_tEnv.tTime) );
		if ( 0 > nRC )
		{
			fprintf( stderr, "%s:: select fail <%d:%s>\n", __func__, errno, strerror(errno) );
			return nRC;
		}
		else if ( 0 == nRC )
		{
			printf( "%ld 초가 경과되었습니다. fd에 변화가 없습니다.\n", g_tEnv.tTime.tv_sec );
			return CS_rErrTimeout;
		}
#endif

		//TODO nonblocking mode 일 때는 어떻게 할지?
		//=> poll/select
		nByte = read( g_tEnv.nClientFd, pucBuf + nCurrent, nBufLen - nCurrent );
		if ( -1 == nByte )
		{
			if ( EINTR == errno )
			{
				//NOTE siganl이 interrupt한 경우에 요청한 byte를 다 읽기 전에 return 될 수 있음
				//따라서 호출한 시스템 콜(read)을 errno가 EINTR이 아닐 때까지 다시 호출해야함
				continue;
			}

			fprintf( stderr, "%s:: read fail <%d:%s>\n", __func__, errno, strerror(errno) );
			return CS_rErrReadFail;
		}
		else if ( 0 == nByte )
		{
			printf( "read End-Of-File\n" );
			break;
		}

		nCurrent += nByte;

		if ( nCurrent >= nBufLen )
		{
			printf( "read all\n" );
			break;
		}
	}

	printf( "\n\n\n%s\n\n\n", pucBuf );

	return CS_rOk;
}
