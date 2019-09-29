//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#include<iostream>
#include"Utilities.h"
#include"iProduct.h"
#include"Perishable.h"
using namespace std;

namespace ama {
	double& operator+=(double& total, const iProduct& prod) {
		total += (prod.total_cost() * prod.qtyAvailable());
		return total;
	}
	ostream& operator<<(ostream& out, const iProduct& prod) {
		prod.write(out,write_human);
		return out;
	}
	istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in,true);
		return in;
	}

	iProduct* createInstance(char tag) {
		if (tag == 'N' || tag == 'n') {
			Product* instance = nullptr;
			instance = new Product();
			return instance;
		}
		else if (tag == 'P' || tag == 'p') {
			Perishable* instance = nullptr;
			instance = new Perishable();
			return instance;
		}
		else return nullptr;
	}
}