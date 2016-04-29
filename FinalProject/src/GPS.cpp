#include "GPS.h"
#include <vector>
#include <iostream>
#include <climits>

using namespace std;

GPS::GPS()
{
    //ctor
	avoidTollFlag = false;
}

GPS::~GPS()
{
    //dtor
}

void GPS::addEdge(std::string v1, std::string v2, int weight, int time, bool toll)
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    av.time = time;
                    av.toll = toll;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    av2.time = time;
                    av2.toll = toll;
                    vertices[j].adj.push_back(av2);
                }
            }
        }
    }
}

void GPS::addVertex(std::string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            std::cout << vertices[i].name <<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);
    }
}

void GPS::displayEdges(){
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if(j != vertices[i].adj.size()-1)
                cout<<"***";
        }
        cout<<endl;
    }
}


vertex * GPS::findVertex(std::string name)
{
	for (int i = 0; i < vertices.size(); ++i)
		if (vertices[i].name == name)
			return &vertices[i];

	return 0;
}

void GPS::BFTraversalLabel(std::string startingCity, int distID)
// Note: this function is called by assignDistrict, and shortestPath
// since they utilize BFS algorithm.
// shortestPath will pass distID = -1
{
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].visited = false;
		vertices[i].distance = INT_MAX/2;
		vertices[i].parent = 0;
	}

	vertex* startingVertex = findVertex(startingCity);
	std::vector<vertex> source, dest;

	startingVertex->distance = 0;
	startingVertex->visited = true;

	source.push_back(*startingVertex);

	while (source.size() > 0)
	{
		dest.clear();

		for (int srcIdx = 0; srcIdx < source.size(); ++srcIdx)
			for (int adjIdx = 0; adjIdx < source[srcIdx].adj.size(); ++adjIdx)
                // find shortest distance
				{
					int sourceDist = source[srcIdx].distance;
					int weight = source[srcIdx].adj[adjIdx].weight;// weight from source to its adj

					//if (source[srcIdx].adj[adjIdx].v->distance > sourceDist + weight)
					if(false == source[srcIdx].adj[adjIdx].v->visited)
					{
					    source[srcIdx].adj[adjIdx].v->visited = true;
						source[srcIdx].adj[adjIdx].v->distance = sourceDist + weight;
						source[srcIdx].adj[adjIdx].v->parent = findVertex(source[srcIdx].name);
						dest.push_back(*(source[srcIdx].adj[adjIdx].v));
					}
				}
		source = dest;
	}
}

void GPS::shortestDistance(std::string starting, std::string ending){
    vertex *start = findVertex(starting);
    vertex *endPlace = findVertex(ending);
    if (0 == start || 0 == endPlace)
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else{
        for (int l = 0; l < vertices.size(); l++) {
            vertices[l].visited = false;
            vertices[l].distance = INT_MAX/2;
            vertices[l].parent = NULL;
        }

        start->visited = true;
        start->distance = 0;
        start->parent = NULL;
        vertex *solvedV;
        vertex *s;
        vertex *previous;
        int minDist;
        int dist;
        vector<vertex*> solved;
        solved.push_back(start);
        while(true){
            minDist = INT_MAX;
            solvedV = NULL;
            for(int i=0; i<solved.size(); i++){
                s = solved[i];
                for(int j=0; j<s->adj.size(); j++) {
                    if(!s->adj[j].v->visited && (!avoidTollFlag || !s->adj[j].toll)){
                        dist = s->distance + s->adj[j].weight;
                        if(dist < minDist){
                            solvedV = s->adj[j].v;
                            minDist = dist;
                            previous = s;
                        }
                    }
                }
            }

			if (solvedV == NULL)
			{
				break;
			}
            solvedV->distance = minDist;
            solvedV->parent = previous;
            solvedV->visited = true;
            solved.push_back(solvedV);
        }
			vector<vertex>path;
			vertex *current = endPlace;
			while (current != 0) {
				path.push_back(*current);
				current = current->parent;
			}
			if (path.size() > 1)
			{
				cout << endPlace->distance;
				for (int k = path.size() - 1; k >= 0; --k) {
					cout << "," << path[k].name;
				}
				cout << endl;
			}
			else
			{
				cout << "No path found between " << starting << " and " << ending << endl;
			}
    }
}

// return: shortest road trip if shortestPath parameter is true.
//         Otherwise, longest path.
void GPS::DFS_trip(vertex* s, vertex* endVertex, int depth, int totalDist, const bool findLongestPath)
{
    roadTripName.push_back(s->name);
    if (s->name == endVertex->name)
    {
		if (findLongestPath)
		{
			if (longestPathTrip < totalDist)
			{
				longestPathTrip = totalDist;
				longestPathName = roadTripName;
			}
		}
		else
		{
			if (shortestRoadTrip > totalDist)
			{
				shortestRoadTrip = totalDist;
				shortestRoadTripName = roadTripName;
			}
		}
    }
    else
    {
        for(int j=0; j<s->adj.size(); j++)
        {
            if (s->adj[j].v->visited == false && (!avoidTollFlag || !s->adj[j].toll))
            {
                s->adj[j].v->visited = true;
                DFS_trip(s->adj[j].v, endVertex, depth+1, totalDist+s->adj[j].weight, findLongestPath);
                s->adj[j].v->visited = false;
            }
        }
    }
    roadTripName.pop_back();
}

