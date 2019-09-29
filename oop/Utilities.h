//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#ifndef AMA_UTILITIES_H
#define AMA_UTILITIES_H

#include"Product.h"
#include"iProduct.h"
#include<iostream>

namespace ama {
	double& operator+=(double& total, const iProduct& prod);
	ostream& operator<<(ostream& out, const iProduct& prod);
	istream& operator>>(istream& in, iProduct& prod);
	iProduct* createInstance(char tag);
}
#endif
