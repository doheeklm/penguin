/* BCP_Main.c */
#include "BCP_Inc.h"

int			g_nRunFlag = 1;
BCP_Env_t	g_tEnv;

void SignalHandler( int nSigno );

int main( int argc, char **argv )
{
	int nRC = 0;

	if( argc > 3 )
	{
		printf( "Usage: client [Server Ip] [Port]\n" );
		return 0;
	}
	else if ( argc == 1 )
	{
		strncpy( g_tEnv.szIp, "127.0.0.1", sizeof(g_tEnv.szIp) );
		g_tEnv.szIp[ strlen(g_tEnv.szIp) ] = '\0';

		g_tEnv.nPort = 20200;	
	}
	else
	{
		strncpy( g_tEnv.szIp, argv[1], sizeof(g_tEnv.szIp) );
		g_tEnv.szIp[ strlen(g_tEnv.szIp) ] = '\0';

		for ( int i = 0; i < strlen(argv[2]); i++ )
		{
			if ( isdigit(argv[2][i]) == 0 )
			{
				printf( "Port number contains character\n" );
				return 0;
			}
		}

		g_tEnv.nPort = atoi( argv[2] );
	}

	signal( SIGHUP, SignalHandler );
	signal( SIGINT, SignalHandler );
	signal( SIGTERM, SignalHandler );
	signal( SIGQUIT, SignalHandler );
	signal( SIGKILL, SignalHandler );
	signal( SIGPIPE, SIG_IGN );

	printf( "Server Ip[%s] Port[%d]\n", g_tEnv.szIp, g_tEnv.nPort );	
/*
	nRC = SOCK_Init();
	if ( BCP_rOk != nRC )
	{
		printf( "SOCK_Init() fail\n" );
		return -1;
	}
*/
	while( g_nRunFlag )
	{
		nRC = TASK_Login();
		if ( BCP_rOk != nRC )
		{
			goto exit_main;
		}

		//(1) Select BC_INFO
		//(2) Insert BC_INFO
		//(3) Delete BC_INFO
		//(4) Logout

		sleep(10);
	}

exit_main:
	FD_CLOSE( g_tEnv.nFd );

	return 0;
}

void SignalHandler( int nSigno )
{
	printf( "\nSigno %d\n", nSigno );

	g_nRunFlag = 0;
}


