/* CS_Sock.h */
#ifndef _CS_SOCK_H_
#define _CS_SOCK_H_

int SOCK_Init		();
int SOCK_Write		( unsigned char *pucBuf, int nBufLen );
int SOCK_ReadHeader	( unsigned char *pucBuf, int nBufLen );
int SOCK_ReadBody	( unsigned char *pucBuf, int nBufLen, int nBodyLen );

#endif /* _CS_SOCK_H_ */
