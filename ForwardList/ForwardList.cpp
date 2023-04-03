#include"FrowardList.h"

////////////////////////////////////////////////////////////////////////////////////
/////							ForwardList										////

template <typename T> Iterator<T> ForwardList<T>::begin()
{
	return Head;
}
template <typename T> Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}
template <typename T> const ConstIterator<T> ForwardList<T>::begin()const
{
	return Head;
}
template <typename T> const ConstIterator<T> ForwardList<T>::end()const
{
	return nullptr;
}

template <typename T> ForwardList<T>::ForwardList()
{
	Head = nullptr; // если список пуст его голова указывает на ноль
	size = 0;
	cout << "LConstructor: \t" << this << endl;
}
template <typename T> ForwardList<T>::ForwardList(initializer_list<T> il) :ForwardList()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template <typename T> ForwardList<T>::ForwardList(const ForwardList<T>& other) :ForwardList()
{
	*this = other;
}
template <typename T> ForwardList<T>::ForwardList(ForwardList<T>&& other) : ForwardList()
{
	*this = std::move(other);
}
template <typename T> ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor: \t" << this << endl;
}

//---------------------------Adding Elements--------------------------

template<typename T> void ForwardList<T>::push_front(T Data)
{
	/*
	Element* New = new Element(Data);	//создаем новый элемент

	New->pNext = Head;					//новый элемент должен указывать на начало списка

	Head = New;							//переводим √олову списка на новый элемент
	*/

	Head = new Element<T>(Data, Head);
	size++;

}
template<typename T> void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);

	//Element<T>* New = new Element<T>(Data);
	Element<T>* Temp = Head;

	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	Temp->pNext = new Element<T>(Data); +size++;

}
template<typename T> void ForwardList<T>::insert(T Data, int index)			//вставл€ет значение в список по указанному индексу
{
	if (index == 0)return push_front(Data);
	if (index > size)return;
	Element<T>* New = new Element<T>(Data);
	Element<T>* Temp = Head;

	for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;

	New->pNext = Temp->pNext;
	Temp->pNext = New;
	size++;
}

//---------------------Removing elements-----------------------------

template<typename T>void ForwardList<T>::pop_front()
{
	Element<T>* Erased = Head;
	Head = Head->pNext;

	delete Erased;
	size--;

}
template<typename T>void ForwardList<T>::pop_back()
{
	Element<T>* Temp = Head;

	while (Temp->pNext->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}
template<typename T>void ForwardList<T>::erase(int index)		   //удал€ет значение из списка по указанному индексу
{
	/*
	if (index == 0)return pop_front();
	if (index > size)return;
	Element* Temp = Head;
	Element* Erased = Head->pNext;

	for (int i = 0; i < index - 1; i++)
	{
		Temp = Temp->pNext;
		Erased = Temp->pNext->pNext;
	}
	delete Temp->pNext;

	Temp->pNext = Erased;
	*/

	if (index == 0)return pop_front();
	if (index > size)return;
	//доходим до элемента перед удал€емым
	Element<T>* Temp = Head;
	for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
	//запоминаем адрес удал€емого элеменрта
	Element<T>* Erased = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete Erased;

	size--;
}
template<typename T>void ForwardList<T>::reverse()
{
	ForwardList<T> buffer;
	while (Head)
	{
		buffer.push_front(Head->Data);
		pop_front();
	}
	this->Head = buffer.Head;
	buffer.Head = nullptr;

}

//------------------------Operators----------------------------------

template<typename T>ForwardList<T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
	/*Element* Temp = list.Head;
	int i = 0;

	while (i < list.size)
	{
		this->push_back(Temp->Data);
		Temp = Temp->pNext;
	}
	*/
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)
		//push_back(Temp->Data);
		push_front(Temp->Data);
	reverse();
	return *this;
}
template<typename T>ForwardList<T>& ForwardList<T>::operator=(ForwardList<T>&& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	this->Head = other.Head;
	this->size = other.size;
	other.Head = nullptr;
	other.size = 0;
	return *this;
}

//-------------------------Methods-----------------------------------
template<typename T>void ForwardList<T>::print()const
{
	Element<T>* Temp = Head;
	/*Temp - итератор (указаель при помощи которого
	можно получить доступ к элементам структуры данных)*/
	while (Temp)
	{
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		Temp = Temp->pNext;

	}
	cout << " оличество элементов списка: " << size << endl;
	cout << "ќбщее количество элементов: " << Element<T>::count << endl;
}

/////							ForwardList										////
////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////
/////							Iterator										////

template<typename T> Iterator<T>::Iterator(Element<T>* Temp) : Temp(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template<typename T> Iterator<T>::~Iterator()
{
	cout << "ItDestructor:\t" << this << endl;
}

template<typename T> Iterator<T>& Iterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

template<typename T>bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> T& Iterator<T>::operator*()
{
	return Temp->Data;
}

/////							Iterator										////
////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////
/////							ConstIterator									////

template<typename T> ConstIterator<T>::ConstIterator(Element<T>* Temp) : Temp(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template<typename T> ConstIterator<T>::~ConstIterator()
{
	cout << "ItDestructor:\t" << this << endl;
}

template<typename T>ConstIterator<T>& ConstIterator<T>::operator++()
{
	Temp = Temp->pNext;
	return *this;
}

template<typename T>bool ConstIterator<T>::operator==(const ConstIterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>bool ConstIterator<T>::operator!=(const ConstIterator<T>& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& ConstIterator<T>::operator*()const
{
	return Temp->Data;
}

/////							ConstIterator									////
////////////////////////////////////////////////////////////////////////////////////

///------------------------------------------------------------------------------///

////////////////////////////////////////////////////////////////////////////////////
/////								Element										////

template<typename T>Element<T>::Element(T Data, Element<T>* pNext) : Data(Data), pNext(pNext)
{
	count++;
	//cout << "EConstructor: \t" << this << endl;
}
template<typename T>Element<T>::~Element()
{
	count--;
	//	cout << "EDestructor: \t" << this << endl;
}

/////								Element										////
////////////////////////////////////////////////////////////////////////////////////

template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right)
{
	ForwardList<T> cat = left;
	for (Element<T>* Temp = right.Head; Temp; Temp = Temp->pNext)
		cat.push_back(Temp->Data);
	return cat;
}
template<typename T> void print(const ForwardList<T>& list)
{
	for (const T& i : list)
	{
		//i *= 10;
		cout << i << tab;
	}
	cout << endl;
}