#pragma once

#include "./dataStructureBase.hpp"
#include "./typeHandler.hpp"

template <typename T>
class Queue: public DataStructureBase {
    Queue(const Queue<T>& other) = delete;
    Queue<T>& operator=(const Queue<T>& other) = delete;

    private:
        struct Node {
            T data{ };

            Node* next{ };
        };

    public:
        Queue();
        Queue(Queue<T>&& other) noexcept;
        ~Queue() noexcept;

        explicit operator bool() const noexcept;

        Queue<T>& operator=(Queue<T>&& other) noexcept;

        void enqueue(const T& data);
        void dequeue();
        void clear();

        const T& peek() const;
        T& peek();

    private:
        Node* mTail{ };
};

template <typename T> Queue<T>::Queue()
    : DataStructureBase{} { }
template <typename T> Queue<T>::Queue(Queue<T>&& other) noexcept
    : DataStructureBase{} { *this = move(other); }
template <typename T> Queue<T>::~Queue() noexcept { clear(); }

template <typename T> Queue<T>::operator bool() const noexcept { return !isEmpty(); }

template <typename T> Queue<T>& Queue<T>::operator=(Queue<T>&& other) noexcept {
    clear();

    mTail = other.mTail;
    mSize = other.mSize;

    other.mTail = { };
    other.mSize = { };

    return *this;
}

template <typename T> void Queue<T>::enqueue(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;

    if (isEmpty())
        newNode->next = newNode;

    else {
        newNode->next = mTail->next;
        mTail->next = newNode;
    }

    mTail = newNode;
    ++mSize;
}
template <typename T> void Queue<T>::dequeue() {
    if (!isEmpty()) {
        Node* headNode = mTail->next;

        mTail->next = headNode->next;
        delete headNode;

        if ((--mSize) == 0)
            mTail = { };
    }
}
template <typename T> void Queue<T>::clear() {
    while (!isEmpty())
        dequeue();
}

template <typename T> const T& Queue<T>::peek() const { return mTail->next->data; }
template <typename T> T& Queue<T>::peek() { return mTail->next->data; }