#include <stdio.h>
#include <stdlib.h>		//malloc, free
#include <string.h>		//strlen
#include <stdio_ext.h>	//__fpurge

enum { SIZE_NAME = 13, MAX_PERSON = 10,
        NAME_LENGTH_ERROR = -13, PERSON_RANGE_ERROR = 6, SEAT_RANGE_ERROR = 7,
        EMPTY_QUEUE = -1, DEQUEUE_SUCCESS = 1 };

typedef struct _Person {	//대기자 정보
    char name[SIZE_NAME];	//이름 - UTF-8은 한글 1글자를 3바이트로 저장
    int num;				//인원수
    struct _Person* next;	//다음 노드를 가리키는 포인터
} Person;

typedef struct _Queue {
    Person* front;
    Person* rear;
    int count;				//큐 안의 노드 갯수 최대 10개
} Queue;

void Clear_stdin(char* c);
void Init(Queue* q);
int isEmpty(Queue* q);
void Enqueue(Queue* q, char c[], int n);
int Dequeue(Queue* q);
int PERSON_RANGE_CHECK(int n);
int SEAT_RANGE_CHECK(int n);

void Clear_stdin(char* c)
{
	if (c == NULL)
    	return;
	if (c[strlen(c) - 1] == '\n')
		c[strlen(c) - 1] = '\0';

	__fpurge(stdin);
}

void Init(Queue* q)
{
    q->front = q->rear = NULL;
    q->count = 0;
}

int isEmpty(Queue* q)
{
    return (q->count == 0);
}

void Enqueue(Queue* q, char c[], int n)
{
    Person* p = (Person *)malloc(sizeof(Person));
    
    strcpy(p->name, c);
    
    p->num = n;
    p->next = NULL;

#ifdef DEBUG
    printf("Enqueue된 이름: %s\n", p->name);
    printf("Enqueue된 인원 수: %d\n", p->num);
#endif

    if (isEmpty(q))			//초기 상태에는 큐가 비어있으니까
        q->front = p;		//front에 p를 넣어줌
    else					//나머지 모두 rear 뒤쪽에 푸쉬해야함
        q->rear->next = p;	//따라서 rear의 next에 p를 넣어줌

    q->rear = p;			//p는 마지막에 들어온 노드임 (초기 상태에는 p는 front이자 rear임)
    q->count++;				//큐 갯수 1 증가

#ifdef DEBUG
    printf("큐에 들어있는 노드의 갯수: %d\n", q->count);
#endif
}

int Dequeue(Queue* q)
{
    if (isEmpty(q)) {
        puts("큐가 이미 비어있습니다.");
        return EMPTY_QUEUE;
    }

    Person* temp = q->front;
    puts("==================");
    printf("입장하실 분: %s(%d)\n", temp->name, temp->num);
    
    q->front = temp->next;	//맨 앞 원소는 결국 맨 앞의 다음 노드를 가리킴
    free(temp);				//맨 앞 원소 삭제
    q->count--;				//큐 갯수 1 감소

#ifdef DEBUG
    printf("큐에 들어있는 노드의 갯수: %d\n", q->count);
#endif

    return DEQUEUE_SUCCESS;
}

int PERSON_RANGE_CHECK(int n)
{
    if (n < 1 || n > 4) {
        puts("인원 수는 1부터 4까지입니다. 다시 입력해주세요.");
        return PERSON_RANGE_ERROR;
    }
    return 0;
}

int SEAT_RANGE_CHECK(int n)
{
    if (n != 1 && n != 2 && n != 4) {
        puts("유휴 좌석 수는 1, 2, 4만 가능합니다. 다시 입력해주세요.");
        return SEAT_RANGE_ERROR;
    }
    return 0;
}

int main()
{
    Queue q;
    Init(&q);

    char input[SIZE_NAME];
    int numPerson;
    int numSeat;

    /* 대기자 정보 입력 */
    do {
        puts("==================");
        printf("현재 대기자 수: %d\n", q.count);
        printf("대기자 이름: ");

        fgets(input, sizeof(input), stdin);

		Clear_stdin(input);

        if (strcmp(input, "exit\n") == 0) {
            puts("대기자 정보 입력을 종료합니다."); 
            puts("==================");
            break;
        }

        do {
            printf("대기 인원수: ");
            scanf("%d", &numPerson);
            while (getchar() != '\n') {};
        } while (PERSON_RANGE_CHECK(numPerson));

        Enqueue(&q, input, numPerson);

        puts("대기자 입력이 완료되었습니다.");
        puts("==================");
    } while (q.count < MAX_PERSON);		//대기자가 10명을 넘기면 반복문 중지

    /* 유휴 좌석 수 입력 */
    do {
        do {
            printf("현재 대기자 수: %d\n", q.count);
            printf("유휴 좌석 수: ");
            scanf("%d", &numSeat);
        } while (SEAT_RANGE_CHECK(numSeat));

        if (!isEmpty(&q) &&				//큐가 비어있지 않고,
            q.front->num <= numSeat) {	//인원 수가 유휴 좌석 수보다 작거나 같으면
            Dequeue(&q);				//가장 빠른 순번을 제거
        }
        else {
            puts("조건에 만족하는 사람이 없습니다.");
            puts("유휴 좌석 수를 다시 입력해주세요.");
            puts("==================");
        }
    } while (!isEmpty(&q));

    return 0;
}
