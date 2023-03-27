#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//�������� ��������
	Element* pNext; //����� ���������� ��������

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
		Head = nullptr; // ���� ������ ���� ��� ������ ��������� �� ����
		cout << "LConstructor: \t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor: \t" << this << endl;
	}

	//---------------------------Adding Elements--------------------------

	void push_front(int Data)
	{
		Element* New = new Element(Data);	//������� ����� �������

		New->pNext = Head;					//����� ������� ������ ��������� �� ������ ������

		Head = New;							//��������� ������ ������ �� ����� �������


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

	void insert()			//��������� �������� � ������ �� ���������� �������
	{

	}

	void erase()		   //������� �������� �� ������ �� ���������� �������
	{

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
}