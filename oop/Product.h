//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include "iProduct.h"
#include "ErrorState.h"
#include<iostream>

namespace ama {

	class Product : public iProduct{
		const char p_type;
		char p_sku[max_length_sku +1];
		char p_unit[max_length_unit + 1];
		char* p_name;
		int p_now_qty;
		int p_need_qty;
		double p_price;
		bool tax_yn;
	

	protected:
		ErrorState p_err;
		void message(const char* pText);
		bool isClear() const;
		
	public:
		Product(const char type = 'N');
		Product(const char* sku, const char* name, const char* unit, double price = 0, int need_qty = 0, int now_qty = 0, bool taxable = true);

		Product(const Product& src);
		~Product();

		Product& operator=(const Product& src);

		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator> (const iProduct& other)const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		const char* name() const;
		double total_cost() const;
		bool isEmpty() const;

		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;

	};
}

#endif