/* CS_Macro.h */
#ifndef _CS_MACRO_H_
#define _CS_MACRO_H_

#define F_FORMAT( _fmt )		"\n[%s: %d][%s] "_fmt"\n", __FILE__, __LINE__, __func__
#define LOG_ERR_F( _fmt, ... )	printf( F_FORMAT( _fmt ), ##__VA_ARGS__ );

#define CHECK_TLV_LENGTH( _spec, _res_len ) \
	do { \
		if ( _spec != _res_len ) \
		{ \
			LOG_ERR_F( "received wrong TLV length (%d)!=(%d)", _spec, _res_len ); \
			return CS_rErrSystemFail; \
		} \
	} while ( 0 )

#define CHECK_PARAM( _param, _return ) \
	do { \
		if ( NULL == _param ) \
		{ \
			LOG_ERR_F ( "invalid parameter <(%s)=false>", #_param ); \
			_return; \
		} \
	} while( 0 )

#define CHECK_PARAM_RC( _param ) CHECK_PARAM( _param, return CS_rErrInvalidParam )

#define CHECK_OVERFLOW( _a, _b, _err ) \
	do { \
		if ( (int)(_a) > (int)(_b) ) \
		{ \
			LOG_ERR_F ( "%d > %d overflow fail", (int)(_a), (int)(_b) );\
			return (_err); \
		} \
	} while( 0 )

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

#define PRT_LF				printf( "\n" );
#define PRT_MENU			printf( "\n... Menu ...\n" \
									"(1) Create Info\n" \
									"(2) Search Info\n" \
									"(3) Delete Info\n" \
									"(4) Logout\n" \
									"Input: " );
#define PRT_SYS				printf( "\n... System ...\n\n" );
#define PRT_REQ				printf( "\n... Request ..." );
#define PRT_RES				printf( "\n... Response ..." );
#define PRT_SUCCESS			printf( "\n\n... Success ...\n" );
#define PRT_FAIL			printf( "\n\n... Fail ...\n" );
#define PRT_ERR_CNT( _cnt ) printf( "로그인 실패 횟수 (%d)\n", _cnt );
#define PRT_EXIT			printf( "\n프로그램을 종료합니다.\n\n" ); 
#define PRT_RETRY			printf( "최대 3번까지 재시도 가능합니다.\n" \
									"로그인 정보를 다시 입력해주세요.\n" );
#define PRT_SYS_FAIL		printf( "\n서버 오류를 감지했습니다.\n" \
									"프로그램을 종료합니다.\n\n" ); 

#endif /* _CS_MACRO_H_ */
