//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Product.h"
#include"Date.h"
#include"ErrorState.h"
#include<iostream>

namespace ama {
	class Perishable : public Product {
		Date p_date;
	public:
		Perishable();
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
	
}

#endif