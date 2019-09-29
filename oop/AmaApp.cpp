//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<iomanip>
#include<sstream>
#include<cstring>
#include <fstream>
#include"Utilities.h"
#include"AmaApp.h"


using namespace std;

namespace ama {
	AmaApp::AmaApp(const char filename[]) {
		strcpy(m_filename, filename);
		for (int i = 0; i < 100; i++) {
			m_products[i] = nullptr;
		}
		m_noOfProducts = 0;
		loadProductRecords();
	}
	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++) {
			delete m_products[i];
		}
	}

	void AmaApp::pause() const {
		string pass;
		cout << "Press Enter to continue...";
		getline(cin,pass);
		cout << endl;
	}
	int AmaApp::menu() const {
		int opt;
		cout << "Disaster Aid Supply Management Program" << endl <<
			"--------------------------------------" << endl <<
			"1- List products" << endl <<
			"2- Search product" << endl <<
			"3- Add non-perishable product" << endl <<
			"4- Add perishable product" << endl <<
			"5- Add to product quantity" << endl <<
			"6- Delete product" << endl <<
			"7- Sort products" << endl <<
			"0- Exit program" << endl
			<< "> ";
		cin >> opt ;
		if (cin.fail() || opt < 0 || opt>7) {
			cin.clear();
			opt = -1;
		}
		return opt;
	}

	void AmaApp::loadProductRecords() {
		for (int i = 0; i < 100; i++) {
			delete m_products[i];
			m_products[i] = nullptr;
		}
		iProduct* prod = nullptr;
		int index = 0;

		ifstream finput;
		finput.open(m_filename, ios::in);
		if (finput.fail()) {
			ofstream emptyfile("empty.txt");
			emptyfile.close();
		}
		else {
			while (!finput.eof()) {
				prod = createInstance(finput.get());
				if (prod != nullptr) {
					m_products[index] = prod;
					finput.get();
					m_products[index]->read(finput, false);
					index++;
				}
			}
		}
		m_noOfProducts = index;
		finput.close();
	}

	void AmaApp::saveProductRecords()const {
		ofstream fout(m_filename, ios::out);
		for (int i = 0; i < m_noOfProducts; i++) {
			m_products[i]->write(fout, write_condensed);
			fout << endl;
		}
		fout.close();
	}

	void AmaApp::listProducts() const {
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;
		double total = 0;
		for (int i = 0; i < m_noOfProducts; i++) {
			cout << "|" << setw(4)<<right << i + 1 << " |";
			m_products[i]->write(cout, write_table);
			total += *m_products[i];
			cout << endl;
		}
		cout << "------------------------------------------------------------------------------------------------" << endl <<
			"|                                                      Total cost of support ($): | " << setw(10) << total << " |" << endl <<
			"------------------------------------------------------------------------------------------------";
		cout << endl << endl;
	}
	iProduct* AmaApp::find(const char* sku) const {
		bool result = false;
		int i;
		for (i = 0; i < m_noOfProducts && result == false; i++) {
			result = *m_products[i] == sku;
		}
		return result ? m_products[i - 1] : nullptr;
	}
	void AmaApp::addQty(iProduct* product) {
		int add;

		product->write(cout, write_human);
		cout << endl << endl;
		cout << "Please enter the number of purchased items: ";
		cin >> add;
		if (cin.fail()) {
			cin.clear();
			cout << "Invalid quantity value!" << endl<<endl;
			cin.ignore(2000, '\n');
		}
		else {
			int needed = product->qtyNeeded() - product->qtyAvailable();
			if (add <= needed)
				*product += add;
			else {

				*product += needed;
				cout << "Too many items; only " << needed << " is needed. Please return the extra " << (add - needed) << " items." << endl;
			}

			saveProductRecords();
			cout << endl << "Updated!" << endl <<endl;
		}
	}
	void AmaApp::addProduct(char tag) {
		if (m_noOfProducts < 100) {
			m_products[m_noOfProducts] = createInstance(tag);
			m_noOfProducts++;

			if (m_products[m_noOfProducts - 1] != nullptr) {
				cin >> *m_products[m_noOfProducts - 1];
				if (cin.fail()) {
					cin.clear();
					cin.ignore(2000, '\n');
					cout << endl << *m_products[m_noOfProducts - 1] << endl << endl;
					m_noOfProducts--;
				}
				else {
					cin.ignore(2000, '\n');
					cout << endl << "Success!" << endl << endl;
					saveProductRecords();
				}
			}
		}
	}

	int AmaApp::run() {
		int option;
		do {
			option = menu();
			switch (option) {
			case 1:
				listProducts();
				cin.ignore();
				pause();
				break;
			case 2:
				char store[max_length_sku];
				cin.ignore();
				cout << "Please enter the product SKU: ";
				cin.getline(store, max_length_sku,'\n');
				cout << endl;
				if (find(store) != nullptr) {
					find(store)->write(cout, write_human);
					cout << endl;
				}
				else
					cout << "No such product!" << endl;
				pause();
				break;
			case 3:
				addProduct('N');
				loadProductRecords();
				break;
			case 4:
				addProduct('P');
				loadProductRecords();
				break;
			case 5:
				char store2[max_length_sku];
				cout << "Please enter the product SKU: ";
				cin.ignore();
				cin.getline(store2, max_length_sku,'\n');
				cout << endl;
				if (find(store2) != nullptr) {
					addQty(find(store2));
				}
				else
					cout << "No such product!" << endl << endl;
				break;
			case 6:
				break;
			case 7:
				break;
			case 0:
				cout << "Goodbye!" << endl;
				break;
			default:
				cout << "~~~Invalid selection, try again!~~~" << endl;
				cin.ignore();
				pause();
				break;
			}
		} while (option != 0);
		return 0;
	}
}
