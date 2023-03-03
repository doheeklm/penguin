/* CS_Conf.c */
#include "CS_Inc.h"

extern CS_Env_t g_tEnv;

int CONF_Init( int nArg, char *pszPort, char *pszIp )
{
	if( 3 < nArg )
	{
		printf( "Usage: client [Server Ip] [Port]\n" );
		return CS_rErrConfigInit;
	}
	else if ( 1 == nArg )
	{
		strncpy( g_tEnv.szIp, "127.0.0.1", sizeof(g_tEnv.szIp) );
		g_tEnv.szIp[ strlen(g_tEnv.szIp) ] = '\0';
		
		g_tEnv.nPort = 20200;
	}
	else
	{
		strncpy( g_tEnv.szIp, pszIp, sizeof(g_tEnv.szIp) );
		g_tEnv.szIp[ strlen(g_tEnv.szIp) ] = '\0';

		for ( int i = 0; i < strlen(pszPort); i++ )
		{
			if ( isdigit(pszPort[i]) == 0 )
			{
				printf( "Port number contains character\n" );
				return CS_rErrConfigInit;
			}
		}
		g_tEnv.nPort = atoi(pszPort);
	}

	printf( "Server Ip[%s] Port[%d]\n", g_tEnv.szIp, g_tEnv.nPort );	

	return CS_rOk;
}
