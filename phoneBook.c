#include"phoneBook.h"
#include"AVLTree.h"
#include<stdlib.h>

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

/* 比较函数 */
int compareFunc(ELEMENTTYPE p1, ELEMENTTYPE p2)
{

}
/* 打印函数*/
int printFunc(ELEMENTTYPE p1)
{

}

/* 通讯录初始化 */
int phoneBookTreeInit(phoneBook **pPhoneBook)
{
    AVLInit(pPhoneBook,compareFunc,printFunc);
    return SUCCESS;
}



/* 插入新的联系人 */
int phoneBookInsert(phoneBook *pPhoneBook)
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

    printf("请输入电话号码\n");
    scanf("%d",  data->teleNumber);

    /* 插入 */
    AVLInsert(pPhoneBook, data);

    return SUCCESS;
}



/* 联系人的查找 */
int phoneBookTreeFind(phoneBook *pPhoneBook)
{
    /* 判空 */
    CHECK_MALLOC_ERROR(pPhoneBook);
    /* 输入姓名 */
    char *name = malloc(BUFFER_SIZE1);
    memset(name, 0, BUFFER_SIZE1);
    printf("请输入姓名：\n");
    scanf("%s", name);
    /* 查找 */
    

    return SUCCESS;
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

