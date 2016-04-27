#ifndef FINALPROJECT_H
#define FINALPROJECT_H
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

struct customerInformation {
	std::string last;
	std::string first;
	bool vendor = false;
	string userName;
	string pin;
};

struct classInformation{
	std::string title;
	int weekdays[7][3];
	int currSize = (rand()%10) + 1;
	vector<customerInformation> classMembers;

	};
	
	class Reservation {
	public:
		Reservation();
		~Reservation();
		void addMember(std::string first, std::string last);
		customerInformation findMember(std::string first, std::string last);
		void deleteMember(std::string first, std::string last);
		void reserveSpace(string firstName, string lastName, string className, string classDay, int classTime);
		void checkAvailability(); 
		void readFileClasses(); 
		void displayClasses(); 
		void printMemberList();
		void becomeVendor(std::string name, std::string lastName);
		void addClass(std::string firstName, std::string lastName);


protected:
private:
	vector<classInformation> gymClass;
	vector<customerInformation> customer;
	string realDayNames(int x);
	int inputToNumber(string s);

	
};


#endif






