//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#include <iostream>
#include<iomanip>
#include "Date.h"
using namespace std;


namespace ama {
	Date::Date() {
		c_status = no_error;
		year = 0;
		month = 0;
		day = 0;
	}

	Date::Date(int i_year, int i_month, int i_day) {
		int thisStatus = valid(i_year, i_month, i_day);

		if (thisStatus == no_error) {
			year = i_year;
			month = i_month;
			day = i_day;
			status(thisStatus);
		}
		else {
			*this = Date();
			status(thisStatus);
		}
	}

	void Date::status(int newstatus) {
		c_status = newstatus;
	}

	int Date::status(void) {
		return this->c_status;
	}

	int Date::valid(int i_year, int i_month, int i_day) {
		bool c_year = i_year >= min_year && i_year <= max_year;
		int howDays = mdays(i_year, i_month);
		bool c_day = howDays > 0 && i_day <= howDays && i_day >0;
		int status;

		if (c_year == false) {
			status = error_year;
		}
		else if (howDays <= 0) {
			status = error_mon;
		}
		else if (c_day == false) {
			status = error_day;
		}
		else
			status = no_error;
		return status;
	}

	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };   int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	void Date::clearError(void) {
		status(no_error);
	}

	bool Date::isGood() const {
		bool valid;
		if (year != 0 && month != 0 && day != 0 && c_status == no_error)
			valid = true;
		else
			valid = false;
		return valid;
	}
	Date& Date::operator+=(int days) {
		Date t = *this;
		t.day += days;
		if (t.day <= mdays(this->year, this->month)&&t.day > 0 && c_status ==no_error &&isGood()) {
			this->day = t.day;
		}
		else{
			status(error_invalid_operation);
		}
		return *this;
	}

	Date& Date::operator++(void) {
		if (day < mdays(this->year, this->month) && c_status == no_error && isGood()) {
			day += 1;
		}
		else
			status(error_invalid_operation);
		return *this;
	}
	Date Date::operator++(int day) {
		Date t = *this;
		++(*this);
		return t;
	}
	Date Date::operator+(int days) {
		Date t = *this;
		t.day += days;
		if (t.day > mdays(this->year, this->month) || t.day < 1 || c_status != no_error || !(isGood())) {
			t.status(error_invalid_operation);
			t.day = this->day;
		}
		return t;
	}

	bool Date::operator==(const Date& rhs)const {
		bool y = this->year == rhs.year;
		bool m = this->month == rhs.month;
		bool d = this->day == rhs.day;

		return(y && m && d);
	}

	bool Date::operator!=(const Date& rhs)const {
		return !(*this == rhs);
	}

	bool Date::operator<(const Date& rhs)const {
		bool lessy = this->year < rhs.year;
		bool lessm = this->month < rhs.month;
		bool lessd = this->day < rhs.day;
		bool valid;

		if (lessy)
			valid = true;
		else if (this->year == rhs.year && lessm)
			valid = true;
		else if (this->year == rhs.year && this->month == rhs.month &&lessd)
			valid = true;
		else
			valid = false;

		return valid;
	}

	bool Date::operator>(const Date& rhs)const {
		return !(*this < rhs)&& !(*this==rhs);
	}

	bool Date::operator<=(const Date& rhs)const {
		return(*this < rhs) || (*this == rhs);
	}

	bool Date::operator>=(const Date& rhs)const {
		return (*this > rhs) || (*this == rhs);
	}

	std::istream& Date::read(std::istream& is)
	{
		char symbol;
		is.clear();
		is >> year >> symbol >> month >> symbol >> day;


		if (is.fail())
		{
			*this = Date();
			status(error_input);
		}
		else if (min_year > year || year > max_year)
		{
			*this = Date();
			status(error_year);
		}
		else if (1 > month || month > 12)
		{
			*this = Date();
			status(error_mon);
		}
		else if (day > mdays(year, month) || day <1)
		{
			*this = Date();
			status(error_day);
		}
		else
			status(no_error);

		return is;
	}

	// Works with an ostream object to print a date to the console
	std::ostream& Date::write(std::ostream& os) const
	{
		char symbol = '/';
		if (year == 0) {
			os << 0<<0<<0;
		}
		os << year << symbol;

		if (month < 10)
		{
			os << 0;
		}

		os << month << symbol;

		if (day < 10)
		{
			os << 0;
		}

		os << day;

		return os;
	}
	std::istream& operator>>(std::istream& is, Date& s)
	{
		return s.read(is);
	}

	std::ostream& operator<<(std::ostream& os,const Date& k)
	{
		return k.write(os);
	}
}
