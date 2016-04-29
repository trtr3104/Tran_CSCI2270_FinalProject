#include "GPS.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    GPS cityGraph=GPS();
    ifstream inFile;
    string data;
    inFile.open("cities.txt");
	vector <string> cityNames;
    if (inFile.good())
    {
		// read city names
		getline(inFile, data);
		istringstream ss(data);
		// ignore 'cities'
		string text;
		getline(ss, text, ',');

		// read city names
		while (ss)
		{
			if (!getline(ss, text, ',')) break;
			cityNames.push_back(text);
			cityGraph.addVertex(text);
		}

		int rowIdx = 0;
		while (getline(inFile, data))
		{
			int colIdx = 0;
			string data2;

			stringstream text(data);
			while (getline(text, data2, ','))
			{
				if (colIdx == 0)
				{
					//do nothing, ignore city name
					colIdx++;
				}
				else
				{
					// default values
					int dist = -1;
					int speed = 0;
					bool toll = false;
					string data3;

					int idx = 0;
					stringstream text2(data2);
					while (getline(text2, data3, ' '))
					{
						if (idx == 0)
						{
							istringstream(data3) >> dist;
						}
						else if (idx == 1)
						{
							istringstream(data3) >> speed;
						}
						else
						{
							istringstream(data3) >> toll;
						}
						idx++;
					}

					if (dist != -1 && colIdx > rowIdx) {
						cityGraph.addEdge(cityNames[rowIdx], cityNames[colIdx-1], dist, speed, toll);
					}
					colIdx++;
				}
			}
			rowIdx++;
		}
	}

	else
		cout << "file unsuccessfully opened" << endl;
	inFile.close();



    int n=0;
    while (n==0)
    {
        int choice;
        cout<<"======Main Menu======\n"
        "1. Print vertices\n"
        "2. Add city\n"
        "3. Find shortest distance\n"
        "4. Find shortest time\n"
        "5. Find longest distance\n"
        "6. Avoid toll\n"
        "7. Show all time and distance\n"
        "8. Delete city\n"
        "9. Quit"<<endl;
        cin>>choice;
        cin.ignore(1000, '\n');

        switch (choice)
        {
        case 1:
            {
				cityGraph.displayEdges();
                break;
            }
        case 2:
            {
                string city1, city2, Toll;
                int speed, distance, time;
                bool toll;
				cout << "Enter new city:" << endl;
				getline(cin, city1);
				cout << "Enter city connected to it:" << endl;
				getline(cin, city2);
				cout << "Does it have toll (Yes/No):" << endl;
				getline(cin, Toll);
				cout << "Enter distance (miles):" << endl;
				cin>>distance;
				cout << "Enter speed limit (mph):" << endl;
				cin>>speed;
				time = distance/speed;
				if(Toll == "Yes")
                {
                    toll = true;
                }
                else if(Toll == "No")
                {
                    toll = false;
                }
				cityGraph.addVertex(city1);
				cityGraph.addEdge(city1, city2, distance, time, toll);
                break;
            }
        case 3:
            {
				string startingCity, endingCity;
				cout << "Enter a starting city:" << endl;
				getline(cin, startingCity);
				cout << "Enter an ending city:" << endl;
				getline(cin, endingCity);
				cityGraph.shortestDistance(startingCity, endingCity);
                break;
            }
        case 4:
            {
                string starting, ending;
                cout << "Enter a starting city:" << endl;
                getline(cin, starting);
                cout << "Enter an ending city:" << endl;
                getline(cin, ending);
                cityGraph.shortestTime(starting, ending);
                break;
            }
        case 5:
            {
				string starting, ending;
				cout << "Enter a starting city:" << endl;
				getline(cin, starting);
				cout << "Enter an ending city:" << endl;
				getline(cin, ending);
                cityGraph.longestPath(starting, ending);
                break;
            }
        case 6:
            {
                cityGraph.avoidToll();
                break;
            }
        case 7:
            {
                string starting;
                cout << "Enter a starting city:" << endl;
                getline(cin, starting);
                cityGraph.showAlltimeDistance(starting);
                break;
            }
        case 8:
            {
                string starting;
                cout << "Enter a city:" << endl;
                getline(cin, starting);
                cityGraph.deleteCity(starting);
                break;
            }
        case 9:
            {
                cout<<"Goodbye!"<<endl;
                n++;
                return 0;
                break;
            }
        }
    }
}
