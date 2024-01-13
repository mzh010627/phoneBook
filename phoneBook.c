#include"phoneBook.h"
#include"AVLTree.h"
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,
};
/* 宏函数 */
/* 检测分配空间是否成功 */
#define CHECK_MALLOC_ERROR(ptr)                 \
    do                                          \
    {                                           \
        if(ptr == NULL)                         \
        {                                       \
            return MALLOC_ERROR;                \
        }                                       \
    } while(0)

/* 释放节点 */
#define FREE_NODE(node)                         \
    do                                          \
    {                                           \
        if(node != NULL)                        \
        {                                       \
            free(node);                         \
            node = NULL;                        \
        }                                       \
    } while(0)

/* 树判空 */
#define CHECK_NODE_NULL(phoneBook)              \
    do                                          \
    {                                           \
        if(phoneBook->size == 0)               \
        {                                       \
            return UNDERFLOW;                   \
        }                                       \
    } while(0)

/* 保存联系人  */
static int phoneBookSave(phoneBook *pPhoneBook, contactPerson *data);
/* 通讯录读取 */
static int pBRead();
/* 通讯录判空 */
static int isFileEmpty();

/* 比较函数 */
int compareFunc(ELEMENTTYPE p1, ELEMENTTYPE p2)
{
    contactPerson *data1 = (contactPerson*)p1;
    contactPerson *data2 = (contactPerson*)p2;
    /* 比较 */
    return strcmp((char*)data1->name, (char*)data2->name);
}
/* 打印函数*/
int printFunc(ELEMENTTYPE p1)
{
    printf("name:%s\n", ((contactPerson*)p1)->name);
    printf("teleNumber:%s\n", ((contactPerson*)p1)->teleNumber);
    return SUCCESS;

}

/* 打印界面 */
void menu()//菜单
{
    system("clear");//清屏
    printf("----------------------------------\n");
    printf("| 1.添加联系人信息               |\n");
    printf("| 2.查找指定联系人信息           |\n");
    printf("| 3.删除指定联系人信息           |\n");
    printf("| 4.修改指定联系人信息           |\n");
    printf("| 按任意数字键退出               |\n");
    printf("----------------------------------\n");

}

/* 通讯录初始化 */
int phoneBookTreeInit(phoneBook **pPhoneBook)
{
    AVLInit(pPhoneBook,compareFunc,printFunc);
    return SUCCESS;
}

/* 查找姓名相同的节点 */
static contactPerson* findAContact(phoneBook *pPhoneBook, char *name)
{
    /* 判空 */
    AVLTreeNode *travelNode = pPhoneBook->root;
    AVLTreeNode *tempNode = (AVLTreeNode *) malloc(sizeof(AVLTreeNode));
    if(tempNode == NULL)
    {
        return NULL;
    }
    memset(tempNode, 0, sizeof(AVLTreeNode));
    contactPerson *data = (contactPerson*)malloc(sizeof(contactPerson));
    if(data == NULL)
    {
        return NULL;
    }
    memset(data, 0, sizeof(contactPerson));
    strncpy(data->name, name, sizeof(char)*strlen(name));
    tempNode->data = data;

    int cmp = 0;
    while (travelNode != NULL)
    {
        cmp = compareFunc(travelNode->data,tempNode->data);
        if (cmp == 0)
        {
            /* 销毁临时节点及数据 */
            FREE_NODE(tempNode);
            FREE_NODE(data);

            return travelNode->data;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->left;
        }
        else
        {
            travelNode = travelNode->right;
        }
    }
    /* 销毁临时节点及数据 */
    FREE_NODE(tempNode);
    FREE_NODE(data);
    return NULL;
}

/* 保存联系人 */
static int phoneBookSave(phoneBook *pPhoneBook, contactPerson *data)
{
    #if 0
    int fd = open("./phoneBook.txt", O_RDWR | O_CREAT |O_APPEND, 0644);
    if (fd == -1) 
    {
        perror("open error");
        return UNDERFLOW;
    }
   
    ssize_t byteWrite = write(fd, data, sizeof(phoneBook));
    if(byteWrite == -1)
    {
        perror("write error");
        return UNDERFLOW;
    }
    // write(fd, "\n", 1);
    close(fd);
    return SUCCESS;
    #endif
    FILE *file = fopen("phoneBook.txt", "aw");
    if(file == NULL)
    {
        printf("无法打开文件\n");
        return UNDERFLOW;
    }
    fprintf(file, "姓名：%s\t 号码：%s\n", data->name,data->teleNumber);
    fclose(file);
    return SUCCESS;
}

