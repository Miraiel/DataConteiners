#include<iostream>
using namespace std;


void FillRand(int arr[], const int n);							//функция задает массив на n элементов
void Print(int arr[], const int n);								//функция вывода массива на n элементов

int* Push_Back(int arr[], int& n, int value);					//функция добавления значение в конец массива
int* Push_Front(int arr[], int& n, int value);					//функция добавления значение в начало массива
int* Insert(int arr[], int& n, int value, int index);			//функция добавляет значение в массив по заданному индексу

int* Pop_Back(int arr[], int& n);								//функция удаляет последний элемент массива
int* Pop_Front(int arr[], int& n);								//функция удаляет нулевой элемент массива
int* Erase(int arr[], int& n, int value, int index);			//функция удаляет элемент из массива по заданному индексу


void main()
{
	setlocale(LC_ALL, "");

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

}

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
	delete[]arr;
	arr = buffer;
	arr[index] = value;
	n++;
	return buffer;
}

int* Pop_Back(int arr[], int& n)
{
	int* buffer = new int[n - 1] {};
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i] = arr[i];
	}
	delete[]arr;
	arr = buffer;
	n--;
	return buffer;
}

int* Pop_Front(int arr[], int& n)
{
	int* buffer = new int[n - 1] {};
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i - 1] = arr[i];
	}
	delete[]arr;
	arr = buffer;
	n--;

	return buffer;
}

int* Erase(int arr[], int& n, int value, int index)
{
	int* buffer = new int [n - 1] {};
	for (int i = 0; i < n - 1; i++)
	{
		buffer[i] = arr[i - 1];
	}
	delete[]arr;
	arr = buffer;
	arr[index] = value;
	n--;
	return buffer;
}

