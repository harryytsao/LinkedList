#include <iostream>
#include <vector>
#include <exception>

using namespace std;

template <typename T>
class LinkedList
{   
public:
    struct Node
    {
        mutable T data;
        Node* next;
        Node* prev;
    };
    struct Node* GetNewNode(const T& data)
    {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->next = nullptr;
        newNode->prev = nullptr;
        return newNode;
    }
    void PrintForward() const;
    void PrintReverse() const;
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    unsigned int NodeCount() const;
    
    LinkedList();
    ~LinkedList();

    Node* n;
    Node* head;
    Node* tail;

    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    Node* GetNode(unsigned int index);
    const Node* GetNode(unsigned int index) const;
    T& operator[](unsigned int index);
    const T& operator[](unsigned int index) const;
    Node* Find(const T& data);
    const Node* Find(const T& data) const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    LinkedList(const LinkedList<T>& list); 
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;

    bool RemoveHead();
    bool RemoveTail();
    bool RemoveAt(unsigned int index);
    unsigned int Remove(const T& data);
    void Clear();
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
};

template <typename T>
inline bool LinkedList<T>::RemoveHead()
{
    if (head == nullptr)
        return false;
    Node* temp = head->next;
    delete head;
    head = temp;
    return true;
}

template <typename T>
inline bool LinkedList<T>::RemoveTail()
{
    if (head == nullptr)
        return false;
    Node* temp = tail->prev;
    delete tail;
    tail = temp;
    if (tail == nullptr)
    {
        head = tail;
    }
    else {
        tail->next = nullptr;
    }
    return true;
}

template <typename T>
inline bool LinkedList<T>::RemoveAt(unsigned int index)
{
    unsigned int size = NodeCount();
    if (size < index)
    {
        return false;
    }
    if (index == 0)
    {
        Node* temp = head->next;
        delete head;
        head = temp;
        return true;
    }
    if (index == size)
    {
        Node* temp = tail->prev;
        delete tail;
        tail = temp;
        return true;
    }
    Node* target = GetNode(index);
    Node* previousNode = target->prev;
    Node* forwardNode = target->next;
    delete target;
    previousNode->next = forwardNode;
    forwardNode->prev = previousNode;
    return true;
}

template <typename T>
inline unsigned int LinkedList<T>::Remove(const T &data)
{
    unsigned int count = 0;
    Node* start = tail;
    for (unsigned int i = 0; i < NodeCount(); i++)
    {
        if (start->data == data)
        {
            count += 1;
            Node* prevNode = start->prev;
            Node* forwardNode = start->next;
            delete start;
            prevNode->next = forwardNode;
            forwardNode->prev = prevNode;
            start = prevNode;
        }
        start = start->prev;
    }
    return count;
}

template <typename T>
inline void LinkedList<T>::Clear()
{
    while (head)
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
    delete head;
    head = nullptr;
    tail = head;
}

template <typename T>
inline void LinkedList<T>::PrintForwardRecursive(const LinkedList<T>::Node *node) const
{
    if (node == tail)
    {
        cout << tail->data << endl;
    }
    else {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}

template <typename T>
inline void LinkedList<T>::PrintReverseRecursive(const LinkedList<T>::Node *node) const
{
    if (node == head)
    {
        cout << head->data << endl;
    }
    else {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
}

template <typename T>
inline void LinkedList<T>::InsertAfter(LinkedList<T>::Node *node, const T &data)
{
    Node* start = head;
    while (true)
    {
        if (start == node)
        {
            Node* newNode = GetNewNode(data);
            Node* forwardNode = node->next;
            forwardNode->prev = newNode;
            node->next = newNode;
            newNode->prev = node;
            newNode->next = forwardNode;
            return;
        }
        start = start->next;
    }
}

template <typename T>
inline void LinkedList<T>::InsertBefore(LinkedList<T>::Node *node, const T &data)
{
    Node* start = head;
    while (true)
    {
        if (start == node)
        {
            Node* newNode = GetNewNode(data);
            Node* backwardsNode = node->prev;
            backwardsNode->next = newNode;
            node->prev = newNode;
            newNode->next = node;
            newNode->prev = backwardsNode;
            return;
        }
        start = start->next;
    }
}

template <typename T>
inline void LinkedList<T>::InsertAt(const T &data, unsigned int index)
{
    unsigned int size = NodeCount();
    if (size < index)
    {
        throw out_of_range("out of range");
    }
    if (index == 0)
    {
        Node* target = head;
        Node* newNode = GetNewNode(data);
        target->prev = newNode;
        newNode->next = target;
        head = newNode;
        return;
    }
    if (index == size)
    {
        Node* newNode = GetNewNode(data);
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
        return;
    }
    Node* target = GetNode(index);
    Node* newNode = GetNewNode(data);
    Node* forwardNode = target->next;
    forwardNode->prev = newNode;
    target->next = newNode;
    newNode->prev = target;
    newNode->next = forwardNode;
}

template <typename T>
inline bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const
{
    Node* start1 = head;
    Node* start2 = rhs.head;
    while (start1 != nullptr)
    {
        if (start1->data != start2->data)
            return false;
        start1 = start1->next;
        start2 = start2->next;
    }
    return start1 == start2;
}

template <typename T>
inline LinkedList<T>::LinkedList()
{
    head = nullptr;
    tail = nullptr;
}

template <typename T>
inline LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
    Node* temp = list.head;
    head = GetNewNode(temp->data);
    tail = head;
    temp = temp->next;
    while (temp != nullptr)
    {
        Node* newNode = GetNewNode(temp->data);
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        temp = temp->next;
    }
}

template <typename T>
inline LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* next = current->next;
        delete current;
        current = next;
    }
    Node* temp = rhs.head;
    head = GetNewNode(temp->data);
    tail = head;
    temp = temp->next;
    while (temp != nullptr)
    {
        Node* newNode = GetNewNode(temp->data);
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        temp = temp->next;
    }
    return *this;
}

