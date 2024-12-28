#pragma once
#include "LinkedQueue.h"



template <typename T>
class CancelQueue : public LinkedQueue<T> {
public:
    bool cancel(const T& entryToCancel) {
        if (this->isEmpty()) return false;

        Node<T>* current = this->frontPtr;
        Node<T>* previous = nullptr;

        while (current != nullptr) {
            if (current->getItem() == entryToCancel) {
                if (previous == nullptr) {

                    this->frontPtr = current->getNext();
                }
                else {

                    previous->setNext(current->getNext());
                }


                if (current == this->backPtr) {
                    this->backPtr = previous;
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





