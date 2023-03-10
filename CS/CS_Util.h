/* CS_Util.h */
#ifndef _CS_UTIL_H_
#define _CS_UTIL_H_

void UTIL_ClearStdin( char *pszBuf );
void UTIL_ClearLine();

void UTIL_PrtBuf( const char *pszBuf, int nBufLen );
int UTIL_InputData( const char *pszPrt, char *pszBuf, int nBufLen );

int UTIL_MappingStrToPosition( const char *pszStr, unsigned char *pucPosition, int nStrLen );
int UTIL_MappingStrToTitle( const char *pszStr, unsigned char *pucTitle, int nStrLen );

int UTIL_ValidInputCardId( const char *pszStr, unsigned int *punCardId );

char* UTIL_MappingPositionToStr( unsigned char ucPosition );
char* UTIL_MappingTitleToStr( unsigned char ucPosition );

#endif /* _CS_UTIL_H_ */
