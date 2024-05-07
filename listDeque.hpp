#pragma once

#include "./dataStructureBase.hpp"
#include "./typeHandler.hpp"

template <typename T>
class Deque: public DataStructureBase {
    Deque(const Deque<T>& other) = delete;
    Deque<T>& operator=(const Deque<T>& other) = delete;

    private:
        struct Node {
            T data{ };

            Node* prev{ };
            Node* next{ };
        };

    public:
        Deque();
        Deque(Deque<T>&& other) noexcept;
        ~Deque() noexcept;

        explicit operator bool() const noexcept;

        Deque<T>& operator=(Deque<T>&& other) noexcept;

        void push_front(const T& data);
        void push_back(const T& data);

        void pop_front();
        void pop_back();
        void clear();

        const T& front() const;
        const T& back() const;

        T& front();
        T& back();

    private:
        Node* mHead{ };
        Node* mTail{ };
};

template <typename T> Deque<T>::Deque()
    : DataStructureBase{} { }
template <typename T> Deque<T>::Deque(Deque<T>&& other) noexcept
    : DataStructureBase{} { *this = move(other); }
template <typename T> Deque<T>::~Deque() noexcept { clear(); }

template <typename T> Deque<T>::operator bool() const noexcept { return !isEmpty(); }

template <typename T> Deque<T>& Deque<T>::operator=(Deque<T>&& other) noexcept {
    clear();

    mTail = other.mTail;
    mSize = other.mSize;

    other.mTail = { };
    other.mSize = { };

    return *this;
}

template <typename T> void Deque<T>::push_front(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = mHead;

    if (!isEmpty()) [[likely]]
        mHead->prev = newNode;

    else [[unlikely]] {
        newNode->prev = { };

        mTail = newNode;
    }

    mHead = newNode;
    ++mSize;
}
template <typename T> void Deque<T>::push_back(const T& data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->prev = mTail;

    if (!isEmpty()) [[likely]]
        mTail->next = newNode;

    else [[unlikely]] {
        newNode->next = { };

        mHead = newNode;
    }

    mTail = newNode;
    ++mSize;
}

template <typename T> void Deque<T>::pop_front() {
    if (!isEmpty()) {
        Node* nextNode = mHead->next;
        delete mHead;

        if ((--mSize) != 0) [[likely]] {
            nextNode->prev = { };

            mHead = nextNode;
        }

        else [[unlikely]]
            mHead = mTail = { };
    }
}
template <typename T> void Deque<T>::pop_back() {
    if (!isEmpty()) {
        Node* prevNode = mTail->prev;
        delete mTail;

        if ((--mSize) != 0) [[likely]] {
            prevNode->next = { };

            mTail = prevNode;
        }
        else [[unlikely]]
            mHead = mTail = { };
    }
}
template <typename T> void Deque<T>::clear() {
    while (!isEmpty())
        pop_back();
}

template <typename T> const T& Deque<T>::front() const { return mTail->next->data; }
template <typename T> const T& Deque<T>::back() const { return mTail->data; }
template <typename T> T& Deque<T>::front() { return mTail->next->data; }
template <typename T> T& Deque<T>::back() { return mTail->data; }