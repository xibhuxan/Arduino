
//https://stackoverflow.com/questions/9986591/vectors-in-arduino
//This library is from a user from that web, I modified a bit adding one function

#ifndef LinkedList_hpp
#define LinkedList_hpp

template <class T>
class ListNode
{
public:
    T element;
    ListNode *next;
    ListNode *prev;

    ListNode(T element, ListNode *prev, ListNode *next) : element(element)
    {
        this->next = next;
        this->prev = prev;
    };
};

template <class T>
class LinkedList
{
private:
    int length;
    ListNode<T> *head;
    ListNode<T> *tail;
    ListNode<T> *curr;

public:
    LinkedList();
    LinkedList(const LinkedList<T> &);
    ~LinkedList();
    T &getCurrent();
    T &First() const;
    T &Last() const;
    int getLength();
    void Append(T);
    void DeleteLast();
    void DeleteFirst();
    void DeleteCurrent();
    bool next();
    bool moveToStart();
    bool prev();
    void Delete(T &);
    bool Search(T);
    T &getElement(int x);
    void Clear();
    void PutFirstToLast();
    void Update(T elem);
    LinkedList &operator=(const LinkedList<T> &);
};

template <class T>
LinkedList<T>::LinkedList()
{
    length = 0;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &list)
{
    length = 0;
    head = nullptr;
    tail = nullptr;
    curr = nullptr;

    ListNode<T> *temp = list.head;

    while (temp != nullptr)
    {
        Append(temp->element);
        temp = temp->next;
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &list)
{
    Clear();

    ListNode<T> *temp = list.head;

    while (temp != nullptr)
    {
        Append(temp->element);
        temp = temp->next;
    }

    return *this;
}

template <class T>
LinkedList<T>::~LinkedList()
{
    Clear();
}

template <class T>
T &LinkedList<T>::getCurrent()
{
    return curr->element;
}

template <class T>
T &LinkedList<T>::First() const
{
    return head->element;
}

template <class T>
T &LinkedList<T>::Last() const
{
    return tail->element;
}

template <class T>
int LinkedList<T>::getLength()
{
    return length;
}

template <class T>
void LinkedList<T>::Append(T element)
{
    ListNode<T> *node = new ListNode<T>(element, tail, nullptr);

    if (length == 0)
        curr = tail = head = node;
    else
    {
        tail->next = node;
        tail = node;
    }

    length++;
}

template <class T>
void LinkedList<T>::DeleteLast()
{
    if (length == 0)
        return;
    curr = tail;
    DeleteCurrent();
}

template <class T>
void LinkedList<T>::DeleteFirst()
{
    if (length == 0)
        return;
    curr = head;
    DeleteCurrent();
}

template <class T>
bool LinkedList<T>::next()
{
    if (length == 0)
        return false;

    if (curr->next == nullptr)
        return false;

    curr = curr->next;
    return true;
}

template <class T>
bool LinkedList<T>::moveToStart()
{
    curr = head;
    return length != 0;
}

template <class T>
bool LinkedList<T>::prev()
{
    if (length == 0)
        return false;

    if (curr->prev != nullptr)
        return false;

    curr = curr->prev;
    return true;
}

template <class T>
void LinkedList<T>::Delete(T &elem)
{
    if (Search(elem))
        DeleteCurrent();
}

template <class T>
void LinkedList<T>::DeleteCurrent()
{
    if (length == 0)
        return;
    length--;
    ListNode<T> *temp = curr;

    if (temp->prev != nullptr)
        temp->prev->next = temp->next;
    if (temp->next != nullptr)
        temp->next->prev = temp->prev;

    if (length == 0)
        head = curr = tail = nullptr;
    else if (curr == head)
        curr = head = head->next;
    else if (curr == tail)
        curr = tail = tail->prev;
    else
        curr = curr->prev;

    delete temp;
}

template <class T>
T &LinkedList<T>::getElement(int x)
{

    if (moveToStart())
    {
        if (x == 0)
            return head->element;
        if (x + 1 == length)
            return tail->element;

        for (int i = 0; i < x; i++)
            next();
        return curr->element;
    }
}

template <class T>
bool LinkedList<T>::Search(T elem)
{
    if (length == 0)
        return false;
    if (moveToStart())
        do
        {
            if (curr->element == elem)
                return true;
        } while (next());
    return false;
}

template <class T>
void LinkedList<T>::PutFirstToLast()
{
    if (length < 2)
        return;
    ListNode<T> *temp = head->next;
    head->next->prev = nullptr;
    head->next = nullptr;
    head->prev = tail;
    tail->next = head;
    tail = head;
    head = temp;
}

template <class T>
void LinkedList<T>::Update(T elem)
{
    if (Search(elem))
        curr->element = elem;
}

template <class T>
void LinkedList<T>::Clear()
{
    if (length == 0)
        return;
    ListNode<T> *temp = head;

    while (temp != nullptr)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    head = curr = tail = nullptr;

    length = 0;
}

#endif
