#include "finalProject.h"


using namespace std;


int main(){
	Reservation *res2= new Reservation();
	res2->readFileClasses();
	int input = 0;
	while(input!=9){
		cout<<" "<<endl;
		cout<<"======= Main Menu ======="<<endl;
		cout<<" Welcome to Swoll, where you can get swoll"<<endl;
		cout<<"all throughout your busy week!"<<endl;
		cout<<" "<<endl;
		cout<<"1. Become a Member"<<endl;
		cout<<"2. See Classes We Offer"<<endl;
		cout<<"3. Check The Weekly Schedule"<<endl;
		cout<<"4. Check Class Availability"<<endl;
		cout<<"5. Delete Membership"<<endl;
		cout<<"6. Print Member List"<<endl;
		cout<<"7. Become a Vendor"<<endl;
		cout<<"8. Add a Class"<<endl;
		cout<<"9. Quit"<<endl;

		cin>>input;

		if(input == 1){
			string firstName;
			string lastName;
			cout<<"Please Enter your First Name"<<endl;
			cin.get();
			getline(cin, firstName);
			cout<<"Please Enter your Last Name"<<endl;
			getline(cin, lastName);
			res2->addMember(firstName, lastName);
		}

		if(input == 2){
			res2->displayClasses();
		}


		if(input == 3){	
			res2->checkAvailability();
		}
		if(input == 4){
			string firstName;
			string lastName;
			string className;
			string classDay;
			string classTime;

			cout<<"Please Enter your First Name"<<endl;
			cin.get();
			getline(cin, firstName);
			cout<<"Please Enter your Last Name"<<endl;
			getline(cin, lastName);
			cout<<"Which class would you like to book?"<<endl;
			getline(cin, className);
			cout<<"Which Day?"<<endl;
			getline(cin, classDay);
			cout<<"which Time?"<<endl;
			getline(cin, classTime);
			res2->reserveSpace(firstName, lastName, className, classDay, atoi(classTime.c_str()));
		}

		if(input == 5){
			string firstName;
			string lastName;
			cout<<"Please Enter your First Name"<<endl;
			cin.get();
			getline(cin, firstName);
			cout<<"Please Enter your Last Name"<<endl;
			getline(cin, lastName);			
			res2->deleteMember(firstName, lastName);
		}
		if(input ==6){
			res2->printMemberList();
		}
		if(input == 7){
			string firstName;
			string lastName;
			cout<<"Please Enter your First Name"<<endl;
			cin.get();
			getline(cin, firstName);
			cout<<"Please Enter your Last Name"<<endl;
			getline(cin, lastName);	
			res2->becomeVendor(firstName, lastName);
		}
		if(input == 8){
			string firstName;
			string lastName;
			cout<<"Please Enter your First Name"<<endl;
			cin.get();
			getline(cin, firstName);
			cout<<"Please Enter your Last Name"<<endl;
			getline(cin, lastName);	
			customerInformation test = res2->findMember(firstName, lastName);
			cout<<test.userName<<endl;
			res2->addClass(firstName, lastName);
		}
		if(input == 9){
			cout<<"Hope to See You Soon!"<<endl;
		}

	}
	return 0;
}

