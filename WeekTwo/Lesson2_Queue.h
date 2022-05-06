//
// Created by irish.li on 2022/4/25.
//

#ifndef CPP_LEARN_LESSON2_QUEUE_H
#define CPP_LEARN_LESSON2_QUEUE_H

#define MAX_Q_SIZE 100

typedef struct SqQueue {
    int *base;
    int front;//指向队头
    int rear;//指向队尾
    int queueSize;//队列容量
    int length;//队列长度
} SqQueue;

class Lesson2_Queue {

private:
    Status InitQueue(SqQueue &Q, int size);

    Status ClearQueue(SqQueue &Q);

    Status DestroyQueue(SqQueue &Q);

    bool QueueEmpty(SqQueue Q);

    Status EnQueue(SqQueue &Q, int e);

    Status DeQueue(SqQueue &Q, int &e);

    void PrintQueue(SqQueue Q);

public:
    void Excute();
};

#endif //CPP_LEARN_LESSON2_QUEUE_H

Status Lesson2_Queue::InitQueue(SqQueue &Q, int size) {
    Q.base = new int[size];

    if (!Q.base)exit(OVERFLOW);

    Q.queueSize = size;
    Q.length = 0;
    Q.rear = Q.front = 0;

    return OK;
}

Status Lesson2_Queue::ClearQueue(SqQueue &Q) {
    Q.rear = Q.front = 0;
    Q.length = 0;
}

Status Lesson2_Queue::DestroyQueue(SqQueue &Q) {
    if (!Q.base)return ERROR;

    delete Q.base;
    Q.rear = Q.front = 0;
    Q.length = Q.queueSize = 0;

    return OK;
}

bool Lesson2_Queue::QueueEmpty(SqQueue Q) {
    return Q.length <= 0;
}

Status Lesson2_Queue::EnQueue(SqQueue &Q, int e) {
    if (!Q.base)return ERROR;//异常
    if (Q.length >= Q.queueSize)return ERROR;//队列满了

    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % Q.queueSize;
    Q.length++;

    printf("EnQueue Success, %i\n", e);
    return OK;
}

Status Lesson2_Queue::DeQueue(SqQueue &Q, int &e) {
    if (!Q.base)return ERROR;//异常
    if (Q.length <= 0)return ERROR;//队列空了

    e = Q.base[Q.front];
    Q.front = (Q.front + 1) % Q.queueSize;
    Q.length--;

    printf("DeQueue Success, %i\n", e);
    return OK;
}

void Lesson2_Queue::PrintQueue(SqQueue Q) {
    if (!Q.base)return;//异常
    printf(">> ");

    if (Q.length > 0) {
        int p = Q.rear;

        if (p == Q.front) {
            p = (p - 1 + Q.queueSize) % Q.queueSize;
            printf("%i ", Q.base[p]);
        }

        while (p != Q.front) {
            p = (p - 1 + Q.queueSize) % Q.queueSize;
            printf("%i ", Q.base[p]);
        }
    }

    printf(">>\n");
}

void Lesson2_Queue::Excute() {
    printf("----------Lesson2_Queue Execute----------\n");

    SqQueue queue;
    InitQueue(queue, 10);
    PrintQueue(queue);

    EnQueue(queue, 1);
    PrintQueue(queue);

    EnQueue(queue, 2);
    EnQueue(queue, 15);
    EnQueue(queue, 21);
    EnQueue(queue, 31);
    PrintQueue(queue);

    int temp;

    DeQueue(queue, temp);
    PrintQueue(queue);

    DeQueue(queue, temp);
    PrintQueue(queue);

    ClearQueue(queue);
    PrintQueue(queue);

    EnQueue(queue, 1);
    EnQueue(queue, 2);
    EnQueue(queue, 3);
    PrintQueue(queue);
}