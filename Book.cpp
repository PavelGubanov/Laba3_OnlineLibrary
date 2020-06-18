#include "Book.h"
#include <iostream>


string Book::get_author_of_book() const { return author_of_book; }
string Book::get_name_of_book() const { return name_of_book; }
int Book::get_year_of_publication() const { return year_of_publication; }
string Book::get_publishing_house() const { return publishing_house; }


void Book::set_author_of_book(const string& author)
{
	this->author_of_book = author;
}
void Book::set_name_of_book(const string& name)
{
	this->name_of_book = name;
}
void Book::set_year_of_publication(const int year)
{
	this->year_of_publication = year;
}
void Book::set_publishing_house(const string& house)
{
	this->publishing_house = house;
}

function<void(BookInfo&)> BookInfo::get_print_func(bool status)
{
	int count = status ? 5 : 4;
	return [count](BookInfo& bookinfo) -> void
	{
		for (int i = 1; i <= count; i++)
		{
			bookinfo.print_field_by_num(i);
		}
		cout << endl;
	};
}

function<bool(BookInfo&, BookInfo&)> BookInfo::get_compare_func_by_num(int n)
{
	function<bool(BookInfo & b1, BookInfo & b2)> compare;
	switch (n)
	{
		case 1:
		{
			compare = [](BookInfo& b1, BookInfo& b2) {
				return b1.get_book().get_author_of_book() < b2.get_book().get_author_of_book();
			};
			break;
		}
		case 2:
		{
			compare = [](BookInfo& b1, BookInfo& b2) {
				return b1.get_book().get_name_of_book() < b2.get_book().get_name_of_book();
			};
			break;
		}
		case 3:
		{
			compare = [](BookInfo& b1, BookInfo& b2) {
				return b1.get_book().get_year_of_publication() < b2.get_book().get_year_of_publication();
			};
			break;
		}
		case 4:
		{
			compare = [](BookInfo& b1, BookInfo& b2) {
				return b1.get_book().get_publishing_house() < b2.get_book().get_publishing_house();
			};
			break;
		}
		case 5:
		{
			compare = [](BookInfo& b1, BookInfo& b2) {
				return b1.get_status() < b2.get_status();
			};
			break;
		}
	}
	return compare;
}

void BookInfo::print_name_sort_field(int n)
{
	cout << "Книги отсортированы по ";
	switch (n)
	{
		case 1:
		{
			cout << "автору" << endl;
			break;
		}
		case 2:
		{
			cout << "названию" << endl;
			break;
		}
		case 3:
		{
			cout << "году издательства" << endl;
			break;
		}
		case 4:
		{
			cout << "названию издательства" << endl;
			break;
		}
		case 5:
		{
			cout << "текущему статусу" << endl;
			break;
		}
	}
}

int BookInfo::get_num_selected_field(const string& name, bool canBack)
{
	int start_item = 1;
	string tmp = name;
	if (canBack)
	{
		start_item = 0;
		tmp += "0 - назад\n";
	}
	tmp += "1 - автор книги\n2 - название книги\n";
	tmp += "3 - год издательства\n4 - издательство\n";
	tmp += "5 - статус\n";		
	cout << tmp << "Ваш выбор - ";
	string s;
	int num;
	cin >> num;
	getline(cin, s);
	while (num < start_item || num > 5)
	{
		cout << "Ошибка! Поле с таким номером отсутствует! Повторите ввод!\n";
		cout << "Ваш  выбор - ";
		cin >> num; 
		getline(cin, s);
	}
	return num;
}

void Book::input_author_of_book()
{
	string author;
	cout << "Введите автора книги: ";
	getline(cin, author);
	this->set_author_of_book(author);
}

void Book::input_name_of_book()
{
	string name_book;
	cout << "Введите название книги: ";
	getline(cin, name_book);
	this->set_name_of_book(name_book);
}

void Book::input_year_of_publication()
{
	string s;
	int year_of_publication;
	cout << "Введите год издания книги: ";
	cin >> year_of_publication;
	getline(cin, s);
	this->set_year_of_publication(year_of_publication);
}

void Book::input_publishing_house()
{
	string publishing_house;
	cout << "Введите название издательства: ";
	getline(cin, publishing_house);
	this->set_publishing_house(publishing_house);
}

void BookInfo::input_status()
{
	string question = "Статус книги:\n0 - у читателя\n1 - доступна\n";
	cout << question << "Ваш выбор - ";
	int num;
	cin >> num;
	while (num < 0 || num > 1)
	{
		cout << "Ошибка! Вид статуса с таким номером отсутствует! Повторите ввод!";
		cout << "Ваш  выбор - ";
		cin >> num;
	}
	this->set_status(num);
}

