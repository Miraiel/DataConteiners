#include "List2.h"

//////////////////////////////////////////////////////////////////////////////////
////                                 List                                     ////

template<typename T>const List<T>::ConstIterator<T> List<T>::begin()const
{
    return Head;
}
template<typename T>const List<T>::ConstIterator<T> List<T>::end()const
{
    return nullptr;
}
template<typename T>const List<T>::ConstReverseIterator<T> List<T>::rbegin()const
{
    return Tail;
}
template<typename T>const List<T>::ConstReverseIterator<T> List<T>::rend()const
{
    return nullptr;
}
template<typename T>List<T>::Iterator<T> List<T>::begin()
{
    return Head;
}
template<typename T>List<T>::Iterator<T> List<T>::end()
{
    return nullptr;
}
template<typename T>List<T>::ReverseIterator<T> List<T>::rbegin()
{
    return Tail;
}
template<typename T>List<T>::ReverseIterator<T> List<T>::rend()
{
    return nullptr;
}

template<typename T>List<T>::List()
{
    Head = Tail = nullptr;
    size = 0;
    cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(initializer_list<T> il) :List()
{
    cout << typeid(il.begin()).name() << endl;
    for (int const* it = il.begin(); it != il.end(); it++)
    {
        push_back(*it);
    }
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
    *this = other;
    cout << "LCopyConstruct:\t" << this << endl;
}
template<typename T>List<T>::List(List<T>&& other) : Head(other.Head), Tail(other.Tail), size(other.size)
{
    other.Head = other.Tail = nullptr;
    other.size = size_t();
}
template<typename T>List<T>::~List()
{
    //while (Head)pop_front();
    while (Tail)pop_back();
    cout << "LDesturctor:\t" << this << endl;
}
//------------------------Operator------------------------------

template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
    if (this == &other)return *this;
    while (Head)pop_front();
    for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
        push_back(Temp->Data);
    cout << "LCopyAssigment:\t" << this << endl;
    return *this;
}
template<typename T>List<T>& List<T>::operator=(List<T>&& other)
{
    if (this == &other) return *this;

    while (Head)pop_front();
    while (Tail)pop_back();
    this->Head = other.Head;
    this->Tail = other.Tail;
    this->size = other.size;
    other.Head = other.Tail = nullptr;
    other.size = size_t();
    return *this;
}

//------------------------Adding List---------------------------

