//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#ifndef AMA_DATE_H
#define AMA_DATE_H

#include<iostream>
using namespace std;

namespace ama {
	const int min_year = 2019;
	const int max_year = 2028;

	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date {
	private:
		int year;
		int month;
		int day;
		int c_status;
		void status(int newStatus);
		int mdays(int year, int month) const;
	public:
		Date();
		Date(int, int, int);
		int valid(int, int, int);
		int status(void);
		void clearError(void);
		bool isGood(void) const;
		Date& operator+=(int days);
		Date& operator++(void);
		Date operator++(int);
		Date operator+(int days);
		bool operator==(const Date& rhs)const;
		bool operator!=(const Date& rhs)const;
		bool operator<(const Date& rhs)const;
		bool operator>(const Date& rhs)const;
		bool operator<=(const Date& rhs)const;
		bool operator>=(const Date& rhs)const;

		std::istream& read(std::istream& is);
		std::ostream& write(std::ostream& os) const;
	};
	std::ostream& operator<<(std::ostream& os,const Date&);
	std::istream& operator>>(std::istream& is, Date&);

}

#endif

