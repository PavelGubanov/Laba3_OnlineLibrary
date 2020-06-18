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

// ������ ������� ����� ������ �� �������
void get_eoln()
{
	do
	{

	} while (getchar() != '\n');
}

//���� ����� � ����������� ��������� ��� �� �������������� ������� [min, max]
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

//���� ������ �� �������
string get_string(string& text)
{
	cout << text;
	string result_string;
	getline(cin, result_string);
	return result_string;
}

//������ ������� �������� ����
int print_main_menu() 
{
	cout << "\n�������� ����� ������ ���������:" << "\n"
		<< "0 - �����" << "\n"
		<< "1 - ��������" << "\n"
		<< "2 - ������������" << "\n";
	return 2;
}

//������ ������� ���� ��� ��������
int print_reader_menu(bool has_books)
{
	int stop_item = 1;
	cout << "\n�������� ���� �� ��������� ��������:" << "\n"
		<< "0 - ��������� � ������� ����" << "\n"
		<< "1 - ����� �����" << "\n";
	if (has_books) 
	{
		stop_item = 2;
		cout << "2 - ����� �����" << "\n";
	}		
	return stop_item;
}

//������ ������� ���� ��� ������������
int print_librarian_menu()
{
	cout << "\n�������� ���� �� ��������� ��������:" << "\n"
		<< "0 - ��������� � ������� ����" << "\n"
		<< "1 - ������������� ������ ���������" << "\n"
		<< "2 - ������������� ������ ����" << "\n"
		<< "3 - ����������� ������� ������ ���� �� ����" << "\n"
		<< "4 - ����������� ������ ���� � ������� ��������" << "\n";
	return 4;
}

//������ ���� ��� �������������� ������ ���������
int print_editing_reader_list_menu(bool are_any_readers = true)
{
	int stop_item = 1;
	cout << "\n�������� ���� �� ��������� ��������:" << "\n"
		<< "0 - ��������� �����" << "\n"
		<< "1 - ����������������� ������ ��������" << "\n";
	if (are_any_readers)
	{
		stop_item = 3;
		cout << "2 - ������� �������� �� ����" << "\n"
			<< "3 - ������������� ���������� � ��������" << "\n";
	}		
	return stop_item;
}

//������ ���� ��� �������������� ������ ����
int print_editing_book_list_menu(bool are_any_books)
{
	int stop_item = 1;
	cout << "\n�������� ���� �� ��������� ��������:" << "\n"
		<< "0 - ��������� �����" << "\n"
		<< "1 - ����������������� ����� �����" << "\n";
	if (are_any_books)
	{
		cout << "2 - ������� ����� �� ����" << "\n"
			<< "3 - ������������� ���������� � �����" << "\n";
		stop_item = 3;
	}		
	return stop_item;
}

//������ ���� ��� ��������� ���������� � ��������
int print_change_reader_menu()
{
	cout << endl
		<< "�������� ���� �� ������� ������ � ��������, ������� ���������� ��������:" << "\n"
		<< "0 - ������ �� ����� ��������" << "\n"
		<< "1 - ����� ������������� ������" << "\n"
		<< "2 - ������� ��������" << "\n"
		<< endl;
	return 2;
}

//������ ���� ��� ��������� ���������� � �����
int print_change_book_menu()
{
	cout << endl
		<< "�������� ���� �� ������� ������ � �����, ������� ���������� ��������:" << "\n"
		<< "0 - ������ �� ����� ��������" << "\n"
		<< "1 - ����� �����" << "\n"
		<< "2 - �������� �����" << "\n"
		<< "3 - ��� ������������" << "\n"
		<< "4 - �������� ������������" << "\n"
		<< endl;
	return 4;
}

//������ ���� ��� �������������� ������ ��������
int print_change_filters_menu(bool elem_has_filters)
{
	int stop_item = 1;
	cout << endl
		<< "0 - �����" << "\n"
		<< "1 - ��������/�������� ������" << "\n";
	if (elem_has_filters)
	{
		cout << "2 - ������� ������" << "\n"
			<< endl;
		stop_item = 2;
	}
	return stop_item;
}