void GPS::longestPath(std::string startingCity, std::string endingCity)
{
	for (int l = 0; l < vertices.size(); l++) {
		vertices[l].visited = false;
		vertices[l].distance = 0;
		vertices[l].parent = NULL;
	}

	vertex *startVertex = findVertex(startingCity);
	vertex *endVertex = findVertex(endingCity);
	if (0 == startVertex || 0 == endVertex)
	{
		cout << "One or more cities doesn't exist" << endl;
	}
	else
	{
		startVertex->visited = true;

		longestPathTrip = 0;
		roadTripName.clear();

		DFS_trip(startVertex, endVertex, 0, 0, true);

		cout << longestPathTrip << endl;
		cout << longestPathTrip;
		for (int i = 0; i < longestPathName.size(); ++i)
		{
			cout << "," << longestPathName[i];
		}
		cout << endl;
	}
}

void GPS::shortestTime(std::string starting, std::string ending){
    vertex *start = findVertex(starting);
    vertex *endPlace = findVertex(ending);
    if (0 == start || 0 == endPlace)
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else{
        for (int l = 0; l < vertices.size(); l++) {
            vertices[l].visited = false;
            vertices[l].duration = INT_MAX/2;
            vertices[l].parent = NULL;
        }

        start->visited = true;
        start->duration = 0;
        start->parent = NULL;
        vertex *solvedV;
        vertex *s;
        vertex *previous;
        int minTime;
        int time;
        vector<vertex*> solved;
        solved.push_back(start);
        while(true){
            minTime = INT_MAX;
            solvedV = NULL;
            for(int i=0; i<solved.size(); i++){
                s = solved[i];
                for(int j=0; j<s->adj.size(); j++) {
                    if(!s->adj[j].v->visited && (!avoidTollFlag || !s->adj[j].toll)){
                        time = s->duration + s->adj[j].time;
                        if(time < minTime){
                            solvedV = s->adj[j].v;
                            minTime = time;
                            previous = s;
                        }
                    }
                }
            }
			if (solvedV == NULL)
			{
				break;
			}
            solvedV->duration = minTime;
            solvedV->parent = previous;
            solvedV->visited = true;
            solved.push_back(solvedV);
        }
			vector<vertex>path;
			vertex *current = endPlace;
			while (current != 0) {
				path.push_back(*current);
				current = current->parent;
			}
			if (path.size() > 1)
			{
				cout << endPlace->distance;
				for (int k = path.size() - 1; k >= 0; --k) {
					cout << "," << path[k].name;
				}
				cout << endl;
			}
			else
			{
				cout << "No path found between " << starting << " and " << ending << endl;
			}
    }
}

void GPS::avoidToll()
{
	// toggle avoid toll flag
	avoidTollFlag = !avoidTollFlag;
	if (avoidTollFlag)
	{
		cout << "Avoid toll On" << endl;
	}
	else
	{
		cout << "Avoid toll Off" << endl;
	}
}

void GPS::showAlltimeDistance(std::string starting)
{
    vertex *start = findVertex(starting);
    if (0 == start)
    {
        cout << "One or more cities doesn't exist" << endl;
    }
    else{
        for (int l = 0; l < vertices.size(); l++) {
            vertices[l].visited = false;
            vertices[l].duration = INT_MAX/2;
            vertices[l].distance = INT_MAX/2;
            vertices[l].parent = NULL;
        }
        start->visited = true;
        start->duration = 0;
        start->distance = 0;
        start->parent = NULL;
        vertex *solvedV;
        vertex *s;
        vertex *previous;
        int minTime;
        int minDist;
        int time;
        int dist;
        vector<vertex*> solved;
        solved.push_back(start);
        while(true){
            minTime = INT_MAX;
            minDist = INT_MAX;
            solvedV = NULL;
            for(int i=0; i<solved.size(); i++){
                s = solved[i];
                for(int j=0; j<s->adj.size(); j++) {
                    if(!s->adj[j].v->visited && (!avoidTollFlag || !s->adj[j].toll)){
                        time = s->duration + s->adj[j].time;
                        dist = s->distance + s->adj[j].weight;
                        if(time < minTime){
                            solvedV = s->adj[j].v;
                            minTime = time;
                            previous = s;
                        }
                        if(dist < minDist){
                            solvedV = s->adj[j].v;
                            minDist = dist;
                            previous = s;
                        }
                    }
                }
            }
			if (solvedV == NULL)
			{
				break;
			}
            solvedV->duration = minTime;
            solvedV->distance = minDist;
            solvedV->parent = previous;
            solvedV->visited = true;
            solved.push_back(solvedV);
        }
        for (int l = 0; l < vertices.size(); l++){
            if (vertices[l].visited && (vertices[l].parent != NULL)){
                cout << vertices[l].name << ":  Distance - " <<vertices[l].distance << ", Time - " << vertices[l].duration <<endl;
            }
        }
    }
}

void GPS::deleteCity(std::string city)
{
    vertex *delCity = findVertex(city);
	int delCityIdx = 0;

	for (int i = 0; i < vertices.size(); ++i)
		if (vertices[i].name == city)
		{
			delCity = &vertices[i];
			delCityIdx = i;
		}

	if (0 == delCity)
	{
		cout << "City doesn't exist" << endl;
	}
	else
	{
		for (int j = 0; j < delCity->adj.size(); j++) {
			deleteEdge(delCity->name, delCity->adj.at(j).v->name);
		}

		vertices.erase(vertices.begin() + delCityIdx);
	}
}

void GPS::deleteEdge(std::string city1, std::string city2)
{
	vertex *v1 = findVertex(city1);
	vertex *v2 = findVertex(city2);

	for (int j = 0; j < v1->adj.size(); j++)
		if (v1->adj[j].v->name == city2)
		{
			v1->adj.erase(v1->adj.begin() + j);
			break;
		}
	for (int j = 0; j < v2->adj.size(); j++)
		if (v2->adj[j].v->name == city1)
		{
			v2->adj.erase(v2->adj.begin() + j);
			break;
		}
}