template <typename T>
inline LinkedList<T>::~LinkedList()
{
    while (head)
    {
        Node* next = head->next;
        delete head;
        head = next;
    }
    delete head;
}

template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::Head()
{
    return head;
}

template <typename T>
inline const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
    return head;
}

template <typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
    return tail;
}

template <typename T>
inline const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
    return tail;
}

template <typename T>
inline typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index)
{
    Node* start = head;
    unsigned int count = 0;
    unsigned int size = NodeCount();
    if (size < index)
    {
        throw out_of_range("out of range");
    }
    while (start != nullptr)
    {
        if (count == index)
        {
            return start;
        }
        start = start->next;
        count += 1;
    }
    return nullptr;
}

template <typename T>
inline const typename LinkedList<T>::Node *LinkedList<T>::GetNode(unsigned int index) const
{
    Node* start = head;
    unsigned int count = 0;
    unsigned int size = NodeCount();
    if (size < index)
    {
        throw out_of_range("out of range");
    }
    while (start != nullptr)
    {
        if (count == index)
        {
            return start;
        }
        start = start->next;
        count += 1;
    }
    return nullptr;
}

template <typename T>
inline T& LinkedList<T>::operator[](unsigned int index)
{
    const Node* start = head;
    unsigned int count = 0;
    unsigned int size = NodeCount();
    if (size <= index)
    {
        throw out_of_range("out of range");
    }
    while (start != nullptr)
    {
        if (count == index)
        {
            return start->data;
        }
        count += 1;
        start = start->next;
    }
    throw out_of_range("out of range");
}

template <typename T>
const inline T& LinkedList<T>::operator[](unsigned int index) const
{
    const Node* start = head;
    unsigned int count = 0;
    unsigned int size = NodeCount();
    if (size <= index)
    {
        throw out_of_range("out of range");
    }
    while (start != nullptr)
    {
        if (count == index)
        {
            return start->data;
        }
        count += 1;
        start = start->next;
    }
    throw out_of_range("out of range");
}


template <typename T>
inline typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data)
{
    Node* start = head;
    while(start != nullptr)
    {
        if (start->data == data)
        {
            return start;
        }
        start = start->next;
    }
    return nullptr;
}
template <typename T>
const typename LinkedList<T>::Node *LinkedList<T>::Find(const T &data) const
{
    Node* start = head;
    while(start != nullptr)
    {
        if (start->data == data)
        {
            return start;
        }
        start = start->next;
    }
    return nullptr;
}

template <typename T>
inline void LinkedList<T>::FindAll(std::vector<LinkedList<T>::Node *> &outData, const T &value) const
{
    Node* start = head;
    while(true)
    {
        if(start == nullptr)
        {
            return;
        }
        if(start->data == value)
        {
            outData.push_back(start);
        }
        start = start->next;
    }
}

template <typename T>
inline void LinkedList<T>::AddHead(const T &data)
{
    Node* temp = GetNewNode(data);
    if (head == nullptr)
    {
        head = temp;
        tail = temp;
        return;
    }
    head->prev = temp;
    temp->next = head;
    head = temp;
}

template <typename T>
inline void LinkedList<T>::AddTail(const T &data)
{
    Node* temp = GetNewNode(data);
    if (head == nullptr)
    {
        head = temp;
        tail = temp;
        return;
    }
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
}

template <typename T>
inline void LinkedList<T>::AddNodesHead(const T *data, unsigned int count)
{
    Node* arrayTail;
    Node* previousNode;
    Node* arrayHead = GetNewNode(data[0]);
    arrayTail = arrayHead;
    previousNode = arrayHead;

    for (unsigned int i = 1; i < count; i++)
    {
        Node* temp = GetNewNode(data[i]);
        if (i == 1)
        {
            temp->prev = arrayHead;
            previousNode = temp; 
        }
        temp->next = nullptr;
        temp->prev = previousNode;
        arrayTail->next = temp;
        arrayTail = temp;
        previousNode = temp;
    }
    arrayTail->next = head;
    head->prev = arrayTail;
    head = arrayHead;
}

template <typename T>
inline void LinkedList<T>::AddNodesTail(const T *data, unsigned int count)
{
    Node* arrayTail;
    Node* previousNode;
    Node* arrayHead = GetNewNode(data[0]);
    arrayTail = arrayHead;
    previousNode = arrayHead;

    for (unsigned int i = 1; i < count; i++)
    {
        Node* temp = GetNewNode(data[i]);
        if (i == 1)
        {
            temp->prev = arrayHead;
            previousNode = temp; 
        }
        temp->next = nullptr;
        temp->prev = previousNode;
        arrayTail->next = temp;
        arrayTail = temp;
        previousNode = temp;
    }
    arrayHead->prev = tail;
    tail->next = arrayHead;
    tail = arrayTail;
}

template <typename T>
inline unsigned int LinkedList<T>::NodeCount() const
{
    Node* start = head;
    int count = 0;
    while (start != nullptr)
    {
        count += 1;
        start = start->next;
    }
    return count;
}

template <typename T>
inline void LinkedList<T>::PrintForward() const
{
    Node* start = head;
    while (start != nullptr)
    {
        cout << start->data << endl;
        start = start->next;
    }
}

template <typename T>
inline void LinkedList<T>::PrintReverse() const
{
    Node* temp = head;
    if (temp == nullptr) return;
    Node* start = tail;
    while (start != nullptr)
    {
        cout << start->data << endl;
        start = start->prev;
    }
}