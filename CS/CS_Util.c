/* CS_Util.c */
#include "CS_Inc.h"

void UTIL_ClearStdin( char *pszBuf )
{
	if ( NULL == pszBuf )
	{
		return;
	}

	if ( pszBuf[strlen(pszBuf) - 1] == '\n' )
	{
		pszBuf[strlen(pszBuf) - 1] = '\0';
	}

	__fpurge(stdin);
}

void UTIL_ClearLine()
{
	while ( getchar() != '\n' );
}

void UTIL_PrtBuf( const char *pszBuf, int nBufLen )
{
	int i = 0;

	for ( i = 0; i < nBufLen; i++ )
	{
		if ( (i != 0) && (i % 50 == 0) )
		{
			PRT_LF;
		}

		printf( "%02x ", pszBuf[i] );
	}
}

int UTIL_InputData( const char *pszPrt, char *pszBuf, int nBufLen )
{
	CHECK_PARAM_RC( pszPrt );
	CHECK_PARAM_RC( pszBuf );

	printf( "%s: ", pszPrt );

	char *pszTemp;
	pszTemp = pszBuf;
	
	fgets( pszTemp, nBufLen, stdin );
	UTIL_ClearStdin( pszTemp );

	return CS_rOk;
}

int UTIL_MappingStrToPosition( const char *pszStr, unsigned char *pucPosition, int nStrLen )
{
	CHECK_PARAM_RC( pszStr );
	CHECK_PARAM_RC( pucPosition );

	if ( 0 == strncmp( pszStr, "사원", nStrLen ) )
	{
		*pucPosition = CS_P_EMPLOYEE;
	}
	else if ( 0 == strncmp( pszStr, "대리", nStrLen ) )
	{
		*pucPosition = CS_P_ASSISTANT_MANAGER;
	}
	else if ( 0 == strncmp( pszStr, "과장", nStrLen ) )
	{
		*pucPosition = CS_P_MANAGER;
	}
	else if ( 0 == strncmp( pszStr, "차장", nStrLen ) )
	{
		*pucPosition = CS_P_DEPUTY_GENERAL_MANAGER;
	}
	else if ( 0 == strncmp( pszStr, "부장", nStrLen ) )
	{
		*pucPosition = CS_P_GENERAL_MANAGER;
	}
	else if ( 0 == strncmp( pszStr, "주임", nStrLen ) )
	{
		*pucPosition = CS_P_ASSISTANT;
	}
	else if ( 0 == strncmp( pszStr, "선임", nStrLen ) )
	{
		*pucPosition = CS_P_JUNIOR;
	}
	else if ( 0 == strncmp( pszStr, "책임", nStrLen ) )
	{
		*pucPosition = CS_P_SENIOR;
	}
	else if ( 0 == strncmp( pszStr, "수석", nStrLen ) )
	{
		*pucPosition = CS_P_PRINCIPAL;
	}
	else if ( 0 == strncmp( pszStr, "이사", nStrLen ) )
	{
		*pucPosition = CS_P_DIRECTOR;
	}
	else if ( 0 == strncmp( pszStr, "상무 이사", nStrLen ) )
	{
		*pucPosition = CS_P_MANAGING_DIRECTOR;
	}
	else if ( 0 == strncmp( pszStr, "전무 이사", nStrLen ) )
	{
		*pucPosition = CS_P_SENIOR_MANAGING_DIRECTOR;
	}
	else if ( 0 == strncmp( pszStr, "사장", nStrLen ) )
	{
		*pucPosition = CS_P_CEO;
	}
	else if ( 0 == strncmp( pszStr, "회장", nStrLen ) )
	{
		*pucPosition = CS_P_CHAIRMAN;
	}
	else
	{
		return CS_rErrWrongInput; 
	}

	return CS_rOk;
}

