#pragma once
#include <iostream>
#include <string>

using namespace std;

int get_number_from_stringdate(string& str);

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date(int d = 1, int m = 1, int y = 1970)
    {
        setDate(d, m, y);
    }

    Date(const Date& date)
    {
        setDate(date.day, date.month, date.year);
    }

    int getDay() const
    {
        return day;
    }

    int getMonth() const
    {
        return month;
    }

    int getYear() const
    {
        return year;
    }

    void setDay(int day)
    {
        this->day = day;
        if (this->day > daysInMonth(year, month))
        {
            this->day -= daysInMonth(year, month);
            setMonth(++month);
        }
    }

    void setMonth(int month)
    {
        this->month = month;
        if(this->month > 12)
        {
            year++;
            this->month %= 12;
        }
    }

    void setYear(int year)
    {
        this->year = year;
    }

    void setDate(int day, int month, int year)
    {
        if (isValidDate(day, month, year))
        {
            setYear(year);            
            setMonth(month);
            setDay(day);
        }
    }
    
    friend ostream& operator <<(ostream& out, const Date& date)
    {
        out << date.day << '.'
            << date.month << '.'
            << date.year ;
        return out;
    }

    friend istream& operator >>(istream& in, Date& date)
    {
        int day, month, year;
        string tmp_date, tmp_substr;
        getline(in, tmp_date);
        day = get_number_from_stringdate(tmp_date);
        month = get_number_from_stringdate(tmp_date);
        year = atoi(tmp_date.c_str());
        date.setDate(day, month, year);
        return in;
    }

    friend static bool operator== (const Date& d1, const Date& d2)
    {
        return ((d1.day == d2.day) && (d1.month == d2.month) && (d1.year == d2.year));
    }

    friend static bool operator!= (const Date& d1, const Date& d2)
    {
        return (!(d1 == d2));
    }

    friend static bool operator< (const Date& d1, const Date& d2)
    {
        if (d1.year < d2.year)
            return true;
        if (d1.year > d2.year)
            return false;
        if (d1.month < d2.month)
            return true;
        if (d1.month > d2.month)
            return false;
        return d1.day < d2.day;
    }

    friend static bool operator> (const Date& d1, const Date& d2)
    {
        return (!(d1 < d2) && !(d1 == d2));
    }
    friend static bool operator<= (const Date& d1, const Date& d2)
    {
        return ((d1 < d2) || (d1 == d2));
    }
    friend static bool operator>= (const Date& d1, const Date& d2)
    {
        return ((d1 > d2) || (d1 == d2));
    }
    void addDays(int days) 
    {
        while (days >= daysInYear(year))
        {
            days -= daysInYear(year);
            year++;
        }
        while (days >= daysInMonth(year, month))
        {
            days -= daysInMonth(year, month);
            setMonth(++month);
        }
        if (days > 0)
        {
            setDay(this->day + days);
        }
    }

    static bool isValidDate(int day, int month, int year)
    {
        if ((day < 1 || day>31) || (month < 1 || month>12))
        {
            return false;
        }
        return true;
    }

    static int daysInYear(int year)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400)
        {
            return 366;
        }
        return 365;
    }

    static bool isLeapYear(int year) 
    {
        return daysInYear(year) == 366;
    }

    static int daysInMonth(int year, int month)
    {
        int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (isLeapYear(year)) 
        {
            days[1] = 29;
        }
        return days[month - 1];
    }
};



