//
// Created by irish.li on 2022/4/7.
//

#ifndef CPP_LEARN_LESSON1_STACK_H
#define CPP_LEARN_LESSON1_STACK_H

#include <iostream>

// 栈（stack）是一个特殊的线性表，限定元素仅在一端（通常是表尾）进行插入和删除操作的线性表。
// 又称为先进后出（Last In First Out）的线性表，简称为LIFO结构
// 插入元素到栈顶的操作，成为入栈
// 从栈顶删除最后一个元素的操作，称为出栈
// 栈可以有顺序结构和链式结构两种实现方式
// 应用场景：进制转换（取余法）、括号匹配的检验、表达式求值

/**
 * 栈的顺序数据结构定义
 */
typedef struct SqStack {
    int stacksize;//栈的最大容量
    int *top;//栈顶指针
    int *base;//栈底指针
} SqStack;

typedef struct LNode {
    int data;
    struct LNode *next;
} LNode;

/**
 * 栈的链式数据结构定义
 */
typedef struct LinkStack {
    LNode *top;
    LNode *base;
    int length;//栈的长度
} LinkStack;

// 队列（queue）同样也是一个特殊的线性表，是一种先进先出FIFO（First In First Out）的线性表。
// 在表一段插入（表尾），在另一端删除（表头）
// 队列同样可以有顺序结构和链式结构两种实现方式

/// 定义一些常量
#define TRUE  1
#define FALSE  0
#define OK  1
#define ERROR  0
#define INFEASIBLE  -1
#define OVERFLOW  -2

typedef int Status;

class Lesson1_Stack {
private:
    //栈的常见操作

    /// 初始化操作
    /// \param S
    Status InitStack(SqStack &S, int size);

    /// 初始化操作
    /// \param S
    /// \param size
    /// \return
    Status InitStack(LinkStack &S);

    /// 销毁栈
    /// \param S
    Status DestroyStack(SqStack &S);

    /// 销毁栈
    /// \param S
    /// \return
    Status DestroyStack(LinkStack &S);

    /// 判断栈是否为空
    /// \param S
    /// \return
    bool StackEmpty(SqStack S);

    /// 判断栈是否为空
    /// \param S
    /// \return
    bool StackEmpty(LinkStack S);

    /// 获取栈的长度
    /// \param S
    /// \return
    int StackLength(SqStack S);

    /// 查询栈顶元素
    /// \param S
    /// \param e
    /// \return
    Status GetTop(SqStack S, int &e);

    /// 查询栈顶元素
    /// \param S
    /// \param e
    /// \return
    Status GetTop(LinkStack S, int &e);

    /// 清空栈
    /// \param S
    Status ClearStack(SqStack &S);

    /// 清空栈
    /// \param S
    Status ClearStack(LinkStack &S);

    /// 将新元素压入栈中
    /// \param S
    /// \param e
    Status Push(SqStack &S, int e);

    /// 将新元素压入栈中
    /// \param S
    /// \param e
    Status Push(LinkStack &S, int e);

    /// 出栈操作
    /// \param S
    /// \param e
    Status Pop(SqStack &S, int &e);

    /// 出栈操作
    /// \param S
    /// \param e
    Status Pop(LinkStack &S, int &e);

    void PrintStack(SqStack S);

    void PrintStack(LinkStack S);

public:
    void Execute();
};

#endif //CPP_LEARN_LESSON1_STACK_H

Status Lesson1_Stack::InitStack(SqStack &S, int size) {

    S.base = new int[size];

    if (!S.base)exit(OVERFLOW);//分配空间失败

    S.top = S.base;
    S.stacksize = size;

    printf("Init Success, StackSize: %i\n", S.stacksize);
    return OK;
}

Status Lesson1_Stack::InitStack(LinkStack &S) {

    //base指向栈底、即尾节点
    //top指向栈顶、即头节点

    S.base = S.top = (LNode *) malloc(sizeof(LNode));//分配空间

    if (!S.base)exit(OVERFLOW);

    S.length = 0;

    printf("Init Success, Length: %i\n", S.length);
    return OK;
}

bool Lesson1_Stack::StackEmpty(SqStack S) {
    return S.base == S.top;
}

bool Lesson1_Stack::StackEmpty(LinkStack S) {
    return S.base == S.top;
}

//地址相减的结果是间隔了多少个存储空间，并不是十六进制数值的相减
int Lesson1_Stack::StackLength(SqStack S) {
    return S.top - S.base;
}

//在使用栈的时候top指针上面的存储空间不论值是什么，我们都认为是空的，因此我们只需要关注top指针的位置就可以了
//不需要依次把整个栈的元素清空
Status Lesson1_Stack::ClearStack(SqStack &S) {
    if (S.base)S.top = S.base;
    return OK;
}

