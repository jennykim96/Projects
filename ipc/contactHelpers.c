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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

// This source file needs to "know about" the SYSTEM string library functions.
// HINT: The library name is string.h.
//       #include the string.h header file on the next line:
#include<string.h>

// ----------------------------------------------------------
// Include your contactHelpers header file on the next line:
#include"contactHelpers.h"
#include"contacts.h"


// ----------------------------------------------------------
// define MAXCONTACTS for sizing contacts array (5):
#define MAXCONTACTS 5


//------------------------------------------------------
// Function Definitions
//------------------------------------------------------


// Clear the standard input buffer
void clearKeyboard(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
}

// pause function definition goes here:
void pause(void)
{
	printf("(Press Enter to Continue)");
	clearKeyboard();
}

// getInt function definition goes here:
int getInt(void)
{
	char NL = 'x';
	int Value;
	while (NL != '\n') {
		scanf(" %d%c", &Value, &NL);
		if (NL != '\n')
		{
			clearKeyboard();
			printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		}
	}
	return Value;
}

// getIntInRange function definition goes here:
int getIntInRange(int min, int max)
{
	int i;
	do {
		i = getInt();
		if (i<min || i>max) {
			printf("*** OUT OF RANGE *** <Enter a number between %d and %d>: ", min, max);
		}
	} while (i<min || i>max);
	return i;
}

// yes function definition goes here:
int yes(void) {
	char opt;
	char NL = 'x';
	int flag = 10;
	do {
		scanf(" %c%c", &opt, &NL);
		if ((opt != 'Y' && opt != 'y' && opt != 'N' && opt != 'n') || NL != '\n') {
			clearKeyboard();
			printf("*** INVALID ENTRY *** <Only (Y)es or (N)o are acceptable>: ");
		}
		else if (opt == 'Y' || opt == 'y') {
			flag = 1;
		}
		else {
			flag = 0;
		}
	} while (flag == 10);
	return flag;
}

// menu function definition goes here:
int menu(void) {
	int sel;
	printf("Contact Management System\n");
	printf("-------------------------\n");
	printf("1. Display contacts\n");
	printf("2. Add a contact\n");
	printf("3. Update a contact\n");
	printf("4. Delete a contact\n");
	printf("5. Search contacts by cell phone number\n");
	printf("6. Sort contacts by cell phone number\n");
	printf("0. Exit\n\n");
	printf("Select an option:> ");
	sel = getIntInRange(0, 6);

	return sel;
}

// contactManagerSystem function definition goes here:
void contactManagerSystem(void) {

		struct Contact contacts[MAXCONTACTS] =
	{ { { "Rick", {'\0'}, "Grimes" },
		{ 11, "Trailer Park", 0, "A7A 2J2", "King City" },
		{ "4161112222", "4162223333", "4163334444" } },
	{   { "Maggie", "R.", "Greene" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		{ "9051112222", "9052223333", "9053334444" } },
	{   { "Morgan", "A.", "Jones" },
		{ 77, "Cottage Lane", 0, "C7C 9Q9", "Peterborough" },
		{ "7051112222", "7052223333", "7053334444" } },
	{   { "Sasha", {'\0'}, "Williams" },
		{ 55, "Hightop House", 0, "A9A 3K3", "Bolton" },
		{ "9052223333", "9052223333", "9054445555" } },

	};
	int sel1, flag = 10;
	do {
		sel1 = menu();
		switch (sel1)
		{
		case 0:
			printf("\nExit the program? (Y)es/(N)o: ");
			if (yes())
			{
				printf("\nContact Management System: terminated");
				flag = 1;
			}
			printf("\n");
			break;
		case 1:
			printf("\n");
			displayContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 2:
			printf("\n");
			addContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 3:
			printf("\n");
			updateContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 4:
			printf("\n");
			deleteContact(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 5:
			printf("\n");
			searchContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;
		case 6:
			printf("\n");
			sortContacts(contacts, MAXCONTACTS);
			pause();
			printf("\n");
			break;

		default:
			break;
		}
	} while (flag == 10);
}



void getTenDigitPhone(char telNum[])
{

	int i, orderNum = 0, needInput = 1;

	while (needInput == 1) {
		scanf("%10s", telNum);
		clearKeyboard();
		orderNum = 0;
		// (String Length Function: validate entry of 10 characters)
		if (strlen(telNum) == 10)
		{
			for (i = 0; i < 10; i++)
				if (telNum[i] >= '0' && telNum[i] <= '9')
					orderNum = orderNum + 1;

			if (orderNum == 10)
				needInput = 0;
			else
				printf("Enter a 10-digit phone number: ");
		}
		else
			printf("Enter a 10-digit phone number: ");
	}
}

// findContactIndex:
int findContactIndex(const struct Contact contacts[], int size, const char cellNum[])
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (strcmp(contacts[i].numbers.cell,cellNum) ==0)
		return i; 
	}
	return -1;
}


