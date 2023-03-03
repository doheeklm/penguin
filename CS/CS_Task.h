/* CS_Task.h */
#ifndef _CS_TASK_H_
#define _CS_TASK_H_

#define TASK_CREATE(a) ((1)==(a))
#define TASK_SEARCH(a) ((2)==(a))
#define TASK_DELETE(a) ((3)==(a))
#define TASK_LOGOUT(a) ((4)==(a))

#define TASK_MENU(a) (TASK_CREATE(a)||TASK_SEARCH(a)||TASK_DELETE(a)||TASK_LOGOUT(a))

int TASK_Login();
int TASK_Menu();

#endif /* _CS_TASK_H_ */
