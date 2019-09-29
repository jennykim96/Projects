//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<cstring>
#include "ErrorState.h"

using namespace std;

namespace ama {
	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage == nullptr || errorMessage[0] == '\0') {
			text = nullptr;
		}
		else {
			text = new char[strlen(errorMessage) + 1];
			strcpy(text, errorMessage);
		}
	}

	ErrorState::~ErrorState() {
		if (text != nullptr) {
			delete[] text;
			text = nullptr;
		}
	}

	ErrorState::operator bool() const {
		return (text != nullptr) ? true : false;
	}

	ErrorState& ErrorState::operator=(const char* pText) {
		if (this->text != pText) {
			if (pText == nullptr || pText[0] == '\0') {
				text = nullptr;
			}
			else {
				delete [] text;
				text = new char[strlen(pText) + 1];
				strcpy(text, pText);
			}
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {
		if (pText == nullptr || pText[0] == '\0') {
			text = nullptr;
		}
		else {
			text = new char[strlen(pText) + 1];
			strcpy(text, pText);
		}
	}

	const char* ErrorState::message() const{
		return text != nullptr ? text : nullptr;
	}
	std::ostream& operator<<(std::ostream& os, const ErrorState& t) {
		if (t.message() != nullptr) {
			os << t.message();
		}
		return os;
	}
}