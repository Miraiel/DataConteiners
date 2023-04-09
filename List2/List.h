#pragma once

#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------\n"


template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;

	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr): Temp(Temp) {}
		~ConstBaseIterator(){}

		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		T& operator*()const;
	};
public:

	class ConstIterator :public ConstBaseIterator
	{
	public:

		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp){}
		~ConstIterator(){}

		ConstIterator& operator++();
		ConstIterator& operator--();
		ConstIterator operator++(int);
		ConstIterator operator--(int);
	};

	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator(){}

		ConstReverseIterator& operator++();
		ConstReverseIterator& operator--();
		ConstReverseIterator operator++(int);
		ConstReverseIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp){}
		~Iterator(){}
		T& operator*();
	};

	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr):ConstReverseIterator(Temp){}
		~ReverseIterator(){}
		T& operator*();
	};

////////////////////////////////////////////////////////////////////////
//							LIST									  //

	const ConstIterator begin()const;
	const ConstIterator end()const;
	Iterator begin();
	Iterator end();
	const ConstReverseIterator rbegin()const;
	const ConstReverseIterator rend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();

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

//							LIST									  //
////////////////////////////////////////////////////////////////////////

};

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right);