// displayContactHeader
// Put empty function definition below:
void displayContactHeader(void)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("|                              Contacts Listing                               |\n");
	printf("+-----------------------------------------------------------------------------+\n");
}


// displayContactFooter
// Put empty function definition below:
void displayContactFooter(int total)
{
	printf("+-----------------------------------------------------------------------------+\n");
	printf("Total contacts: %d\n\n", total);
}


// displayContact:
void displayContact(const struct Contact* contacts)
{
		printf(" %s ", contacts->name.firstName);
		if (strlen(contacts->name.middleInitial) != 0) {
			printf("%s ", contacts->name.middleInitial);
		}
		printf("%s\n", contacts->name.lastName);
		printf("    C: %-10s   H: %-10s   B: %-10s\n", contacts->numbers.cell, contacts->numbers.home, contacts->numbers.business);
		printf("       %d %s, ", contacts->address.streetNumber, contacts->address.street);
		if (contacts->address.apartmentNumber > 0)
		{
			printf("Apt# %d, ", contacts->address.apartmentNumber);
		}
		printf("%s, %s\n", contacts->address.city, contacts->address.postalCode);
}


// displayContacts:
// Put empty function definition below:
void displayContacts(const struct Contact contacts[], int size)
{
	int i;
	int total = 0;
	displayContactHeader();
	for (i = 0; i < size; i++)
	{
		if (strlen(contacts[i].numbers.cell) > 0)
		{
			total++;
			displayContact(&contacts[i]);
		}
	}
	displayContactFooter(total);

}


// searchContacts:
// Put empty function definition below:
void searchContacts(const struct Contact contacts[], int size)
{
	char searchNum[11];
	int index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(searchNum);
	index = findContactIndex(contacts, size, searchNum);
	if (index == -1) {
		printf("*** Contact NOT FOUND ***\n\n");
	}
	else {
		printf("\n");
		displayContact(&contacts[index]);
		printf("\n");
	}
}


// addContact:
// Put empty function definition below:
void addContact(struct Contact contacts[], int size)
{
	int i;
	for (i = 0;i < size; i++) {
		if (strlen(contacts[i].numbers.cell) == 0) {
			break;
		}
	}
	if (i == size) {
		printf("*** ERROR: The contact list is full! ***\n\n");
	}
	else {
		getContact(&contacts[i]);
		printf("--- New contact added! ---\n\n");
	}
}


// updateContact:
// Put empty function definition below:
void updateContact(struct Contact contacts[], int size)
{
	int yn;
	char searchNum[11];
	int index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(searchNum);
	index = findContactIndex(contacts, size, searchNum);
	if (index == -1) {
		printf("*** Contact NOT FOUND ***\n\n");
	}
	else {
		printf("\nContact found:\n");
		displayContact(&contacts[index]);
		printf("\nDo you want to update the name? (y or n): ");
		yn = yes();
		if (yn == 1) {
			getName(&contacts[index].name);
		}
		printf("Do you want to update the address? (y or n): ");
		yn = yes();
		if (yn == 1) {
			getAddress(&contacts[index].address);
		}
		printf("Do you want to update the numbers? (y or n): ");
		yn = yes();
		if (yn == 1) {
			getNumbers(&contacts[index].numbers);
		}
		printf("--- Contact Updated! ---\n\n");
	}
}


// deleteContact:
// Put empty function definition below:
void deleteContact(struct Contact contacts[], int size)
{
	int yn;
	char searchNum[11];
	int index;
	printf("Enter the cell number for the contact: ");
	getTenDigitPhone(searchNum);
	index = findContactIndex(contacts, size, searchNum);
	if (index == -1) {
		printf("*** Contact NOT FOUND ***\n\n");
	}
	else {
		printf("\nContact found:\n");
		displayContact(&contacts[index]);
		printf("\nCONFIRM: Delete this contact? (y or n): ");
		yn = yes();
		if (yn ==1) {
			contacts[index].numbers.cell[0] = '\0';
			printf("--- Contact deleted! ---\n\n");
		}else printf("\n");
	}
}


// sortContacts:
// Put empty function definition below:
void sortContacts(struct Contact contacts[], int size)
{
	int i, j;
	struct Contact temp;
	for (i = 0;i < size; i++)
	{
		for (j = i + 1;j < size;j++) {
			if (strlen(contacts[i].numbers.cell) != 0 && strlen(contacts[j].numbers.cell) != 0) {
				if (strcmp(contacts[i].numbers.cell, contacts[j].numbers.cell) > 0) {
					temp = contacts[i];
					contacts[i] = contacts[j];
					contacts[j] = temp;
				}
			}
		}
	}
	printf("--- Contacts sorted! ---\n\n");
}
