#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

const int LIST_INIT_SIZE = 10;
const int LIST_INCREMENT = 10;

typedef int Status;
typedef int ElemType;
typedef struct
{
    ElemType *elem;
    int length;
    int listsize;
} List;

void printList(List *L);

Status initList(List *L)
{
    L->elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if (L->elem)
    {
        L->length = 0;
        L->listsize = LIST_INIT_SIZE;
        printf("建立线性表成功！\n");
        return OK;
    }
    else
    {
        printf("建立线性表失败！\n");
        return ERROR;
    }
}

Status destroyList(List *L)
{
    if (L->elem)
    {
        free(L->elem);
        printf("线性表销毁成功！\n");
    }
    return OK;
}

//判断线性表是否为空
Status listEmpty(List *L)
{
    if (L->elem)
    {
        if (L->length == 0)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return TRUE;
    }
}

//返回L中的第i个元素
ElemType getElem(List *L, int i)
{
    if (!L->elem)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        if (i < 1 || i > (L->length + 1))
        {
            exit(EXIT_FAILURE);
        }
    }
    return L->elem[i - 1];
}

//比较两个元素
Status compail(ElemType e1, ElemType e2)
{
    return e1 == e2;
}

//返回L中第1个与e满足关系compare()的数据元素的位序，若这样的元素不存在则返回0
int locateElem(List *L, ElemType e)
{
    for (int i = 0; i < L->length; i++)
    {
        ElemType elem = L->elem[i];
        if (compail(elem, e))
        {
            return ++i;
        }
    }
    return 0;
}

//返回前驱元素 fix
ElemType priorElem(List *L, ElemType e)
{
    int i = locateElem(L, e);
    if (i == 0 || i == 1)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        int index = --i;
        return L->elem[--index];
    }
}

//返回后继元素
ElemType nextElem(List *L, ElemType e)
{
    int i = locateElem(L, e);
    if (i == L->length)
    {
        exit(EXIT_FAILURE);
    }
    else
    {
        return L->elem[i];
    }
}

//在L中第i个位置之前插入新的数据元素e
Status listInsert(List *L, int i, ElemType e)
{
    if (i < 1 || i > L->length + 1)
    {
        return ERROR;
    }
    else
    {
        if (L->length >= L->listsize)
        {
            //当前存储空间已满，增加分配
            L->elem = (ElemType *)realloc(L->elem, (L->listsize + LIST_INCREMENT) * sizeof(ElemType));
            if (!L->elem)
            {
                printf("增加线性表容量失败！\n");
                return ERROR;
            }
            else
            {
                L->listsize += LIST_INCREMENT;
            }
        }
        //q为插入位置
        ElemType *q = &(L->elem[i - 1]);
        //插入位置及之后的元素右移
        ElemType *p;
        for (p = &(L->elem[L->length - 1]); p >= q; p--)
        {
            *(p + 1) = *p;
        }
        *q = e;
        ++L->length;
        return OK;
    }
}

//删除表中的第i个元素
Status listDelete(List *L, int i)
{
    if (i < 1 || i > L->length)
    {
        printf("位置不合法，删除失败！");
        return ERROR;
    }
    else
    {
        //删除元素的地址
        ElemType *q = &(L->elem[i - 1]);
        //删除元素之后的所有元素从后往前移动一个
        ElemType *p;
        for (p = q; p < &(L->elem[L->length - 1]); p++)
        {
            *p = *(p + 1);
        }
        //数组长度减1
        --L->length;
        return OK;
    }
}

// void listTraverse(List *L)
// {
// }

// 将所有线性表Lb中但不在La中的数据元素插入到La中
void unions(List *La, List *Lb)
{
    int laLen = La->length;
    int lbLen = Lb->length;

    //遍历Lb
    for (int i = 0; i < lbLen; i++)
    {
        ElemType lbItem = Lb->elem[i];
        int index = locateElem(La, lbItem);
        if (index == 0)
        {
            //La中没有该元素，将该元素插入到La中
            listInsert(La, laLen + 1, lbItem);
        }
    }
}

//已知线性表La和Lb中的数据元素按值递增排列，归并La和Lb得到的新的线性表的数据元素也按值递增排列
Status mergeList(List *la, List *lb, List *resultList)
{
    initList(resultList);
    int i = 0, j = 0, k = 0;
    while (i < la->length && j < lb->length)
    {
        ElemType a = la->elem[i];
        ElemType b = lb->elem[j];
        if (a > b)
        {
            listInsert(resultList, ++k, b);
            j++;
        }
        else
        {
            listInsert(resultList, ++k, a);
            i++;
        }
    }

    while (i < la->length)
    {
        listInsert(resultList, ++k, la->elem[i]);
        i++;
    }

    while (j < lb->length)
    {
        listInsert(resultList, ++k, lb->elem[j]);
        j++;
    }

    return OK;
}

//输出线性表中的数据
void printList(List *L)
{
    int i;
    for (i = 0; i < L->length; i++)
    {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    List L;
    initList(&L);
    listInsert(&L, 1, 7);
    listInsert(&L, 2, 8);
    listInsert(&L, 3, 11);
    listInsert(&L, 4, 18);


    printList(&L);

    // printf("%d\n", getElem(&L, 1));
    // printf("%d\n", getElem(&L, 2));
    // printf("%d\n", getElem(&L, 3));
    // printf("%d\n", getElem(&L, 4));

    // printf("元素7在位置：%d\n", locateElem(&L, 7));

    // printf("删除第2个元素\n");
    // listDelete(&L, 2);
    // printList(&L);
    // printf("删除第4个元素\n");
    // listDelete(&L, 4);
    // printList(&L);

    // printf("返回第1的前驱元素\n");
    // printf("%d\n", priorElem(&L, 1));
    // printf("返回第1的后继元素\n");
    // printf("%d\n", nextElem(&L, 1));

    List Lb;
    initList(&Lb);
    listInsert(&Lb, 1, 1);
    listInsert(&Lb, 2, 2);
    listInsert(&Lb, 3, 4);
    listInsert(&Lb, 4, 13);
    listInsert(&Lb, 5, 14);
    listInsert(&Lb, 6, 1993);

    printList(&Lb);

    printf("归并线性表\n");

    List result;
    mergeList(&L, &Lb, &result);
    printList(&result);

    // printf("合并数组");

    // unions(&L, &Lb);

    // printList(&L);

    // destroyList(&L);
    return 0;
}
