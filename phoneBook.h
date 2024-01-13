#ifndef __PHONEBOOK_H_
#define __PHONEBOOK_H_
#include "common.h"

#define BUFFER_SIZE1 5
#define BUFFER_SIZE2 8


typedef AVLTree phoneBook;
// typedef AVLTreeNode contactPerson;
/* 定义通讯录人员信息结构体 */
typedef struct contactPerson
{
    char name[BUFFER_SIZE1];
    char teleNumber[BUFFER_SIZE2];

} contactPerson;


/* 打印界面 */
void menu();//菜单

/* 通讯录的初始化 */
int phoneBookTreeInit(phoneBook **pPhoneBook);

/* 联系人的增加 */
int phoneBookTreeInsert(phoneBook *pPhoneBook);

/* 联系人的查找 */
int phoneBookTreeFind(phoneBook *pPhoneBook);

/* 联系人的修改 */
int phoneBookTreeChange(phoneBook *pPhoneBook);

/* 联系人的删除 */
int phoneBookDelete(phoneBook *pPhoneBook);

/* 通讯录的读取 */
int phoneBookRead();

/* 清空通讯录 */
int clearPhone();



#endif  //__BINARY_SEARCH_TREE_H_