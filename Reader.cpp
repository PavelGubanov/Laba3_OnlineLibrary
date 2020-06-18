#include "Reader.h"

void Reader::set_number_of_library_card(const int number)
{
	this->number_of_library_card = number;
}

void Reader::set_surname(const string& surname)
{
	this->surname = surname;
}

void Reader::input_number_of_library_card()
{
	string s;
	int number;
	cout << "Введите номер читательского билета: ";
	cin >> number;	
	getline(cin, s);
	this->set_number_of_library_card(number);
}

void Reader::input_surname()
{
	string surname;
	cout << "Введите фамилию читателя: ";
	getline(cin, surname);
	this->set_surname(surname);
}

int Reader::get_number_of_library_card() const { return number_of_library_card; }
string Reader::get_surname() const { return surname; }

ostream& operator<<(ostream& out, const Reader& reader)
{
	out << reader.number_of_library_card << endl
		<< reader.surname << endl;
	return out;
}

istream& operator>>(istream& in, Reader& reader)
{
	string s;
	in >> reader.number_of_library_card;
	getline(in, s);
	getline(in, reader.surname);
	return in;
}

ostream& operator<<(ostream& out, const ReaderInfo& reader_info)
{
	out << reader_info.reader
		<< reader_info.books_on_hand.size() << endl;
	auto iter = reader_info.books_on_hand.begin();
	while (iter != reader_info.books_on_hand.end())
	{
		out << *iter;
		iter++;
	}
	return out;
}

istream& operator>>(istream& in, ReaderInfo& reader_info)
{
	in >> reader_info.reader;
	int size;
	string s;
	in >> size;
	getline(in, s);
	reader_info.books_on_hand.clear();
	for (int i = 0; i < size; i++)
	{
		IssuedBook issued_book;
		in >> issued_book;
		reader_info.books_on_hand.push_back(issued_book);
	}
	getline(in, s);
	return in;
}

Reader& ReaderInfo::get_reader()
{
	return reader;
}

void ReaderInfo::set_reader(const Reader& reader)
{
	this->reader = reader;
}

void ReaderInfo::take_book(const IssuedBook& issued_book)
{
	books_on_hand.push_back(issued_book);
}

bool ReaderInfo::has_chosen_book(Book& book, Date& issue_date)
{
	bool result = false;
	auto iter = books_on_hand.begin();
	while (iter != books_on_hand.end() && !result)
	{
		result = (*iter).get_book() == book;
		if (result)
		{
			issue_date = (*iter).get_issue_date();
		}
		iter++;
	}
	return result;
}

void ReaderInfo::show_books_on_hand()
{
	cout << "\nВаши книги:\n" << endl;
	for (IssuedBook issued_book : books_on_hand)
	{		
		cout << "Автор книги: " << issued_book.get_book().get_author_of_book() << endl
			<< "Название книги: " << issued_book.get_book().get_name_of_book() << endl
			<< "Год издательства: " << issued_book.get_book().get_year_of_publication() << endl
			<< "Издательство: " << issued_book.get_book().get_publishing_house() << endl
			<< "Дата выдачи книг: " << issued_book.get_issue_date() << endl << endl;
	}
}

int ReaderInfo::get_count_books_on_hand()
{
	return books_on_hand.size();
}

void ReaderInfo::return_book(Book& book)
{
	bool del = false;
	auto iter = books_on_hand.begin();
	while (!del &&  iter != books_on_hand.end())
	{
		del = (*iter).get_book() == book;
		if (del)
		{
			books_on_hand.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

bool ReaderInfo::has_books_on_hand()
{
	return books_on_hand.size() > 0;
}
