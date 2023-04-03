#include "ForwardList.cpp"

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

	ForwardList<int> i_list = { 3, 5, 8, 13, 21 };
	for (int i : i_list)cout << i << tab; cout << endl;

	ForwardList<double> d_list = { 2.7, 3.14, 5.1, 8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;

	ForwardList<std::string> s_list = { "Хорошо","живет","на","свете","Вини","Пух" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
}