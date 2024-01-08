#include<stdio.h>
#include<stdlib.h>
#include"phoneBook.h"
#include"balanceBinarySearchTree.h"
#include<string.h>

enum SECLET
{

    INSERT = 1,
    FIND,
    DELETE,
    MODIFY,
    QUIT
};



int CompareName(void *arg1, void *arg2)
{
    phoneBook *idx1 = (phoneBook *) arg1;
    phoneBook *idx2 = (phoneBook *) arg2;
    int result = 0;
    result = strcmp(idx1->name, idx2->name);
    return result;
}

//自定义打印
int printStruct(void *arg)
{
    int ret = 0;
    phoneBook* target = (phoneBook*)arg;
    printf("name:%s\tsex:%c\tage:%d\tteleNumber:%d\taddress:%s\n", target->name, target->sex, target->age, target->teleNumber, target->address);
    return ret;
}

int main()
{
    phoneBookTree *BookStree = NULL;

    /* 通讯录初始化 */
    phoneBookTreeInit(*BookStree, CompareName, printStruct);

        int choice = 0;    
        //int count = 0;    
        while ( choice <= QUIT && choice >= 0)
        {
            printf("请输入选项\n");
            scanf("%d", &choice);
            switch (choice)
            {
            /* 增加联系人 */
            case INSERT:
                    phoneBook * target;
                    createInit(target,target->name, &target->sex, target->age, target->teleNumber, target->address);
                    createInit(target,target->name, &target->sex, target->age, target->teleNumber, target->address);
                    printf("请输入姓名\n");
                    scanf("%s", target->name);
                    printf("请输入性别\n");
                    scanf("%s", &target->sex);
                    printf("请输入年龄\n");
                    scanf("%d", &target->age);
                    printf("请输入电话号码\n");
                    scanf("%d", target->teleNumber);
                    printf("请输入地址\n");
                    scanf("%s", target->address);
                    
                    
                    phoneBookInsert(BookStree, target);
                    target++;
                // choice = DELETE;
            break;
            /* 查找联系人 */
            case FIND:                   
                        phoneBookSelect(BookStree, target);
                //choice = 0;
                break;
            /* 删除联系人 */
            case DELETE:
                        printf("请输入需要删除的联系人姓名\n");
                        scanf("%s", target->name);
                        phoneBookDelete(BookStree, target, target->name);
                        //count--;
                        if (BookStree->root->left == NULL && BookStree->root->right == NULL)
                        {
                            printf("通讯录为空\n");
                            return 0;
                        }
                        
                break;
            /* 修改联系人信息 */
            case MODIFY:
                        phoneBookmodifica(BookStree, target);
                break;
            default:
                choice = QUIT;
                break;
            }
        }


    return 0;
}