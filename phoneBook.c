#include"phoneBook.h"
#include<stdlib.h>

enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
};

int phoneBookMenu()
{
    printf("***********************************\n");
    printf("********1.添加联系人信息***********\n");
    printf("********2.删除指定联系人信息*******\n");
    printf("********3.查找指定联系人信息*******\n");
    printf("********4.修改指定联系人信息*******\n");
    printf("************按0退出程序************\n");
    printf("***********************************\n");

}


/* 判空 */
static int panNull(phoneBookTree *pBstree);

/* 获取指定联系人的结点 */
static phoneBookNode * baseAppointValGetAVLTreeNode(phoneBookTree *pBstree, ELEMENTTYPE val);

/* 判空 */
static int panNull(phoneBookTree *pBstree)
{
    int ret = 0;
    if (pBstree == NULL)
    {
        return NULL_PTR;
    }
    return 0;
}

/* 通讯录初始化 */
int phoneBookTreeInit(phoneBookTree **pBstree, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int (*printFunc)(ELEMENTTYPE val))
{
    int ret = 0;
    phoneBookTree * bstree = (phoneBookTree *)malloc(sizeof(phoneBookTree) * 1);
    if (bstree == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清除脏数据 */
    memset(bstree, 0, sizeof(phoneBookTree) * 1);
    /* 初始化树 */
    {
        bstree->root = NULL;
        bstree->size = 0;

        /* 钩子函数在这边赋值. */
        bstree->compareFunc = compareFunc;
        /* 钩子函数包装器 自定义打印. */
        bstree->printFunc = printFunc;
    }
    bstree->root = createAVLTreeNewNode(0, NULL);
    if (bstree->root == NULL)
    {
        return MALLOC_ERROR;
    }
    *pBstree = bstree;
    return ret;
}

/* 人员信息结点初始化 */
phoneBook *createInit(phoneBook *data, char *name, char *sex,  char *age, char *teleNumber, char *address)
{
    data = (phoneBook*)malloc(sizeof(phoneBook));
    if (data == NULL)
    {
        return NULL;
    }
    strncpy(data->name, name, BUFFER_SIZE1 - 1);
    strncpy(&data->sex, sex, sizeof(data->sex));
    strncpy(data->age, age, sizeof(data->age));
    strncpy(data->teleNumber, teleNumber, BUFFER_SIZE2 - 1);
    strncpy(data->address, address, BUFFER_SIZE3 - 1);
    
}

/* 插入新的联系人 */
int phoneBookInsert(phoneBookTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    panNull(*pBstree);

    printf("请输入姓名\n");
    scanf("%s", data->name);

    printf("请输入性别\n");
    scanf("%s",  &data->sex);

    printf("请输入年龄\n");
    scanf("%d",  &data->age);

    printf("请输入电话号码\n");
    scanf("%d",  data->telephone);

    printf("请输入地址\n");
    scanf("%s", data->address);

    balanceBinarySearchTreeInsert(pBstree,data);
    return ret;
}

static phoneBookNode * baseAppointValGetAVLTreeNode(phoneBookTree *pBstree, ELEMENTTYPE val)
{
    phoneBookNode * travelNode = pBstree->root;

    int cmp = 0;
    while (travelNode != NULL)
    {
        /* 比较大小 */
        cmp = pBstree->compareFunc(val, travelNode->data);
        if (cmp < 0)
        {
            travelNode = travelNode->left;
        }
        else if (cmp > 0)
        {
            travelNode = travelNode->right;
        }
        else
        {
            /* 找到了. */
            return travelNode;
        }
    }
    return NULL;
}

/* 联系人的查找 */
int phoneBookTreeFind(phoneBookTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    phoneBook *target = data; 
    printf("请输入你要查找的姓名：\n");
    scanf("%s", target->name);
    data = (phoneBook *)baseAppointValGetaddressBookNode(pBstree, data);
    if (target == NULL)
    {
        printf("未找到相匹配的联系人\n");
        return -1;
    }
    pBstree->printFunc(data);
    return ret;
}


/* 联系人的修改 */
int phoneBookTreeChange(phoneBookTree *pBstree, ELEMENTTYPE val)
{
    int ret = 0;
    phoneBook *target = data;
    printf("请输入要修改的人员姓名：\n");
    scanf("%s", target->name);
    target = (phoneBook *)baseAppointValGetaddressBookNode(pBstree, data);
       if (target == NULL)
    {
        printf("未找到相匹配的联系人\n");
        printf("输入该联系人的信息：\n");
        createPersontarget(target, target->name, &target->sex, target->age, target->teleNumber, target->address); /*   标记  */
        addressBookInsert(pBstree,target);
        return 0;
    }
    int choice = 0;
    while (choice <= 6)
    {
        printf("请输入要修改的名称:\n");
        printf("1、姓名 2、性别 3、年龄 4、电话 5、地址  6、退出\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("请输入新的名字：\n");
            char *newName = malloc(BUFFER_SIZE1);
            memset(newName, 0, BUFFER_SIZE1);
            scanf("%s", newName);
            *target->name = *newName;
            phoneBook newtarget = *target;
            phoneBookTreeDelete(pBstree, target, target->name);
            phoneBookTreeInsert(pBstree, &newtarget); 
        break;

        case 2:
            printf("请输入新的性别：\n");
            char  newSex; 
            memset(&newSex, 0, sizeof(char));
            scanf("%c",&newSex);
            strncpy(&target->sex, &newSex, sizeof(target->sex));
        break;

        case 3:
            printf("请输入新的年龄：\n");
            int  newAge; 
            memset(&newAge, 0, sizeof(int));
            scanf("%c",&newAge);
            strncpy(&target->age, &newAge, sizeof(target->age));
        break;

        case 4:
            printf("请输入新的电话：\n");
            char  *newTelephone = malloc(BUFFER_SIZE2);
            memset(newTelephone, 0, BUFFER_SIZE2);
            scanf("%s",newTelephone);
            strncpy(target->teleNumber, newTelephone, BUFFER_SIZE2);
        break;


        case 5:
            printf("请输入新的地址：\n");
            char  *newAddress = malloc(BUFFER_SIZE3);
            memset(newAddress, 0, BUFFER_SIZE3);
            scanf("%s",newAddress);
            strncpy(target->address, newAddress, BUFFER_SIZE3);
        break;

        case 6:
            return 0;
        break;

        default:
            return 0;
            break;
        }  

    }

    return ret;
}


/* 联系人的删除 */
phoneBookDelete(phoneBookTree *pBstree, ELEMENTTYPE data, char *val)
{
    int ret = 0;
    phoneBook *target = data; 
    balanceBinarySearchTreeDelete(pBstree, data);
    return ret;
}

