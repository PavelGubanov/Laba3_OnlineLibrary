#pragma once
#include "Book.h"
#include "Date.h"
#include <string>
#include <list>

using namespace std;

class Reader //��������
{
private:
	int number_of_library_card; // ����� ������������� ������
	string surname; // ������� ��������
public:
	int get_number_of_library_card() const;
	string get_surname() const;

	void set_number_of_library_card(const int number);
	void set_surname(const string& surname);

	void input_number_of_library_card();
	void input_surname();

	friend ostream& operator<< (ostream& out, const Reader& reader);
	friend istream& operator>> (istream& in, Reader& reader);
};

class ReaderInfo //�������������� ������ � �������� � ���������� � ��������� ���� �������� ��� ����
{
private:
	Reader reader; // ��������
	list<IssuedBook> books_on_hand; // ������ ����, ������� ��������� � ��������
public:
	Reader& get_reader();
	void set_reader(const Reader& reader);

	void take_book(const IssuedBook& issued_book); //����� �����
	bool has_chosen_book(Book& book, Date& issue_date); //��������� ������� ��������� ����� � ��������
	void show_books_on_hand(); //���������� ������������ ��� �����, ������� �� ���� � �� ������
	int get_count_books_on_hand(); //�������� ���������� ���� �� ����� � ��������
	void return_book(Book& book); //������� ����� � ����������
	bool has_books_on_hand(); //������, ���� �� ����� � �������� �� �����

	friend ostream& operator<< (ostream& out, const ReaderInfo& reader_info);
	friend istream& operator>> (istream& in, ReaderInfo& reader_info);
};

