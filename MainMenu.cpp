#include "MainMenu.h"
#include "DataController.h"
#include "BookRecord.h"
#include "Reader.h"
#include <Windows.h>
#include <cstdio>
#include <string>
#include <list>
#include <iostream>

using namespace std;

// чтение символа конца строки из консоли
void get_eoln()
{
	do
	{

	} while (getchar() != '\n');
}

//ввод числа с последующей проверкой его на принадлежность отрезку [min, max]
int get_num(const string& str, const string& err, int min, int max)
{
	int num;
	cout << str;
	cin >> num;
	get_eoln();
	while (num < min || num > max) {
		cout << err;
		cout << str;
		cin >> num;
		get_eoln();
	}
	return num;
}

//ввод строки из консоли
string get_string(string& text)
{
	cout << text;
	string result_string;
	getline(cin, result_string);
	return result_string;
}

//печать пунктов главного меню
int print_main_menu() 
{
	cout << "\nВыберите режим работы программы:" << "\n"
		<< "0 - выход" << "\n"
		<< "1 - читатель" << "\n"
		<< "2 - библиотекарь" << "\n";
	return 2;
}

//печать пунктов меню для читателя
int print_reader_menu(bool has_books)
{
	int stop_item = 1;
	cout << "\nВыберите одно из возможных действий:" << "\n"
		<< "0 - вернуться в главное меню" << "\n"
		<< "1 - взять книгу" << "\n";
	if (has_books) 
	{
		stop_item = 2;
		cout << "2 - сдать книгу" << "\n";
	}		
	return stop_item;
}

//печать пунктов меню для библиотекаря
int print_librarian_menu()
{
	cout << "\nВыберите одно из возможных действий:" << "\n"
		<< "0 - вернуться в главное меню" << "\n"
		<< "1 - редактировать список читателей" << "\n"
		<< "2 - редактировать список книг" << "\n"
		<< "3 - просмотреть историю выдачи книг на руки" << "\n"
		<< "4 - просмотреть список книг с текущим статусом" << "\n";
	return 4;
}

//печать меню для редактирования списка читателей
int print_editing_reader_list_menu(bool are_any_readers = true)
{
	int stop_item = 1;
	cout << "\nВыберите одно из возможных действий:" << "\n"
		<< "0 - вернуться назад" << "\n"
		<< "1 - зарегистирировать нового читателя" << "\n";
	if (are_any_readers)
	{
		stop_item = 3;
		cout << "2 - удалить читателя из базы" << "\n"
			<< "3 - редактировать информацию о читателе" << "\n";
	}		
	return stop_item;
}

//печать меню для редактирования списка книг
int print_editing_book_list_menu(bool are_any_books)
{
	int stop_item = 1;
	cout << "\nВыберите одно из возможных действий:" << "\n"
		<< "0 - вернуться назад" << "\n"
		<< "1 - зарегистирировать новую книгу" << "\n";
	if (are_any_books)
	{
		cout << "2 - удалить книгу из базы" << "\n"
			<< "3 - редактировать информацию о книге" << "\n";
		stop_item = 3;
	}		
	return stop_item;
}

//печать меню для изменения информации о читателе
int print_change_reader_menu()
{
	cout << endl
		<< "Выберите один из пунктов записи о читателе, который необходимо изменить:" << "\n"
		<< "0 - ничего не нужно изменять" << "\n"
		<< "1 - номер читательского билета" << "\n"
		<< "2 - фамилия читателя" << "\n"
		<< endl;
	return 2;
}

//печать меню для изменения информации о книге
int print_change_book_menu()
{
	cout << endl
		<< "Выберите один из пунктов записи о книге, который необходимо изменить:" << "\n"
		<< "0 - ничего не нужно изменять" << "\n"
		<< "1 - автор книги" << "\n"
		<< "2 - название книги" << "\n"
		<< "3 - год издательства" << "\n"
		<< "4 - название издательства" << "\n"
		<< endl;
	return 4;
}

