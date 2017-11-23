//Deven Damiano dad152@zips.uakron.edu

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#define N 6

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    vector< pair<int,int> > adjList[N];
    
    Graph(vector<Edge> edges)
    {
        for (int i = 0; i < edges.size(); i++)
        {
            int src = edges[i].src;
            int dest = edges[i].dest;
            int weight = edges[i].weight;
            
            adjList[src].push_back(make_pair(dest, weight));
        }
    }
    
};

vector<Edge> openInput(vector<Edge>);
void sort();


int main()
{
    int choice;
    string file_string;
    
    vector<Edge> edges;
    
    while(true)
    {
        cout << "Enter one of the following options and hit enter: \n";
        cout << "1) Open Input File\n";
        cout << "2) Topological Sort\n";
        cout << "3) Quit\n";
        
        cin >> choice;
        
        cin.ignore(1000,'\n');
        
        switch (choice)
        {
            case 1:
                edges = openInput(edges);
                
                for(int i = 0; i < edges.size(); i++)
                {
                    cout << edges[i].src << " " << edges[i].dest << " " << edges[i].weight << endl;
                }
                break;
            case 2:
                sort();
                break;
            case 3:
                cout << "Quitting...\n";
                return 0;
            default:
                cout << "Incorrect Input..\n";
            
        }
    }
    
    return 0;
}

vector<Edge> openInput(vector<Edge> edges)
{
    string file_string;
    
    vector<string>fileVect;
    
    
    
    //getline(cin, file_string);
    
    ifstream inFile;
    
    //inFile.open(file_string);
    inFile.open("graph.txt");
    
    while(!inFile.eof())
    {
        getline(inFile, file_string);
        cout << file_string << endl;
        fileVect.push_back(file_string);
    }
    inFile.close();
    
    cout << "FILE OPENED..." << endl;
    
    for (int i = 0; i < fileVect.size(); i++)
    {
        string current = fileVect[i];
        Edge current_edge;
        int space_counter = 0;
        int j = 0;
        
        while(j != current.size())
        {
            if(!isspace(current[j]) && space_counter == 0)
            {
                current_edge.src = current[j] - '0';
            }
            else if(!isspace(current[j]) && space_counter == 1)
            {
                current_edge.dest = current[j] - '0';
            }
            else if(!isspace(current[j]) && space_counter == 2)
            {
                current_edge.weight = current[j] - '0';
            }
            else
            {
                space_counter++;
            }
            
            j++;
        }
        
        edges.push_back(current_edge);
    }
    
    
    return edges;
    
}

void sort()
{
    cout << "We are sorting...\n";
    
}
