//NOTES:
//graph implementation using adjacency list from own stepik 7.1.2 answer

#include<sstream>
#include <iostream>
#include<cstring>
#include<map>
#include<vector>
#include<iomanip>
using namespace std;

class AdjacencyList{
private:
    int totNumEdges = 0;
public:
    map<string, vector<string>> adjListIntermediate;//original adjacency list
    map<string, vector<pair<string, double>>> pageRanks;//intermediate page ranks for all elements
    vector<double> powerIters;
    map<string, double> finalOutput;//final output of url and page ranks

    //creation functions
    void insertEdge(string from, string to);
    void makePageRank();
    void powerIter(int pow);

    //testing functions
    void printGraph();
};

void AdjacencyList::insertEdge(string from, string to){
    //insert edges into graph
    adjListIntermediate[from].push_back(to);
    totNumEdges++;

    if (adjListIntermediate.find(to) == adjListIntermediate.end())
        adjListIntermediate[to] = {};
}

void AdjacencyList::makePageRank() {
    //determine matrix values for each element (1/outdegs)
    for (auto itr = adjListIntermediate.begin(); itr != adjListIntermediate.end(); itr++){
        if ((*itr).second.size() == 0){
            cout << fixed;
            cout << setprecision(2);
            float pageRank = 0.0f;
            pageRanks[(*itr).first].push_back(make_pair("", pageRank));
        }
        for (int i = 0; i < (*itr).second.size(); i++){
            cout << fixed;
            cout << setprecision(2);
            float pageRank = 1.0f/(*itr).second.size();
            pageRanks[(*itr).first].push_back(make_pair((*itr).second[i], pageRank));
        }
    }
}

void AdjacencyList::powerIter(int pow){
    //do power iterations
    float r = 1.0f/adjListIntermediate.size();

    //when default or p = 1 makes r(0)
    for (int i = 0; i < adjListIntermediate.size(); i++){
        powerIters.push_back(r);
    }

    //special case of pow = 1
    if (pow == 1){
        //make r(0) final output
        int i = 0;
        for (auto itr = pageRanks.begin(); itr != pageRanks.end(); itr++) {
            finalOutput[(*itr).first] = powerIters.at(i);
            i++;
        }
    }
        //all other cases
    else{
        vector<double> toReturn;

        //loop for calculations up to pow
        for (int u = 0; u < (pow - 1); u++){
            //initialize values to return to zero (reset if needed)
            if (!toReturn.empty())
                toReturn.clear();
            for (int i = 0; i < adjListIntermediate.size(); i++)
                toReturn.push_back(0.0f);

            //matrix multiplication (dot product)
            int k = 0;
            string curr = (*pageRanks.begin()).first;
            for (auto iter = pageRanks.begin(); iter != pageRanks.end(); iter++){
                int j = 0;
                for (auto itr = pageRanks.begin(); itr != pageRanks.end(); itr++){
                    int i = 1;
                    for (auto it = (*itr).second.begin(); it != (*itr).second.end(); it++){
                        if (i == 1)
                            j++;
                        if ((*it).first == (*iter).first) {
                            if ((*iter).first != curr){
                                k++;
                                curr = (*iter).first;
                            }
                            toReturn.at(k) += (powerIters.at(j - 1) * (*it).second);
                        }
                        i++;
                    }
                }
            }

            //copy values from toReturn to powerIters for possible future use
            for (int i = 0; i < powerIters.size(); i++){
                powerIters[i] = toReturn[i];
            }
        }

        //transfer values into map with related url
        int i = 0;
        for (auto itr = pageRanks.begin(); itr != pageRanks.end(); itr++) {
            finalOutput[(*itr).first] = toReturn.at(i);
            i++;
        }
    }
}

void AdjacencyList::printGraph(){
    //print final outputs (power iterators)
    for (auto itr = finalOutput.begin(); itr != finalOutput.end(); itr++){
        cout << (*itr).first << " " << (*itr).second << endl;
    }
}

int main() {
    AdjacencyList adjL;
    int numLines, powIter;
    string from, to;

    //take in input
    cin >> numLines;
    cin >> powIter;

    //insert edges into graph
    for (int i = 0; i < numLines; i++){
        cin >> from;
        cin >> to;

        adjL.insertEdge(from, to);
    }

    //calculate page rank/power iterations
    adjL.makePageRank();
    adjL.powerIter(powIter);
    adjL.printGraph();
}
