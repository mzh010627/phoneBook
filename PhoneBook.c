#include "PhoneBook.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>



/* 状态码 */
enum STATUS_CODE
{
    SUCCESS = 0,        //成功
    NULL_PTR = -1,      //空指针
    MALLOC_ERROR = -2,  //开辟空间未成功
    ILLEGAL_ACCESS = -3,//非法访问
    UNDERFLOW = -4,     //通讯录空
    OVERFLOW = -5       //通讯录满

};

/* 宏函数 */
/* 指针判空*/
#define CHECK_NULL_POINTER(ptr) \
    do \
    { \
        if(ptr == NULL) \
        { \
            return NULL_PTR; \
        }\
    } while(0)  
/* 通讯录判空 */
#define IS_EMPTY(book) (book->count == 0)
/* 通讯录判满 */
#define IS_FULL(book) (book->count == book->capacity)


/* 打印联系人 */
static void printContact(Contact *contact);

/* 初始化通讯录 */
PhoneBook *initPhoneBook(int capacity)
{
    PhoneBook *book = (PhoneBook *)malloc(sizeof(PhoneBook));
    book->count = 0;
    book->capacity = capacity;
    book->contacts = (Contact *)malloc(sizeof(Contact) * capacity);
    return book;
}

/* 释放通讯录 */
int freePhoneBook(PhoneBook *book)
{
    if(book)
    {
        free(book->contacts);
        free(book);
    }
    return SUCCESS;
}

/* 添加联系人 */
int addContact(PhoneBook *book, char name, char phone, char email)
{
    /* 判空 */
    CHECK_NULL_POINTER(book);
    /* 通讯录判满 */
    if(IS_FULL(book))
    {
        return OVERFLOW;
    }
    Contact contact = {name, phone, email};
    contact.id = book->count;
    book->contacts[book->count++] = contact;
    return SUCCESS;

}

/* 删除联系人 */
int deleteContact(PhoneBook *book)
{
    /* 判空 */
    CHECK_NULL_POINTER(book);
    /* 通讯录判空 */
    if(IS_EMPTY(book))
    {
        return UNDERFLOW;
    }
    Contact *contact = queryContact(book);
    if(contact == NULL)
    {
        return ILLEGAL_ACCESS;
    }
    for(int idx = contact->id; idx < book->count; idx++)
    {
        book->contacts[idx] = book->contacts[idx + 1];
    }
    book->count--;
    return SUCCESS;

}

/* 查询联系人 */
Contact *queryContact(PhoneBook *book)
{
    /* 通讯录判空 */
    if(IS_EMPTY(book))
    {
        return UNDERFLOW;
    }
    printf("请输入要查询的方式：\n1、姓名\n2、电话号码\n3、邮箱\n");
    int choice = 0;
    scanf("%d", &choice);
    switch(choice)
    {
        case 1:
        {
            char name[20] = {0};
            printf("请输入姓名：\n");
            scanf("%s", name);
            for(int idx = 0; idx < book->count; idx++)
            {
                if(book->contacts[idx].name == name)
                {
                    return &book->contacts[idx];
                }
            }
            printf("查无此人\n");
            break;
        }
        case 2:
        {
            char phone[20] = {0};
            printf("请输入电话号码：\n");
            scanf("%s", phone);
            for(int idx = 0; idx < book->count; idx++)
            {
                if(book->contacts[idx].phone == phone)
                {
                    return &book->contacts[idx];
                }
            }
            printf("查无此人\n");
            break;
        }
        case 3:
        {
            char email[20] = {0};
            printf("请输入邮箱：\n");
            scanf("%s", email);
            for(int idx = 0; idx < book->count; idx++)
            {
                if(book->contacts[idx].email == email)
                {
                    return &book->contacts[idx];
                }
            }
            printf("查无此人\n");
            break;
        }
        default:
            printf("输入错误\n");
    }
    return  NULL;
}

/* 修改联系人 */
int updateContact(PhoneBook *book)
{
    Contact *oldContact = queryContact(book);
    if(oldContact)
    {
        printContact(oldContact);
        printf("请输入新的联系人信息：\n");
        scanf("%s", oldContact->name);
        scanf("%s", oldContact->phone);
        scanf("%s", oldContact->email);
        return SUCCESS;
    }
    return ILLEGAL_ACCESS;
}

/* 打印通讯录 */
void printPhoneBook(PhoneBook *book)
{
    /* 判空 */
    CHECK_NULL_POINTER(book);
    /* 通讯录判空 */
    if(IS_EMPTY(book))
    {
        return UNDERFLOW;
    }
    for(int idx = 0; idx < book->count; idx++)
    {
        printContact(&book->contacts[idx]);
    }
}


/* 打印联系人 */
static void printContact(Contact *contact)
{
    printf("联系人信息：\n");
    printf("联系人ID: %s\n", contact->id);
    printf("姓名：%s\n", contact->name);
    printf("电话：%s\n", contact->phone);
    printf("邮箱：%s\n", contact->email);
}
