/* CS_Macro.h */
#ifndef _CS_MACRO_H_
#define _CS_MACRO_H_

#define CHECK_PARAM( _param, _return ) \
	do { \
		if ( NULL == _param ) \
		{ \
			printf( "invalid parameter <(%s)=false>", #_param ); \
			_return; \
		} \
	} while( 0 )

#define CHECK_PARAM_RC( _param ) CHECK_PARAM( _param, return BCP_rErrInvalidParam )

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
	} while( 0 )

#endif /* _CS_MACRO_H_ */
