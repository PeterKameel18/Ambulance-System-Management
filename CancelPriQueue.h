#pragma once
#include "priQueue.h"

template <typename T>
class CancelPriQueue : public priQueue<T> {
public:
    bool cancel(const T& entryToCancel, int priority) {
        if (this->isEmpty()) return false;

        priNode<T>* current = this->head;
        priNode<T>* previous = nullptr;  

        while (current != nullptr) {
            int nodePriority;
            if (current->getItem(nodePriority) == entryToCancel && nodePriority == priority) {
                if (previous == nullptr) {
                    this->head = current->getNext();
                }
                else {
                    previous->setNext(current->getNext());
                }

                delete current; 
                return true;   
            }

            previous = current;
            current = current->getNext();
        }

        return false;
    }
};