template<typename T>void List<T>::push_front(T Data)
{

    if (Head == nullptr && Tail == nullptr)
    {
        Head = Tail = new Element<T>(Data);
        size++;
        return;
    }
    /*else
    {
        //создаем новый элемент
        Element* New = new Element(Data);
        //пристыковываем новый элемент к списку
        New->pNext = Head;
        //пристыковываем список к новому элементу
        Head->pPrev = New;
        //пееводим голову на новый элеемнт
        Head = New;
    }*/
    Head = Head->pPrev = new Element<T>(Data, Head);
    size++;
}
template<typename T>void List<T>::push_back(T Data)
{
    if (Head == nullptr && Tail == nullptr)return push_front(Data);
    /*
    Element* New = new Element(Data);
    New->pPrev = Tail;
    Tail->pNext = New;
    Tail = New;
    */
    Tail = Tail->pNext = new Element<T>(Data, nullptr, Tail);
    size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
{
    if (Index > size)return;
    if (Index == 0)return push_front(Data);
    Element<T>* Temp;
    if (Index < size / 2)
    {
        Temp = Head;
        for (int i = 0; i < Index; i++)Temp = Temp->pNext;
    }
    else
    {
        Temp = Tail;
        for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
    }
    /*//создаем новый элемент
    Element* New = new Element(Data);
    //прицепляем новый элемент к списку
    New->pNext = Temp;
    New->pPrev = Temp->pPrev;
    //прицепляем список к новому элементу
    Temp->pPrev->pNext = New;
    Temp->pPrev = New;
    */
    Temp->pPrev = Temp->pPrev->pNext = new Element<T>(Data, Temp, Temp->pPrev);
    size++;
}

//------------------------Removin Element-----------------------

template<typename T>void List<T>::pop_front()
{
    if (Head == nullptr && Tail == nullptr)return;
    if (Head == Tail)
    {
        delete Head;
        Head = Tail = nullptr;
        return;
    }
    Head = Head->pNext;
    delete Head->pPrev;
    Head->pPrev = nullptr;
    size--;
}
template<typename T>void List<T>::pop_back()
{
    if (Head == Tail)return pop_front();
    Tail = Tail->pPrev;
    delete Tail->pNext;
    Tail->pNext = nullptr;
    size--;
}
template<typename T>void List<T>::erese(int Index)
{
    if (Head == nullptr && Tail == nullptr)return;
    if (Index > size)return;
    if (Index == 0 && Head == Tail)return pop_front();
    Element<T>* Temp;
    if (Index < size / 2)
    {
        Temp = Head;
        for (int i = 0; i < Index; i++)Temp = Temp->pNext;
    }
    else
    {
        Temp = Tail;
        for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
    }

    Temp->pPrev->pNext = Temp->pNext;
    Temp->pNext->pPrev = Temp->pPrev;
    delete Temp;
    size--;
}

//--------------------------Methods-----------------------------

template<typename T>void List<T>::print()const
{
    for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
        cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
    cout << "Количество элементов к списке :" << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
    for (Element<T>* Temp = Tail; Temp; Temp = Temp->pPrev)
        cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
    cout << "Количествол жлементов в списке :" << size << endl;
}

////                                 List                                     ////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
////                                Element                                   ////

template <typename T>List<T>::Element<T>::Element(T Data, Element<T>* pNext, Element<T>* pPrev) : Data(Data), pNext(pNext), pPrev(pPrev)
{
    cout << "EConstructor:\t" << this << endl;
}
template <typename T>List<T>::Element<T>::~Element()
{
    cout << "EDestructor:\t" << this << endl;
}

////                                Element                                   ////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
////                            ConstBaseIterator                             ////

template<typename T>List<T>::ConstBaseIterator<T>::ConstBaseIterator(Element<T>* Temp) :Temp(Temp) {}
template<typename T>List<T>::ConstBaseIterator<T>::~ConstBaseIterator() {}

template<typename T>bool List<T>::ConstBaseIterator<T>::operator==(const ConstBaseIterator<T>& other)const
{
    return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator<T>::operator!=(const ConstBaseIterator<T>& other)const
{
    return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::ConstBaseIterator<T>::operator*()const
{
    return Temp->Data;
}

////                            ConstBaseIterator                             ////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
////                              ConstIterator                               ////

template<typename T>List<T>::ConstIterator<T>::ConstIterator(Element<T>* Temp) : ConstBaseIterator<T>(Temp) {}
template<typename T>List<T>::ConstIterator<T>::~ConstIterator() {}

template<typename T>list<T>::ConstIterator<T>& ConstIterator<T>::operator--()
{
    Temp = Temp->pPrev;
    return *this;
}
template<typename T>list<T>::ConstIterator<T>::operator++(T)
{
    ConstIterator<T> old = *this;
    Temp = Temp->pNext;
    return old;
}
template<typename T>list<T>::ConstIterator<T>::operator--(T)
{
    ConstIterator<T> old = *this;
    Temp = Temp->pPrev;
    return old;
}


////                              ConstIterator                               ////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
////                            ConstReverseIterator                          ////

template<typename T>List<T>::ConstReverseIterator<T>::ConstReverseIterator(Element<T>* Temp) : ConstBaseIterator<>(Temp) {}
template<typename T>List<T>::ConstReverseIterator<T>::~ConstReverseIterator() {}

template<typename T>List<T>::ConstReverseIterator<T>& ConstReverseIterator<T>::operator++()
{
    Temp = Temp->pPrev;
    return *this;
}
template<typename T>List<T>::ConstReverseIterator<T>& ConstReverseIterator<T>::operator--()
{
    Temp = Temp->pNext;
    return *this;
}
template<typename T>List<T>::ConstReverseIterator<T>::operator++(T)
{
    ConstReverseIterator<T> old = *this;
    Temp = Temp->pPrev;
    return old;
}
template<typename T>List<T>::ConstReverseIterator<T>::operator--(T)
{
    ConstReverseIterator<T> old = *this;
    Temp = Temp->pNext;
    return old;
}

////                            ConstReverseIterator                          ////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
////                                 Iterator                                 ////

template<typename T>List<T>::Iterator<T>::Iterator(Element<T>* Temp = nullptr) :ConstIterator<T>(Temp) {}
template<typename T>List<T>::Iterator<T>::~Iterator() {}
template<typename T> T& List<T>::Iterator<T>::operator*()
{
    return Temp->Data;
}

////                                 Iterator                                 ////
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////
////                             ReverseIterator                              ////

template<typename T>List<T>::ReverseIterator<T>::ReverseIterator(Element<T>* Temp = nullptr) : ConstReverseIterator<T>(Temp) {}
template<typename T>List<T>::ReverseIterator<T>::~ReverseIterator() {}
template<typename T>T& List<T>::ReverseIterator<T>::operator*()
{
    return Temp->Data;
}

////                             ReverseIterator                              ////
//////////////////////////////////////////////////////////////////////////////////

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
    List<T> cat;
    for (List<T>::ConstIterator<T> it = left.begin(); it != left.end(); ++it)cat.push_back(*it);
    for (List<T>::ConstIterator<T> it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
    return cat;
}