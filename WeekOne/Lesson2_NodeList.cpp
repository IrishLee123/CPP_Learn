//
// Created by irish.li on 2022/3/29.
//
#include<iostream>

using namespace std;

/**
 *  线性表的实现方式——链式结构
 *  链式存储结构不需要分配连续的存储空间，逻辑上相邻的元素在空间上并不相邻
 *  链表的构成：链表由数据部分和指向下一个节点的指针构成
 *  头指针：指向链表中首个节点的指针
 *  首元节点：链表中存储第一个数据元素的节点
 *  头节点：链表中首元节点之前附加的一个节点，不计入链表长度计算
 *
 *  不带头节点
 *      空表：头指针为空来表示
 *  带头节点（头指针指向头节点）
 *      空表：头节点的指针域为空，即只有一个头节点
 *      优点：便于处理首元节点、便于空表和非空表的统一处理
 *      数据域：灵活使用，可以存放链表长度等
 *
 *  访问时只能通过头指针进入链表，并通过每个节点的指针域依次向后顺序扫描其余节点，称为顺序存取，时间复杂度为 O(n)
 *
 *  单链表：每个节点只有一个指针域
 *  双链表：每个节点有两个指针域，分别指向前驱节点和后继节点
 *  循环链表：链表节点首尾相接，尾节点指针域指向头节点
 */

/**
 * 线性表常用方法
 * InitList(&L) 构造一个空的线性表L
 * DestrouList(&L)  销毁一个线性表
 * ClearList(&L)  清空一个线性表，表本身还在
 * ListEmpty(&L)  判断线性表是否为空
 * ListLength(&L)  获得线性表长度（元素个数）
 * GetElem(L, i, &e)  获得第i个元素
 * LocateElem(L, e, compare())  根据规则定位某些元素，e为目标元素，compere函数为比较规则，返回线性表中第一个满足规则的元素
 * PriorElem(L, cur_e, &pre_e)  获取当前元素的前驱
 * NextElem(L, cur_e, &next_e)  获取当前元素的后继
 * ListInsert(&L, i, e)
 * ListDelete(&L, i, &e)
 * ListTraverse(&L, visited())  线性表的遍历
 */
void temp() {}

// 定义一些常量
#define TRUE  1
#define FALSE  0
#define OK  1
#define ERROR  0
#define INFEASIBLE  -1
#define OVERFLOW  -2

typedef int Status;

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode, *LinkList;

/**
 * 初始化链表
 * @param L 链表指针(指向头节点)
 * @return
 */
Status InitList_L(LinkList &L) {
    L = (LinkList) malloc(sizeof(LNode));   // 或 L = new LNode;  分配存储空间
    L->data = NULL; // 数据域置空
    L->next = NULL; // 指针域置空
    return OK;
}

/**
 * 判断链表是否为空
 * @param L 链表指针(指向头节点)
 * @return
 */
bool LinkListEmpty(LinkList L) {
    if (L->next)
        return false;
    return true;
}

/**
 * 销毁单链表
 * @param L
 * @return
 */
Status DestroyLinkList(LinkList &L) {
    LNode *p;
    while (L) {
        p = L;
        L = L->next;
        free(p);    // 或 delete p;  释放存储空间
    }
    return OK;
}

/**
 * 清空单链表
 * @param L
 * @return
 */
Status ClearLinkList(LinkList &L) {
    LNode *p = L->next; // 记录首元节点
    while (p) {
        L->next = p->next;
        free(p);
        p = L->next;
    }
    return OK;
}

/**
 * 获取单链表的表长
 * @param L
 * @return
 */
int LengthOf(LinkList L) {
    LNode *p = L->next; // 记录首元节点
    int result = 0;
    while (p) {
        result++;
        p = p->next;
    }
    return result;
}

/**
 * 获取链表中第i个元素
 * 时间复杂度O(n)
 * @param L
 * @param i 目标位置
 * @param result 结果(引用类型)
 * @return
 */
Status GetElem_L(LinkList L, int i, int &result) {
    if (i < 1)
        return ERROR;   // i违规返回错误
    LNode *p = L->next; // 记录首元节点
    int counter = 1;
    while (p) {
        if (counter == i) {
            result = p->data;
            return OK;
        }
        counter++;
        p = p->next;
    }
    return ERROR;   // 越界返回错误
}

