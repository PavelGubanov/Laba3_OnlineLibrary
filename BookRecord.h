#pragma once
#include <string>
#include "Date.h"
#include "Reader.h"
#include "Book.h"

using namespace std;

class BookRecord //�������������� ������ � ������ ����� �� ���� �������� � ����� ��������� � �������� �����
{
private:
	Reader reader; //��������, ������� ���� �����
	Date return_date; // ���� ��������
	IssuedBook issued_book; // �������� �����	

public:
	Reader& get_reader();
	IssuedBook& get_issued_book();
	Date get_return_date() const;

	void set_reader(const Reader& reader);
	void set_issued_book(const IssuedBook& issued_book);
	void set_return_date(const Date& return_date);

	void input_field_by_num(int n);
	void print_field_by_num(int n);
	static function<void(BookRecord&)> get_print_func(); //��������������� ������ ������
	static function<bool(BookRecord&, BookRecord&)> get_compare_func_by_num(int n); //���������� �� ����� ���� ������
	static void print_name_sort_field(int n);
	static int get_num_selected_field(const string& name, bool canBack = false);

	friend ostream& operator<< (ostream& out, const BookRecord& record);
	friend istream& operator>> (istream& in, BookRecord& record);
};

