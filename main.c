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
    DESTROY,
    QUIT,
};


int main()
{
    phoneBook *BookStree = NULL;

    /* 通讯录初始化 */
    phoneBookTreeInit(&BookStree);

    /* 打印界面 */
    menu();//菜单

    int choice = 0;    
    //int count = 0;    
    while ( choice < QUIT && choice >= 0)
    {
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
            /* 通讯录清空 */
            case DESTROY:
            {
                phoneBookTreeDestroy(BookStree,0);
                return 0;
            }
            default:
                choice = QUIT;
                phoneBookTreeDestroy(BookStree,1);
                return 0;
        }
        
        /* 等待一个按键*/
        printf("按回车键继续...");
        getchar();
        getchar();
        printf("\n");
        menu();//菜单
    }


    return 0;
}