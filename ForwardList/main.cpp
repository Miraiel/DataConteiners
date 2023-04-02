#include<iostream>
#include<ctime>
using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"
#define delimeter "\n-------------------------------------------\n"

template<typename T> class Element;
template<typename T> class ForwardList<T>;
template<typename T> ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
template<typename T> class ConstIterator<T>;
template<typename T> class Iterator<T>;

template<typename T> class Element
{
	T Data;		//значение элемента
	Element<T>* pNext; //адрес следующего элемента
	static int count;

public:
	Element(T Data, Element<T>* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		//cout << "EConstructor: \t" << this << endl;
	}
	~Element()
	{
		count--;
		//	cout << "EDestructor: \t" << this << endl;
	}

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
	ConstIterator(Element<T>* Temp) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}

	~ConstIterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	ConstIterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const ConstIterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const ConstIterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}
};

template<typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp) : Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}

	~Iterator()
	{
		cout << "ItDestructor:\t" << this << endl;
	}

	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}

	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	T& operator*()
	{
		return Temp->Data;
	}
};

template<typename T> class ForwardList
{
	Element<T>* Head;
	unsigned int size;

public:

	Iterator<T> begin()
	{
		return Head;
	}

	Iterator<T> end()
	{
		return nullptr;
	}

	const ConstIterator<T> begin()const
	{
		return Head;
	}

	const ConstIterator<T> end()const
	{
		return nullptr;
	}

	ForwardList()
	{
		Head = nullptr; // если список пуст его голова указывает на ноль
		size = 0;
		cout << "LConstructor: \t" << this << endl;
	}

	ForwardList(initializer_list<T> il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	ForwardList(const ForwardList<T>& other) :ForwardList()
	{
		*this = other;
	}

	ForwardList(ForwardList<T>&& other) :ForwardList()
	{
		*this = std::move(other);
	}

	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor: \t" << this << endl;
	}

	//---------------------------Adding Elements--------------------------

	void push_front(T Data)
	{
		/*
		Element* New = new Element(Data);	//создаем новый элемент

		New->pNext = Head;					//новый элемент должен указывать на начало списка

		Head = New;							//переводим Голову списка на новый элемент
		*/

		Head = new Element<T>(Data, Head);
		size++;

	}

	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);

		Element<T>* New = new Element<T>(Data);
		Element<T>* Temp = Head;

		while (Temp->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = New; +size++;

	}

	void insert(T Data, int index)			//вставляет значение в список по указанному индексу
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

	void pop_front()
	{
		Element<T>* Erased = Head;
		Head = Head->pNext;

		delete Erased;
		size--;

	}

	void pop_back()
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

	void erase(int index)		   //удаляет значение из списка по указанному индексу
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
		//доходим до элемента перед удаляемым
		Element<T>* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		//запоминаем адрес удаляемого элеменрта
		Element<T>* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;

		size--;
	}

	//------------------------Operators----------------------------------

	ForwardList<T>& operator=(const ForwardList<T>& other)
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

	ForwardList<T>& operator=(ForwardList<T>&& other)
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
	void print()const
	{
		Element<T>* Temp = Head;
		/*Temp - итератор (указаель при помощи которого
		можно получить доступ к элементам структуры данных)*/
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;

		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов: " << Element<T>::count << endl;
	}
	void reverse()
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

	friend ForwardList<T> operator+(const ForwardList<T>& left, const ForwardList<T>& right);
};

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

//#define BASE_CHECK
//#define OPERATOR_PLUS
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASE_FOR_LIST
//#define PREFORMANCE_TECT

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
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

	cout << "Ведите индекс элемента: "; cin >> index;
	cout << "Введите значение: "; cin >> value;
	list.insert(value, index);
	list.print();

	cout << delimeter << endl;
	cout << "Ведите индекс элемента: "; cin >> index;
	list.erase(index);
	list.print();


	cout << delimeter << endl;
	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();

#endif // BASE_CHECK

#ifdef OPERATOR_PLUS
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	cout << delimeter << endl;
	ForwardList list3;
	cout << delimeter << endl;
	list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASE_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	/*for (int i : list)
	{
		//i *= 10;
		cout << i << tab;
	}*/
	cout << endl;
	print(list);
	list.print();
#endif // RANGE_BASE_FOR_LIST

#ifdef PREFORMANCE_TECT
	int n;
	cout << "Введите размер списка: "; cin >> n;
	clock_t start = clock();
	ForwardList<int> list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	clock_t end = clock();
	double delta = double(end - start) / CLOCKS_PER_SEC;
	cout << "Список заполнен за: " << delta << "секунд" << endl;
	//list.print();
	start = clock();
	ForwardLis<int> list2 = list;
	end = clock();
	delta = double(end - start) / CLOCKS_PER_SEC;
	cout << "Список скопирован" << delta << "секунд" << endl;
	//list2.print();
#endif // PREFORMANCE_TECT

	ForwardList<int> i_list = { 3,5,8,13,21 };
	for (int i : i_list)cout << i << tab; cout << endl;

	ForwardList<double> d_list = { 2.7, 3.14, 5.1, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Хорошо","хивет","на","свете","Вини","Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}