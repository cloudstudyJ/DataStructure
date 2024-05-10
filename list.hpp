#pragma once

#include "./dataStructureBase.hpp"
#include "./typeHandler.hpp"

template <typename T>
class List: public DataStructureBase {
    List(const List<T>& other) = delete;
    List<T>& operator=(const List<T>& other) = delete;

    private:
        struct Node {
            T data{ };

            Node* prev{ };
            Node* next{ };
        };

    public:
        List();
        List(List<T>&& other) noexcept;
        ~List() noexcept;

        explicit operator bool() const noexcept;

        List<T>& operator=(List<T>&& other) noexcept;

        void insert(const T& data, const unsigned long long& idx);
        void push_back(const T& data);
        void push_front(const T& data);

        void remove_data(const T& data);
        void remove_idx(const unsigned long long& idx);
        void clear();

    private:
        Node* mHead{ };
        Node* mTail{ };
};

template <typename T> List<T>::List()
    : DataStructureBase{} { }
template <typename T> List<T>::List(List<T>&& other) noexcept
    : DataStructureBase{} { *this = move(other); }
template <typename T> List<T>::~List() noexcept { clear(); }

template <typename T> List<T>::operator bool() const noexcept { return !isEmpty(); }

template <typename T> List<T>& List<T>::operator=(List<T>&& other) noexcept {
    clear();

    mTail = other.mTail;
    mSize = other.mSize;

    other.mTail = { };
    other.mSize = { };

    return *this;
}

template <typename T> void List<T>::insert(const T& data, const unsigned long long& idx) {
    if (0 < idx && idx < mSize) [[likely]] {
        Node* newNode = new Node;
        newNode->data = data;

        Node* target = mHead;

        for (unsigned long long i = 0; i < idx; ++i)
            target = target->next;

        Node* targetPrev = target->prev;

        newNode->next = target;
        newNode->prev = targetPrev;

        target->prev = newNode;
        targetPrev->next = newNode;
        ++mSize;
    }
    else if (idx == 0) [[unlikely]]
        push_front(data);

    else if (idx == mSize) [[unlikely]]
        push_back(data);
}
template <typename T> void List<T>::push_front(const T& data) {
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
template <typename T> void List<T>::push_back(const T& data) {
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

template <typename T> void List<T>::remove_data(const T& data) {
    Node* target = mHead;

    while (target != nullptr) {
        if (target->data == data) {
            Node* targetPrev = target->prev;
            Node* targetNext = target->next;

            if (targetPrev != nullptr)
                targetPrev->next = targetNext;

            if (targetNext != nullptr)
                targetNext->prev = targetPrev;

            delete target;
            --mSize;

            return;
        }

        target = target->next;
    }
}
template <typename T> void List<T>::remove_idx(const unsigned long long& idx) {
    if (!isEmpty()) {
        Node* target = { };

        if (0 < idx && idx < (mSize - 1)) [[likely]] {
            target = mHead;

            for (unsigned long long i = 0; i < idx; ++i)
                target = target->next;

            Node* targetPrev = target->prev;
            Node* targetNext = target->next;

            if (targetPrev != nullptr)
                targetPrev->next = targetNext;

            if (targetNext != nullptr)
                targetNext->prev = targetPrev;

            delete target;
            --mSize;
        }
        else if (idx == 0) [[unlikely]] {
            target = mHead->next;
            delete mHead;

            if ((--mSize) != 0) [[likely]] {
                target->prev = { };

                mHead = target;
            }

            else [[unlikely]]
                mHead = mTail = { };
        }
        else if (idx == (mSize - 1)) [[unlikely]] {
            target = mTail->prev;
            delete mTail;

            if ((--mSize) != 0) [[likely]] {
                target->next = { };

                mTail = target;
            }
            else [[unlikely]]
                mHead = mTail = { };
        }
    }
}
template <typename T> void List<T>::clear() {
    while (!isEmpty())
        remove_idx(0);
}