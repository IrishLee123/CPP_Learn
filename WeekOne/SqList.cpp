#include <iostream>
#include <stdlib.h>
//
// Created by irish.li on 2022/3/28.
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

/**
 * 通过实现多项式求和来理解线性表结构
 */

/**
 * 浅试一下C++中各类型变量的所占用的空间
 */
void typeInstruction() {
    int list[5] = {1, 2, 3, 4, 5};

    int a = 100;
    std::cout << "a 的地址：";
    std::cout << &a << std::endl;
    std::cout << "int 的大小：";
    std::cout << sizeof a << std::endl;

    std::cout << "list 元素大小：";
    std::cout << sizeof list[0] << std::endl;

    std::cout << "list[0] 的地址：";
    std::cout << &list[0] << std::endl;

    std::cout << "list[1] 的地址：";
    std::cout << &list[1] << std::endl;

    std::cout << "list[2] 的地址：";
    std::cout << &list[2] << std::endl;

    std::cout << "list[3] 的地址：";
    std::cout << &list[3] << std::endl;

    std::cout << "list[4] 的地址：";
    std::cout << &list[4] << std::endl;

    float b = 3.1415926535;
    long c = 123456789;
    char d = 'c';
    double e = 3.1415926535;
    bool f = true;

    std::cout << "float 的大小：";
    std::cout << sizeof b << std::endl;

    std::cout << "long 的大小：";
    std::cout << sizeof c << std::endl;

    std::cout << "char 的大小：";
    std::cout << sizeof d << std::endl;

    std::cout << "double 的大小：";
    std::cout << sizeof e << std::endl;

    std::cout << "bool 的大小：";
    std::cout << sizeof f << std::endl;

}

/**
 * 数组定义相关
 */
void listDefine() {
    /**
     * 数组静态分配
     */
    int data_1[10] = {1};
    std::cout << "data_1 的地址：";
    std::cout << data_1 << std::endl;
    std::cout << "data_1 的数值：";
    std::cout << *data_1 << std::endl;
    /// 可见data_1变量中只是存放了数组中首个元素的地址
    /// TODO 猜测：C++通过[]方法封装了根据数组下标和元素大小确定元素存储地址的实现方法，使用户可以通过[下标]快速访问对应元素

    std::cout << "data_1[0] 的地址：";
    std::cout << &data_1[0] << std::endl;
    std::cout << "data_1[1] 的地址：";
    std::cout << &data_1[1] << std::endl;
    /// 可见数组相邻元素地址是连续的，间隔即为 sizeof(ElemType)

    /**
     * 数组动态分配
     * 通过malloc的方式为数组分配空间
     */
    int *data_2;    /// 先定义指向首个元素地址的指针
    std::cout << "data_2 的地址：";
    std::cout << data_2 << std::endl;
    std::cout << "data_2的数值：";
    std::cout << *data_2 << std::endl;

    std::cout << "data_2[0]的地址：";
    std::cout << &data_2[0] << std::endl;
    std::cout << "data_2[0]的数值：";
    std::cout << data_2[0] << std::endl;

    std::cout << "data_2[1]的地址：";
    std::cout << &data_2[1] << std::endl;
    std::cout << "data_2[1]的数值：";
    std::cout << data_2[1] << std::endl;

    /// 发现 data_2 保存的地址和 data_2[0] 获取到的地址是相同的，data_2[1]的地址 = data_2[0]地址 + sizeof(int)，此时并没有为数组分配存储空间
    /// TODO 猜测：任意指针类型的变量都可以通过 [] 的方式连续访问该地址向后连续的存储空间

    data_2 = (int *) malloc(sizeof(int) * 10);  /// 分配存储空间
    std::cout << "data_2的大小：";
    std::cout << sizeof *data_2 << std::endl;
    /// 观察malloc后并没有改变 data_2 指向地址的存储空间大小，是因为 data_2中保存的只是一个int类型的变量，他的大小就是4
    /// 那么要如何观察到malloc前后的变化呢？

    /// 再试一下结构体
    typedef struct {
        int *data;
        int length;
    } Temp;

    Temp t;
    std::cout << "t 的大小 before malloc：";
    std::cout << sizeof t << std::endl;
    t.data = (int *) malloc(sizeof(int) * 10);
    std::cout << "t 的大小 after malloc：";
    std::cout << sizeof t << std::endl;
    /// 可以看到malloc前后 t 占用的存储空间大小并未发生改变
    /// TODO 猜测：malloc分配内存后只是将这一段内存标记为使用中，其它进程不会继续使用，但这些内存中的数值在首次赋值前还保留分配内存之前的状态
    /// malloc后可以通过 [] 的形式来改变对应存储空间内保存的数值

    /// 用完了记得把申请的空间释放掉
    free(data_2);
    /// TODO 猜测：data_2记录了为其分配的内存大小，不然怎么知道要free掉多少内存

    std::cout << "data_2 after free：";
    std::cout << *data_2 << std::endl;
    /// 释放掉的空间被其它进程使用，数值已经变掉了
}

