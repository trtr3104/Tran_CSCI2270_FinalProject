#include "finalProject.h"
#include <vector>


using namespace std;



Reservation::Reservation(){
}


void Reservation::readFileClasses(){	
	 //instance of Class Information
	ifstream inFile("gymClasses.txt");
	string data;
	int counter = 0;
	if(inFile.is_open()){	
		while(!inFile.eof()){
			getline(inFile, data);
			stringstream ss(data);

			classInformation gymClassMeow;
			bool onThisDay[7];
			int classTimes[3];

			getline(ss, gymClassMeow.title, ',' );
			string token;

			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[0]=true;
			}
			else{
				onThisDay[0]=false;
			}
			
			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[1]=true;
			}
			else{
				onThisDay[1]=false;
			}

			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[2]=true;
			}
			else{
				onThisDay[2]=false;
			}

			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[3]=true;
			}
			else{
				onThisDay[3]=false;
			}

			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[4]=true;
			}
			else{
				onThisDay[4]=false;
			}

			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[5]=true;
			}
			else{
				onThisDay[5]=false;
			}

			getline(ss, token, ',');
			if(atoi(token.c_str())==1){
				onThisDay[6]=true;
			}
			else{
				onThisDay[6]=false;
			}

			getline(ss, token, ',');
			classTimes[0] =  atoi(token.c_str());

			getline(ss, token, ',');
			classTimes[1] =  atoi(token.c_str());

			getline(ss, token, ',');
			classTimes[2] =  atoi(token.c_str());



			for(int i=0;i<7;i++){
				if(onThisDay[i]){
					for (int j = 0; j < 3; ++j)
					{
						gymClassMeow.weekdays[i][j]=classTimes[j];	
					}
					
				}else{
					for (int j = 0; j < 3; ++j)
					{
						gymClassMeow.weekdays[i][j]=0;	
					}
				}
			}

			gymClass.push_back(gymClassMeow); 

		}
	}
	inFile.close();	
}



void Reservation::displayClasses(){
	cout<<" "<<endl;
	cout<<"Available Classes"<<endl;
	cout<<"=================="<<endl;
	for(int i = 0; i< gymClass.size(); i++){	
		cout<<i+1<<". "<<gymClass[i].title<<endl;
	}
}		

void Reservation::checkAvailability(){
	string decision;
	cout<<"Which Class Would you Like to Choose?"<<endl;
	displayClasses();

	cout<<"Please type the class name"<<endl;
	cout<<"";
	cin.get();
	getline(cin, decision);
	for(int i = 0; i<gymClass.size(); i++){
		if(decision == gymClass[i].title){
			cout<<decision<<" is available at: "<<endl;
			for(int j = 0; j< 7; j++){
				cout<<realDayNames(j)<<": ";
				for(int x = 0; x < 3; x++){
					cout<<gymClass[i].weekdays[j][x]<<":00 ";
				}
				cout<<" "<<endl;
			}
			
		}
	}
}


string Reservation::realDayNames(int x){
	if(x == 0){
		return "Sunday";
	}
	if(x == 1){
		return "Monday";
	}
	if(x == 2){
		return "Tuesday";		
	}
	if(x == 3){
		return "Wednesday";
	}
	if(x == 4){
		return "Thursday";
	}
	if(x == 5){
		return "Friday";
	}
	if(x == 6){
		return "Saturday";
	}
	return " ";
}

int Reservation::inputToNumber(string x){
	if(x == "Sunday"){
		return 0;
	}
	if(x == "Monday"){
		return 1;
	}
	if(x == "Tuesday"){
		return 2;		
	}
	if(x == "Wednesday"){
		return 3;
	}
	if(x == "Thursday"){
		return 4;
	}
	if(x == "Friday"){
		return 5;
	}
	if(x == "Saturday"){
		return 6;
	}
	return -1;
}



void Reservation::reserveSpace(string firstName, string lastName, string className, string classDay, int classTime){
	int count = 0;
	for(int i = 0; i < gymClass.size(); i++){
		
		if(className != gymClass[i].title){
			continue;
		}		
		else{ //class day
			for(int j = 0; j < 3; ++j){
				if(gymClass[i].weekdays[inputToNumber(classDay)][j] == 0){
					cout<<"I'm sorry we don't have that class that day"<<endl;
					return;
				}
				else{

					if(gymClass[i].weekdays[inputToNumber(classDay)][j] == classTime){ //if that class times match up
						gymClass[i].currSize +=1;
						customerInformation name;
						name.first = firstName;
						name.last = lastName; 
						gymClass[i].classMembers.push_back(name);
						cout<<" "<<endl;
						cout<< firstName <<" you have been successfully enrolled in: "<<endl;
						cout<<className<<" "<<classDay<<" at "<<classTime<<":00"<<endl;
						return;
					}
				}
			}
			cout<<"Sorry the time requested isn't available that day"<<endl; 
			return;

		}

	}
	cout<<"I'm sorry we don't offer that class"<<endl;
}

