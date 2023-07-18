#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

// make sure both file names match when running code
using namespace std;

int best_time=INT_MAX;
vector<int> best_path; // set vertices size and default values 0
vector<char> cities({ 'H','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'});

void Hamiltonian_Circuit();

vector<vector<int>> ReadFromFile() {

        ifstream inputFile("test4.txt"); // Open the input file

        // Declare variables for storing the data
        vector<pair<char, char>> edges; // Vector of edges
        vector<int> weights; // Vector of weights
        string input;
        map<char, int> vertexIndices; // Map vertex names to indices

        vector<char> cities;
        // Read the vertices from the file
        getline(inputFile, input, '{');
        getline(inputFile, input, '}');
        int startIndex = 0;
        int index = 0;;
        while (startIndex < input.size()) {
            if (input[startIndex] != ',') {
                cities.push_back(input[startIndex]);
                vertexIndices[input[startIndex]] = index;
                index++;
            }

            startIndex++;
        }
        int numVertices = cities.size();
        vector<int> cities_index(4);
        for(int i = 0; i < cities.size(); i++) {
            cities_index.push_back(i);
        }

        // Read the edges from the file
        getline(inputFile, input, '{');
        getline(inputFile, input, '}');
        startIndex = 0;
        while (startIndex < input.size()) {
            if (input[startIndex] == '(') {
                startIndex++;
                continue;
            }

            edges.push_back(make_pair(input[startIndex], input[startIndex + 2]));
            if (startIndex + 5 < input.size())
                startIndex += 5;
            else
                break;
            
        }
        edges;
        int numEdges = edges.size()-1;

        // Read the weights from the file
        getline(inputFile, input, '{');
        getline(inputFile, input, '}');
        startIndex = 0;
        string temp_num;
        while (startIndex < input.size()) {
            temp_num = "";
            while (input[startIndex] != ','){
                if (input[startIndex] == '}' || startIndex >= input.size() )
                    break;
                temp_num += input[startIndex];
                startIndex++;
            }
            
           
            weights.push_back(atoi(temp_num.c_str()));
            weights;
            if (input[startIndex] == '}') {
                break;
            }
            if (startIndex < input.size() )
                startIndex++;
            else
                break;
            
        }
        weights;
        // Initialize the adjacency matrix with all zeros
        vector<vector<int>> adjMatrix(cities.size(),vector<int>(cities.size(),0));

        // Update the adjacency matrix based on the edges and weights
        for (int i = 0; i < numEdges; i++) {
            char startVertex = edges[i].first;
            char endVertex = edges[i].second;
            int weight = weights[i];



            int startIndex = vertexIndices[startVertex];
            int endIndex = vertexIndices[endVertex];
            adjMatrix[startIndex][endIndex] = weight;
            adjMatrix[endIndex][startIndex] = weight; // For undirected graph
        }

        // Print the adjacency matrix
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
        cout << "--------------------" << endl;
        // Close the input file
        inputFile.close();

        
    
        return adjMatrix;
}

vector<int> ReadTotalTime() {
    
    vector<int> total_time;
    total_time.push_back(0); // for 1st index

    ifstream inputFile("test4.txt"); // Open the input file

    string input;
    // Read the vertices from the file
    for (int i = 0; i < 4; i++) {
        getline(inputFile, input);
    }


    input;
    int starting_index = 0;
    int time=0;
    for (; starting_index < input.size();) {
        if (input[starting_index] == '(') {
            

            if ((static_cast<int>(input[starting_index + 5]) >= 48) && (static_cast<int>(input[starting_index + 5]) <= 57 && starting_index+5<input.size()))
                // check for double digits
            {

               
                time += (static_cast<int>(input[starting_index + 4]) - 48) * 10;

               
                time += input[starting_index + 5] - 48;
            }
            else {
                
                time += input[starting_index + 4] - 48;
            }

            
            
            starting_index += 3;

            total_time.push_back(time);
            time = 0;
        }
        
        if (starting_index < input.size()) {
            starting_index++;
            }
        else {
            break;
        }
            
    }
    
    // reading total_time now
    getline(inputFile, input);
    
    int time_temp = 0;
    
    int index = 2;
    string temp_num = "";
    while (index < input.size()) {

        temp_num += input[index];
        index++;
    }
    time_temp = (atoi(temp_num.c_str()));
    
    
    total_time[0] = time_temp;
        
    return total_time;
}


void print_path(vector<int>& temp) { // of cities
    for (int i = 0; i < temp.size(); i++) {
        if(i!=0)
            cout <<" -> "<< cities[temp[i]] ;
        if(i==0)
            cout << cities[temp[i]];
    }

    cout << endl;
}
//void Next_Vertex(int);

void Find_Hamiltonian_Circuit(vector<vector<int>>& Matrix, vector<int>& current_path, vector<bool> &visited, int& current_selection, int& time) {

    // check if cycle has been found , array must be full and last element should be connected with start
    if ( Matrix.size() == current_path.size() && Matrix[current_selection][0] != 0) {

        current_path.push_back(0); // connect with starting vertex
        time += Matrix[current_selection][0]; // add ending edge time

        // check if its time is less than best time and update best path array
        cout << "time : " << time << endl;;
        if (time < best_time) { // new better hamiltonian cycle has been found
            best_path = current_path; // copy into new best path
            best_time = time; // update time
            
        }

        print_path(current_path);
        cout << endl << "--------------------" << endl;
        
        time -= Matrix[current_selection][0]; // remove values so that you can test for other edges in recursive
        current_path.pop_back();
        
        return;
    }


    for (int i = 0; i < Matrix.size(); i++) {

        if (visited[i] == false) { // before adding new vertex check if its not been visited yet

            if (Matrix[current_selection][i]) // check for edge before adding
            {
                current_path.push_back(i);
                visited[i] = true;
                time += Matrix[current_selection][i]; // add edge weight
                //filled++;

                Find_Hamiltonian_Circuit(Matrix, current_path, visited, i, time); // recursively call func for other edges

                visited[i] = false;
                //filled--;
                current_path.pop_back();
                time -= Matrix[current_selection][i];

            }

        }



    }

}


int main() {

    vector<vector<int>> Matrix;
    Matrix = ReadFromFile();
    vector<int> total_time;
    total_time = ReadTotalTime();
    int req_time = total_time[0]; // stored in 1st vertex
    int current_time = 0;
    for (int i = 1; i < total_time.size(); i++) {
        current_time += total_time[i];
    }
        // check if total time taken by robot dsnt exceed
    if (req_time < current_time) {
        cout << "HAMILTONIAN CIRCUIT NOT FEASIBLE " << endl;
        return 0; // terminate
    }


    vector<int> current_path;

    vector<bool> visited(Matrix.size(), false); // initially all vertices are unvisited


    current_path.push_back(0); // starting vertex
    visited;
    visited[0] = true;


    int i = 0;
    int vertex = 0;
    int filled_elements= 4; // 1 element already added 

    int current_selection = 0;
    int time = 0;

    Find_Hamiltonian_Circuit(Matrix, current_path, visited, current_selection, time);

    //

        cout << "best time : " << best_time+current_time  << endl;
        cout << "best path : ";
    
    print_path(best_path);
    return 0;
}


    