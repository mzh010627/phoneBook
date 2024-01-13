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
    PRINT,
    QUIT,
};


int main()
{
    phoneBook *BookStree = NULL;

    /* 通讯录初始化 */
    phoneBookTreeInit(&BookStree);



    int choice = 0;    
    //int count = 0;    
    while ( choice < QUIT && choice >= 0)
    {
        /* 打印界面 */
        menu();//菜单
        printf("请输入选项\n");
        scanf("%d", &choice);
        switch (choice)
        {
            /* 增加联系人 */
            case INSERT:
            {
                phoneBookTreeInsert(BookStree);
                break;
            }

            /* 查找联系人 */
            case FIND:
            {
                phoneBookTreeFind(BookStree);
                break;
            }
            /* 删除联系人 */
            case DELETE:
            {
                phoneBookDelete(BookStree);
                break;
            }
            /* 打印联系人表 */
            case PRINT:
            {
                phoneBookTreePrint(BookStree);
                break;
            }
            /* 修改联系人信息 */
            case MODIFY:
            {
                phoneBookTreeChange(BookStree);
                break;
            }
            default:
                choice = QUIT;
                phoneBookTreeDestroy(BookStree);
        }
    }


    return 0;
}