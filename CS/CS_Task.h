/* CS_Task.h */
#ifndef _CS_TASK_H_
#define _CS_TASK_H_

#define MENU_CREATE 1
#define MENU_SEARCH 2
#define MENU_DELETE 3
#define MENU_LOGOUT 4
#define MENU_ADMIN	5

#define TASK_CREATE(a) ((MENU_CREATE)==(a))
#define TASK_SEARCH(a) ((MENU_SEARCH)==(a))
#define TASK_DELETE(a) ((MENU_DELETE)==(a))
#define TASK_LOGOUT(a) ((MENU_LOGOUT)==(a))
#define TASK_ADMIN(a)  ((MENU_ADMIN)==(a))

#define TASK_MENU(a) (TASK_CREATE(a)||TASK_SEARCH(a)||TASK_DELETE(a)||TASK_LOGOUT(a)||TASK_ADMIN(a))

int TASK_Login();
int TASK_Menu();

#endif /* _CS_TASK_H_ */
