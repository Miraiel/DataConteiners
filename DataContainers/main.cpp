﻿#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t";
#define delimiter "\n--------------------------------------\n"

int** Allocate(const int rows, const int cols);
void Clear(int** arr, const int rows);

void FillRand(int arr[], const int n, int minRand = 0, int maxRand = 100);							//функция задает массив на n элементов
void FillRand(int** arr, const int rows, const int cols);

void Print(int arr[], const int n);																	//функция вывода массива на n элементов
void Print(int** arr, const int rows, const int cols);

int* Push_Back(int arr[], int& n, int value);														//функция добавления значение в конец массива
int** Push_row_Back(int** arr, int& rows, const int cols);
void Push_col_Back(int** arr, const int rows, int& cols);

int* Pop_Back(int arr[], int& n);																	//функция удаляет последний элемент массива
int** Pop_row_Back(int** arr, int& rows, const int cols);
void Pop_col_Back(int** arr, const int rows, int& cols);

int* Push_Front(int arr[], int& n, int value);														//функция добавления значение в начало массива
int** Push_row_Front(int** arr, int& rows, const int cols);
void Push_col_Front(int** arr, const int rows, int& cols);

int* Pop_Front(int arr[], int& n);																	//функция удаляет нулевой элемент массива
void Pop_col_Front(int** arr, const int rows, int& cols);

int* Erase(int arr[], int& n, int value, int index);												//функция удаляет элемент из массива по заданному индексу
int* Insert(int arr[], int& n, int value, int index);												//функция добавляет значение в массив по заданному индексу

//------------------------------------------------------------------------------------------------------------------------//



//#define DYNAMIC_MEMORY_1
#define DYNAMIC_MEMORY_2

void main()
{
	setlocale(LC_ALL, "");

#ifdef DYNAMIC_MEMORY_1

	int n;
	cout << "Ввести размер массива: "; cin >> n;
	int* arr = new int[n];										//выделяем динамическую память

	FillRand(arr, n);
	Print(arr, n);

	int value;
	int index;

	cout << "Введите значение элемента :"; cin >> value;
	arr = Push_Back(arr, n, value);
	Print(arr, n);


	cout << "Введите значение элемента :"; cin >> value;
	//arr = Push_Front(arr, n, value);
	Print(arr = Push_Front(arr, n, value), n);

	cout << "Введите позицию элемента :"; cin >> index;
	cout << "Введите значение элемента :"; cin >> value;
	//arr = Insert(arr, n, value, index);
	Print(arr = Insert(arr, n, value, index), n);

	//arr = Pop_Front(arr, n);
	Print(arr = Pop_Back(arr, n), n);

	//arr = Pop_Front(arr, n);
	Print(arr = Pop_Front(arr, n), n);

	cout << "Введите позицию элемента :"; cin >> index;

	arr = Erase(arr, n, value, index);
	Print(arr, n);

	cout << "Выход" << endl;


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

#ifdef DYNAMIC_MEMORY_2


	int rows;
	int cols;

	cout << "Введите количество строк: "; cin >> rows;
	cout << "Введите количество столбцов: "; cin >> cols;

	int** arr = Allocate(rows, cols);									//создаем массив указателей

	FillRand(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	arr = Push_row_Back(arr, rows, cols);
	FillRand(arr[rows - 1], cols, 100, 200);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	arr = Pop_row_Back(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	Push_col_Back(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	Pop_col_Back(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	Push_col_Front(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	Pop_col_Front(arr, rows, cols);
	Print(arr, rows, cols);

	cout << delimiter << endl;

	Pop_row_Front(arr, rows, cols);
	Print(arr, rows, cols);

	Clear(arr, rows);

#endif //DYNAMIC_MEMORY_2 
}

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

void FillRand(int arr[], const int n, int minRand, int maxRand)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % (maxRand - minRand) + minRand;									// arr[i] также как *(arr + 1)
	}
}

void FillRand(int** arr, const int rows, const int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 100;
		}
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
	if (index<0 || index>n)return arr;
	int* buffer = new int [n + 1] {};
	/*for (int i = 0; i < n; i++)	buffer[i] = arr[i];
	for (int i = index; i < n; i++)buffer[i + 1] = arr[i];*/
	for (int i = 0; i < n; i++)
	{
		/*if (i < index)  buffer[i] = arr[i];
		else			buffer[i + 1] = arr[i];*/
		//(i < index ? buffer[i] : buffer[i + 1]) = arr[i];
		buffer[i < index ? i : i + 1] = arr[i];
	}
	delete[]arr;
	arr = buffer;
	buffer[index] = value;
	n++;
	return buffer;
}

int* Pop_Back(int arr[], int& n)
{
	int* buffer = new int[--n] {};			//--n вместо n-1
	for (int i = 0; i < n; i++)
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
	for (int i = 0; i < n; i++)
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
	if (index<0 || index>n)return arr;
	int* buffer = new int [--n] {};

	for (int i = 0; i < n; i++)
	{
		//buffer[i] = arr[i - 1];
		(i < index ? buffer[i] : buffer[i - 1]) = arr[i];
	}
	delete[]arr;
	arr = buffer;
	buffer[index] = value;
	n--;
	return buffer;
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
	for (int i = 0; i < rows; i++)									//заносим адреса строк в массив указателей
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
	int** buffer = new int* [rows + 1] {};
	for (int i = 0; i < rows; i++)									//заносим адреса строк в массив указателей
	{
		buffer[i + 1] = arr[i];
	}
	delete[]arr;
	buffer[rows] = new int[cols] {};								//выделяем память под новую строку и добавляем ее в массив указателей
	rows++;
	return buffer;
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
		for (int j = 0; j < cols - 1; j++) buffer[j] = arr[i][j];
		delete[]arr[i];
		arr[i] = buffer;
	}
	cols--;
}

void Push_col_Front(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols + 1] {};
		for (int j = 0; j < cols; j++) buffer[j + 1] = arr[i][j];
		delete[]arr[i];
		arr[i] = buffer;
	}
	cols++;
}

void Pop_col_Front(int** arr, const int rows, int& cols)
{
	for (int i = 0; i < rows; i++)
	{
		int* buffer = new int[cols - 1] {};
		for (int j = 0; j < cols; j++) buffer[j] = arr[i][j + 1];
		delete[]arr[i];
		arr[i] = buffer;
	}
	cols--;
}

