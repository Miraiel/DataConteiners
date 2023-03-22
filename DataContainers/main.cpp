#include<iostream>
using namespace std;


void FillRand(int arr[], const int n);							//������� ������ ������ �� n ���������
void Print(int arr[], const int n);								//������� ������ ������� �� n ���������

int* Push_Back(int arr[], int& n, int value);					//������� ���������� �������� � ����� �������
int* Push_Front(int arr[], int& n, int value);					//������� ���������� �������� � ������ �������
int* Insert(int arr[], int& n, int value, int index);			//������� ��������� �������� � ������ �� ��������� �������

int* Pop_Back(int arr[], int& n);								//������� ������� ��������� ������� �������
int* Pop_Front(int arr[], int& n);								//������� ������� ������� ������� �������
int* Erase(int arr[], int& n, int value, int index);			//������� ������� ������� �� ������� �� ��������� �������


void main()
{
	setlocale(LC_ALL, "");

	cout << "1. ���������� �������� � ����� �������" << endl;
	cout << "2. ���������� �������� � ������ �������" << endl;
	cout << "3. ���������� �������� � ������ �� ��������� �������" << endl;
	cout << "4. ������� ��������� ������� �������" << endl;
	cout << "5. ������� ������� ������� �������" << endl;
	cout << "6. ������� ������� �� ������� �� ��������� �������" << endl;

	int n;
	cout << "������ ������ �������: "; cin >> n;
	int* arr = new int[n];										//�������� ������������ ������

	FillRand(arr, n);
	Print(arr, n);

	int value;
	int index;

	char tsk;
	do {
		cout << "\n������� �������: ";
		cin >> tsk;

		switch (tsk)
		{
		case '1':

			cout << "������� �������� �������� :"; cin >> value;
			arr = Push_Back(arr, n, value);
			Print(arr, n);
			break;

		case '2':

			cout << "������� �������� �������� :"; cin >> value;
			arr = Push_Front(arr, n, value);
			Print(arr, n);
			break;

		case'3':

			cout << "������� ������� �������� :"; cin >> index;
			cout << "������� �������� �������� :"; cin >> value;
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

			cout << "������� ������� �������� :"; cin >> index;

			arr = Erase(arr, n, value, index);
			Print(arr, n);
			break;

		case'7':
			cout << "�����" << endl;
			break;


		default: cout << "error 400  bad request\n";

		}

	} while (tsk != '7');


	delete[]arr;												//�������� ��������� ������

	/*
		//������� ����� ������ ������� �������
		int* buffer = new int [n + 1] {};						//�� 1 ������� ������
		//�������� ��� ���������� ��������� ������� � �����
		for (int i = 0; i < n; i++)
		{
			buffer[i] = arr[i];
		}
		//������� �������� ������
		delete[]arr;
		//��������� ����� ��������� ������� ������� ������ �������
		arr = buffer;
		//������ ����� �������� ���� � ����� ������� 'arr' ����� ��������� ��� ���� ��������
		arr[n] = 123;
		//����� ���������� �������� � ������, ���������� ��� ��������� ������������� �� 1
		n++;
	*/

}

void FillRand(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;									// arr[i] ����� ��� *(arr + 1)
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

