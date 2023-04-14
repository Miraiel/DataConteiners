#include<iostream>
using namespace std;

int Fibonacci(int n)
{
	//if (n == 0)return 0;
	//if (n == 1)return 1;
	//return Fibonacci(n - 2) + Fibonacci(n - 1);
	return n == 0 ? 0 : n == 1 ? 1 : Fibonacci(n - 2) + Fibonacci(n - 1);
}

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "¬ведите число: "; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << i << ":" << Fibonacci(i) << endl;
	}

}