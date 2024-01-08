#ifndef __COMMON_H__
#define __COMMON_H__

#define ELEMENTTYPE void*

/* 链表结点取别名 */
typedef struct DoubleLinkNode
{
    ELEMENTTYPE data;

    /* 指向前一个结点的指针 */
    struct DoubleLinkNode * prev;
    /* 指向下一个结点的指针 */
    struct DoubleLinkNode *next;   /* 指针的类型为什么是结点 */
} DoubleLinkNode;


/* 链表 */
typedef struct DoubleLinkList
{
    /* 链表的虚拟头结点 */
    DoubleLinkNode * head;
    DoubleLinkNode * tail;        /* 为什么尾指针不需要分配空间??? */
    /* 链表的长度 */
    int len;
} DoubleLinkList;


typedef struct AVLTreeNode
{
    ELEMENTTYPE data;
    /* 结点维护一个高度属性 */
    int height;
    struct AVLTreeNode *left;        /* 左子树 */
    struct AVLTreeNode *right;       /* 右子树 */
    #if 1
    struct AVLTreeNode *parent;      /* 父结点 */
    #endif
} AVLTreeNode;

typedef struct AVLTree
{   
    /* 根结点 */
    AVLTreeNode * root;
    /* 树的结点个数 */
    int size;

    /* 钩子🪝函数比较器 放到结构体内部. */
    int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2);

    /* 钩子🪝函数 包装器实现自定义打印函数接口. */
    int (*printFunc)(ELEMENTTYPE val);

} AVLTree;

#endif //__COMMON_H_
