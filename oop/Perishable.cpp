//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<cstring>
#include"Perishable.h"

using namespace std;

namespace ama {
	Perishable::Perishable():Product('P') {
		
	}
	std::ostream& Perishable::write(std::ostream& out, int writeMode) const {
		Product::write(out, writeMode);
		if (isClear() && !isEmpty()) {
			if (writeMode == write_condensed) {
				out << ",";
				p_date.write(out);
			}
			else if (writeMode == write_table) {
				out << " ";
				p_date.write(out);
				out<<" |";
			}
			else if(writeMode==write_human){
				out << setw(max_length_label) << right << "Expiry Date: ";
				out << left;
				p_date.write(out);
				out << endl;
			}
		}
		return out;
	}
	std::istream& Perishable::read(std::istream& in, bool interractive) {
		Product::read(in, interractive);
		Date temp_;
		if (interractive==false){
			in.ignore();
			p_date.read(in);
			in.ignore();
		}
		else {
			cout << setfill(' ') <<setw(max_length_label)<< " Expiry date (YYYY/MM/DD): ";
			temp_.read(in);
			if (temp_.status() != no_error) {
				in.setstate(ios::failbit);
				in.ignore();
				if (temp_.status() == error_input) {
					message("Invalid Date Entry");
				}
				else if (temp_.status() == error_year) {
					message("Invalid Year in Date Entry");
				}
				else if (temp_.status() == error_mon) {
					message("Invalid Month is Date Entry");
				}
				else if (temp_.status() == error_day) {
					message("Invalid Day in Date Entry");
				}
			}
			else {
				p_date = temp_;
			}
		}
		return in;
	}

}