/* 插入新的联系人 */
int phoneBookTreeInsert(phoneBook *pPhoneBook)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pPhoneBook);

    contactPerson *data = (contactPerson*)malloc(sizeof(contactPerson));
    if (data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(data, 0, sizeof(contactPerson));

    printf("请输入姓名: ");
    scanf("%s", data->name);

    printf("请输入电话号码: ");
    scanf("%s", data->teleNumber);

    /* 通讯录保存 */
    AVLInsert(pPhoneBook, data);
    printf("是否保存联系人? 1、是 2、否 ");
    int choice = 0;
    scanf("%d", &choice);
    switch (choice)
    {
        case 1: phoneBookSave(pPhoneBook, data);  
                printf("保存联系人成功！🎉\n");
                sleep(1);
                break;
        default: break;
    }
    /* 反馈 */
    return SUCCESS;
}

/* 通讯录读取 */
#if 1
static int pBRead()
{
    #if 1
    int fd = open("./phoneBook.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("open error");
        return UNDERFLOW;
    }
    #if 0
    /* 文件长度 */
    off_t size = lseek(fd, 0, SEEK_END);

    lseek(fd, 0, SEEK_SET);
    #endif

    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    char *lineStart = buffer;  // 行的起始位置
    int bytesRead;
    read(fd, buffer, sizeof(buffer) - 1);

    printf("%s\n", buffer);
    close(fd);
    return SUCCESS;
    #endif
    
}
#endif

/* 通讯录判空 */
#if 1
static int isFileEmpty()
{
    int fd = open("./phoneBook.txt", O_RDONLY);
    if(fd == -1)
    {
        perror("open error");
        return UNDERFLOW;
    }
    off_t size = lseek(fd, 0, SEEK_END);
    if(size == 0)
    {
        printf("文件为空\n");
        sleep(1);
        return UNDERFLOW;
    }
    // return SUCCESS;
    close(fd);
}
#endif
/* 联系人的查找 */
int phoneBookTreeFind(phoneBook *pPhoneBook)
{
    /* 通讯录文件判空 */
    isFileEmpty();
    /* 判空 */
    CHECK_NODE_NULL(pPhoneBook);
    /* 通讯录读取 */
    pBRead();
    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    contactPerson *data = (contactPerson*)findAContact(pPhoneBook, name);
    if(data == NULL)
    {
        printf("未找到相匹配的联系人\n");
        sleep(1);//睡眠
        return SUCCESS;
    }
    printf("姓名：%s\t", data->name);
    printf("电话：%s\n", data->teleNumber);
    sleep(2);//睡眠

    return SUCCESS;
}

/* 联系人的修改 */
int phoneBookTreeChange(phoneBook *pBstree)
{
    /* 判空 */
    CHECK_NODE_NULL(pBstree);
    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    contactPerson *data = (contactPerson*)findAContact(pBstree, name);
    if(data == NULL)
    {
        printf("未找到相匹配的联系人\n");
        sleep(1);
        return SUCCESS;
    }
    /* 修改 */
    printf("请输入新的电话号码\n");
    scanf("%s", data->teleNumber);
    return SUCCESS;

}

/* 清空通讯录 */
int clearPhone()
{
    printf("是否清空通讯录? 1、是 2、否\n");
    int choice = 0;
    scanf("%d", &choice);
    if(choice == 1)
    {
        int fd = open("./phoneBook.txt", O_TRUNC);
        if(fd == -1)
        {
            perror("open error");
            return UNDERFLOW;
        }
        close(fd);
        printf("清空成功！\n");
        sleep(1);
    }
}

/* 联系人的删除 */
int phoneBookDelete(phoneBook *pPhoneBook)
{
    /* 清空通讯录 */
    clearPhone();
    /* 判空 */
    CHECK_NODE_NULL(pPhoneBook);
    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    contactPerson *data = (contactPerson*)findAContact(pPhoneBook, name);
    if(data == NULL)
    {
        printf("未找到相匹配的联系人\n");
        sleep(1);
        return SUCCESS;
    }
    /* 删除 */
    AVLDelete(pPhoneBook, data);
    printf("删除成功!\n");
    sleep(1);
    return SUCCESS;
}