/**
 * 确定某个元素在链表中的位置
 * @param L
 * @param e
 * @return
 */
int LocateElem_L(LinkList L, int e) {
    LNode *p = L->next;
    int counter = 1;
    while (p) {
        if (p->data == e)
            return counter; // 找到匹配节点，返回当前位置
        p = p->next;
    }
    return 0;   // 无匹配结果返回0
}

LNode *GetElem(LinkList L, int e) {
    LNode *p = L->next;
    while (p) {
        if (p->data == e)
            return p;   // 找到目标，返回P
        p = p->next;
    }
    return NULL;   // 无匹配结果返回NULL
}

/**
 * 将置为e的元素插入到第i位置
 * 思路：想插入到第i个位置就要先找到第i-1个位置的节点，然后创建新节点放在i-1节点的后面
 * @param L
 * @param i
 * @param e
 * @return
 */
Status InsertElem(LinkList &L, int i, int e) {
    LNode *p = L;
    int counter = 0;
    while (p) {
        if (counter == i - 1) {
            LNode *node = (LNode *) malloc(sizeof(LNode));
            node->data = e;
            //*注意下面这两步的顺序
            node->next = p->next;
            p->next = node;
            return OK;  // 插入成功
        }
        counter++;
        p = p->next;
    }
    return ERROR;   // i值违规，返回错误
}

/**
 * 删除第i位置上的节点
 * 思路：同样是先找到i-1位置上的节点，然后删掉i位置上的节点
 * @param L
 * @param i
 * @return
 */
Status DeleteElem(LinkList &L, int i, int &res) {
    LNode *p, *t;
    p = L;
    int counter = 0;
    while (p) {
        if (counter == i - 1) {
            t = p->next;  // 缓存要删除的节点
            p->next = t->next;    // t节点断链
            res = t->data;  // 保存删除节点的数据域
            free(t);    // 释放存储空间
            return OK;  // 删除成功
        }
        counter++;
        p = p->next;
    }
    return ERROR;   // i值违规，返回错误
}

/**
 * 头插法建立链表
 * @param L
 * @param length
 * @return
 */
Status CreateList_H(LinkList &L, int length) {
    // 先创建头节点(为头节点分配空间)
    L = (LNode *) malloc(sizeof(LNode));
    L->data = NULL;
    L->next = NULL;
    // 利用for循环向链表中插入元素
    for (int i = 0; i < length; i++) {
        LNode *node = (LNode *) malloc(sizeof(LNode));  //创建新节点
        node->data = i + 1;
        node->next = L->next;
        L->next = node;
    }
    return OK;
}

Status CreateList_T(LinkList &L, int length) {
    // 先创建头节点(为头节点分配空间)
    L = (LNode *) malloc(sizeof(LNode));
    L->data = NULL;
    L->next = NULL;

    LNode *t = L;   // 利用尾指针指向尾节点

    // 利用for循环向链表中插入元素
    for (int i = 0; i < length; i++) {
        LNode *node = (LNode *) malloc(sizeof(LNode));  //创建新节点
        node->data = i + 1;
        node->next = NULL;  //新插入的节点永远在最后面，所以指针域为空
        t->next = node;     //把新节点放到尾节点后面
        t = node;   //然后更新尾节点
    }

    return OK;
}

void PrintLinkList(LinkList L) {
    LNode *p = L;
    printf("head->");
    while (p->next) {
        p = p->next;
        printf("%i->", p->data);
    }
    printf("null\n");
}

//int main() {
//    LinkList L1, L2;
//
//    CreateList_H(L1, 10);
//    PrintLinkList(L1);
//
////    CreateList_T(L2, 10);
////    PrintLinkList(L2);
//
//    printf("insert 98 at idx 10.\n");
//    InsertElem(L1, 10, 98);
//    PrintLinkList(L1);
//
//    int res;
//    DeleteElem(L1, 5, res);
//    printf("delete %i at idx 5.\n", res);
//    PrintLinkList(L1);
//
//    return 0;
//}






//链表的泛型类
//template<class T>
//class Node {
//
//public:
//    Node<T> *next;  // 指向下一个节点的指针
//
//public:
//    T data;
//    Node(const T &item, Node<T> *prtnext = NULL);   // 构造函数
//
//
//};


