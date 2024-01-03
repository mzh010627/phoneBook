#ifndef __PHONE_BOOK__
#define __PHONE_BOOK__

/* 联系人 */
typedef struct {

    char name[20];
    char phone[20];
    char email[20];
    int id; // 联系人id

} Contact;

/* 通讯录 */
typedef struct {
    int count; // 联系人数
    Contact *contacts; // 联系人数组
    int capacity; // 联系人数组容量
} PhoneBook;

/* 初始化通讯录 */
PhoneBook *initPhoneBook(int capacity);
/* 释放通讯录 */
int freePhoneBook(PhoneBook *book);
/* 添加联系人 */
int addContact(PhoneBook *book, char name, char phone, char email);
/* 删除联系人 */
int deleteContact(PhoneBook *book);
/* 查询联系人 */
Contact *queryContact(PhoneBook *book);
/* 修改联系人 */
int updateContact(PhoneBook *book);
/* 打印通讯录 */
void printPhoneBook(PhoneBook *book);


#endif