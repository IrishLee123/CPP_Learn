#include <iostream>
#include <stdlib.h>
#include "./Lesson2_NodeList.cpp"

//
// Created by irish.li on 2022/4/1.
//

/// 定义一些常量
#define TRUE  1
#define FALSE  0
#define OK  1
#define ERROR  0
#define INFEASIBLE  -1
#define OVERFLOW  -2
#define MAX_SIZE 10
typedef int Status;

/// 链表扩展
/**
 *  循环链表：
 *  最后一个节点的指针域指向头节点，形成一个闭环
 *
 *  优点：从任一节点出发均可找到表中其他节点
 *
 *  *注意：由于循环链表中的指针域没有NULL的情况，所以在while中判断循环的条件改为,
 *  p->next!=L, 即指针域保存的地址和头指针保存的地址相同时，认为该节点为尾节点
 *  
 *  通常情况下链表头指针指向头节点，用来保存整个链表。
 *  而链表中我们访问频率最高的往往是头节点和尾节点，头节点有头指针指向，尾节点则需要遍历整个链表才能确定，当链表越长时间越久。
 *  在这里引入一个概念，用尾指针的方式来表示一个循环链表，即尾指针指向尾节点，尾节点的next节点表示头节点。
 *  这样我们就可以快速获得循环链表中的头节点和尾节点。
 */

Status CreateLoopList(LinkList &L, int length) {
    LinkList head = (LinkList) malloc(sizeof(LinkList));//为头节点分配存储空间
    head->data = NULL;
    L = head;
    L->next = head;//尾节点的指针域指向头节点
    //先用尾插法构建链表
    for (int i = 0; i < length; i++) {
        LNode *node = (LNode *) malloc(sizeof(LNode));
        node->data = i + 1;
        L->next = node;
        L = node;
        L->next = head;
    }
    return OK;
}

void PrintLoopLinkList(LinkList L) {
    LNode *p = L->next;//缓存头节点
    printf("head->");
    while (p != L) {
        p = p->next;
        printf("%i->", p->data);
    }
    printf("head\n");
}

/**
 * 连接两个循环链表（合并）
 * @param Ta
 * @param Tb
 * @return
 */
LinkList Connect(LinkList Ta, LinkList Tb) {
    LinkList p = Ta->next;//缓存Ta头节点
    Ta->next = Tb->next->next;//Ta尾节点连接Tb首元节点
    free(Tb->next);//释放链表Tb
    Tb->next = p;//Tb尾节点连接Ta头节点
    return Tb;
}

/**
 * 可以看到不论是单链表还是循环链表，都无法快速获取前驱节点，必须要从表头出发遍历链表，知道找到目标节点，很麻烦
 *
 * 这里引入双向链表
 */

/// 双向链表数据结构
//双向链表拥有前后两个指针域，分别指向当前节点的前驱和后继节点，其中头节点的前驱指针为空，尾节点的后继指针为空
//对称性：p->prior->next = p = p->next->prior
typedef struct DuLNode {
    int data;
    struct DuLNode *prior, *next;
} DuLNode, *DuLinkList;

/**
 *
 * @param L
 * @param length
 * @return
 */
Status DuLinkList_Create(DuLinkList &L, int length) {
    if (length < 1) return ERROR;
    L = (DuLinkList) malloc(sizeof(DuLinkList));//为头指针分配存储空间
    L->data = NULL;
    L->prior = NULL;
    L->next = NULL;
    DuLNode *tail = L;//尾指针
    //尾插法构建链表
    for (int i = 0; i < length; i++) {
        DuLNode *node = (DuLNode *) malloc(sizeof(DuLNode));
        node->data = i + 1;
        node->prior = tail;
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    return OK;
}

void DuLinkList_Print(DuLinkList L) {
    DuLNode *p = L;
    printf("[head]");
    while (p->next) {
        p = p->next;
        if (p->prior && p->prior->next)
            printf("<->[%i]", p->data);
        else
            printf("-[%i]", p->data);
    }
    printf("\n");
}

/**
 * 双向链表插入操作
 * @param L
 * @param i
 * @param e
 * @return
 */
Status DuLinkList_Insert(DuLinkList &L, int i, int e) {
    if (i < 1)return ERROR;//i值违规，返回错误

    DuLNode *target;
    target = L->next;
    int counter = 1;
    //先找到i节点
    while (counter <= i && target) {
        if (counter == i) { //找到目标节点
            DuLNode *node = (DuLNode *) malloc(sizeof(DuLNode));
            node->data = e;
            target->prior->next = node;
            node->prior = target->prior;
            target->prior = node;
            node->next = target;
            return OK;
        }
        target = target->next;
        counter++;
    }
    return ERROR;//i值违规，返回错误
}

/**
 * 双向链表删除操作
 * @param L
 * @param i
 * @return
 */
Status DuLinkList_Delete(DuLinkList &L, int i) {
    if (i < 1) return ERROR;
    DuLNode *target = L->next;
    int counter = 1;
    while (counter <= i && target) {
        if (counter == i) {
            // DO
            target->prior->next = target->next;
            target->next->prior = target->prior;
            target->next = NULL;
            target->prior = NULL;
            free(target);
            return OK;
        }
        target = target->next;
        counter++;
    }
    return ERROR;
}

// 同理双向链表也可以循环，即头节点的前驱指向尾节点，尾节点的后继指向头节点，构成双循环。


int main() {
//    LinkList L;
//    CreateLoopList(L, 10);
//    PrintLoopLinkList(L);
//
//    LinkList La;
//    CreateLoopList(La, 15);
//    PrintLoopLinkList(La);
//
//    L = Connect(L, La);
//    PrintLoopLinkList(L);

    DuLinkList DL;
    DuLinkList_Create(DL, 10);//创建双向链表
    DuLinkList_Print(DL);
    DuLinkList_Insert(DL, 6, 98);//插入98在6号位置
    DuLinkList_Print(DL);
    DuLinkList_Delete(DL, 6);//删除6号位置元素
    DuLinkList_Print(DL);
    return 0;
}