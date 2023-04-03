#pragma once

#include<iostream>
#include<ctime>

using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------------------------\n"

template<typename T> class ForwardList;
template<typename T> class ConstIterator;
template<typename T> class Iterator;
template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);

template<typename T> class Element
{
	T Data;		//значение элемента
	Element<T>* pNext; //адрес следующего элемента
	static int count;

public:
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();

	friend class ForwardList<T>;
	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
	friend class ConstIterator<T>;
	friend class Iterator<T>;

};

template<typename T> int Element<T>::count = 0;

template<typename T> class ConstIterator
{
	Element<T>* Temp;
public:
	ConstIterator(Element<T>* Temp);
	~ConstIterator();
	ConstIterator<T>& operator++();
	bool operator==(const ConstIterator<T>& other)const;
	bool operator!=(const ConstIterator<T>& other)const;
	const T& operator*()const;
};

template<typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp);
	~Iterator();
	Iterator<T>& operator++();
	bool operator==(const Iterator<T>& other)const;
	bool operator!=(const Iterator<T>& other)const;
	T& operator*();
};

template<typename T> class ForwardList
{
	Element<T>* Head;
	unsigned int size;

public:

	Iterator<T> begin();
	Iterator<T> end();
	const ConstIterator<T> begin()const;
	const ConstIterator<T> end()const;

	ForwardList();
	ForwardList(initializer_list<T> il);
	ForwardList(const ForwardList<T>& other);
	ForwardList(ForwardList<T>&& other);
	~ForwardList();

	//---------------------------Adding Elements--------------------------

	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int index);

	//---------------------Removing elements-----------------------------

	void pop_front();
	void pop_back();
	void erase(int index);
	void reverse();

	//------------------------Operators----------------------------------

	ForwardList<T>& operator=(const ForwardList<T>& other);
	ForwardList<T>& operator=(ForwardList<T>&& other);

	//-------------------------Methods-----------------------------------
	void print()const;

	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

