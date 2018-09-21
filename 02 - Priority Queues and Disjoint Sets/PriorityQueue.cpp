
#include <iostream>
#include "PriorityQueue.h"

int main(){
    PriorityQueue priorityQueue(8);
    priorityQueue.add(18);
    priorityQueue.add(42);
    priorityQueue.add(29);
    priorityQueue.add(14);
    priorityQueue.add(7);
    priorityQueue.add(12);
    priorityQueue.add(11);
    priorityQueue.add(5);
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
    std:: cout << priorityQueue.pop() << "\n";
}



void PriorityQueue::add(int i) {
    if (arraySize == maxSize) return;
    arraySize++;
    array[arraySize] = i;
    siftUp(arraySize);
}

int PriorityQueue::pop() {
    int result = peak();
    array[1] = array[arraySize];
    arraySize--;
    siftDown(1);
    return result;
}

int PriorityQueue::peak() {
    return array[1];
}

PriorityQueue::PriorityQueue(int mS){

    arraySize = 1;
    maxSize = mS + 1;
    array.resize(maxSize);
    array[0] = -1;

}


int PriorityQueue::getParent(int i) {
    return array[i/2];
}


int PriorityQueue::getParentIndex(int i) {
    return i/2;
}

int PriorityQueue::getLeftChild(int i) {
    return array[2*i];
}
int PriorityQueue::getLeftChildIndex(int i) {
    return 2*i;
}

int PriorityQueue::getRightChild(int i) {
    return array[2*i+1];
}
int PriorityQueue::getRightChildIndex(int i) {
    return array[2*i+1];
}

void PriorityQueue::siftUp(int i) {
    while (i > 1 && getParent(i) < array[i]){
        int helper = getParent(i);
        array[getParentIndex(i)] = array[i];
        array[i] = helper;
        i = getParentIndex(i);
    }
}

void PriorityQueue::siftDown(int i) {
    int maxIndex = i;
    int l = getLeftChildIndex(i);

    if (l <= arraySize && getLeftChild(i) > array[maxIndex])
        maxIndex = l;

    int r = getRightChildIndex(i);
    if (r <= arraySize && getRightChild(i) > array[maxIndex])
        maxIndex = r;
    if(i!= maxIndex){
        int helper = array[i];
        array[i] = array[maxIndex];
        array[maxIndex] = helper;
        siftDown(maxIndex);
    }

}

