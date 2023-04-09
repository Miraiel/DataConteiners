
#include"List.cpp"

template<typename T> void print(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T> void revers_print(const List<T> list)
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}

//#define METHODS_INSERT_ERESE
//#define ITERATORS_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef METHODS_INSERT_ERESE
	int n;
	cout << "Введите размер списка: "; cin >> n;


	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	cout << delimeter << endl;
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erese(index);
	list.print();
	cout << delimeter << endl;
	list.reverse_print();

#endif // METHODS_INSERT_ERESE

#ifdef ITERATORS_CHECK

	List list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	list.print();
	cout << delimeter << endl;
	list.reverse_print();

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

#endif // ITERATORS_CHECK

	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list_1 = { 2.7, 3.14, 8.2 };
	List<double> d_list_2 = { 7.5, 5.4 };
	List<double> d_list_3 = d_list_1 + d_list_2;
	for (double i : d_list_1)cout << i << tab; cout << endl;
	for (double i : d_list_2)cout << i << tab; cout << endl;
	print(d_list_3);
	revers_print(d_list_3);

	List<std::string> s_list_1 = { "Хорошо","живет","на","свете" };
	List<std::string> s_list_2 = { "Вини","Пух" };
	List<std::string> s_list_3 = s_list_1 + s_list_2;
	for (List<string>::Iterator it = s_list_3.begin(); it != s_list_3.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	print(s_list_2);
	print(s_list_3);
	revers_print(s_list_3);

}
