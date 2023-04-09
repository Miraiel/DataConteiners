#include<iostream>
#include<string>
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
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}*Head, * Tail;

	size_t size;

	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr):Temp(Temp){}
		~ConstBaseIterator() {}

		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}

		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		int& operator*()const
		{
			return Temp->Data;
		}
	};
public:

	class ConstIterator:public ConstBaseIterator
	{
	public:
	
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp)	{}
		~ConstIterator(){}

		ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}

		ConstIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}

		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}

		ConstIterator operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}

	};

	class ConstReverseIterator:public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp) : ConstBaseIterator(Temp){}
		~ConstReverseIterator(){}

		ConstReverseIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}

		ConstReverseIterator& operator--()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}

		ConstReverseIterator& operator++(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}

		ConstReverseIterator& operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator(){}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr): ConstReverseIterator(Temp){}
		~ReverseIterator() {}
		T& operator*()
		{
			return ConstBaseIterator::Temp->Data;
		}
	};

	const ConstIterator begin()const
	{
		return Head;
	}
	
	const ConstIterator end()const
	{
		return nullptr;
	}
	
	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	const ConstReverseIterator rbegin()const
	{
		return Tail;
	}

	const ConstReverseIterator rend()const
	{
		return nullptr;
	}

	ReverseIterator rbegin()
	{
		return Tail;
	}

	ReverseIterator rend()
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	List(initializer_list<T> il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	List(const List<T>& other) :List()
	{
		*this = other;
		cout << "LCopyConstruct:\t" << this << endl;
	}

	List(List<T>&& other) : Head(other.Head), Tail(other.Tail), size(other.size)
	{
		other.Head = other.Tail = nullptr;
		other.size = size_t();
	}

	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDesturctor:\t" << this << endl;
	}
	//------------------------Operator------------------------------

	List<T>& operator=(const List<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssigment:\t" << this << endl;
		return *this;
	}

	List<T>& operator=(List<T>&& other)
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

	void push_front(T Data)
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

	void push_back(T Data)
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

	void insert(T Data, int Index)
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

	void pop_front()
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

	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}

	void erese(int Index)
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

	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов к списке :" << size << endl;
	}

	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количествол жлементов в списке :" << size << endl;
	}
};

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat;
	for (typename List<T>::ConstIterator it = left.begin(); it != left.end(); ++it)cat.push_back(*it);
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
	return cat;
}

template<typename T> void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.bgin(); it != List.endl(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}

template<typename T> void revers_print(const List<T> list)
{
	for (typename List<T>::ConstReverseIterator it = list.bgin(); it != List.endl(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}

//#define METHODS_INSERT_ERESE
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef METHODS_INSERT_ERESE
	int n;
	cout << "Введите размер списка: "; cin >> n;


	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << delimeter << endl;
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erese(index);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();

#endif // METHODS_INSERT_ERESE

#ifdef ITERATORS_CHECK

	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	list.print();
	cout << delimeter << endl;
	list.reverse_print();

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

#endif // ITERATORS_CHECK

	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
	
	List<double> d_list_1 = { 2.7, 3.14, 8.2 };
	List<double> d_list_2 = { 7.5, 5.4 };
	List<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_1)cout << i << tab; cout << endl;
	for (double i : d_list_2)cout << i << tab; cout << endl;
	print(d_list_3);
	revers_print(d_list_3);

	List<std::string> s_list_1 = {"Хорошо","живет","на","свете"};
	List<std::string> s_list_2 = {"Вини","Пух"};
	List<std::string> s_list_3 = s_list_1 + s_list_2;
	for (List<string>::Iterator it = s_list_3.begin(); it != s_list_3.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	print(s_list_2);
	print(s_list_3);
	revers_print(s_list_3);

}
