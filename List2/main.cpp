#include<iostream>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimeter "\n------------------\n"

class List
{
	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
		friend class Iterator;
		friend class ConstIterator;
	}*Head, * Tail;

	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp) :Temp(Temp)
		{
			cout << "ITConstructor:\t" << this << endl;
		}
		~Iterator()
		{
			cout << "ITDestructor:\t" << this << endl;
		}

		bool operator!=(const Iterator& other)const
		{
			return this->Temp == other.Temp;
		}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			Temp = Temp->pPrev;
			return *this;
		}

		int& operator*()
		{
			return Temp->Data;
		}
	};

	class ConstIterator
	{
		Element* Temp;
	public:
		ConstIterator(Element* Temp) :Temp(Temp)
		{
			cout << "ITConstructor:\t" << this << endl;
		}
		~ConstIterator()
		{
			cout << "ITDestructor:\t" << this << endl;
		}
	};

	size_t size;
public:

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return Tail;
	}

	const ConstIterator begin()const
	{
		return Head;
	}

	const ConstIterator end()const
	{
		return Tail;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	List(initializer_list<int> il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	List(const List& other) :List()
	{
		*this = other;
	}

	List(List&& other) : List()
	{
		*this = move(other);
	}

	~List()
	{
		while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDesturctor:\t" << this << endl;
	}
	//------------------------Operator------------------------------

	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);

		/*while (Tail)pop_back();
		for (Element* Temp = other.Tail; Temp; Temp = Temp->pPrev)
			push_front(Temp->Data);*/

		return *this;
	}

	List& operator=(List&& other)
	{
		if (this == &other) return *this;

		while (Head)pop_front();
		while (Tail)pop_back();
		this->Head = other.Head;
		this->Tail = other.Tail;
		this->size - other.size;
		other.Head = nullptr;
		other.Tail = nullptr;
		other.size = 0;
		return *this;
	}

	//------------------------Adding List---------------------------

	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//создаем новый элемент
			Element* New = new Element(Data);
			//пристыковываем новый элемент к списку
			New->pNext = Head;
			//пристыковываем список к новому элементу
			Head->pPrev = New;
			//пееводим голову на новый элеемнт
			Head = New;

			//Head = new Element(Data, Head, Tail);  ??????
		}
		size++;
	}

	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);

		Element* New = new Element(Data);
		New->pPrev = Tail;
		Tail->pNext = New;
		Tail = New;

		//Tail = new Element(Data, Tail, Head); ?????
		size++;
	}

	void insert(int Data, int Index)
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
		//создаем новый элемент
		Element* New = new Element(Data);
		//прицепляем новый элемент к списку
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		//прицепляем список к новому элементу
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
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
		Tail->pPrev = nullptr;
		size--;
	}

	void erese(int Index)
	{
		if (Index > size)return;
		if (Index == 0)return pop_front();
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

//#define METHODS_INSERT_ERESE
//#define H_W

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

#ifdef H_W

	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	list.print();
	cout << delimeter << endl;
	list.reverse_print();

#endif // H_W
}
