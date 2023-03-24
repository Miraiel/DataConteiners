#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#define tab "\t";

int** Allocate(const int rows, const int cols);
void Clear(int** arr, const int rows);

void FillRand(int arr[], const int n);							//функция задает массив на n элементов
void FillRand(int** arr, const int rows, const int cols, int minrand = 0, int maxrand = 0);

void Print(int arr[], const int n);								//функция вывода массива на n элементов
void Print(int** arr, const int rows, const int cols);

int* Push_Back(int arr[], int& n, int value);					//функция добавления значение в конец массива
void Push_col_Back(int** arr, const int rows, int& cols);
void Pop_col_Back(int** arr, const int rows, int& cols);


int* Push_Front(int arr[], int& n, int value);					//функция добавления значение в начало массива
int** Push_row_Front(int** arr, int& rows, const int cols);

int* Insert(int arr[], int& n, int value, int index);			//функция добавляет значение в массив по заданному индексу

int* Pop_Back(int arr[], int& n);								//функция удаляет последний элемент массива
int** Pop_row_Back(int** arr, int& rows, const int cols);

int* Pop_Front(int arr[], int& n);								//функция удаляет нулевой элемент массива

int* Erase(int arr[], int& n, int value, int index);			//функция удаляет элемент из массива по заданному индексу

//------------------------------------------------------------------------------------------------------------------------//



//#define DYNAMIC_MEMORY_1
//#define FANCTIONS_DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY
	cout << "1. Добавления значение в конец массива" << endl;
	cout << "2. Добавления значение в начало массива" << endl;
	cout << "3. Добавления значение в массив по заданному индексу" << endl;
	cout << "4. Удаляет последний элемент массива" << endl;
	cout << "5. Удаляет нулевой элемент массива" << endl;
	cout << "6. Удаляет элемент из массива по заданному индексу" << endl;

	int n;
	cout << "Ввести размер массива: "; cin >> n;
	int* arr = new int[n];										//выделяем динамическую память

	FillRand(arr, n);
	Print(arr, n);

	int value;
	int index;

	char tsk;
	do {
		cout << "\nВведите задание: ";
		cin >> tsk;

		switch (tsk)
		{
		case '1':

			cout << "Введите значение элемента :"; cin >> value;
			arr = Push_Back(arr, n, value);
			Print(arr, n);
			break;

		case '2':

			cout << "Введите значение элемента :"; cin >> value;
			arr = Push_Front(arr, n, value);
			Print(arr, n);
			break;

		case'3':

			cout << "Введите позицию элемента :"; cin >> index;
			cout << "Введите значение элемента :"; cin >> value;
			arr = Insert(arr, n, value, index);
			Print(arr, n);
			break;

		case'4':

			arr = Pop_Back(arr, n);
			Print(arr, n);
			break;

		case'5':

			arr = Pop_Front(arr, n);
			Print(arr, n);
			break;

		case'6':

			cout << "Введите позицию элемента :"; cin >> index;

			arr = Erase(arr, n, value, index);
			Print(arr, n);
			break;

		case'7':
			cout << "Выход" << endl;
			break;


		default: cout << "error 400  bad request\n";

		}

	} while (tsk != '7');


	delete[]arr;												//очищение выделеной памяти
	/*
		//создать новый массив нужного размера
		int* buffer = new int [n + 1] {};						//на 1 элемент больше
		//копируем все содержимое исходного массива в новый
		for (int i = 0; i < n; i++)
		{
			buffer[i] = arr[i];
		}
		//удаляем исходный массив
		delete[]arr;
		//подменяем адрес исходного массива адрегом нового массива
		arr = buffer;
		//только после действий выше в конец массива 'arr' можно дописатоь еще одно значение
		arr[n] = 123;
		//после добавления элемента в массив, количество его элементов увеличивается на 1
		n++;
	*/
