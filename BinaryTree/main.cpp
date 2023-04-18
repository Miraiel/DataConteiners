#include<iostream>
#include<ctime>
using namespace std;

using std::cin;
using std::cout;
using std::endl;

#define delimeter "\n-----------------------------\n"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
	}*Root;

	size_t size;

public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		size = 0;
		cout << "TConstructor:\t" << this << endl;
	}

	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}

	~Tree()
	{
		Clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}

	void Clear(Element* Root)
	{
		if (Root!= NULL)
		{
			if(Clear(Root->pLeft);
			Clear(Root->pRight);
			Clear(Root);
		}
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
		size++;
	}

	int minValue(Element* Root)
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		if (Root == nullptr)return 0;
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)
	{
		//if (Root == nullptr) return 0;
		//return Count(Root->pLeft) + Count(Root->pRight) + 1;
		return Root == nullptr ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}

	int Sum(Element* Root)
	{
		//if (Root == nullptr) return 0;
		//return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
		return Root == nullptr ? 0 : Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;
	}

	double Avg(Element* Root)
	{
		return (double)Sum(Root) / (double)Count(Root);
	}

	int Depth(Element* Root)
	{
		//if (Root == nullptr) return 0;
		//return max(Depth(Root->pLeft) + 1, Depth(Root->pRight) + 1);

		return Root == nullptr ? 0 : max(Depth(Root->pLeft) + 1, Depth(Root->pRight) + 1);

		//if (Depth(Root->pLeft) + 1 >
		//	Depth(Root->pRight) + 1)
		//	return Depth(Root->pLeft) + 1;
		//else return Depth(Root->pRight) + 1;
	}

	void Erase(int index)
	{
		Element* parent = NULL;
		Element* value = Root;

		while (value->Data != index)
		{
			parent = value;
			if (value->Data > index)
			{
				value = value->pLeft;
			}
			else
			{
				value = value->pRight;
			}
		}

		if (!value)return;

		if (value->pLeft == NULL)// если у удаляемого элемента нет левого потомка
		{
			// цепляем правого потомка
			if (parent->pLeft == value) parent->pLeft = value->pRight;
			if (parent->pRight == value)parent->pRight = value->pRight;
			--size;
			delete value;
		}

		if (value->pRight = NULL)// если у удаляемого элемента нет правого потомка
		{
			//цепляем левого потомка
			if (parent->pLeft == value)parent->pLeft = value->pLeft;
			if (parent->pRight == value)parent->pRight = value->pLeft;
			--size;
			delete value;
		}

		// если у элемента есть оба потомка
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree :public Tree
{
public:

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
};

//#define BASE_CHECK
#define DEPTH_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK

	Tree tree;
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	//time_t t// цепляем правого потомка_start = time(NULL);
	//clock_t c_start = clock();
	for (int i = 0; i < n; i++)
	{
		int num = rand() % 100;
		//cout << num << "\t";
		tree.insert(num, tree.getRoot());
	}
	//clock_t c_end = clock();
	//time_t t_end = time(NULL);
	//cout << "Дерево заполнено за " << t_end - t_start << " секунд\n";
	//cout << "Дерево заполнено за " << double(c_end - c_start) / CLOCKS_PER_SEC << " секунд\n";
	tree.print(tree.getRoot());
	cout << endl;
	cout << delimeter << endl;

	cout << "Количество элементов: " << tree.Count(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree.Sum(tree.getRoot()) << endl;
	cout << delimeter << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Среднее арифметическое: " << tree.Avg(tree.getRoot()) << endl;
	cout << delimeter << endl;
	cout << "Глубина дерева: " << tree.Depth(tree.getRoot()) << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100, u_tree.getRoot());
	}
	//u_tree.print(u_tree.getRoot());
	cout << endl;
	cout << delimeter << endl;
	cout << "Количество элементов: " << u_tree.Count(u_tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << u_tree.Sum(u_tree.getRoot()) << endl;
	cout << delimeter << endl;
	cout << "Минимальное значение в дереве: " << u_tree.minValue(u_tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue(u_tree.getRoot()) << endl;
	cout << "Среднее арифметическое: " << u_tree.Avg(u_tree.getRoot()) << endl;
	cout << delimeter << endl;
	cout << "Глубина дерева: " << u_tree.Depth(u_tree.getRoot()) << endl;

#endif // BASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = { 50, 25, 75, 16, 32, 64, 90 };
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Глубина дерева: " << tree.Depth(tree.getRoot()) << endl;

	
#endif // DEPTH_CHECK
}
