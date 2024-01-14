#include <stdio.h>
#include <stdlib.h>
#include "phoneBook.h"
#include <string.h>


enum SECLET
{

    INSERT = 1,
    FIND,
    DELETE,
    MODIFY,
    READ,
    CLEAR,
};


int main()
{
    phoneBook *BookStree = NULL;

    /* 通讯录初始化 */
    phoneBookTreeInit(&BookStree);

    /* 打印界面 */
    menu();//菜单

    int choice = 0;    
    int flag = 0;    
    while (1)
    {
        printf("请输入选项\n");
        scanf("%d", &choice);
        switch (choice)
        {
            /* 增加联系人 */
            case INSERT:
            {
                phoneBookTreeInsert(BookStree);
                flag = 0;
                break;
            }

            /* 查找联系人 */
            case FIND:
            {
                phoneBookTreeFind(BookStree);
                flag = 1;
                break;
            }
            /* 删除联系人 */
            case DELETE:
            {
                phoneBookDelete(BookStree);
                flag = 0;
                break;
            }
            /* 修改联系人信息 */
            case MODIFY:
            {
                phoneBookTreeChange(BookStree);
                flag = 0;
                break;
            }
            /* 打印联系人表 */
            case READ:
            {
                #if 0
                phoneBookRead();
                #else
                phoneBookTreePrint(BookStree);
                flag = 1;
                #endif
                break;
            }
            /* 通讯录清空/销毁 */
            case CLEAR:
            {
                clearPhone(BookStree);
                flag = 1;
                break;
            }
            default:
                isQuit(BookStree);
                flag = 0;
                break;
        }
        #if 1
        if(flag)
        {
           
            /* 等待一个按键*/
            printf("按回车键继续...");
            getchar();
            getchar();
            printf("\n");
        }
        #endif
       
        menu();//菜单
    }


    return 0;
}