//печать меню для редактирования списка фильтров
int print_change_filters_menu(bool elem_has_filters)
{
	int stop_item = 1;
	cout << endl
		<< "0 - назад" << "\n"
		<< "1 - добавить/изменить фильтр" << "\n";
	if (elem_has_filters)
	{
		cout << "2 - удалить фильтр" << "\n"
			<< endl;
		stop_item = 2;
	}
	return stop_item;
}

//печать меню для настроек просмотра списка данных
int print_display_setting()
{
	cout << endl
		<< "0 - вернуться в меню работника библиотеки" << "\n"
		<< "1 - изменить параметры фильтрации" << "\n"
		<< "2 - настроить сортировку" << "\n"
		<< endl;
	return 2;
}

//печать меню для работы с фильтрами
int print_filters(bool mayDeleteFilter) 
{
	int stop_item = 1;
	cout << endl << "Выберите одно из возможных действий с фильтрами:" << endl
		<< "0 - назад" << "\n"
		<< "1 - добавить/изменить фильтр" << "\n";
	if (mayDeleteFilter)
	{
		cout << "2 - удалить фильтр" << "\n" << endl;
		stop_item = 2;
	}		
	return stop_item;
}

//печать списка читателей
void print_reader_list(DataController<ReaderInfo>& readers, bool need_check)
{
	if (need_check && readers.empty())
	{
		cout << endl << "Ни одного зарегистрированного читателя не найдено!\n" << endl;
	}
	else if(!readers.empty())
	{
		cout << endl << "Список зарегистрированных читателей:" << endl;
		auto print = [](ReaderInfo& reader) -> void
		{
			cout << reader.get_reader().get_number_of_library_card()
				<< " - " << reader.get_reader().get_surname() << endl;
		};
		readers.for_each(print);
	}
}

//инициализация булевского массива для хранения фильтров
void init_filter_fields(bool* filters, int size)
{
	for (int i = 0; i < size; i++)
	{
		filters[i] = false;
	}
}

//возвращение книги в библиотеку
void return_book(ReaderInfo& reader, IssuedBook& tmp, DataController<BookRecord>& book_records)
{
	Date return_date;
	cout << "Введите дату сдачи книги: ";
	cin >> return_date;
	BookRecord current_record;
	current_record.set_return_date(return_date);
	current_record.set_issued_book(tmp);
	current_record.set_reader(reader.get_reader());
	book_records.add_elem(current_record);
}

bool check_true_selected_fields(bool *fields, int size)
{
	bool result = false;
	for (int i = 0; i < size; i++)
	{
		result = result || fields[i];
	}
	return result;
}
bool check_false_selected_fields(bool* fields, int size)
{
	bool result = true;
	for (int i = 0; i < size; i++)
	{
		result = result && fields[i];
	}
	return result;
}

//печать элемента списка с проверкой его доступности
void print_item_with_check(bool check, int& item, const string& str)
{
	if (check)
	{
		item++;
		cout << item << str;		
	}
}

//печать меню для добавления критериев поиска книги в библиотеке
int print_find_book_menu(bool *fields, int size, int& start_item) 
{
	start_item = check_true_selected_fields(fields, size) ? 0 : 1;
	int stop_item = 0;
	cout << "\nВыберите критерий для поиска книги:" << endl;
	if (!start_item)
	{
		cout << "0 - не добавлять критерий" << endl;
	}
	print_item_with_check(!fields[0], stop_item, " - автор книги\n");
	print_item_with_check(!fields[1], stop_item, " - название\n");
	print_item_with_check(!fields[2], stop_item, " - год издательства\n");
	print_item_with_check(!fields[3], stop_item, " - издательство\n");
	return stop_item;	
}

//добавление критериев поиска книги
void add_fields_for_search(bool *fields, int size, BookInfo& b) 
{	
	int start_item, stop_item, cur_item = 1;
	while (cur_item != 0)
	{
		stop_item = print_find_book_menu(fields, size, start_item);
		cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", start_item, stop_item);
		int i = 0, j = 0;
		for (i = 0; i < size && j < cur_item; i++)
		{
			if (!fields[i])
			{
				j++;
			}
		}
		if (i > 0)
		{
			fields[i - 1] = true;
		}		
		cur_item = i;
		cout << endl;
		b.input_field_by_num(cur_item);
	}
}

