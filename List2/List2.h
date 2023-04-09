#pragma once

#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------\n"

template<typename T> class Element;
template<typename T> class ConstBaseIterator;
template<typename T> List<T> operator+(const List<T>& left, const List<T>& right);

template<typename T> class List
{
    template<typename T> class Element
    {
        T Data;
        Element<T>* pNext;
        Element<T>* pPrev;
    public:
        Element(T Data, Element<T>* pNext = nullptr, Element<T>* pPrev = nullptr);
        ~Element();
        friend class List<T>;
    }*Head, * Tail;

    size_t size;

    template<typename T> class ConstBaseIterator
    {
    protected:
        Element<T>* Temp;
    public:
        ConstBaseIterator(Element<T>* Temp = nullptr);
        ~ConstBaseIterator();

        bool operator==(const ConstBaseIterator<T>& other)const;
        bool operator!=(const ConstBaseIterator<T>& other)const;
        const T& operator*()const;
    };
public:

    template<typename T> class ConstIterator :public ConstBaseIterator<T>
    {
    public:

        ConstIterator(Element<T>* Temp = nullptr);
        ~ConstIterator();

        ConstIterator<T>& operator++();
        ConstIterator<T>& operator--();
        ConstIterator<T> operator++(T);
        ConstIterator<T> operator--(T);
    };

    template<typename T> class ConstReverseIterator :public ConstBaseIterator<T>
    {
    public:
        ConstReverseIterator(Element<T>* Temp);
        ~ConstReverseIterator();

        ConstReverseIterator<T>& operator++();
        ConstReverseIterator<T>& operator--();
        ConstReverseIterator<T> operator++(T);
        ConstReverseIterator<T> operator--(T);
    };

    template<typename T> class Iterator :public ConstIterator<T>
    {
    public:
        Iterator(Element<T>* Temp = nullptr);
        ~Iterator();
        T& operator*();
    };

    template<typename T> class ReverseIterator :public ConstReverseIterator<T>
    {
    public:
        ReverseIterator(Element<T>* Temp = nullptr);
        ~ReverseIterator();
        T& operator*();
    };

    const ConstIterator<T> begin()const;
    const ConstIterator<T> end()const;
    Iterator<T> begin();
    Iterator<T> end();
    const ConstReverseIterator<T> rbegin()const;
    const ConstReverseIterator<T> rend()const;
    ReverseIterator<T> rbegin();
    ReverseIterator<T> rend();

    List();
    List(initializer_list<T> il);
    List(const List<T>& other);
    List(List<T>&& other);
    ~List();
    //------------------------Operator------------------------------

    List<T>& operator=(const List<T>& other);
    List<T>& operator=(List<T>&& other);

    //------------------------Adding List---------------------------

    void push_front(T Data);
    void push_back(T Data);
    void insert(T Data, int Index);

    //------------------------Removin Element-----------------------

    void pop_front();
    void pop_back();
    void erese(int Index);

    //--------------------------Methods-----------------------------

    void print()const;
    void reverse_print()const;

};