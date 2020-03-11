#pragma once

#include <iostream>
#include <thread>

#ifndef _THREADQUEUE_H_
#define _THREADQUEUE_H_

// template<class T>
struct Node;
class ThreadQueue{
    public:
    Node* front,*rear;
    ThreadQueue(){front=rear=NULL;};
 
    void push(std::thread * t);
    void pop();
    void display();
    ~ThreadQueue();
};

#endif // !_ThreadQueue_H_