int UTIL_MappingStrToTitle( const char *pszStr, unsigned char *pucTitle, int nStrLen )
{
	CHECK_PARAM_RC( pszStr );
	CHECK_PARAM_RC( pucTitle );

	if ( 0 == strlen( pszStr ) )
	{
		return CS_rOk;
	}
	else if ( 0 == strncmp( pszStr, "팀원", nStrLen ) )
	{
		*pucTitle = CS_T_STAFF;
	}
	else if ( 0 == strncmp( pszStr, "파트장", nStrLen ) )
	{
		*pucTitle = CS_T_CHEIF_OF_STAFF;
	}
	else if ( 0 == strncmp( pszStr, "부서장", nStrLen ) )
	{
		*pucTitle = CS_T_HEAD_OF_DEPARTMENT;
	}
	else if ( 0 == strncmp( pszStr, "실장", nStrLen ) )
	{
		*pucTitle = CS_T_HEAD_OF_DEVISION;
	}
	else if ( 0 == strncmp( pszStr, "본부장", nStrLen ) )
	{
		*pucTitle = CS_T_DIRECTOR;
	}
	else if ( 0 == strncmp( pszStr, "그룹장", nStrLen ) )
	{
		*pucTitle = CS_T_GROUP_LEADER;
	}
	else if ( 0 == strncmp( pszStr, "부문장", nStrLen ) )
	{
		*pucTitle = CS_T_MANAGER_OF_DEPARTMENT;
	}
	else if ( 0 == strncmp( pszStr, "CTO", nStrLen ) )
	{
		*pucTitle = CS_T_CTO;
	}
	else if ( 0 == strncmp( pszStr, "CEO", nStrLen ) )
	{
		*pucTitle = CS_T_CEO;
	}
	else
	{
		return CS_rErrWrongInput; 
	}

	return CS_rOk;
}

int UTIL_ValidInputCardId( const char *pszStr, unsigned int *punCardId )
{
	CHECK_PARAM_RC( pszStr );
	CHECK_PARAM_RC( punCardId );

	while ( *pszStr )
	{
		if ( 0 == isdigit( *pszStr ) )
		{
			return CS_rErrWrongInput;
		}
	
		pszStr++;
	}
	
	return CS_rOk;
}

char* UTIL_MappingPositionToStr( unsigned char ucPosition )
{
	switch( ucPosition )
	{
		CASE_RETURN( CS_P_EMPLOYEE, "사원" );
		CASE_RETURN( CS_P_ASSISTANT_MANAGER, "대리" );
		CASE_RETURN( CS_P_MANAGER, "과장" );
		CASE_RETURN( CS_P_DEPUTY_GENERAL_MANAGER, "차장" );
		CASE_RETURN( CS_P_GENERAL_MANAGER, "부장" );
		CASE_RETURN( CS_P_ASSISTANT, "주임" );
		CASE_RETURN( CS_P_JUNIOR, "선임" );
		CASE_RETURN( CS_P_SENIOR, "책임" );
		CASE_RETURN( CS_P_PRINCIPAL, "수석" );
		CASE_RETURN( CS_P_DIRECTOR, "이사" );
		CASE_RETURN( CS_P_MANAGING_DIRECTOR, "상무 이사" );
		CASE_RETURN( CS_P_SENIOR_MANAGING_DIRECTOR, "전무 이사" );
		CASE_RETURN( CS_P_CEO, "사장" );
		CASE_RETURN( CS_P_CHAIRMAN, "회장" );
		CASE_DEFAULT_UNKNOWN;
	}
}

char* UTIL_MappingTitleToStr( unsigned char ucTitle )
{
	switch( ucTitle )
	{
		CASE_RETURN( CS_T_STAFF, "팀원" );
		CASE_RETURN( CS_T_CHEIF_OF_STAFF, "파트장" );
		CASE_RETURN( CS_T_HEAD_OF_DEPARTMENT, "부서장" );
		CASE_RETURN( CS_T_HEAD_OF_DEVISION, "실장" );
		CASE_RETURN( CS_T_DIRECTOR, "본부장" );
		CASE_RETURN( CS_T_GROUP_LEADER, "그룹장" );
		CASE_RETURN( CS_T_MANAGER_OF_DEPARTMENT, "부문장" );
		CASE_RETURN( CS_T_CTO, "CTO" );
		CASE_RETURN( CS_T_CEO, "CEO" );
		CASE_DEFAULT_UNKNOWN;
	}
}
