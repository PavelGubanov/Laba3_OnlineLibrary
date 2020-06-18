#include "BookRecord.h"
#include <functional>

Reader& BookRecord::get_reader()
{
	return reader;
}
IssuedBook& BookRecord::get_issued_book()
{
	return issued_book;
}
Date BookRecord::get_return_date() const { return return_date; }
void BookRecord::set_reader(const Reader& reader)
{
	this->reader = reader;
}
void BookRecord::set_issued_book(const IssuedBook& issued_book)
{
	this->issued_book = issued_book;
}

void BookRecord::set_return_date(const Date& return_date)
{
	this->return_date = return_date;
}

void BookRecord::input_field_by_num(int n)
{
	switch (n)
	{
		case 1:
		{
			int number;
			cout << "Введите номер читательского билета: ";
			cin >> number;
			this->get_reader().set_number_of_library_card(number);
			break;
		}
		case 2:
		{
			string surname_reader;
			cout << "Введите фамилию читателя: ";
			getline(cin, surname_reader);
			this->get_reader().set_surname(surname_reader);
			break;
		}
		case 3:
		{
			Date date;
			cout << "Введите дату выдачи: ";
			cin >> date;
			this->get_issued_book().set_issue_date(date);
			break;
		}
		case 4:
		{
			Date date;
			cout << "Введите дату сдачи книги: ";
			cin >> date;
			this->set_return_date(date);
			break;
		}
		case 5:
		{
			string author;
			cout << "Введите автора книги:";
			getline(cin, author);
			this->get_issued_book().get_book().set_author_of_book(author);
			break;
		}
		case 6:
		{
			string name_book;
			cout << "Введите название книги:";
			getline(cin, name_book);
			this->get_issued_book().get_book().set_name_of_book(name_book);
			break;
		}
		case 7:
		{
			int year_of_publication;
			cout << "Введите год издания книги:";
			cin >> year_of_publication;
			this->get_issued_book().get_book().set_year_of_publication(year_of_publication);
			break;
		}
		case 8:
		{
			string publishing_house;
			cout << "Введите название издательства:";
			getline(cin, publishing_house);
			this->get_issued_book().get_book().set_publishing_house(publishing_house);
			break;
		}
	}
}

void BookRecord::print_field_by_num(int n)
{
	switch (n)
	{
	case 1:
	{
		cout << "Номер читательского билета: " << this->get_reader().get_number_of_library_card() << endl;
		break;
	}
	case 2:
	{
		cout << "Фамилия читателя: " << this->get_reader().get_surname() << endl;
		break;
	}
	case 3:
	{
		cout << "Дата выдачи книги: " << this->get_issued_book().get_issue_date() << endl;
		break;
	}
	case 4:
	{
		cout << "Дата сдачи книги: " << this->get_return_date() << endl;
		break;
	}
	case 5:
	{
		cout << "Автор книги: " << this->get_issued_book().get_book().get_author_of_book() << endl;
		break;
	}
	case 6:
	{
		cout << "Название книги: " << this->get_issued_book().get_book().get_name_of_book() << endl;
		break;
	}
	case 7:
	{
		cout << "Год издательства: " << this->get_issued_book().get_book().get_year_of_publication() << endl;
		break;
	}
	case 8:
	{
		cout << "Издательство: " << this->get_issued_book().get_book().get_publishing_house() << endl;
		break;
	}
	}
}

function<void(BookRecord&)> BookRecord::get_print_func()
{
	return [](BookRecord& bookrecord) -> void
	{
		for (int i = 1; i <= 8; i++)
		{
			bookrecord.print_field_by_num(i);
		}
		cout << endl;
	};
}

function<bool(BookRecord&, BookRecord&)> BookRecord::get_compare_func_by_num(int n)
{
	function<bool(BookRecord& br1, BookRecord& br2)> compare;
	switch (n)
	{
	case 1:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_reader().get_number_of_library_card() < br2.get_reader().get_number_of_library_card();
		};
		break;
	}
	case 2:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_reader().get_surname() < br2.get_reader().get_surname();
		};
		break;
	}
	case 3:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_issued_book().get_issue_date() < br2.get_issued_book().get_issue_date();
		};
		break;
	}
	case 4:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_return_date() < br2.get_return_date();
		};
		break;
	}
	case 5:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_issued_book().get_book().get_author_of_book() < br2.get_issued_book().get_book().get_author_of_book();
		};
		break;
	}
	case 6:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_issued_book().get_book().get_name_of_book() < br2.get_issued_book().get_book().get_name_of_book();
		};
		break;
	}
	case 7:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_issued_book().get_book().get_year_of_publication() < br2.get_issued_book().get_book().get_year_of_publication();
		};
		break;
	}
	case 8:
	{
		compare = [](BookRecord& br1, BookRecord& br2) {
			return br1.get_issued_book().get_book().get_publishing_house() < br2.get_issued_book().get_book().get_publishing_house();
		};
		break;
	}
	}
	return compare;
}

void BookRecord::print_name_sort_field(int n)
{
	cout << "Книги отсортированы по ";
	switch (n)
	{
		case 1:
		{
			cout << "номеру читательского билета" << endl;
			break;
		}
		case 2:
		{
			cout << "фамилии читателя" << endl;
			break;
		}
		case 3:
		{
			cout << "дате выдачи книги" << endl;
			break;
		}
		case 4:
		{
			cout << "дате сдачи книги" << endl;
			break;
		}
		case 5:
		{
			cout << "автору книги" << endl;
			break;
		}
		case 6:
		{
			cout << "названию книги" << endl;
			break;
		}
		case 7:
		{
			cout << "году издательства" << endl;
			break;
		}
		case 8:
		{
			cout << "названию издательства" << endl;
			break;
		}
	}
}


ostream& operator<<(ostream& out, const BookRecord& record)
{
	out << record.reader
		<< record.return_date << endl
		<< record.issued_book;
	return out;
}

istream& operator>>(istream& in, BookRecord& record)
{
	in >> record.reader;
	in >> record.return_date;
	in >> record.issued_book;
	return in;
}

int BookRecord::get_num_selected_field(const string& name, bool canBack)
{
	int start_item = 1;
	string tmp = name;
	if (canBack)
	{
		start_item = 0;
		tmp += "0 - назад\n";
	}
	tmp += "1 - номер читательского билета\n2 - фамилия читателя\n";
	tmp += "3 - дата выдачи\n4 - дата возврата\n";
	tmp += "5 - автор книги\n6 - название книги\n";
	tmp += "7 - год издательства книги\n8 - название издательства\n";	
	
	cout << tmp << "Ваш выбор - ";
	string s;
	int num;
	cin >> num;
	getline(cin, s);
	while (num < start_item || num > 8)
	{
		cout << "Ошибка! Поле с таким номером отсутствует! Повторите ввод!";
		cout << "Ваш  выбор - ";
		cin >> num;
		getline(cin, s);
	}
	return num;
}