//������ ���� ��� �������� ��������� ������ ������
int print_display_setting()
{
	cout << endl
		<< "0 - ��������� � ���� ��������� ����������" << "\n"
		<< "1 - �������� ��������� ����������" << "\n"
		<< "2 - ��������� ����������" << "\n"
		<< endl;
	return 2;
}

//������ ���� ��� ������ � ���������
int print_filters(bool mayDeleteFilter) 
{
	int stop_item = 1;
	cout << endl << "�������� ���� �� ��������� �������� � ���������:" << endl
		<< "0 - �����" << "\n"
		<< "1 - ��������/�������� ������" << "\n";
	if (mayDeleteFilter)
	{
		cout << "2 - ������� ������" << "\n" << endl;
		stop_item = 2;
	}		
	return stop_item;
}

//������ ������ ���������
void print_reader_list(DataController<ReaderInfo>& readers, bool need_check)
{
	if (need_check && readers.empty())
	{
		cout << endl << "�� ������ ������������������� �������� �� �������!\n" << endl;
	}
	else if(!readers.empty())
	{
		cout << endl << "������ ������������������ ���������:" << endl;
		auto print = [](ReaderInfo& reader) -> void
		{
			cout << reader.get_reader().get_number_of_library_card()
				<< " - " << reader.get_reader().get_surname() << endl;
		};
		readers.for_each(print);
	}
}

//������������� ���������� ������� ��� �������� ��������
void init_filter_fields(bool* filters, int size)
{
	for (int i = 0; i < size; i++)
	{
		filters[i] = false;
	}
}

