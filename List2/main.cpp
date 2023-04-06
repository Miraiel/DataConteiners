#include<iostream>
using namespace std;

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
	}*Head, * Tail;

	size_t size;
public:
	
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}

	~List()
	{
		while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDesturctor:\t" << this << endl;
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

			//Head = new Element(Data, Head, );
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

		//Tail = new Element(Data, ,Tail);
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



void main()
{
	setlocale(LC_ALL, "");
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

}