customerInformation Reservation::findMember(string first, string last){
	customerInformation name;
	name.first = first;
	name.last = last;
	for(int  i = 0; i< customer.size(); i++){
		if(first == customer[i].first && last == customer[i].last){
			return name;
		}
		else{
			cout<<"I'm sorry, it appears you aren't a member of Swoll"<<endl;
		}
	}
	customerInformation notFound;
	notFound.first = "0";
	notFound.last = "0";
	return notFound;
}

void Reservation::deleteMember(string first, string last){	
	customerInformation name = findMember(first, last);
	int index;
	if(name.first != "0" && name.last != "0"){
		for(int i  = 0; i< customer.size(); i++){
			if(customer[i].first == name.first && customer[i].last == name.last){
				index = i;
			}
			customer.erase(customer.begin() + index);
		}
	}
}

void Reservation::addMember(string first, string last){
	customerInformation name;
	name.first = first;
	name.last = last;
	customer.push_back(name);	
}

void Reservation::printMemberList(){
	for(int i = 0; i<customer.size(); i++){
		cout<<i+1<<". "<<customer[i].first<<' '<<customer[i].last<<endl;
	}
	if(customer.empty()){
		cout<<"It appears we don't have any members!"<<endl;
	}
}


void Reservation::becomeVendor(string firstName, string lastName){
	customerInformation curr = findMember(firstName, lastName);
	if(curr.first != "0" && curr.last != "0"){
		cout<<"Do you want to become a Vendor of Swoll?"<<endl;
		cout<<"Y or N"<<endl;
		string data;
		cin>>data;
		if(data == "Y"){
			curr.vendor = true;
			cout<<"Enter userName"<<endl;
			cin>>data;			
			curr.userName = data;
			cout<<"Enter a 4 digit pin"<<endl;
			cin>>data;
			curr.pin = data;
		}
	}
}

void Reservation::addClass(string firstName, string lastName){
	customerInformation *curr = new customerInformation;
	*curr = findMember(firstName, lastName);
	bool onThisDay[7];
	int classTimes[3];
	classInformation gymMeowMeow;
	if(curr->first != "0" && curr->last != "0"){
		string data;
		cout<<"Enter Username"<<endl;
		cin>>data;
		if(data == curr->userName){
			cout<<"Enter Pin"<<endl;
			cin>>data;
			if(data == curr->pin)
				
				cout<<"Enter class name"<<endl;
				cin>>data;
				gymMeowMeow.title = data;
				cout<<"Available Sunday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[0]=true;
				}
				else{
					onThisDay[0]=false;
				}
				cout<<"Available Monday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[1]=true;
				}
				else{
					onThisDay[1]=false;
				}
				cout<<"Available Tuesday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[2]=true;
				}
				else{
					onThisDay[2]=false;
				}
				cout<<"Available Wednesday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[3]=true;
				}
				else{
					onThisDay[3]=false;
				}
				cout<<"Available Thursday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[4]=true;
				}
				else{
					onThisDay[4]=false;
				}
				cout<<"Available Friday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[5]=true;
				}
				else{
					onThisDay[5]=false;
				}
				cout<<"Available Saturday? Y or N"<<endl;
				cin>>data;
				if(data=="Y"){
					onThisDay[6]=true;
				}
				else{
					onThisDay[6]=false;
				}
				cout<<"What time is the class available? Use military time, hour only. Must be offered thrice, same time each day it is available."<<endl;
				cout<<"First time"<<endl;
				cin>>data;
				classTimes[0] =  atoi(data.c_str());
				cout<<"Second time"<<endl;
				cin>>data;
				classTimes[1] =  atoi(data.c_str());
				cout<<"Third time"<<endl;
				cin>>data;
				classTimes[2] =  atoi(data.c_str());
				for(int i=0;i<7;i++){
				if(onThisDay[i]){
					for (int j = 0; j < 3; ++j)
					{
						gymMeowMeow.weekdays[i][j]=classTimes[j];	
					}
					
				}else{
					for (int j = 0; j < 3; ++j)
					{
						gymMeowMeow.weekdays[i][j]=0;	
					}
				}
			}

			gymClass.push_back(gymMeowMeow); 
		}
	}

}

Reservation::~Reservation(){}


