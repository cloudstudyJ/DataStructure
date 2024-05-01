#pragma once

#include "./dataStructureBase.hpp"

template <typename T>
class Stack: public DataStructureBase {
    Stack(const Stack<T>& other) = delete;
    Stack<T>& operator=(const Stack<T>& other) = delete;

    private:
        struct Node {
            T data{ };

            Node* prev{ };
        };

    public:
        Stack();
        Stack(Stack<T>&& other) noexcept;
        ~Stack() noexcept;

        explicit operator bool() const noexcept;

        Stack<T>& operator=(Stack<T>&& other) noexcept;

        void push(const T& data);
        void pop();
        void clear();

        const T& peek() const;
        T& peek();

    private:
        Node* mTail{ };
};

template <typename T> Stack<T>::Stack()
    : DataStructureBase{} { }
template <typename T> Stack<T>::Stack(Stack<T>&& other) noexcept { *this = move(other); }
template <typename T> Stack<T>::~Stack() noexcept { clear(); }

template <typename T> Stack<T>::operator bool() const noexcept { return !isEmpty(); }

template <typename T> Stack<T>& Stack<T>::operator=(Stack<T>&& other) noexcept {
    clear();

    mTail = other.mTail;
    other.mTail = { };
    other.mSize = { };

    return *this;
}

template <typename T> void Stack<T>::push(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = mTail;

    mTail = newNode;
    ++mSize;
}
template <typename T> void Stack<T>::pop() {
    if (!isEmpty()) {
        Node* prevNode = mTail->prev;

        delete mTail;
        mTail = prevNode;

        --mSize;
    }
}
template <typename T> void Stack<T>::clear() {
    while (!isEmpty())
        pop();
}

template <typename T> const T& Stack<T>::peek() const { return mTail->data; }
template <typename T> T& Stack<T>::peek() { return mTail->data; }