//удаление фильтров для отображения списка элементов
void delete_filters(bool* filters, int size, function<int()> print_menu)
{
	int stop_item, cur_item = 1;
	while (cur_item != 0)
	{
		stop_item = print_menu();
		cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, stop_item);
		int i = 0, j = 0;
		for (i = 0; i < size && j < cur_item; i++)
		{
			if (filters[i])
			{
				j++;
			}
		}
		if (i > 0)
		{
			filters[i - 1] = false;
		}
		if (!check_true_selected_fields(filters, size))
		{
			cur_item = 0;
		}
	}
}

const string READER_BASE = "readers.txt";
const string BOOK_BASE = "books.txt";
const string BOOKRECORD_BASE = "bookrecords.txt";

void main_menu()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Данная программа демонстрирует процесс работы виртуальной библиотеки." << endl;
	DataController<ReaderInfo> readers;
	DataController<BookInfo> books;
	DataController<BookRecord> book_records;
	ifstream from_base_readers(READER_BASE);
	ifstream from_base_books(BOOK_BASE);
	ifstream from_base_bookrecords(BOOKRECORD_BASE);
	if (!from_base_readers.is_open())
	{
		cout << endl << "Не удаётся найти файл с базой читателей - readers.txt! Устраните проблему доступа к нему и перезапустите приложение!" << endl;
	}
	else
	{
		if (!from_base_books.is_open())
		{
			from_base_readers.close();
			cout << endl << "Не удаётся найти файл с базой книг - books.txt! Устраните проблему доступа к нему и перезапустите приложение!" << endl;
		}
		else
		{			
			if (!from_base_bookrecords.is_open())
			{
				from_base_readers.close();
				from_base_books.close();
				cout << endl << "Не удаётся найти файл с историей выдачи книг на руки - bookrecords.txt! Устраните проблему доступа к нему и перезапустите приложение!" << endl;
			}
			else
			{
				readers.fill_container(from_base_readers);
				books.fill_container(from_base_books);
				book_records.fill_container(from_base_bookrecords);
				from_base_readers.close();
				from_base_books.close();
				from_base_bookrecords.close();

				int stop_item, cur_item = 1;
				while (cur_item != 0)
				{
					stop_item = print_main_menu();
					cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, stop_item);
					switch (cur_item)
					{
						case 1: //режим читателя
						{
							if (readers.empty())
							{
								cout << endl << "Не найдено ни одного читателя!" << endl
									<< "Попросите работника библиотеки зарегистрировать Вас!" << endl;
								break;
							}
							else
							{
								bool log_in_reader = false;
								while (!log_in_reader)
								{
									print_reader_list(readers, false);
									cout << "\nВведите Ваш номер читательского билета: ";
									int number;
									cin >> number;
									auto check_number = [&number](ReaderInfo& r) {
										return r.get_reader().get_number_of_library_card() == number;
									};
									ReaderInfo current_reader;
									if (readers.get_elem(check_number, current_reader))
									{
										log_in_reader = true;
										int stop_item, cur_item = 1;
										while (cur_item != 0)
										{
											stop_item = print_reader_menu(current_reader.has_books_on_hand());
											cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, stop_item);
											switch (cur_item)
											{
											case 1: //читатель пытается взять книгу
											{
												BookInfo tmp;
												bool selected_fields[] = { false, false, false, false };
												int size = 4;
												add_fields_for_search(selected_fields, size, tmp);
												auto check = [&tmp, &selected_fields](BookInfo& b)
												{
													bool result = true;
													if (selected_fields[0])
													{
														result = result && (b.get_book().get_author_of_book() == tmp.get_book().get_author_of_book());
													}
													if (selected_fields[1])
													{
														result = result && (b.get_book().get_name_of_book() == tmp.get_book().get_name_of_book());
													}
													if (selected_fields[2])
													{
														result = result && (b.get_book().get_year_of_publication() == tmp.get_book().get_year_of_publication());
													}
													if (selected_fields[3])
													{
														result = result && (b.get_book().get_publishing_house() == tmp.get_book().get_publishing_house());
													}
													return result;
												};
												if (!books.get_elem(check, tmp))
												{
													cout << "Книга, которая Bас интересует, отсутствует в нашей библиотеке." << endl;
													break;
												}
												else
												{
													book_status status = tmp.get_status();
													switch (status)
													{
														case book_status::is_issued:
														{
															Date issue_date;
															if (current_reader.has_chosen_book(tmp.get_book(), issue_date))
															{
																int ans_num = get_num("Данная книга находится у вас.\nХотите сдать её?\n1 - да\n2 - нет\nВаш выбор - ", "Ошибка! Некорректный вариант ответа! Повторите ввод!\n", 1, 2);
																if (ans_num == 1)
																{
																	IssuedBook issued_book;
																	issued_book.set_book(tmp.get_book());
																	issued_book.set_issue_date(issue_date);
																	books.change_elem(check, [](BookInfo& bi) {
																		bi.set_status(true);
																		});
																	readers.change_elem(check_number, [&tmp](ReaderInfo& ri) {
																		ri.return_book(tmp.get_book());
																		});
																	return_book(current_reader, issued_book, book_records);
																	cout << "Книга успешно возвращена в библотеку!" << endl;
																}																
															}
															else
															{
																cout << "Книга, которая Вас интересует, находится у другого читателя.\n"
																	<< "Выберите другую книгу." << endl;
															}
															break;
														}
														case book_status::is_available:
														{
															cout << "Книга по вашему запросу найдена!\n\n";
															Date issue_date;
															cout << "Введите дату выдачи книги: ";
															cin >> issue_date;
															cout << "\nКнига в Вашем распоряжении. Приятного прочтения!" << endl;
															IssuedBook issued_book(tmp.get_book(), issue_date);
															books.change_elem(check, [](BookInfo& bi) {
																bi.set_status(false);
																});
															readers.change_elem(check_number, [&issued_book](ReaderInfo& r) {
																r.take_book(issued_book);
																});
															break;
														}
													}
													break;
												}
												
											}
											case 2: //читатель пытается сдать книгу
											{
												current_reader.show_books_on_hand();
												Date issue_date;
												Book tmp;
												cout << "Необходимо ввести данные книги, которую Вы хотите вернуть." << endl;
												tmp.input_author_of_book();
												tmp.input_name_of_book();
												tmp.input_year_of_publication(); 
												tmp.input_publishing_house();
												while (!current_reader.has_chosen_book(tmp, issue_date))
												{
													cout << "Вы ошиблись! Такой книги у Bас нет!"
														<< "Проверьте корректность заданных значений." << endl;
													tmp.input_author_of_book();
													tmp.input_name_of_book();
													tmp.input_year_of_publication();
													tmp.input_publishing_house();
												}
												cout << "\nОтлично! Такая книга найдена в списке выданных Вам.\n";
												IssuedBook issued_book;
												issued_book.set_book(tmp);
												issued_book.set_issue_date(issue_date);
												return_book(current_reader, issued_book, book_records);
												books.change_elem([tmp](BookInfo& bi) {
													return bi.get_book() == tmp;
													}, 
													[](BookInfo& bi) {
													bi.set_status(true);
													});
												readers.change_elem(check_number, [&tmp](ReaderInfo& ri) {
													ri.return_book(tmp);
													});
												cout << "Книга успешно возвращена в библотеку!" << endl;
											}
											case 0:
											{
												break;
											}
											}
											readers.get_elem(check_number, current_reader);
										}
									}
									else
									{
										cout << "Читатель с заданным номером читательского билета не найден! Повторите ввод!" << endl;
									}
								}
							}
							break;
						}
						case 2: //режим работника библиотеки
						{
							int stop_item, cur_item = 1;
							while (cur_item != 0)
							{
								stop_item = print_librarian_menu();
								cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, stop_item);
								switch (cur_item)
								{
									case 1://редактирование списка читателей
									{
										int stop_item, cur_item = 1;
										while (cur_item != 0)
										{
												print_reader_list(readers, true);
												stop_item = print_editing_reader_list_menu(!readers.empty());
												cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!", 0, stop_item);
												switch (cur_item)
												{
												case 1://регистрация нового читателя
												{
													ReaderInfo reader, tmp;
													cout << "\nНужно ввести основные данные о новом читателе.\n";
													reader.get_reader().input_number_of_library_card();
													reader.get_reader().input_surname();													
													auto check_reader = [&reader](ReaderInfo& ri) {
														return (ri.get_reader().get_number_of_library_card() == reader.get_reader().get_number_of_library_card());
													};
													if (readers.get_elem(check_reader, tmp))
													{
														cout << "\nЧитатель с таким номер читательского билета уже есть в базе! Нужно сделать другой номер!" << endl;
													}
													else 
													{
														readers.add_elem(reader);
														cout << "\nНовый читатель успешно добавлен в базу!" << endl;
													}													
													break;
												}
												case 2://удаление читателя из базы
												{
													string s;
													cout << "\nВведите номер билета нужного читателя: ";
													int number;
													cin >> number;
													getline(cin, s);
													auto check_number = [number](ReaderInfo& r) {
														return r.get_reader().get_number_of_library_card() == number;
													};
													if (readers.delete_elem(check_number))
													{
														cout << "\nЧитатель успешно удалён из базы!" << endl;
													}
													else
													{
														cout << "\nОшибка! Читатель с заданным номером читательского билета не найден!\n" << endl;
													}
													break;
												}
												case 3://изменение данных о существующем читателе
												{
													string s;
													cout << "\nВведите номер билета нужного читателя: ";
													int number;
													cin >> number;
													getline(cin, s);
													auto check_number = [&number](ReaderInfo& r) {
														return r.get_reader().get_number_of_library_card() == number;
													};
													ReaderInfo tmp;
													if (readers.get_elem(check_number, tmp))
													{
														int cur_change_item = 1;
														while (cur_change_item != 0)
														{
															int tmp_int;
															string tmp_str;
															print_change_reader_menu();
															cur_change_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!", 0, 2);
															if (cur_change_item != 0)
															{
																cout << endl << "Введите новое значение для выбранного пункта: ";
																switch (cur_change_item)
																{
																case 1: //изменение номера читательского билета читателя
																{
																	cin >> tmp_int;
																	getline(cin, tmp_str);
																	readers.change_elem(check_number, [tmp_int](ReaderInfo& r) {
																		(r.get_reader()).set_number_of_library_card(tmp_int);
																		});
																	number = tmp_int;
																	break;
																}
																case 2://изменение фамилии читателя
																{
																	getline(cin, tmp_str);
																	readers.change_elem(check_number, [tmp_str](ReaderInfo& r) {
																		(r.get_reader()).set_surname(tmp_str);
																		});
																	break;
																}
																}
															}
														}
													}
													else
													{
														cout << "\nОшибка! Читатель с заданным номером читательского билета не найден!\n" << endl;
													}
													break;
												}
												case 0:
												{
													break;
												}
												}
											
										}
										break;
									}
								case 2://редактирование списка книг
								{
									int stop_item, cur_item = 1;
									while (cur_item != 0)
									{
										if (books.empty())
										{
											cout << endl << "В библиотеке не найдено ни одной книги." << endl;
										}
										else
										{
											cout << endl << "Список книг в библиотеке:" << endl;
											books.for_each(BookInfo::get_print_func(false));
										}										
										stop_item = print_editing_book_list_menu(!books.empty());
										cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!", 0, stop_item);
										switch (cur_item)
										{
										case 1: //добавление новой книги в библиотеку
										{
											Book book;
											cout << "\nНужно ввести основные данные о новой книге.\n";
											book.input_author_of_book();
											book.input_name_of_book();
											book.input_year_of_publication();
											book.input_publishing_house();
											BookInfo book_info(book);
											books.add_elem(book_info);
											cout << "\nНовая книга успешно добавлена в базу!\n" << endl;
											break;
										}
										case 2://удаление книги из базы библиотеки
										{
											cout << "\nВведите автора нужной книги: ";
											string author;
											getline(cin, author);
											cout << "Введите название нужной книги: ";
											string name_book;
											getline(cin, name_book);
											auto check_book = [&author, &name_book](BookInfo& book) {
												return book.get_book().get_author_of_book() == author &&
													book.get_book().get_name_of_book() == name_book;
											};
											if (books.delete_elem(check_book))
											{
												cout << "\nКнига успешно удалена из базы!\n" << endl;
											}
											else
											{
												cout << "\nОшибка! Книга с такими названием и автором не найдена!\n" << endl;
											}
											break;
										}
										case 3:// изменение информации о существующей книге в библиотеке
										{
											cout << "\nВведите автора нужной книги: ";
											string author;
											getline(cin, author);
											cout << "Введите название нужной книги: ";
											string name_book;
											getline(cin, name_book);
											auto check_book = [author, name_book](BookInfo& book) {
												return book.get_book().get_author_of_book() == author &&
													book.get_book().get_name_of_book() == name_book;
											};
											BookInfo tmp;
											if (books.get_elem(check_book, tmp))
											{
												int cur_change_item = 1;
												while (cur_change_item != 0)
												{
													int tmp_int;
													string tmp_str;
													print_change_book_menu();
													cur_change_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, 4);
													if (cur_change_item != 0)
													{
														cout << endl << "Введите новое значение для выбранного пункта: ";
														switch (cur_change_item)
														{
														case 1: //изменение автора книги
														{
															getline(cin, tmp_str);
															tmp.get_book().set_author_of_book(tmp_str);
															break;
														}
														case 2://изменение названия книги
														{
															getline(cin, tmp_str);
															tmp.get_book().set_name_of_book(tmp_str);
															break;
														}
														case 3://изменения года публикации книги
														{
															cin >> tmp_int;
															getline(cin, tmp_str);
															tmp.get_book().set_year_of_publication(tmp_int);
															break;
														}
														case 4://изменение названия издательства книги
														{
															getline(cin, tmp_str);
															tmp.get_book().set_publishing_house(tmp_str);
															break;
														}
														}
													}
												}
												books.change_elem(check_book, [&tmp](BookInfo& bi) {
													bi.get_book().set_author_of_book(tmp.get_book().get_author_of_book());
													bi.get_book().set_name_of_book(tmp.get_book().get_name_of_book());
													bi.get_book().set_year_of_publication(tmp.get_book().get_year_of_publication());
													bi.get_book().set_publishing_house(tmp.get_book().get_publishing_house());
													});												
											}
											else
											{
												cout << "\nОшибка! Книга с такими названием и автором не найдена!\n" << endl;
											}
											break;
										}
										case 0:
										{
											break;
										}
										}
									}
									break;
								}
								case 3://просмотр истории выдачии книг на руки
								{
									if (book_records.empty())
									{
										cout << "История выдачи книг на руки отсутствует!" << endl;
										break;
									}
									else
									{
										DataController<BookRecord> records;
										int num_sort_field = 1;
										BookRecord filter_elem;
										const int size_filters = 8;
										bool filter_fields[size_filters];
										init_filter_fields(filter_fields, size_filters);
										auto filter = [&filter_fields, &filter_elem, size_filters](BookRecord& bookrecord) {
											bool result = true;
											if (filter_fields[0])
											{
												result = result && filter_elem.get_reader().get_number_of_library_card() == bookrecord.get_reader().get_number_of_library_card();
											}
											if (filter_fields[1])
											{
												result = result && filter_elem.get_reader().get_surname() == bookrecord.get_reader().get_surname();
											}
											if (filter_fields[2])
											{
												result = result && filter_elem.get_issued_book().get_issue_date() == bookrecord.get_issued_book().get_issue_date();
											}
											if (filter_fields[3])
											{
												result = result && filter_elem.get_return_date() == bookrecord.get_return_date();
											}
											if (filter_fields[4])
											{
												result = result && filter_elem.get_issued_book().get_book().get_author_of_book() == bookrecord.get_issued_book().get_book().get_author_of_book();
											}
											if (filter_fields[5])
											{
												result = result && filter_elem.get_issued_book().get_book().get_name_of_book() == bookrecord.get_issued_book().get_book().get_name_of_book();
											}
											if (filter_fields[6])
											{
												result = result && filter_elem.get_issued_book().get_book().get_year_of_publication() == bookrecord.get_issued_book().get_book().get_year_of_publication();
											}
											if (filter_fields[7])
											{
												result = result && filter_elem.get_issued_book().get_book().get_publishing_house() == bookrecord.get_issued_book().get_book().get_publishing_house();
											}
											return result;
										};
										int cur_item = 1;
										while (cur_item != 0)
										{
											records.clear();
											records.set_elems(book_records.linear_search_elements(filter));
											records.sort(BookRecord::get_compare_func_by_num(num_sort_field));
											if (records.empty())
											{
												cout << "По заданной фильтрации не найдени ни одной записи о выдаче книги.\n\n";
											}
											else
											{
												cout << endl << "История выдачи книг на руки:" << endl;
												records.for_each(BookRecord::get_print_func());
											}											
											if (!check_true_selected_fields(filter_fields, size_filters))
											{
												cout << "Фильтрация отсутствует." << endl;
											}
											else
											{
												cout << "Фильтры:" << endl;
												for (int i = 0; i < size_filters; i++)
												{
													if (filter_fields[i])
													{
														filter_elem.print_field_by_num(i + 1);
													}
												}
											}
											BookRecord::print_name_sort_field(num_sort_field);
											print_display_setting();
											cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, 2);
											switch (cur_item)
											{
											case 1: //изменение параметров просмотра истории выдачи
											{												
												int cur_item = 1;
												while (cur_item != 0)
												{
													print_filters(check_true_selected_fields(filter_fields, size_filters));
													cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, 2);
													switch (cur_item)
													{
													case 1://добавление или изменение фильтра
													{
														int num_new_filter = BookRecord::get_num_selected_field("\nДля какого поля добавить/изменить фильтр?\n");
														filter_fields[num_new_filter - 1] = true;
														filter_elem.input_field_by_num(num_new_filter);
														cout << "\nФильтр успешно добавлен/изменён!" << endl;
														break;
													}
													case 2://удаление существующего фильтра
													{
														auto print = [&filter_fields]() {
															int stop_item = 0;
															cout << "\nВыберите номер фильтра, который хотите удалить:" << endl
																<< "0 - назад" << endl;
															print_item_with_check(filter_fields[0], stop_item, " - номер читательского билета\n");
															print_item_with_check(filter_fields[1], stop_item, " - фамилия читателя\n");
															print_item_with_check(filter_fields[2], stop_item, " - дата выдачи\n");
															print_item_with_check(filter_fields[3], stop_item, " - дата возврата\n");
															print_item_with_check(filter_fields[4], stop_item, " - автор книги\n");
															print_item_with_check(filter_fields[5], stop_item, " - название книги\n");
															print_item_with_check(filter_fields[6], stop_item, " - год издательства\n");
															print_item_with_check(filter_fields[7], stop_item, " - издательство\n");
															return stop_item;
														};
														delete_filters(filter_fields, size_filters, print);
														break;
													}
													case 0:
													{
														break;
													}
													}
												}
												break;
											}
											case 2://изменение поля, по которому происходит сортировка записей
											{
												num_sort_field = BookRecord::get_num_selected_field("\nПо какому полю выполнить сортировку записей?\n");
												break;
											}
											case 0:
											{
												break;
											}
											}
										}
										break;
									}
								}
								case 4://просмотр всех книг в библиотеке с их текущим статусом
								{
									if (books.empty())
									{
										cout << "Не найдено ни одной книги!\n" << endl;
										break;
									}
									else
									{
										DataController<BookInfo> filtered_books;
										int num_sort_field = 1;
										BookInfo filter_elem;
										const int size_filters = 5;
										bool filter_fields[size_filters];
										init_filter_fields(filter_fields, size_filters);
										auto filter = [&filter_fields, &filter_elem, size_filters](BookInfo& book) {
											bool result = true;
											if (filter_fields[0])
											{
												result = result && filter_elem.get_book().get_author_of_book() == book.get_book().get_author_of_book();
											}
											if (filter_fields[1])
											{
												result = result && filter_elem.get_book().get_name_of_book() == book.get_book().get_name_of_book();
											}
											if (filter_fields[2])
											{
												result = result && filter_elem.get_book().get_year_of_publication() == book.get_book().get_year_of_publication();
											}
											if (filter_fields[3])
											{
												result = result && filter_elem.get_book().get_publishing_house() == book.get_book().get_publishing_house();
											}
											if (filter_fields[4])
											{
												result = result && filter_elem.get_status() == book.get_status();
											}
											return result;
										};
										int cur_item = 1;
										while (cur_item != 0)
										{
											filtered_books.clear();
											filtered_books.set_elems(books.linear_search_elements(filter));
											filtered_books.sort(BookInfo::get_compare_func_by_num(num_sort_field));
											if (filtered_books.empty())
											{
												cout << "По заданным фильтрации не найдено ни одной книги.\n\n";
											}
											else
											{
												cout << endl << "Список книг с их текущим статусом:" << endl;
												filtered_books.for_each(BookInfo::get_print_func(true));
											}											
											if (!check_true_selected_fields(filter_fields, size_filters))
											{
												cout << "Фильтрация отсутствует." << endl;
											}
											else
											{
												cout << "Фильтры:" << endl;
												for (int i = 0; i < size_filters; i++)
												{
													if (filter_fields[i])
													{
														filter_elem.print_field_by_num(i + 1);
													}
												}
											}
											BookInfo::print_name_sort_field(num_sort_field);
											print_display_setting();
											cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, 2);
											switch (cur_item)
											{
											case 1://изменение параметров просмотра списка книг
											{
												int cur_item = 1;
												while (cur_item != 0)
												{
													print_filters(check_true_selected_fields(filter_fields, size_filters));
													cur_item = get_num("Ваш выбор - ", "Ошибка! Такой пункт отсутствует в меню. Повторите ввод!\n", 0, 2);
													switch (cur_item)
													{
													case 1://добавление или изменение фильтра
													{
														int num_new_filter = BookInfo::get_num_selected_field("\nДля какого поля добавить/изменить фильтр?\n", false);
														filter_fields[num_new_filter - 1] = true;
														filter_elem.input_field_by_num(num_new_filter);
														cout << "\nФильтр успешно добавлен/изменён!" << endl;
														break;
													}
													case 2://удаление существующего фильтра
													{
														auto print = [&filter_fields]() {
															int stop_item = 0;
															cout << "\nВыберите номер фильтра, который хотите удалить:" << endl
																<< "0 - назад" << endl;
															print_item_with_check(filter_fields[0], stop_item, " - автор книги\n");
															print_item_with_check(filter_fields[1], stop_item, " - название книги\n");
															print_item_with_check(filter_fields[2], stop_item, " - год издательства\n");
															print_item_with_check(filter_fields[3], stop_item, " - издательство\n");
															print_item_with_check(filter_fields[4], stop_item, " - статус книги\n");
															return stop_item;
														};
														delete_filters(filter_fields, size_filters, print);
														break;
													}
													case 0:
													{
														break;
													}
													}
												}
												break;
											}
											case 2://изменение поля, по которому происходит сортировка списка книг
											{
												num_sort_field = BookInfo::get_num_selected_field("\nПо какому полю выполнить сортировку книг?\n", true);
												break;
											}
											case 0:
											{
												break;
											}
											}
										}
										break;
									}
								}
								case 0:
								{
									break;
								}
								}
							}
							break;
						}
						case 0:
						{
							break;
						}
					}
				}
				//выгрузка всех данных в соответствующие текстовые файлы для хранения информации о работе библиотеки
				//после завершения работы приложения
				ofstream out_base_books(BOOK_BASE, ios_base::out | ios_base::trunc); 
				ofstream out_base_readers(READER_BASE, ios_base::out | ios_base::trunc);
				ofstream out_base_book_records(BOOKRECORD_BASE, ios_base::out | ios_base::trunc);
				books.fill_file_from_container(out_base_books);
				readers.fill_file_from_container(out_base_readers);
				book_records.fill_file_from_container(out_base_book_records);
				out_base_books.close();
				out_base_readers.close();
				out_base_book_records.close();
			}
		}
	}	
}
