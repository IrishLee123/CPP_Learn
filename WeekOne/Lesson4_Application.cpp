//
// Created by irish.li on 2022/4/6.
//
#include "./Lesson1_SqList.cpp"
#include "./Lesson2_NodeList.cpp"

//问题一：线性表的合并
//用两个线性表La和Lb分别表示A和B两个集合，现要求一个新的集合 A=AB的并集，重复元素要去重
//思路：依次查找Lb中的元素，若La中没有该元素则将该元素插入到La中，时间复杂度：O(n^2)

void combine(SqList<int> &La, SqList<int> Lb) {
    int temp;
    for (int i = 1; i <= Lb.length; i++) {
        GetElem(Lb, i, temp);
        if (!LocateElem(La, temp))//A中没有该元素
            ListInsert_Sq(La, La.length + 1, temp);//将该元素插入A中
    }
}

//问题二：有序表的合并
//已知线性表La和Lb中的数据元素按值非递减有序排列，现将La和Lb归并为一个新的线性表Lc，且Lc中的数据元素仍按照值非递减有序排列

///顺序表实现
SqList<int> OrderCombine_SqList(SqList<int> La, SqList<int> Lb) {
    int p = 1, q = 1;
    SqList<int> result;
    InitList_Sq(result);
    while (p != La.length + 1 && q != Lb.length + 1) {
        if (La.elem[p - 1] <= Lb.elem[q - 1]) {
            ListInsert_Sq(result, result.length + 1, La.elem[p - 1]);
            p++;
        } else {
            ListInsert_Sq(result, result.length + 1, Lb.elem[q - 1]);
            q++;
        }
    }

    if (p != La.length + 1) {
        for (p; p <= La.length; p++)
            ListInsert_Sq(result, result.length + 1, La.elem[p - 1]);
    } else if (q != Lb.length + 1) {
        for (q; q <= Lb.length; q++)
            ListInsert_Sq(result, result.length + 1, Lb.elem[q - 1]);
    }

    return result;
}

///单向链表实现
LinkList OrderCombine_LinkList(LinkList La, LinkList Lb) {
    LinkList result;
    CreateList_T(result, 0);
    LNode *tail = result, *p = La->next, *q = Lb->next;//定义变量
    while (p && q) {
        if (p->data <= q->data) {
            LNode *node = (LNode *) malloc(sizeof(LNode));
            node->data = p->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            p = p->next;
        } else {
            LNode *node = (LNode *) malloc(sizeof(LNode));
            node->data = q->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            q = q->next;
        }
    }

    if (p) {
        while (p) {
            LNode *node = (LNode *) malloc(sizeof(LNode));
            node->data = p->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            p = p->next;
        }
    } else if (q) {
        while (q) {
            LNode *node = (LNode *) malloc(sizeof(LNode));
            node->data = q->data;
            node->next = NULL;
            tail->next = node;
            tail = node;
            q = q->next;
        }
    }
    return result;
}

Status LinkList_CreateWithList(LinkList &L, int length, int elems[]) {
    // 先创建头节点(为头节点分配空间)
    L = (LNode *) malloc(sizeof(LNode));
    L->data = NULL;
    L->next = NULL;

    LNode *t = L;   // 利用尾指针指向尾节点

    // 利用for循环向链表中插入元素
    for (int i = 0; i < length; i++) {
        LNode *node = (LNode *) malloc(sizeof(LNode));  //创建新节点
        node->data = elems[i];
        node->next = NULL;  //新插入的节点永远在最后面，所以指针域为空
        t->next = node;     //把新节点放到尾节点后面
        t = node;   //然后更新尾节点
    }

    return OK;
}


int main() {
//    SqList<int> La;
//    InitList_Sq(La);
//    for (int i = 1; i <= 10; i++) {
//        ListInsert_Sq(La, La.length + 1, i);
//    }
//    PrintSqList(La);
//
//    SqList<int> Lb;
//    InitList_Sq(Lb);
//    for (int i = 1; i <= 10; i++) {
//        ListInsert_Sq(Lb, Lb.length + 1, i + 5);
//    }
//    PrintSqList(Lb);
//
//    combine(La, Lb);
//    PrintSqList(La);

//    SqList<int> La;
//    InitList_Sq(La);
//    ListInsert_Sq(La, La.length + 1, 1);
//    ListInsert_Sq(La, La.length + 1, 4);
//    ListInsert_Sq(La, La.length + 1, 7);
//    ListInsert_Sq(La, La.length + 1, 9);
//    PrintSqList(La);
//
//    SqList<int> Lb;
//    InitList_Sq(Lb);
//    ListInsert_Sq(Lb, Lb.length + 1, 5);
//    ListInsert_Sq(Lb, Lb.length + 1, 6);
//    ListInsert_Sq(Lb, Lb.length + 1, 10);
//    ListInsert_Sq(Lb, Lb.length + 1, 11);
//    PrintSqList(Lb);
//
//    SqList<int> Lc = OrderCombine_SqList(La, Lb);
//    PrintSqList(Lc);

    LinkList La;
    int e_a[] = {1, 7, 8};
    LinkList_CreateWithList(La, 3, e_a);
    PrintLinkList(La);

    LinkList Lb;
    int e_b[] = {2, 4, 6, 8, 10, 11};
    LinkList_CreateWithList(Lb, 6, e_b);
    PrintLinkList(Lb);

    LinkList Lc = OrderCombine_LinkList(La, Lb);
    PrintLinkList(Lc);

    return 0;
}