//Deven Damiano dad152@zips.uakron.edu
//Data Structures Project 3

#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <stack>
using namespace std;

struct Edge
{
    int src, dest, weight;
};

struct Graph
{
    int number_of_vertices;
    list< pair<int, int> > *adj;
    
    Graph()
    {
        number_of_vertices = 0;
    }
    
    Graph(int number_of_vertices)
    {
        this->number_of_vertices = number_of_vertices;
        adj = new list< pair<int, int> >[number_of_vertices];
    }
    
    void add_edge(Edge edge)
    {
        adj[edge.src].push_back(make_pair(edge.dest, edge.weight));
    }
    
    void print_graph()
    {
        for (int i = 0; i < number_of_vertices; i++)
        {
            bool canPrint = false;
            
            for (pair<int, int> v : this->adj[i])
            {
                cout << "[" << i << "," << v.first << "," << v.second << "] ";
                canPrint = true;
            }
            
            if(canPrint)
            {
                cout << endl;
            }
        }
    }
    
    void topological_sort_loop(int v, bool visited[], stack<int>& Stack)
    {
        visited[v] = true;
        
        list< pair<int, int> >::iterator i;
        for (i = this->adj[v].begin(); i != this->adj[v].end(); ++i)
        {
            if(!visited[i->first])
            {
                topological_sort_loop(i->first, visited, Stack);
            }
        }
        
        Stack.push(v);
    }
    
    void topological_sort()
    {
        stack<int> Stack;
        
        bool* visited = new bool [number_of_vertices];
        
        for (int i = 0; i < number_of_vertices; i++)
        {
            visited[i] = false;
        }
        
        for (int i = 0; i < number_of_vertices; i++)
        {
            if (visited[i] == false)
            {
                topological_sort_loop(i, visited, Stack);
            }
        }
        
        while(Stack.empty() == false)
        {
            cout << Stack.top() << " ";
            Stack.pop();
        }
    }
};

vector<Edge> open_input(vector<Edge>);
void sort(vector<Edge>);


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
                edges = open_input(edges);
                break;
            case 2:
                sort(edges);
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

vector<Edge> open_input(vector<Edge> edges)
{
    string file_string;
    
    vector<string>fileVect;
    
    cout << "Input the file name:\n";
    
    getline(cin, file_string);
    
    ifstream inFile;
    
    inFile.open(file_string);
    //inFile.open("graph.txt");
    
    while(!inFile.eof())
    {
        getline(inFile, file_string);
        //cout << file_string << endl;
        fileVect.push_back(file_string);
    }
    inFile.close();
    
    cout << "\nFILE OPENED..." << endl << endl;
    
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

void sort(vector<Edge> edges)
{
    Graph graph(edges.size());
    
    for (int i = 0; i < edges.size(); i++)
    {
        graph.add_edge(edges[i]);
    }
    
    cout << "\nAdjacency List Representation of Graph:\n";
    graph.print_graph();
    cout << endl;
    
    cout << "Topological Sorting of Graph:\n";
    graph.topological_sort();
    cout << endl << endl;
    
    
}
