#ifndef DATASTRUCTURES_PRIORITYQUEUE_H
#define DATASTRUCTURES_PRIORITYQUEUE_H

//
// This is not an assignment of the course
// In order to do them, I would have had to buy license
//

#include <vector>

class PriorityQueue {
public:
    PriorityQueue(int mS);
    void add(int i);
    int pop();
    int peak();

private:
    int getParent(int i);
    int getParentIndex(int i);
    int getLeftChild(int i);
    int getLeftChildIndex(int i);
    int getRightChild(int i);
    int getRightChildIndex(int i);
    void siftUp(int i);
    void siftDown(int i);
    int maxSize;
    int arraySize;
    std::vector<int> array;
};


#endif //DATASTRUCTURES_PRIORITYQUEUE_H
