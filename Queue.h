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
    void transform(Queue& queue, const void (*function)(T&)) const;

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
    Node* append;
    try {
        append = new Node;
    } catch (std::bad_alloc& e) {
        throw std::bad_alloc();
    }
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

#endif // EX3_QUEUE_H
