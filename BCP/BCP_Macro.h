/* BCP_Macro.h */
#ifndef _BCP_MACRO_H_
#define _BCP_MACRO_H_

#define FD_CLOSE( _fd ); \
	do { \
		if ( -1 == close( _fd ) ) \
		{ \
			fprintf( stderr, "close fail <%d:%s>\n", errno, strerror(errno) ); \
		} \
		else \
		{ \
			printf( "%s:: close fd[%d]\n", __func__, _fd ); \
		} \
	} while ( 0 )

#endif /* _BCP_MACRO_H_ */