void BookInfo::set_book(const Book& book)
{
	this->book = book;
}

void BookInfo::set_status(const bool status)
{
	if (status)
	{
		this->status = book_status::is_available;
	}
	else
	{
		this->status = book_status::is_issued;
	}
}

void BookInfo::input_field_by_num(int n)
{
	switch (n)
	{
		case 1:
		{
			this->get_book().input_author_of_book();
			break;
		}
		case 2:
		{
			this->get_book().input_name_of_book();
			break;
		}
		case 3:
		{
			this->get_book().input_year_of_publication();
			break;
		}
		case 4:
		{
			this->get_book().input_publishing_house();
			break;
		}
		case 5:
		{
			this->input_status();
			break;
		}
	}
}

void BookInfo::print_field_by_num(int n)
{
	switch (n)
	{
	case 1:
	{
		cout << "Автор книги: " << this->get_book().get_author_of_book() << endl;
		break;
	}
	case 2:
	{
		cout << "Название книги: " << this->get_book().get_name_of_book() << endl;
		break;
	}
	case 3:
	{
		cout << "Год издательства: " << this->get_book().get_year_of_publication() << endl;
		break;
	}
	case 4:
	{
		cout << "Издательство: " << this->get_book().get_publishing_house() << endl;
		break;
	}
	case 5:
	{
		cout << "Текущий статус книги: ";
		switch (this->get_status())
		{
			
			case book_status::is_available:
			{
				cout << "доступна" << endl;
				break;
			}
			case book_status::is_issued:
			{
				cout << "у читателя" << endl;
				break;
			}
		}
		break;
	}
	}
}

ostream& operator<<(ostream& out, const book_status& status)
{
	switch (status)
	{
	case book_status::is_available:
		{
		out << 0;
			break;
		}
	case book_status::is_issued:
	{
		out << 1;
		break;
	}
	}
	return out;
}

istream& operator>>(istream& in, book_status& status)
{
	string s;	
	int num;
	in >> num;
	getline(in, s);
	status = num ? book_status::is_issued : book_status::is_available;
	return in;
}

bool operator==(const Book& book1, const Book& book2)
{
	return book1.get_author_of_book() == book2.get_author_of_book() &&
		book1.get_name_of_book() == book2.get_name_of_book() &&
		book1.get_year_of_publication() == book2.get_year_of_publication() &&
		book1.get_publishing_house() == book2.get_publishing_house();
}

bool operator!=(const Book& book1, const Book& book2)
{
	return !(book1 == book2);
}

ostream& operator<<(ostream& out, const Book& book)
{
	out << book.author_of_book << endl
		<< book.name_of_book << endl
		<< book.year_of_publication << endl
		<< book.publishing_house << endl;
	return out;
}

istream& operator>>(istream& in, Book& book)
{
	string s;
	getline(in, book.author_of_book);
	getline(in, book.name_of_book);
	in >> book.year_of_publication;
	getline(in, s);
	getline(in, book.publishing_house);	
	return in;
}

ostream& operator<<(ostream& out, const BookInfo& bookinfo)
{
	out << bookinfo.book
		<< bookinfo.status << endl;
	return out;
}

istream& operator>>(istream& in, BookInfo& bookinfo)
{
	string s;
	in >> bookinfo.book;
	in >> bookinfo.status;
	getline(in, s);
	return in;
}

ostream& operator<<(ostream& out, const IssuedBook& issued_book)
{
	out << issued_book.book 
		<< issued_book.issue_date << endl;
	return out;
}

istream& operator>>(istream& in, IssuedBook& issued_book)
{
	in >> issued_book.book;
	in >> issued_book.issue_date;
	return in;
}

BookInfo::BookInfo(const Book& book)
{
	this->book = book;
	this->set_status(true);
}

BookInfo::BookInfo()
{
	this->set_status(true);
}

Book& BookInfo::get_book()
{
	return book;
}

book_status BookInfo::get_status() const { return status; }

Book& IssuedBook::get_book()
{
	return book;
}

Date IssuedBook::get_issue_date() const { return issue_date; }

void IssuedBook::set_book(const Book& book)
{
	this->book = book;
}

void IssuedBook::set_issue_date(const Date& date)
{
	this->issue_date = date;
}

IssuedBook::IssuedBook() {}

IssuedBook::IssuedBook(const Book& book, const Date& issue_date)
{
	this->set_book(book);
	this->set_issue_date(issue_date);
}
