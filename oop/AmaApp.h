//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#ifndef AMA_APP_H
#define AMA_APP_H
#include"iProduct.h"

namespace ama {

	class AmaApp {
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts;

		AmaApp(const AmaApp& other) = delete;
		AmaApp& operator=(const AmaApp& other) = delete;
		
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);
	public:
		AmaApp(const char[]);
		~AmaApp();
		int run();

	};
}

#endif