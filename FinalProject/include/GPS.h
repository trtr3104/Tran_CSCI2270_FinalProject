#ifndef GPS_H
#define GPS_H
#include<vector>
#include<iostream>
#include <string>

struct vertex;

struct adjVertex{
    vertex *v;
    int weight;
    int time;
    bool toll;
};

struct vertex{
    vertex *parent;
    std::string name;
    bool visited;
    int distance;
    int duration;
    bool toll;
    std::vector<adjVertex> adj;
};

struct queueVertex{
    int distance;
    int duration;
    std::vector<vertex *> path;
};
class GPS
{
    public:
        GPS();
        ~GPS();
        void addEdge(std::string v1, std::string v2, int weight, int time, bool toll);
        void addVertex(std::string name);
        void displayEdges();
        void showAlltimeDistance(std::string startingCity);
        void shortestDistance(std::string starting, std::string ending);
        void shortestTime(std::string starting, std::string ending);
		void longestPath(std::string startingCity, std::string endingCity);
		void avoidToll();
		void deleteCity(std::string city);
		void deleteEdge(std::string city1, std::string city2);

    protected:
    private:
        std::vector<vertex> vertices;
        int shortestRoadTrip;
		int longestPathTrip;
		bool avoidTollFlag;
        std::vector<std::string> roadTripName;
        std::vector<std::string> shortestRoadTripName;
		std::vector<std::string> longestPathName;
        vertex * findVertex(std::string name);
        //call this from within assignDistricts to label the districts.
        //This method should implement a breadth first traversal from the startingCity
        //and assign all cities encountered the distID value
        void BFTraversalLabel(std::string startingCity, int distID);
		void DFS_trip(vertex* s, vertex* endVertex, int depth, int totalDist, const bool findLongestPath);

};

#endif // GRAPH_H
