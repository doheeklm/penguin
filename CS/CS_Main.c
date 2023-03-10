/* CS_Main.c */
#include "CS_Inc.h"

int g_nRunFlag = 1;
CS_Env_t g_tEnv;

void SignalHandler( int nSigno );

int main( int argc, char **argv )
{
	int nRC = 0, nLoginFailCnt = 0;

	nRC = CONF_Init( argc, argv[2], argv[1] );
	if ( CS_rOk != nRC )
	{
		printf( "CONF_Init fail\n" );
		return -1;
	}

	signal( SIGHUP, SignalHandler );
	signal( SIGINT, SignalHandler );
	signal( SIGTERM, SignalHandler );
	signal( SIGQUIT, SignalHandler );
	signal( SIGKILL, SignalHandler );
	signal( SIGPIPE, SIG_IGN );

#ifdef RUN
	nRC = SOCK_Init();
	if ( CS_rOk != nRC )
	{
		if ( CS_rErrSocketFail == nRC )
		{
			return -1;
		}
		LOG_ERR_F( "SOCK_Init fail <%d>", nRC );
		goto exit_main;
	}

	nRC = SOCK_SetFd();
	if ( CS_rOk != nRC )
	{
		LOG_ERR_F( "SOCK_SetFd fail <%d>", nRC );
		goto exit_main;
	}
#endif

	while( g_nRunFlag )
	{
		nRC = TASK_Login();
		if ( CS_rOk != nRC )
		{
			if ( CS_rErrLoginFail == nRC ) //서버로부터 로그인 실패를 응답 받을 경우
			{
				nLoginFailCnt++;
				PRT_TITLE( "System" );
				PRT_ERR_CNT( nLoginFailCnt );

				if ( nLoginFailCnt >= 3 ) //재시도 횟수 3번을 넘어가는 경우 프로그램 종료
				{
					PRT_EXIT;
					goto exit_main;
				}
				else
				{
					PRT_RETRY; //로그인 재시도
					continue;
				}
			}
			else if ( CS_rExitProgram == nRC )
			{
				goto exit_main;
			}
			else
			{
				PRT_SYS_FAIL;
				goto exit_main;
			}
		}
	
		nRC = TASK_Menu();
		if ( CS_rBackToLogin == nRC ) //로그아웃 성공 
		{
			continue;
		}
		else if ( CS_rOk != nRC )
		{	
			PRT_EXIT;
			goto exit_main;	
		}
	}

exit_main:
	FD_CLOSE( g_tEnv.nClientFd );

	return 0;
}

void SignalHandler( int nSigno )
{
	printf( "\nSigno %d\n", nSigno );

	g_nRunFlag = 0;
}
