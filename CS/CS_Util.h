/* CS_Util.h */
#ifndef _CS_UTIL_H_
#define _CS_UTIL_H_

int UTIL_IsBigEndian();

void UTIL_ClearStdin( char *pszBuf );
void UTIL_ClearLine();

void UTIL_PrtBuf( const char *pszBuf, int nBufLen );
int UTIL_InputData( const char *pszPrt, char *pszBuf, int nBufLen );

#endif /* _CS_UTIL_H_ */
