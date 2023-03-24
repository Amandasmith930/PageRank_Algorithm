#include <iostream>
#include<unordered_map>
#include<map>
#include<vector>
#include <iomanip>

//Conceptual advice from Julia TA office hours, used Julia's P2Help sheet from the slack for setting up my graph,
//tested with some cases sent in slack
//used the base code outline given from the project documentation
using namespace std;

class AdjacencyList {
public:
    map<string, vector<pair<string, float>>> in;
    map<string, float> degreeOut;
    map<string, float> rank;

    void initialize();

public:
    AdjacencyList() = default;

    void PageRank(int n);

    void CreateEdge(string from, string to);

    void calculateDegree();

    void print();
};

//initialize the page rank to the proper formula of 1/|V| using the size of the degrees in map
void AdjacencyList::initialize() {
    for (auto &iter: in) {
        rank[iter.first] = 1.00f / (float) in.size();
    }
}

//iterate through the in map for each vector and for each "from" website calculate the proper 1/outdegree after completely making the outdegree map
void AdjacencyList::calculateDegree() {
    for (auto entry: in) {
        float temp = 0.00f;
        for (int i = 0; i < entry.second.size(); i++) {
            //calculate the degree store it in a temp and then update the float in the In map
            temp = 1.00f / degreeOut[entry.second[i].first];
            in[entry.first][i].second = temp;
        }
    }
}

//function to test, print all values in the in and degreeOut maps to ensure the maps are correct
void AdjacencyList::print() {
    for (auto entry: degreeOut) {
        cout << entry.first << " " << entry.second << endl;
    }
    for (auto it: in) {
        for (int i = 0; i < in[it.first].size(); i++) {
            cout << it.first << " " << it.second[i].first << " " << it.second[i].second << endl;
        }
    }
}

void AdjacencyList::PageRank(int n) {
    initialize();
    map<string, float> currentRank;
    //iterate through for n times, for each power iteration
    for (int i = 1; i < n; i++) {
        currentRank = rank; //set rank equal to the temp current rank
        float individualRank = 0.00f;
        for (auto &iter: in) {
            for (int j = 0; j < iter.second.size(); j++) {
                //the rank of each "to" website is equal to the sum of the current "to" website multiplied by
                // the calculated rank from the initialize function which is 1/V
                individualRank += (float) iter.second[j].second * currentRank[iter.second[j].first];
            }
            rank[iter.first] = individualRank;
            //must reset the individual website rank to zero after each iteration
            individualRank = 0.00f;
        }
    }
//print out the rank using precision and fixed to ensure proper rounding
    for (auto it: rank) {
        cout << setprecision(2) << fixed << it.first << " " << it.second << endl;
    }
}

//create the edge from two from and to vertices. Add the out degree to the from->to edge
//and add each to->from edge to the In map. If the to vertex is not existant set the degreeOut = 1.00
void AdjacencyList::CreateEdge(string from, string to) {
    in[to].push_back(make_pair(from, -1.00));
    if(in.find(from) == in.end()){
        in[from] = {};
    }
    //if it does not exist in the map add it with a value of 1.00, there is an outdegree of 1
    if (degreeOut.find(from) == degreeOut.end()) {
        degreeOut[from] = 1.00;
    } else {
        //increment value if it exists in map
        degreeOut[from]++;
    }
}
////watch his adj list video i need a few more if statements to handle when outdegree isnt anything yet for create edge
int main() {
    int no_of_lines, power_iterations;

    cin >> no_of_lines;
    cin >> power_iterations;

    AdjacencyList graph;
    for (int i = 0; i < no_of_lines; i++) {
        string from, to;
        cin >> from;
        cin >> to;
// create the edge from the given from and to vertices
        graph.CreateEdge(from, to);
        // printing the map!
        cout << endl;
        cout << endl;
    }
    graph.calculateDegree();
   //  graph.print();
    //Create a graph object
    graph.PageRank(power_iterations);
}

