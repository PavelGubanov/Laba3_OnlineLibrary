#pragma once
#include <list>
#include <string>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <functional>

using namespace std;

template<typename T>
int distance(typename list<T>::iterator first, typename list<T>::iterator last, const list<T>& list);

template<typename T>
void fill_file(const list<T>& list, ofstream& fout); // заполнение файла элементами подмножества

template<typename T>
void print(const list<T>& list); // печать элементов подмножества в консоль

// Шаблонный класс для управления различными данными
template<typename T>
class DataController
{
private:
	//Выбранный тип контейнера для хранения данных - список
	list<T> _list;
public:
	DataController();
	DataController(const DataController<T>& controller);
	void add_elem(const T& elem); // добавление элемента
	bool change_elem(function<bool(T&)> check, function<void(T&)> change); // изменение элемента с помощью
										  // переданной функции 
	bool delete_elem(function<bool(T&)> check); // удаление элемента
	void clear(); // очистка контейнера
	bool empty(); // проверка контейнера на пустоту
	bool get_elem(function<bool(T&)> check, T& to_elem); //возвращает элемент, найденный в контейнере с помощью предиката check
	void sort(function<bool(T&, T&)> compare); //сортирует контейнер с использованием переданного компаратора
	void set_elems(const list<T>& list); //копирует элементы из переданного list-а

	void for_each(function<void(T&)> action); //выполняет предикат action для всех элементов контейнера
	void fill_container(ifstream& fin); // ввод элементов из файла
	void fill_file_from_container(ofstream& fout); // заполнение файла элементами контейнера
	void print_container(); // печать элементов контейнера в консоль	

	// линейный поиск элементов по заданным критериям
	// check - унарный предикат (если элемент подходит, возвращает true) 
	list<T> linear_search_elements(function<bool(T&)> check);

	// двоичный поиск элементов по заданным критерим
	// value - минимальное значение (если результатом поиска является диапозон элементов,
	// подходящих под указанные критерии 
	// check - унарный предикат (если элемент подходит, возвращает true) 
	// compare - компаратор для сортировки элементов
	list<T> binary_search_elements(T& value, function<bool(T&)> check, function<bool(T&, T&)> compare);
};

template<typename T>
inline DataController<T>::DataController()
{
}

template<typename T>
inline DataController<T>::DataController(const DataController<T>& controller)
{
	copy(controller._list.begin(), controller._list.end(), *this._list.begin());
}

template<typename T>
void DataController<T>::add_elem(const T& elem)
{
	_list.push_back(elem);
}	

template<typename T>
bool DataController<T>::change_elem(function<bool(T&)> check, function<void(T&)> change)
{
	auto iter = find_if(_list.begin(), _list.end(), check);
	if (iter != _list.end())
	{
		change(*iter);
		return true;
	}
	return false;	
}

template<typename T>
bool DataController<T>::delete_elem(function<bool(T&)> check)
{
	auto iter = find_if(_list.begin(), _list.end(), check);
	if (iter != _list.end())
	{
		_list.erase(iter);
		return true;
	}
	return false;	
}

template<typename T>
void DataController<T>::clear()
{
	_list.clear();
}

template<typename T>
bool DataController<T>::empty()
{
	return _list.empty();
}

template<typename T>
inline bool DataController<T>::get_elem(function<bool(T&)> check, T& to_elem)
{
	auto iter = find_if(_list.begin(), _list.end(), check);
	if (iter != _list.end())
	{
		to_elem = *iter;
		return true;
	}
	return false;
}

template<typename T>
inline void DataController<T>::sort(function<bool(T&, T&)> compare)
{
	_list.sort(compare);
}

template<typename T>
inline void DataController<T>::set_elems(const list<T>& list)
{
	for (T elem : list)
	{
		this->add_elem(elem);
	}
}

template<typename T>
inline void DataController<T>::for_each(function<void(T&)> action)
{
	std::for_each(_list.begin(), _list.end(), action);
}

template<typename T>
void DataController<T>::fill_container(ifstream& fin)
{
	copy(istream_iterator<T>(fin), istream_iterator<T>(), back_inserter(_list));		
}

template<typename T>
void DataController<T>::fill_file_from_container(ofstream& fout)
{
	fill_file(_list, fout);
}

template<typename T>
void DataController<T>::print_container()
{
	print(_list);
}

template<typename T>
list<T> DataController<T>::linear_search_elements(function<bool(T&)> check)
{
	list<T> result_list;
	for (T elem : _list)
	{
		if (check(elem))
		{
			result_list.push_back(elem);
		}
	}
	return result_list;
}

template<typename T>
inline list<T> DataController<T>::binary_search_elements(T& value, function<bool(T&)> check, function<bool(T&, T&)> compare)
{

	_list.sort(compare);
	auto left_border = _list.begin();
	auto right_border = _list.end();
	--right_border;
	int dist = distance(left_border, right_border, _list);

	while (dist > 0)
	{
		auto mid = left_border;
		int offset = dist / 2;
		for (int i = 0; i < offset; i++)
		{
			++mid;
		}
		if (compare(value, *mid))
		{
			right_border = mid;
			--right_border;
		}
		else
		{
			left_border = mid;
			++left_border;
		}
		dist = distance(left_border, right_border, _list);
	}

	list<T> result_list;
	for (; (right_border != _list.begin() && check(*right_border)); --right_border)
	{
		result_list.push_front(*right_border);
	}
	if (check(*right_border))
	{
		result_list.push_front(*right_border);
	}
	return result_list;
}

template<typename T>
int distance(const typename list<T>::iterator _first, const typename list<T>::iterator _last, const list<T>& _list)
{
	typename list<T>::iterator first = _first;
	typename list<T>::iterator last = _last;
	int dist = 0;
	while ((first != _list.end()) && (first != last))
	{
		++first;
		dist++;
	}
	if (first != last)
	{
		dist = -1;
	}
	return dist;
}

template<typename T>
void fill_file(const list<T>& list, ofstream& fout)
{
	ostream_iterator<T> ositer(fout, "\n");
	copy(list.begin(), list.end(), ositer);
}

template<typename T>
void print(const list<T>& list)
{
	ostream_iterator<T> ositer(cout, "\n");
	copy(list.begin(), list.end(), ositer);
}