//����������� ����� � ����������
void return_book(ReaderInfo& reader, IssuedBook& tmp, DataController<BookRecord>& book_records)
{
	Date return_date;
	cout << "������� ���� ����� �����: ";
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

//������ �������� ������ � ��������� ��� �����������
void print_item_with_check(bool check, int& item, const string& str)
{
	if (check)
	{
		item++;
		cout << item << str;		
	}
}

//������ ���� ��� ���������� ��������� ������ ����� � ����������
int print_find_book_menu(bool *fields, int size, int& start_item) 
{
	start_item = check_true_selected_fields(fields, size) ? 0 : 1;
	int stop_item = 0;
	cout << "\n�������� �������� ��� ������ �����:" << endl;
	if (!start_item)
	{
		cout << "0 - �� ��������� ��������" << endl;
	}
	print_item_with_check(!fields[0], stop_item, " - ����� �����\n");
	print_item_with_check(!fields[1], stop_item, " - ��������\n");
	print_item_with_check(!fields[2], stop_item, " - ��� ������������\n");
	print_item_with_check(!fields[3], stop_item, " - ������������\n");
	return stop_item;	
}

//���������� ��������� ������ �����
void add_fields_for_search(bool *fields, int size, BookInfo& b) 
{	
	int start_item, stop_item, cur_item = 1;
	while (cur_item != 0)
	{
		stop_item = print_find_book_menu(fields, size, start_item);
		cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", start_item, stop_item);
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

//�������� �������� ��� ����������� ������ ���������
void delete_filters(bool* filters, int size, function<int()> print_menu)
{
	int stop_item, cur_item = 1;
	while (cur_item != 0)
	{
		stop_item = print_menu();
		cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, stop_item);
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
	cout << "������ ��������� ������������� ������� ������ ����������� ����������." << endl;
	DataController<ReaderInfo> readers;
	DataController<BookInfo> books;
	DataController<BookRecord> book_records;
	ifstream from_base_readers(READER_BASE);
	ifstream from_base_books(BOOK_BASE);
	ifstream from_base_bookrecords(BOOKRECORD_BASE);
	if (!from_base_readers.is_open())
	{
		cout << endl << "�� ������ ����� ���� � ����� ��������� - readers.txt! ��������� �������� ������� � ���� � ������������� ����������!" << endl;
	}
	else
	{
		if (!from_base_books.is_open())
		{
			from_base_readers.close();
			cout << endl << "�� ������ ����� ���� � ����� ���� - books.txt! ��������� �������� ������� � ���� � ������������� ����������!" << endl;
		}
		else
		{			
			if (!from_base_bookrecords.is_open())
			{
				from_base_readers.close();
				from_base_books.close();
				cout << endl << "�� ������ ����� ���� � �������� ������ ���� �� ���� - bookrecords.txt! ��������� �������� ������� � ���� � ������������� ����������!" << endl;
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
					cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, stop_item);
					switch (cur_item)
					{
						case 1: //����� ��������
						{
							if (readers.empty())
							{
								cout << endl << "�� ������� �� ������ ��������!" << endl
									<< "��������� ��������� ���������� ���������������� ���!" << endl;
								break;
							}
							else
							{
								bool log_in_reader = false;
								while (!log_in_reader)
								{
									print_reader_list(readers, false);
									cout << "\n������� ��� ����� ������������� ������: ";
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
											cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, stop_item);
											switch (cur_item)
											{
											case 1: //�������� �������� ����� �����
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
													cout << "�����, ������� B�� ����������, ����������� � ����� ����������." << endl;
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
																int ans_num = get_num("������ ����� ��������� � ���.\n������ ����� �?\n1 - ��\n2 - ���\n��� ����� - ", "������! ������������ ������� ������! ��������� ����!\n", 1, 2);
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
																	cout << "����� ������� ���������� � ���������!" << endl;
																}																
															}
															else
															{
																cout << "�����, ������� ��� ����������, ��������� � ������� ��������.\n"
																	<< "�������� ������ �����." << endl;
															}
															break;
														}
														case book_status::is_available:
														{
															cout << "����� �� ������ ������� �������!\n\n";
															Date issue_date;
															cout << "������� ���� ������ �����: ";
															cin >> issue_date;
															cout << "\n����� � ����� ������������. ��������� ���������!" << endl;
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
											case 2: //�������� �������� ����� �����
											{
												current_reader.show_books_on_hand();
												Date issue_date;
												Book tmp;
												cout << "���������� ������ ������ �����, ������� �� ������ �������." << endl;
												tmp.input_author_of_book();
												tmp.input_name_of_book();
												tmp.input_year_of_publication(); 
												tmp.input_publishing_house();
												while (!current_reader.has_chosen_book(tmp, issue_date))
												{
													cout << "�� ��������! ����� ����� � B�� ���!"
														<< "��������� ������������ �������� ��������." << endl;
													tmp.input_author_of_book();
													tmp.input_name_of_book();
													tmp.input_year_of_publication();
													tmp.input_publishing_house();
												}
												cout << "\n�������! ����� ����� ������� � ������ �������� ���.\n";
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
												cout << "����� ������� ���������� � ���������!" << endl;
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
										cout << "�������� � �������� ������� ������������� ������ �� ������! ��������� ����!" << endl;
									}
								}
							}
							break;
						}
						case 2: //����� ��������� ����������
						{
							int stop_item, cur_item = 1;
							while (cur_item != 0)
							{
								stop_item = print_librarian_menu();
								cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, stop_item);
								switch (cur_item)
								{
									case 1://�������������� ������ ���������
									{
										int stop_item, cur_item = 1;
										while (cur_item != 0)
										{
												print_reader_list(readers, true);
												stop_item = print_editing_reader_list_menu(!readers.empty());
												cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!", 0, stop_item);
												switch (cur_item)
												{
												case 1://����������� ������ ��������
												{
													ReaderInfo reader, tmp;
													cout << "\n����� ������ �������� ������ � ����� ��������.\n";
													reader.get_reader().input_number_of_library_card();
													reader.get_reader().input_surname();													
													auto check_reader = [&reader](ReaderInfo& ri) {
														return (ri.get_reader().get_number_of_library_card() == reader.get_reader().get_number_of_library_card());
													};
													if (readers.get_elem(check_reader, tmp))
													{
														cout << "\n�������� � ����� ����� ������������� ������ ��� ���� � ����! ����� ������� ������ �����!" << endl;
													}
													else 
													{
														readers.add_elem(reader);
														cout << "\n����� �������� ������� �������� � ����!" << endl;
													}													
													break;
												}
												case 2://�������� �������� �� ����
												{
													string s;
													cout << "\n������� ����� ������ ������� ��������: ";
													int number;
													cin >> number;
													getline(cin, s);
													auto check_number = [number](ReaderInfo& r) {
														return r.get_reader().get_number_of_library_card() == number;
													};
													if (readers.delete_elem(check_number))
													{
														cout << "\n�������� ������� ����� �� ����!" << endl;
													}
													else
													{
														cout << "\n������! �������� � �������� ������� ������������� ������ �� ������!\n" << endl;
													}
													break;
												}
												case 3://��������� ������ � ������������ ��������
												{
													string s;
													cout << "\n������� ����� ������ ������� ��������: ";
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
															cur_change_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!", 0, 2);
															if (cur_change_item != 0)
															{
																cout << endl << "������� ����� �������� ��� ���������� ������: ";
																switch (cur_change_item)
																{
																case 1: //��������� ������ ������������� ������ ��������
																{
																	cin >> tmp_int;
																	getline(cin, tmp_str);
																	readers.change_elem(check_number, [tmp_int](ReaderInfo& r) {
																		(r.get_reader()).set_number_of_library_card(tmp_int);
																		});
																	number = tmp_int;
																	break;
																}
																case 2://��������� ������� ��������
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
														cout << "\n������! �������� � �������� ������� ������������� ������ �� ������!\n" << endl;
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
								case 2://�������������� ������ ����
								{
									int stop_item, cur_item = 1;
									while (cur_item != 0)
									{
										if (books.empty())
										{
											cout << endl << "� ���������� �� ������� �� ����� �����." << endl;
										}
										else
										{
											cout << endl << "������ ���� � ����������:" << endl;
											books.for_each(BookInfo::get_print_func(false));
										}										
										stop_item = print_editing_book_list_menu(!books.empty());
										cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!", 0, stop_item);
										switch (cur_item)
										{
										case 1: //���������� ����� ����� � ����������
										{
											Book book;
											cout << "\n����� ������ �������� ������ � ����� �����.\n";
											book.input_author_of_book();
											book.input_name_of_book();
											book.input_year_of_publication();
											book.input_publishing_house();
											BookInfo book_info(book);
											books.add_elem(book_info);
											cout << "\n����� ����� ������� ��������� � ����!\n" << endl;
											break;
										}
										case 2://�������� ����� �� ���� ����������
										{
											cout << "\n������� ������ ������ �����: ";
											string author;
											getline(cin, author);
											cout << "������� �������� ������ �����: ";
											string name_book;
											getline(cin, name_book);
											auto check_book = [&author, &name_book](BookInfo& book) {
												return book.get_book().get_author_of_book() == author &&
													book.get_book().get_name_of_book() == name_book;
											};
											if (books.delete_elem(check_book))
											{
												cout << "\n����� ������� ������� �� ����!\n" << endl;
											}
											else
											{
												cout << "\n������! ����� � ������ ��������� � ������� �� �������!\n" << endl;
											}
											break;
										}
										case 3:// ��������� ���������� � ������������ ����� � ����������
										{
											cout << "\n������� ������ ������ �����: ";
											string author;
											getline(cin, author);
											cout << "������� �������� ������ �����: ";
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
													cur_change_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, 4);
													if (cur_change_item != 0)
													{
														cout << endl << "������� ����� �������� ��� ���������� ������: ";
														switch (cur_change_item)
														{
														case 1: //��������� ������ �����
														{
															getline(cin, tmp_str);
															tmp.get_book().set_author_of_book(tmp_str);
															break;
														}
														case 2://��������� �������� �����
														{
															getline(cin, tmp_str);
															tmp.get_book().set_name_of_book(tmp_str);
															break;
														}
														case 3://��������� ���� ���������� �����
														{
															cin >> tmp_int;
															getline(cin, tmp_str);
															tmp.get_book().set_year_of_publication(tmp_int);
															break;
														}
														case 4://��������� �������� ������������ �����
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
												cout << "\n������! ����� � ������ ��������� � ������� �� �������!\n" << endl;
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
								case 3://�������� ������� ������� ���� �� ����
								{
									if (book_records.empty())
									{
										cout << "������� ������ ���� �� ���� �����������!" << endl;
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
												cout << "�� �������� ���������� �� ������� �� ����� ������ � ������ �����.\n\n";
											}
											else
											{
												cout << endl << "������� ������ ���� �� ����:" << endl;
												records.for_each(BookRecord::get_print_func());
											}											
											if (!check_true_selected_fields(filter_fields, size_filters))
											{
												cout << "���������� �����������." << endl;
											}
											else
											{
												cout << "�������:" << endl;
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
											cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, 2);
											switch (cur_item)
											{
											case 1: //��������� ���������� ��������� ������� ������
											{												
												int cur_item = 1;
												while (cur_item != 0)
												{
													print_filters(check_true_selected_fields(filter_fields, size_filters));
													cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, 2);
													switch (cur_item)
													{
													case 1://���������� ��� ��������� �������
													{
														int num_new_filter = BookRecord::get_num_selected_field("\n��� ������ ���� ��������/�������� ������?\n");
														filter_fields[num_new_filter - 1] = true;
														filter_elem.input_field_by_num(num_new_filter);
														cout << "\n������ ������� ��������/������!" << endl;
														break;
													}
													case 2://�������� ������������� �������
													{
														auto print = [&filter_fields]() {
															int stop_item = 0;
															cout << "\n�������� ����� �������, ������� ������ �������:" << endl
																<< "0 - �����" << endl;
															print_item_with_check(filter_fields[0], stop_item, " - ����� ������������� ������\n");
															print_item_with_check(filter_fields[1], stop_item, " - ������� ��������\n");
															print_item_with_check(filter_fields[2], stop_item, " - ���� ������\n");
															print_item_with_check(filter_fields[3], stop_item, " - ���� ��������\n");
															print_item_with_check(filter_fields[4], stop_item, " - ����� �����\n");
															print_item_with_check(filter_fields[5], stop_item, " - �������� �����\n");
															print_item_with_check(filter_fields[6], stop_item, " - ��� ������������\n");
															print_item_with_check(filter_fields[7], stop_item, " - ������������\n");
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
											case 2://��������� ����, �� �������� ���������� ���������� �������
											{
												num_sort_field = BookRecord::get_num_selected_field("\n�� ������ ���� ��������� ���������� �������?\n");
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
								case 4://�������� ���� ���� � ���������� � �� ������� ��������
								{
									if (books.empty())
									{
										cout << "�� ������� �� ����� �����!\n" << endl;
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
												cout << "�� �������� ���������� �� ������� �� ����� �����.\n\n";
											}
											else
											{
												cout << endl << "������ ���� � �� ������� ��������:" << endl;
												filtered_books.for_each(BookInfo::get_print_func(true));
											}											
											if (!check_true_selected_fields(filter_fields, size_filters))
											{
												cout << "���������� �����������." << endl;
											}
											else
											{
												cout << "�������:" << endl;
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
											cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, 2);
											switch (cur_item)
											{
											case 1://��������� ���������� ��������� ������ ����
											{
												int cur_item = 1;
												while (cur_item != 0)
												{
													print_filters(check_true_selected_fields(filter_fields, size_filters));
													cur_item = get_num("��� ����� - ", "������! ����� ����� ����������� � ����. ��������� ����!\n", 0, 2);
													switch (cur_item)
													{
													case 1://���������� ��� ��������� �������
													{
														int num_new_filter = BookInfo::get_num_selected_field("\n��� ������ ���� ��������/�������� ������?\n", false);
														filter_fields[num_new_filter - 1] = true;
														filter_elem.input_field_by_num(num_new_filter);
														cout << "\n������ ������� ��������/������!" << endl;
														break;
													}
													case 2://�������� ������������� �������
													{
														auto print = [&filter_fields]() {
															int stop_item = 0;
															cout << "\n�������� ����� �������, ������� ������ �������:" << endl
																<< "0 - �����" << endl;
															print_item_with_check(filter_fields[0], stop_item, " - ����� �����\n");
															print_item_with_check(filter_fields[1], stop_item, " - �������� �����\n");
															print_item_with_check(filter_fields[2], stop_item, " - ��� ������������\n");
															print_item_with_check(filter_fields[3], stop_item, " - ������������\n");
															print_item_with_check(filter_fields[4], stop_item, " - ������ �����\n");
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
											case 2://��������� ����, �� �������� ���������� ���������� ������ ����
											{
												num_sort_field = BookInfo::get_num_selected_field("\n�� ������ ���� ��������� ���������� ����?\n", true);
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
				//�������� ���� ������ � ��������������� ��������� ����� ��� �������� ���������� � ������ ����������
				//����� ���������� ������ ����������
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