#endif DYNAMIC_MEMORY

	int rows;
	int cols;

	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество столбцов: "; cin >> cols;

	int** arr = Allocate(rows, cols);									//создаем массив указателей

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	arr = Push_row_Back(arr, rows, cols);
	Print(arr, rows, cols);

	//FillRand(arr[rows - 1], cols, 100,200);
	Print(arr, rows, cols);
	arr = Pop_row_Back(arr, rows, cols);

	Push_col_Back(arr, rows, cols);
	Print(arr, rows, cols);

	Pop_col_Back(arr, rows, cols);
	Print(arr, rows, cols);

	Clear(arr, rows);

}

#ifdef FANCTIONS_DYNAMIC_MEMORY_1

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;									// arr[i] также как *(arr + 1)
	}
}

void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;
}

int* Push_Back(int arr[], int& n, int value)
{
	int* buffer = new int[n + 1] {};
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	delete[]arr;
	arr = buffer;
	arr[n] = value;
	n++;

	return buffer;

}

int* Push_Front(int arr[], int& n, int value)
{
	int* buffer = new int[n + 1] {};
	for (int i = 0; i < n; i++)
	{
		buffer[i + 1] = arr[i];
	}
	delete[]arr;
	arr = buffer;
	arr[0] = value;
	n++;

	return buffer;
}

int* Insert(int arr[], int& n, int value, int index)
{
	int* buffer = new int [n + 1] {};
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	for (int i = 0; i < n; i++)
	{
		(i < index ? buffer[i] : buffer[i + 1]) = arr[i];
		buffer[i < index ? i : i + 1] = arr[i];
	}
	delete[]arr;
	arr = buffer;
	arr[index] = value;
	n++;
	return buffer;
}

int* Pop_Back(int arr[], int& n)
{
	int* buffer = new int[--n] {};			//--n вместо n-1
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i] = arr[i];
	}
	delete[]arr;
	//arr = buffer; 
	//n--;
	return buffer;
}

int* Pop_Front(int arr[], int& n)
{
	int* buffer = new int[--n] {};
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i] = arr[i + 1];
	}
	delete[]arr;
	//arr = buffer;
	//n--;
	return buffer;
}

int* Erase(int arr[], int& n, int value, int index)
{
	int* buffer = new int [--n] {};
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i] = arr[i - 1];
	}
	delete[]arr;
	//arr = buffer;
	//arr[index] = value;
	//n--;
	return buffer;
}

#endif // FANCTIONS_DYNAMIC_MEMORY_1

int** Allocate(const int rows, const int cols)
{
	int** arr = new int* [rows];
	for (int i = 0; i < rows; i++)
	{
		arr[i] = new int[cols];
	}
	return arr;
}

void Clear(int** arr, const int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[]arr[i];
	}
	delete[] arr;
}

void FillRand(int** arr, const int rows, const int cols, int minrand, int maxrand)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand(minrand - maxrand) % 100;
		}
	}
}

void Print(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << tab;
		}
		cout << endl;
	}
}

int** Push_row_Back(int** arr, int& rows, const int cols)
{
	int** buffer = new int* [rows + 1] {};
	for (int i = 0; i < rows; i++)								//заносим адреса строк в массив указателей
	{
		buffer[i] = arr[i];
	}
	delete[]arr;
	buffer[rows] = new int[cols] {};								//выделяем память под новую строку и добавляем ее в массив указателей
	rows++;
	return buffer;
}

int** Push_row_Front(int** arr, int& rows, const int cols)
{

}

int** Pop_row_Back(int** arr, int& rows, const int cols)
{
	//удаляем последнюю строку массива
	delete[]arr[rows - 1];
	//переопределяем массив указателей
	int** buffer = new int* [--rows] {};

	for (int i = 0; i < rows; i++)buffer[i] = arr[i];

	delete[]arr;
	return buffer;
}

void Push_col_Back(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < cols; j++) buffer[j] = arr[i][j];
		delete[]arr[i];
		arr[i] = buffer;
	}
	cols++;
}

void Pop_col_Back(int** arr, const int rows, int& cols) 
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1] {};
		for (int j = 0; j < cols-1; j++) buffer[j] = arr[i][j];
		delete[]arr[i];
		arr[i] = buffer;
	}
	cols--;
}
