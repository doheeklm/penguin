/* CS_Main.c */
#include "CS_Inc.h"

int			g_nRunFlag = 1;
CS_Env_t	g_tEnv;

void SignalHandler( int nSigno );

int main( int argc, char **argv )
{
	int nRC = 0, nLoginFailCnt = 0;

	printf( "%s-endian system\n", UTIL_IsBigEndian() ? "big" : "little" );

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
#endif
	
	while( g_nRunFlag )
	{
		nRC = TASK_Login();
		if ( CS_rOk != nRC )
		{
			if ( CS_rErrLoginFail == nRC )
			{
				nLoginFailCnt++;
				PRT_TITLE( "System" );
				PRT_ERR_CNT( nLoginFailCnt );

				if ( nLoginFailCnt >= 3 )
				{
					PRT_EXIT;
					goto exit_main;
				}
				else
				{
					PRT_RETRY;
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
		if ( CS_rBackToLogin == nRC )
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
