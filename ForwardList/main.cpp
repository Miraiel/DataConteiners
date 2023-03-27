#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//значение элемента
	Element* pNext; //адрес следующего элемента

public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor: \t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor: \t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;

public:

	ForwardList()
	{
		Head = nullptr; // если список пуст его голова указывает на ноль
		cout << "LConstructor: \t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor: \t" << this << endl;
	}

	//---------------------------Adding Elements--------------------------

	void push_front(int Data)
	{
		Element* New = new Element(Data);	//создаем новый элемент

		New->pNext = Head;					//новый элемент должен указывать на начало списка

		Head = New;							//переводим Голову списка на новый элемент


	}

	void push_back(int Data)
	{
		Element* New = new Element(Data);
	
		New->pNext = New;
		
	}

	void pop_front()
	{

	}

	void pop_back()
	{

	}

	void insert()			//вставляет значение в список по указанному индексу
	{

	}

	void erase()		   //удаляет значение из списка по указанному индексу
	{

	}
	//-------------------------Methods-----------------------------------
	void print()const
	{
		Element* Temp = Head;
		/*Temp - итератор (указаель при помощи которого 
		можно получить доступ к элементам структуры данных)*/
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;

		}
	}

};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
}