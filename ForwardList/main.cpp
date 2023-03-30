#include<iostream>
using namespace std;

#define tab "\t"
#define delimeter "\n-------------------------------------------\n"

class Element
{
	int Data;		//�������� ��������
	Element* pNext; //����� ���������� ��������
	static int count;

public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor: \t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor: \t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;

public:

	ForwardList()
	{
		Head = nullptr; // ���� ������ ���� ��� ������ ��������� �� ����
		size = 0;
		cout << "LConstructor: \t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor: \t" << this << endl;
	}

	//---------------------------Adding Elements--------------------------

	void push_front(int Data)
	{
		/*
		Element* New = new Element(Data);	//������� ����� �������

		New->pNext = Head;					//����� ������� ������ ��������� �� ������ ������

		Head = New;							//��������� ������ ������ �� ����� �������
		*/

		Head = new Element(Data, Head);
		size++;

	}

	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);

		Element* New = new Element(Data);
		Element* Temp = Head;

		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New; +size++;

	}

	void insert(int Data, int index)			//��������� �������� � ������ �� ���������� �������
	{
		if (index == 0)return push_front(Data);
		if (index > size)return;
		Element* New = new Element(Data);
		Element* Temp = Head;

		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;

		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}

	//---------------------Removing elements-----------------------------

	void pop_front()
	{
		Element* Erased = Head;
		Head = Head->pNext;

		delete Erased;
		size--;

	}

	void pop_back()
	{
		Element* Temp = Head;

		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)		   //������� �������� �� ������ �� ���������� �������
	{
		if (index > size)return;
		Element* Temp = Head;
		Element* Erased = Head->pNext;

		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
			Erased = Temp->pNext->pNext;
		}
		delete Temp->pNext;

		Temp= Temp->pNext;
		Temp->pNext = Erased;

	
		size--;
	}

	//-------------------------Methods-----------------------------------
	void print()const
	{
		Element* Temp = Head;
		/*Temp - �������� (�������� ��� ������ ��������
		����� �������� ������ � ��������� ��������� ������)*/
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;

		}
		cout << "���������� ��������� ������: " << size << endl; 
		cout << "����� ���������� ���������: " <<Element::count << endl;
	}

};


void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimeter << endl;
	//list.pop_front();
	//list.print();
	//cout << delimeter << endl;
	//list.pop_back();
	//list.print();
	//list.push_back(123);
	//list.print();
	int index;
	int value;

	cout << "������ ������ ��������: "; cin >> index;
	cout << "������� ��������: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << delimeter << endl;
	cout << "������ ������ ��������: "; cin >> index;
	list.erase(index);
	list.print();
	cout << delimeter << endl;

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

}