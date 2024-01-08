#ifndef __BINARY_SEARCH_TREE_H_
#define __BINARY_SEARCH_TREE_H_
#include "common.h"
#include "balanceBinarySearchTree.h"

#define BUFFER_SIZE1 20
#define BUFFER_SIZE2 12
#define BUFFER_SIZE3 50

typedef BalanceBinarySearchTree phoneBookTree;
typedef AVLTreeNode phoneBookNode;

/* 定义通讯录人员信息结构体 */
typedef struct phoneBook
{
    char name[BUFFER_SIZE1];
    char sex;
    int age;
    int teleNumber[BUFFER_SIZE2];
    char address[BUFFER_SIZE3];
}phoneBook;

/* 通讯录菜单 */
int phoneBookMenu();

/* 人员信息初始化 */
phoneBook *createInit(phoneBook *data, char *name, char *sex,  char *age, char *teleNumber, char *address);

/* 通讯录的初始化 */
int phoneBookTreeInit(phoneBookTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val));

/* 联系人的增加 */
int phoneBookTreeInsert(phoneBookTree *pBstree, ELEMENTTYPE val);

/* 联系人的查找 */
int phoneBookTreeFind(phoneBookTree *pBstree, ELEMENTTYPE val);

/* 联系人的修改 */
int phoneBookTreeChange(phoneBookTree *pBstree, ELEMENTTYPE val);


/* 联系人的删除 */
phoneBookDelete(phoneBookTree *pBstree, ELEMENTTYPE data, char *val);





#endif  //__BINARY_SEARCH_TREE_H_