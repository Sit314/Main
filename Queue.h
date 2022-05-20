#ifndef EX3_QUEUE_H
#define EX3_QUEUE_H

#include <new>

template <class T>
class Queue {

public:
    Queue();

    void pushBack(const T& value);
    T& front();
    const T& front() const;
    void popFront();
    int size() const;

    Queue filter(const Queue& queue, const bool (*function)(T)) const;
    void transform(Queue& queue, const void (*function)(T&));

    Queue(Queue const& value);
    ~Queue();
    Queue& operator=(const Queue&);

    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    class EmptyQueue {
    };

private:
    struct Node {
        T data;
        Node* next;
    };

    Node* m_front;
    Node* m_rear;
};

template <class T>
Queue<T>::Queue()
    : m_front(nullptr)
    , m_rear(nullptr)
{
}

template <class T>
void Queue<T>::pushBack(const T& value)
{
    Node* append = new Node;
    append->data = value;
    append->next = nullptr;

    if (m_front == nullptr) {
        m_front = m_rear = append;
    } else {
        m_rear->next = append;
        m_rear = append;
    }
}

template <class T>
T& Queue<T>::front()
{
    if (m_front == nullptr) {
        throw Queue<T>::EmptyQueue();
    }
    return m_front->data;
}

template <class T>
const T& Queue<T>::front() const
{
    if (m_front == nullptr) {
        throw Queue<T>::EmptyQueue();
    }
    return m_front->data;
}

template <class T>
void Queue<T>::popFront()
{
    Node* toDelete = m_front;
    m_front = m_front->next;
    delete toDelete;
}

template <class T>
int Queue<T>::size() const
{
    int size = 0;
    for (Queue<T>::Iterator i = begin(); i != end(); ++i) {
        size++;
    }
    return size;
}

template <class T>
Queue<T> Queue<T>::filter(const Queue<T>& queue, const bool (*function)(T)) const
{
    Queue<T> out();
    for (Queue<T>::Iterator i = begin(); i != end(); ++i) {
        if (function(*i)) {
            out.pushBack(*i);
        }
    }
    return out;
}

template <class T>
void Queue<T>::transform(Queue<T>& queue, const void (*function)(T&))
{
    for (Queue<T>::Iterator i = begin(); i != end(); ++i) {
        *i = function(*i);
    }
}

template <class T>
class Queue<T>::Iterator {

    Iterator& operator++();
    bool operator!=(const Iterator& other) const;
    const T& operator*() const;

    class InvalidOperation {
    };

private:
    Node* m_current;
};

template <class T>
Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if (*this == nullptr) {
        throw InvalidOperation();
    }
    m_current = m_current->next;
    return *this;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Queue<T>::Iterator& other) const
{
    return m_current->data != other.m_current->data || m_current->next != other.m_current->next;
}

template <class T>
const T& Queue<T>::Iterator::operator*() const
{
    if (*this == nullptr) {
        throw InvalidOperation();
    }
    return m_current->data;
}

template <class T>
Queue<T>::Iterator Queue<T>::begin() const
{
    Iterator out();
    out.m_current = m_front;
    return out;
}

template <class T>
Queue<T>::Iterator Queue<T>::end() const
{
    Iterator out();
    out.m_current = m_rear->next;
    return out;
}

#endif // EX3_QUEUE_H
