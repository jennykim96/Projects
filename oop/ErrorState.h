//Geonhee Kim 161675178
//OOP244SAA
//2019-04-07

#ifndef AMA_ERRORSTATE_H
#define AMA_ERRORSTATE_H

#include<iostream>
using namespace std;

namespace ama {
	class ErrorState {
		char * text;
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		ErrorState& operator=(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		ErrorState& operator=(const char* pText);
		
		void message(const char* pText);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& os, const ErrorState& t);

}

#endif