/**
 *  线性表的实现方式——顺序结构
 *  顺序结构存储的线性表需要占用一块连续的存储空间, 逻辑上连续的元素空间上也连续
 *
 *  顺序表中元素特点：
 *      地址连续
 *      一次存放
 *      随机存取
 *      类型相同
 *  根据上述特点发现可以用一维数组来实现顺序表
 *
 *  但线性表长度可变，数组的长度不能动态定义
 *  TODO: 是否可以动态扩容？
 *  使用一个变量表示顺序表的长度属性
 */

/**
 * 顺序表通用结构体
 * @tparam T 数据泛型
 */
template<class T>
struct SqList {
    T *elem;
    int length; // 当前长度
};

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

/**
 * 初始化线性表
 * @tparam T
 * @param L
 * @return
 */
template<class T>
Status InitList_Sq(SqList<T> &L) {
    L.elem = new T[MAX_SIZE];
    if (!L.elem)exit(OVERFLOW);
    L.length = 0;
    return OK;
}

/**
 * 销毁线性表
 * @tparam T
 * @param L
 */
template<class T>
void DestroyList(SqList<T> &L) {
    /// 释放存储空间
    if (L.elem)delete L.elem;
}

/**
 * 清空线性表
 * @tparam T
 * @param L
 */
template<class T>
void ClearList(SqList<T> &L) {
    /// 将线性表长度置为0
    L.length = 0;
}

/**
 * 获得线性表的长度
 * @tparam T
 * @param L
 * @return
 */
template<class T>
int GetLength(SqList<T> L) {
    return L.length;
}

/**
 * 判断线性表是否为空
 * @tparam T
 * @param L
 * @return
 */
template<class T>
int IsEmpty(SqList<T> L) {
    if (L.length == 0)
        return 1;
    return 0;
}

/**
 * 获取线性表中的元素
 * 时间复杂度：O(1)
 * @tparam T 泛型
 * @param L 线性表
 * @param i 目标元素下标
 * @param e 结果载体（引用类型）
 * @return
 */
template<class T>
int GetElem(SqList<T> L, int i, T &e) {
    if (i < 1 || i > L.length)return ERROR; /// i 不合规返回 Error
    e = L.elem[i - 1];
    return OK;
}

/**
 * 顺序查找目标元素
 * 时间复杂度：O(n)
 * @tparam T 泛型
 * @param L 线性表
 * @param e 目标元素
 * @return 返回目标元素位置
 */
template<class T>
int LocateElem(SqList<T> L, T e) {
    for (int i = 0; i < L.length; i++)  /// 利用for循环遍历数组全部元素
        if (L.elem[i] == e) return i + 1;   /// 查找成功，返回序号
    return 0;   /// 查找失败返回0
}

/**
 * 向顺序表中插入元素
 * 时间复杂度：O(n)
 * @tparam T 数据泛型
 * @param L 顺序表（引用类型）
 * @param i 插入位置
 * @param e 插入元素
 * @return
 */
template<class T>
Status ListInsert_Sq(SqList<T> &L, int i, T e) {
    if (i < 1 || i > L.length + 1) return ERROR;    /// i值不合法
    if (L.length == MAX_SIZE) return ERROR;     /// 存储空间已满
    for (int j = L.length - 1; j >= i - 1; j--)
        L.elem[j + 1] = L.elem[j];  /// 插入位置之后的元素后移
    L.elem[i - 1] = e;  /// 插入元素放到目标位置
    L.length++; /// 更新顺序表长度
    return OK;
}

/**
 * 删除顺序表中指定位置的元素
 * 时间复杂度：O(n)
 * @tparam T 数据泛型
 * @param L 顺序表（引用类型）
 * @param i 删除元素位置
 * @param e 结果返回
 * @return
 */
template<class T>
Status ListDelete(SqList<T> &L, int i, T &e) {
    if (i < 1 || i > L.length) return ERROR;    /// i值不合法
    e = L.elem[i - 1];  /// 保存结果
    for (int j = i - 1; j < L.length - 1; j++)
        L.elem[j] = L.elem[j + 1];
    L.length--;
    return OK;
}

template<class T>
void PrintSqList(SqList<T> L) {
    std::cout << "Length: ";
    std::cout << L.length << std::endl;
    std::cout << "[";
    for (int i = 0; i < L.length; i++) {
        std::cout << L.elem[i];
        if (i != L.length - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

int main() {

//    typeInstruction();
//    listDefine();

    SqList<int> sqList;

    InitList_Sq(sqList);
    for (int i = 1; i < 10; i++) {
        ListInsert_Sq(sqList, sqList.length + 1, i);
    }

    PrintSqList(sqList);

    int a;
    GetElem(sqList, 8, a);
    std::cout << "get num 8 elem: ";
    std::cout << a << std::endl;

    ListDelete(sqList,3,a);
    std::cout << "delete num 3 elem: ";
    std::cout << a << std::endl;

    PrintSqList(sqList);

    return 0;
}

//顺序表总结：
//优点：
//存储密度大
//可以随机存取表中任一元素
//缺点：
//插入、删除某一元素时，需要移动大量元素
//需要大块连续存储空间，但往往不能全部使用
//静态存储方式，存储容量不能自由扩充

