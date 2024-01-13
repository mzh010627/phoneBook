#include"phoneBook.h"
#include"doubleLinkListQueue.h"
#include"AVLTree.h"
#include<stdlib.h>
#include<string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,
    NULL_PTR = -1,
    MALLOC_ERROR = -2,
    ILLEGAL_ACCESS = -3,
    UNDERFLOW = -4,
};
#define BUFFER_SIZE 1024
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

/* 通讯录判空 */
static int isFileEmpty();
/* 静态函数声明 */
/* 通讯录保存 */
static int savePhoneBook(phoneBook *pPhoneBook, contactPerson *data, char* mode);
/* 通讯录读取 */
static int readPhoneBook(phoneBook *pPhoneBook);
/* 通讯录联系人删除的本地处理 */
static int deletePhoneBook(phoneBook *pPhoneBook,contactPerson *data);
/* 节点在中序遍历中的位置 */
static int findInInOrderPosition(AVLTreeNode * root, contactPerson *data, int *position);


/* 比较函数 */
int compareFunc(ELEMENTTYPE p1, ELEMENTTYPE p2)
{
    contactPerson *data1 = (contactPerson*)p1;
    contactPerson *data2 = (contactPerson*)p2;
    // printf("p1:%s\n", data1->name);
    // printf("p2:%s\n", data2->name);
    /* 数据有效性 */
    if(data1->name == NULL || data2->name == NULL)
    {
        return NULL_PTR;
    }
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
    printf("| 4.查看通讯录                   |\n");
    printf("| 5.修改指定联系人信息           |\n");
    printf("| 6.清空通讯录                   |\n");
    printf("| 按任意数字键退出               |\n");
    printf("----------------------------------\n");

}

/* 通讯录初始化 */
int phoneBookTreeInit(phoneBook **pPhoneBook)
{
    /* 读取 */
    AVLInit(pPhoneBook,compareFunc,printFunc);
    readPhoneBook(*pPhoneBook);

    return SUCCESS;
}

/* 查找姓名相同的节点 */
static AVLTreeNode* findAContact(phoneBook *pPhoneBook, char *name)
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

            return travelNode;//return node->data
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


    printf("请输入姓名\n");
    scanf("%s", data->name);

    if(pPhoneBook->size != 0)
    {
    if(findAContact(pPhoneBook, data->name) != NULL)
    {
        printf("姓名重复，插入失败\n");
        FREE_NODE(data);
        return SUCCESS;
    }
    }

    printf("请输入电话号码\n");
    scanf("%s",  data->teleNumber);

    /* 插入 */
    AVLInsert(pPhoneBook, data);
    /* 反馈 */
    printf("插入成功\n");
    int count = 0;
    findInInOrderPosition(pPhoneBook->root, data, &count);
    printf("ID:%d\n", count);

    /* 保存 */
    savePhoneBook(pPhoneBook, data, "ab+");
}
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
    close(fd);
    return SUCCESS;
}
#endif
/* 联系人的查找 */
int phoneBookTreeFind(phoneBook *pPhoneBook)
{
    /* 通讯录文件判空 */
    isFileEmpty();
    /* 判空 */
    CHECK_NODE_NULL(pPhoneBook);

    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    AVLTreeNode *Node = findAContact(pPhoneBook, name);
    if(Node == NULL)
    {
        printf("未找到相匹配的联系人\n");
        sleep(1);//睡眠
        return SUCCESS;
    }
    contactPerson *data = (contactPerson*)Node->data;
    printf("姓名：%s\n", data->name);
    printf("电话：%s\n", data->teleNumber);
    sleep(2);//睡眠

    return SUCCESS;
}

/* 联系人的修改 */
int phoneBookTreeChange(phoneBook *pPhoneBook)
{
    /* 判空 */
    CHECK_NODE_NULL(pPhoneBook);
    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    AVLTreeNode *Node = findAContact(pPhoneBook, name);
    if(Node == NULL)
    {
        printf("未找到相匹配的联系人\n");
        sleep(1);
        return SUCCESS;
    }
    contactPerson *data = (contactPerson*)Node->data;
    /* 修改 */
    printf("请输入新的电话号码\n");
    scanf("%s", data->teleNumber);
    /* 保存 */
    savePhoneBook(pPhoneBook, data, "rb+");
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
	
    /* 判空 */
    CHECK_NODE_NULL(pPhoneBook);
    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    AVLTreeNode *Node = findAContact(pPhoneBook, name);
    if(Node == NULL)
    {
        printf("未找到相匹配的联系人\n");
        sleep(1);
        return SUCCESS;
    }
    contactPerson *data = (contactPerson*)Node->data;
    deletePhoneBook(pPhoneBook, data);
    /* 删除 */
    AVLDelete(pPhoneBook, data);
    return SUCCESS;
}

