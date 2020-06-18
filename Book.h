#pragma once
#include "Date.h"
#include <vector>
#include <list>
#include <string>
#include <functional>

using namespace std;

enum class book_status //������ �����
{
	is_available, //����� ��������
	is_issued // ����� ������		
};

ostream& operator<< (ostream& out, const book_status& status);
istream& operator>> (istream& in, book_status& status);

class Book //�����
{
private:
	string author_of_book; // ����� �����
	string name_of_book; // ��������
	int year_of_publication; // ��� ������������
	string publishing_house; // ������������
public:
	string get_author_of_book() const;
	string get_name_of_book() const;
	int get_year_of_publication() const;
	string get_publishing_house() const;

	void set_author_of_book(const string& author);
	void set_name_of_book(const string& name);
	void set_year_of_publication(const int year);
	void set_publishing_house(const string& house);

	void input_author_of_book();
	void input_name_of_book();
	void input_year_of_publication();
	void input_publishing_house();	

	friend bool operator== (const Book& book1, const Book& book2);
	friend bool operator!= (const Book& book1, const Book& book2);
	friend ostream& operator<< (ostream& out, const Book& book);
	friend istream& operator>> (istream& in, Book& book);
};

class BookInfo //�������������� ������ � ����� � ����������
{
private:
	Book book; // �����
	book_status status; // ������� ������ �����
public:
	BookInfo(const Book& book);
	BookInfo();

	Book& get_book();
	book_status get_status() const;

	void set_book(const Book& book);
	void set_status(const bool status);

	void input_field_by_num(int n);
	void print_field_by_num(int n);
	static function<void(BookInfo&)> get_print_func(bool status); //��������������� ������ ������
	static function<bool(BookInfo&, BookInfo&)> get_compare_func_by_num(int n); //���������� ���������� �� ������ ����
	static void print_name_sort_field(int n); //�������� �������� ���� ��� ���������� �� ��� ������
	static int get_num_selected_field(const string& name, bool canBack = false); //������� ������ ���� ������ ��� ������-���� ��������

	void input_status();
	friend ostream& operator<< (ostream& out, const BookInfo& book);
	friend istream& operator>> (istream& in, BookInfo& book);
};

class IssuedBook //�������������� ������ � �����, ������ ��������� �� ���� � ����� ������
{
private:
	Date issue_date; // ���� ������ �����
	Book book; // �����	
public:
	Book& get_book();
	Date get_issue_date() const;

	void set_book(const Book& book);
	void set_issue_date(const Date& date);

	IssuedBook();
	IssuedBook(const Book& book, const Date& issue_date);

	friend ostream& operator<< (ostream& out, const IssuedBook& issued_book);
	friend istream& operator>> (istream& in, IssuedBook& issued_book);
};
