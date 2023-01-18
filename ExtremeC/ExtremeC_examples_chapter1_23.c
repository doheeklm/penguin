/*
 *	몇 가지 중첩 구조체 선언하기
 */
typedef struct
{
	int x;
	int y;
} point_t;

typedef struct
{
	point_t center;
	int radius;
} circle_t;

typedef struct
{
	point_t start;
	point_t end;
} line_t;
