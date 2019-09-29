
#ifndef CONTACTS_H_
#define CONTACTS_H_

/* -------------------------------------------
Name: Geonhee Kim
Student number: 161675178
Email: gkim54@myseneca.ca
Section: IPC144
Date:2018-12-03
----------------------------------------------
Assignment: 2
Milestone:  4
---------------------------------------------- */


//------------------------------------------------------
// Structure Types
//------------------------------------------------------



// Structure type Name declaration
struct Name {
    char firstName[31];
    char middleInitial[7];
    char lastName[36];
};

// Structure type Address declaration
// Place your code here...
struct Address {
	int streetNumber;
	char street[41];
	int apartmentNumber;
	char postalCode[8];
	char city[41];
};


// Structure type Numbers declaration
// Place your code here...
struct Numbers {
	char cell[11];
	char home[11];
	char business[11];
};


// Structure type Contact declaration
// Place your code here...

struct Contact {
	struct Name name;
	struct Address address;
	struct Numbers numbers;
};


//------------------------------------------------------
// Function Prototypes
//------------------------------------------------------


// Get and store from standard input the values for Name
// Place your code here...
void getName(struct Name *);

// Get and store from standard input the values for Address
// Place your code here...
void getAddress(struct Address *);

// Get and store from standard input the values for Numbers
// Place your code here...
void getNumbers(struct Numbers *);

// Get and store from standard input the values for a Contact
// Place your code here...
void getContact(struct Contact *);

#endif // !CONTACTS_H_
