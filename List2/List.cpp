#include "List.h"

////////////////////////////////////////////////////////////////////////
//							LIST									  //
template<typename T>const typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>const typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename const List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename const List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	//cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(initializer_list<T> il) :List()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	//cout << "LCopyConstruct:\t" << this << endl;
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
	//cout << "LDesturctor:\t" << this << endl;
}

//------------------------Operator------------------------------

template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);
	//cout << "LCopyAssigment:\t" << this << endl;
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
		Head = Tail = new Element(Data);
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
	Head = Head->pPrev = new Element(Data, Head);
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
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index > size)return;
	if (Index == 0)return push_front(Data);
	Element* Temp;
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
	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
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
	Element* Temp;
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
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов к списке :" << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количествол жлементов в списке :" << size << endl;
}

//							LIST									  //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//							ConstBaseIterator   					  //

template<typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

//							ConstBaseIterator   					  //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//							ConstIterator       					  //

template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T>typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//							ConstIterator       					  //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//							ConstReverseIterator   					  //

template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//							ConstReverseIterator   					  //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//							Iterators			  					  //

template<typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
template<typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

//							Iterators	  							  //
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
//							Element				  					  //
template<typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
	//cout << "EConstructor:\t" << this << endl;
}
template<typename T>List<T>::Element::~Element()
{
	//cout << "EDestructor:\t" << this << endl;
}
//							Element				  					  //
////////////////////////////////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); ++it)cat.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
	return cat;
}