/* 通讯录销毁 */
int phoneBookTreeDestroy(phoneBook *pPhoneBook)
{
    /* 判空 */
    CHECK_NODE_NULL(pPhoneBook);
    /* 销毁 */
    AVLDestroy(pPhoneBook);
    return SUCCESS;
}

/* 打印所有联系人 */
int phoneBookTreePrint(phoneBook *pPhoneBook)
{
    return AVLInOrderTravel(pPhoneBook);
}


/* 静态函数部分 */

/* 通讯录保存 */
static int savePhoneBook(phoneBook *pPhoneBook, contactPerson *data, char* mode)
{

    /* 判断是删除还是修改 */
    int size = 0;
    findInInOrderPosition(pPhoneBook->root, data, &size);

    
    /*文件不存在则新建 */
    FILE *fd = fopen("phoneBook.bak", mode);
    
    
    if(fd == NULL)
    {
        return ILLEGAL_ACCESS;
    }
    /* 定位到位置 */
    fseek(fd, sizeof(contactPerson) * (size-1), SEEK_SET);
    /* 保存 */
    fwrite(data, sizeof(contactPerson), 1, fd);
    fclose(fd);
    return SUCCESS;
}

/* 通讯录读取 */
static int readPhoneBook(phoneBook *pPhoneBook)
{
    FILE *fd = fopen("phoneBook.bak", "rb+");
    if(fd == NULL)
    {
        return ILLEGAL_ACCESS;
    }
    /* 获取文件大小 */
    if(fseek(fd,0,SEEK_END) != 0)
    {
        printf("fseek error\n");
        fclose(fd);
        return ILLEGAL_ACCESS;
    }
    int size = ftell(fd);
    for(int idx = 0; idx < (size/sizeof(contactPerson));idx++)
    {
        /* 读取 */
        contactPerson data;// 用来接数据
        fseek(fd, sizeof(contactPerson) * idx, SEEK_SET);
        fread(&data, sizeof(contactPerson), 1, fd);
        printf("Name: %s, TeleNumber: %s\n", data.name, data.teleNumber);
        /* 插入 */
        contactPerson *pData = (contactPerson*)malloc(sizeof(contactPerson));
        if(pData == NULL)
        {
            return MALLOC_ERROR;
        }
        memset(pData, 0, sizeof(contactPerson));
        strncpy(pData->name, data.name, sizeof(char)*strlen(data.name));
        strncpy(pData->teleNumber, data.teleNumber, sizeof(char)*strlen(data.teleNumber));
        AVLInsert(pPhoneBook, pData);
    }
    
    fclose(fd);
    return SUCCESS;
}

/* 通讯录联系人删除的本地处理 */
static int deletePhoneBook(phoneBook *pPhoneBook,contactPerson *data)
{
    FILE * fd = fopen("phoneBook.bak","rb+");
    if(fd == NULL)
    {
        perror("fopen error");
        return ILLEGAL_ACCESS;
    }

    /* 定位要删除的位置 */
    int size = 0;
    findInInOrderPosition(pPhoneBook->root, data, &size);
    long start = sizeof(contactPerson) * size;
    if(fseek(fd, start, SEEK_SET) != 0)
    {
        perror("fseek error");
        return ILLEGAL_ACCESS;
    }

    /* 迁移后续数据 */
    char buffer[BUFFER_SIZE] = {0};
    long remaining = sizeof(contactPerson);
    while(remaining > 0)
    {
        size_t readSize = fread(buffer, 1, sizeof(buffer), fd);
        if(readSize == 0)
        {
            perror("fread error");
            fclose(fd);
            return ILLEGAL_ACCESS;
        }

        /* 重新定位指针 */
        if(fseek(fd, -(readSize + sizeof(contactPerson)), SEEK_CUR) != 0)
        {
            perror("fseek error");
            fclose(fd);
            return ILLEGAL_ACCESS;
        }
        /* 写入 */
        if(fwrite(buffer, 1, readSize, fd) == 0)
        {
            perror("fwrite error");
            fclose(fd);
            return ILLEGAL_ACCESS;
        }
        remaining -= readSize;
    }

    /* 切掉多余的部分 */
    ftruncate(fileno(fd), ftell(fd));
    fclose(fd);
}

/* 节点在中序遍历中的位置 */
static int findInInOrderPosition(AVLTreeNode * root, contactPerson *data, int *position)
{
    if(root == NULL)
    {
        return 0;
    }
    int leftResult = findInInOrderPosition(root->left, data, position);
    if(leftResult != 0)
    {
        return leftResult;
    }

    (*position)++;

    if(compareFunc(root->data, data) == 0)
    {
        return *position;
    }
    int rightResult = findInInOrderPosition(root->right, data, position);

    if(rightResult != 0)
    {
        return rightResult;
    }

    return SUCCESS;
}
