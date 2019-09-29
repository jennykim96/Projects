//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<iomanip>
#include"ErrorState.h"
#include"Product.h"
#include"iProduct.h"

using namespace std;

namespace ama {

	void Product::message(const char* pText) {
		p_err.message(pText);
	}
	bool Product::isClear() const {
		return p_err ? false : true;
	}

	Product::Product(const char type) : p_type(type) {
		p_sku[0] = '\0';
		p_unit[0] = '\0';
		p_name = nullptr;
		p_now_qty = 0;
		p_need_qty = 0;
		p_price = 0;
		tax_yn = false;
	}
	Product::Product(const char* sku, const char* name, const char* unit, double price, int need_qty, int now_qty, bool taxable) :p_type('N') {
		if (name == nullptr) {
			*this = Product();
		}
		else {
			int length = strlen(name);
			p_name = nullptr;
			p_name = new char[length + 1];
			strcpy(p_name, name);
			p_name[length] = '\0';

			strncpy(p_sku, sku, max_length_sku);
			p_sku[max_length_sku] = '\0';

			strncpy(p_unit, unit, max_length_unit);
			p_unit[max_length_unit] = '\0';

			p_price = price;
			p_need_qty = need_qty;
			p_now_qty = now_qty;
			tax_yn = taxable;
		}
	}
	Product::Product(const Product& src) : p_type(src.p_type) {
		p_name = nullptr;
		*this = src;
	}

	Product::~Product() {
		delete[] p_name;
	}

	Product& Product::operator=(const Product& src) {
		if (this != &src) {
			strncpy(p_sku, src.p_sku, max_length_sku);
			p_sku[max_length_sku] = '\0';

			strncpy(p_unit, src.p_unit, max_length_unit);
			p_unit[max_length_unit] = '\0';

			p_price = src.p_price;
			p_need_qty = src.p_need_qty;
			p_now_qty = src.p_now_qty;
			tax_yn = src.tax_yn;

			if (src.p_name != nullptr) {
				int length = strlen(src.p_name);
				char* temp;
				temp = new char[length+1];
				strcpy(temp, src.p_name);
				delete[] p_name;
				p_name = new char[length+1];
				strcpy(p_name,temp);
				p_name[length] = '\0';
				delete[] temp;
				temp = nullptr;

			}
			else
				p_name = nullptr;
		}

		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			p_now_qty += cnt;
		}
		return p_now_qty;
	}

	bool Product::operator==(const char* sku) const {
		return strcmp(p_sku, sku) == 0 ? true : false;
	}

	bool Product::operator> (const char* sku) const {
		return strcmp(p_sku, sku) > 0 ? true : false;
	}

	bool Product::operator>(const iProduct& cmp) const {
		return strcmp(p_name, cmp.name()) > 0 ? true : false;
	}

	int Product::qtyAvailable() const {
		return p_now_qty;
	}

	int Product::qtyNeeded() const {
		return p_need_qty;
	}
	const char* Product::name() const {
		return p_name;
	}
	double Product::total_cost() const {
		double total;
		if (tax_yn) {
			total = p_price * (1 + tax_rate);
		}
		else
			total = p_price;
		return total;
	}

	bool Product::isEmpty() const {
		return p_name == nullptr ? true : false;
	}

	std::istream& Product::read(std::istream& in, bool interractive) {
		char sku[max_length_sku] = { '\0' };
		char name[max_length_name] = { '0' };
		char unit[max_length_unit] = { '0' };
		double price = 0;
		bool taxable;
		int nowqty = 0;
		int needqty = 0;
		bool breakPoint = true;
		char y_n;
		in.clear();

		if (interractive == false) {
			in.getline(sku, max_length_sku, ',');
			in.getline(name, max_length_name, ',');
			in.getline(unit, max_length_unit, ',');
			in >> price;
			in.get();
			in >> taxable;
			in.get();
			in >> nowqty;
			in.get();
			in >> needqty;
			if (!this->p_err)
				*this = Product(sku, name, unit, price, needqty, nowqty, taxable);
		}
		else {
			cout << setfill(' ') << setw(max_length_label) << right << "Sku: ";
			in >> sku;
			cout << setw(max_length_label) << "Name (no spaces): ";
			in >> name;
			cout << setw(max_length_label) << "Unit: ";
			in >> unit;
			cout << setw(max_length_label) << "Taxed? (y/n): ";
			in >> y_n;
			if (y_n == 'Y' || y_n == 'y') {
				taxable = true;
			}
			else if (y_n == 'N' || y_n == 'n') {
				taxable = false;
			}
			else {
				message("Only (Y)es or (N)o are acceptable!");
				in.setstate(ios::failbit);
				breakPoint = false;
			}
			if (breakPoint) {
				cout << setw(max_length_label) << "Price: ";
				in >> price;
				if (in.fail() || price < 0) {
					message("Invalid Price Entry!");
					breakPoint = false;
				}

			}
			if (breakPoint) {
				cout << setw(max_length_label) << "Quantity on hand: ";
				in >> nowqty;
				if (in.fail() || nowqty < 0) {
					message("Invalid Quantity Available Entry!");
					breakPoint = false;
				}
			}
			if (breakPoint) {
				cout << setw(max_length_label) << "Quantity needed: ";
				in >> needqty;
				if (in.fail() || needqty < 0) {
					message("Invalid Quantity Needed Entry!");
					breakPoint = false;
				}
			}
			if (!in.fail()) {
				*this = Product(sku, name, unit, price, needqty, nowqty, taxable);
			}
		}
		return in;
	}

	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (isClear()) {
			if (!isEmpty()) {
				if (writeMode == write_condensed) {
					out << p_type << "," << p_sku << "," << name() << "," << p_unit << "," <<fixed<<setprecision(2) << p_price << "," << tax_yn << "," << qtyAvailable() << "," << qtyNeeded();
				}
				else if (writeMode == write_table) {

					out << " " << fixed << setprecision(2) << right << setw(max_length_sku) << p_sku << " | ";
					if (strlen(p_name) > 16) {
						char temp[14] = { '\0' };
						strncpy(temp, p_name, 13);
						out << left << setw(13) << temp << "... | ";
					}
					else {
						out << left << setw(16) << name() << " | ";
					}
					out << setw(10) << p_unit << " | ";
					out << right << setw(7) << p_price << " | ";
					tax_yn ? out << "yes | " : out << " no | ";
					out << setw(6) << qtyAvailable() << " | ";
					out << setw(6) << qtyNeeded() << " |";
				}
				else if (writeMode == write_human) {

					out << fixed << setprecision(2) << right
						<< setw(max_length_label) << "Sku: " << p_sku << "\n"
						<< setw(max_length_label) << "Name: " << name() << "\n"
						<< setw(max_length_label) << "Price: " << p_price << "\n"
						<< setw(max_length_label) << "Price after Tax: " << total_cost() << "\n"
						<< setw(max_length_label) << "Quantity Available: " << qtyAvailable() << " " << p_unit << "\n"
						<< setw(max_length_label) << "Quantity Needed: " << qtyNeeded() << " " << p_unit << endl;
				}
			}
				else
					cout << "";
			}
			else
				out << p_err.message();
			return out;
		}
	}