Status Lesson1_Stack::ClearStack(LinkStack &S) {
    if (S.base)S.top = S.base;
    S.length = 0;
    return OK;
}

Status Lesson1_Stack::DestroyStack(SqStack &S) {
    if (S.base == NULL) return ERROR;//异常情况

    delete S.base;
    S.stacksize = 0;
    S.base = S.top = NULL;

    return OK;
}

Status Lesson1_Stack::DestroyStack(LinkStack &S) {
    if (S.base == NULL) return ERROR;//异常情况

    while (S.top != S.base) {
        LNode *temp = S.top;
        S.top = temp->next;
        free(temp);
    }
    free(S.base);
    S.length = 0;
    free(&S);

    return OK;
}

Status Lesson1_Stack::Push(SqStack &S, int e) {
    if (S.base == NULL) return ERROR;
    if (S.top - S.base == S.stacksize) return OVERFLOW;//栈满了

    *S.top++ = e;

    printf("Push %i to stack\n", e);
    return OK;
}

Status Lesson1_Stack::Push(LinkStack &S, int e) {
    if (S.base == NULL) return ERROR;

    S.top->data = e;
    LNode *newNode = (LNode *) malloc(sizeof(LNode));
    newNode->next = S.top;
    S.top = newNode;

    printf("Push %i to stack\n", e);
    return OK;
}

Status Lesson1_Stack::Pop(SqStack &S, int &e) {
    if (S.base == NULL) return ERROR;
    if (S.top == S.base) return OVERFLOW;//栈空了

    e = *--S.top;

    printf("Pop %i from stack\n", e);
    return OK;
}

Status Lesson1_Stack::Pop(LinkStack &S, int &e) {
    if (S.base == NULL) return ERROR;
    if (S.top == S.base) return OVERFLOW;//栈空了

    LNode *temp = S.top;
    S.top = S.top->next;//top指针下移
    free(temp);
    e = S.top->data;
    S.length--;

    printf("Pop %i from stack\n", e);
    return OK;
}

void Lesson1_Stack::PrintStack(SqStack S) {
    int *p = S.top;
    while (S.base != p)
        printf("| %i |\n", *--p);
    printf("-----\n");
}

void Lesson1_Stack::PrintStack(LinkStack S) {
    LNode *p = S.top;
    while (S.base != p) {
        p = p->next;
        printf("| %i |\n", p->data);
    }
    printf("-----\n");
}

void Lesson1_Stack::Execute() {
    printf("----------Lesson1_StackAndQueue Execute----------\n");

/*
    SqStack sqStack;
    InitStack(sqStack, 20);
    PrintStack(sqStack);

    Push(sqStack, 1);
    PrintStack(sqStack);

    Push(sqStack, 2);
    PrintStack(sqStack);

    int res;
    Pop(sqStack, res);
    PrintStack(sqStack);
*/

    LinkStack linkStack;
    InitStack(linkStack);
    PrintStack(linkStack);

    Push(linkStack, 1);
    PrintStack(linkStack);

    Push(linkStack, 2);
    PrintStack(linkStack);

    int res;
    Pop(linkStack, res);
    PrintStack(linkStack);
}

///栈与递归
//若一个对象部分的包含它自己，或用它自己给自己定义，称这个对象是递归的
//若一个过程（方法）直接或间接的调用自己，则称这个过程是递归的过程

/**
 * 例如求N的阶乘
 */
long Fact(long n) {
    if (n == 0)return 1;    /// 基本项，递归的出口
    return n * Fact(n - 1);    ///归纳项，向下递归
}
//还有斐波那契数列

//具有递归特性的数据结构：二叉树、广义表
//用递归解决有趣的问题：迷宫问题、Hanoi塔问题
//递归思想的本质是 分治思想，对一个较为复杂的问题能够分解成几个相对简单且解法相同或类似的自问题来求解

///使用递归方法的场景条件：
//  能将一个问题转变成一个新问题，而新问题与原问题的解法相同或类似，不同的仅仅是处理的对象，而且这些处理对象的变化有规律的
//  可以通过上述转化而使问题简化
//  必须有一个明确的递归出口，或称为递归的边界

///递归函数调用过程：
//调用前：
// 将实参、返回地址等传递给被调用函数
// 为被调用函数的局部变量分配存储区（可以看成入栈的过程）
// 被调用函数开始执行
//调用后：
// 保存被调用函数的计算结果
// 释放先前为被调用函数分配的存储区（可以看成出栈的过程）
// 根据保存的返回地址将控制权和结果返回给调用函数

//可以看到递归函数调用的整体流程遵循栈数据结构 先入后出、后入先出 的特点
//因此一个函数（不仅限于递归调用）的局部变量通常也会保存在系统栈内存中
