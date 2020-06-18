#pragma once
#include <string>
#include "Date.h"
#include "Reader.h"
#include "Book.h"

using namespace std;

class BookRecord //Информационная запись о выдаче книги на руки читателя с датой получения и возврата книги
{
private:
	Reader reader; //читатель, который брал книгу
	Date return_date; // дата возврата
	IssuedBook issued_book; // выданная книга	

public:
	Reader& get_reader();
	IssuedBook& get_issued_book();
	Date get_return_date() const;

	void set_reader(const Reader& reader);
	void set_issued_book(const IssuedBook& issued_book);
	void set_return_date(const Date& return_date);

	void input_field_by_num(int n);
	void print_field_by_num(int n);
	static function<void(BookRecord&)> get_print_func(); //форматированная печать записи
	static function<bool(BookRecord&, BookRecord&)> get_compare_func_by_num(int n); //компаратор по номер поля записи
	static void print_name_sort_field(int n);
	static int get_num_selected_field(const string& name, bool canBack = false);

	friend ostream& operator<< (ostream& out, const BookRecord& record);
	friend istream& operator>> (istream& in, BookRecord& record);
};

