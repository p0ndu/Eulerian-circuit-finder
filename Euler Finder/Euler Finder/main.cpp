//
    //  main.cpp
    //  Euler Circuit Finder
    //
    //  Created by Alexander Ley on 19/02/2024.
    //
    #include <set>
    #include <iostream>
    #include <algorithm>
    using namespace std;


    class Graph
    {
    private:
        vector<vector<char>> edges;
        set<char> vertices;
        
        
        
        vector<char> getConnections(char charToFind)
        {
            vector <char> bufferVec;
            
            for (int i = 0; i < edges.size(); i++)
            {
                if (charToFind == edges[i][0])
                {
                    bufferVec.push_back(edges[i][1]);
                }
                else if (charToFind == edges[i][1])
                {
                    bufferVec.push_back(edges[i][0]);
                }
                
                
            }
            
            return bufferVec;
        }
        
        
        vector<char> removeItem(vector<char> vec, char item) // removes item from vec if it is inside of it, if not does nothing
        {
            auto it = vec.begin(); //using auto because i dont really know what datatype its supposed to be lmao       ***** ask the ginger SLA guy about this *****
            
            for(int i = 0; i < vec.size(); i++)
            {
                
                if (vec[i] == item)
                {
                    vec.erase(it)    ;
                }
                it ++;
            }
            return vec;
        }
        
        
        void removeEdge(vector<char> edge) //removes the edge from the list of edges, goes both ways so if you pass {a,b} it will do the same as {b,a}
        {
            auto it = edges.begin();
            
            vector<char> revEdge = edge; //basically a buffer for the reversed version of the edge
            reverse(revEdge.begin(), revEdge.end());
            
            
            for (int i = 0; i < edges.size(); i++)
            {
                if ((edges[i] == edge) || (edges[i] == revEdge))
                {
                    edges.erase(it);
                }
                it++;
            }
        }
        
        
        bool isIn (vector<char> vec, char item) // returns true if item is in vec, false if it isnt
        {
            bool result = false;
            for (int i = 0; i < vec.size(); i++)
            {
                if (vec[i] == item)
                {
                    result = true;
                    i = vec.size();
                }
            }
            return result;
        }
        
        
        bool isEdge (vector <char> edge)
        {
            bool returnVal = false;
            vector<char> revEdge = edge;
            reverse(edge.begin(), edge.end());
            
            for (int i = 0; i < edges.size(); i++)
            {
                if ((edges[i] == edge) || (edges[i] == revEdge))
                {
                    returnVal =  true;
                }
            }
            return returnVal;
        }
        
        
        

        
        void createCircuit(char node, vector<char>& circuit) //WIP
        {
            for (char neighbour : getConnections(node))
            {
                if (isEdge(vector<char> {node, neighbour})) // if node,neighbour is exists as an untraversed edge
                {
                    removeEdge(vector<char> {node, neighbour});
                    createCircuit(neighbour, circuit);
                    circuit.push_back(node);
                    
                   
                }
            }
            
            
            
        }
        
        
        
        
        
        
        
    public:
        vector<vector <char>> getEdges()
        {
            return edges;
        }
        
        set<char> getVertices()
        {
            return vertices;
        }
        
        void setupGraph(string inputData)
        {
            
            char v1, v2, bufferArray[3];
            string bufferString;
            vector <char> bufferVector;
            
            
            for (int i = 0; i <= ((inputData.length() - 2) / 6); i++)//loops through the string and pulls out the vertices/edges to add to the objects attributes
            {
                bufferString = inputData.substr(i * 6 + 2, 3);
                strcpy(bufferArray, bufferString.c_str());
                
                v1 = bufferArray[0];
                v2 = bufferArray[2];
                
                
                vertices.insert(v1);
                vertices.insert(v2);
                
                bufferVector.push_back(v1);
                bufferVector.push_back(v2);
                edges.push_back(bufferVector);
                
                bufferVector.clear();
                
                
                
                
                
            }
            

        }
        
        vector<char> eulerCircuit(char startNode)
        {
            vector<char> circuit;
            
            createCircuit(startNode, circuit);
            vector<char> revCircuit = circuit;
            reverse(revCircuit.begin(), revCircuit.end());
            revCircuit.push_back(startNode); //just to add the start node at the end making an actual circuit
            
            
            return revCircuit;
        }
        
        
        
        

    };
    string getInputData()//gets the user input for the graph
    {
        
        string graphBuffer;
        cout << "Please enter your graph, it must be a connected graph with all vertices being of +ve even degree \nEnter it the way you would define a 2d array\nI.E. {{a,b},{b,c},{c,a}} \nmay not have any other characters like trailing/leading spaces \n> ";
        cin >> graphBuffer;
        return graphBuffer;
    }

    int main(int argc, const char * argv[]) {
        Graph newGraph;
        char startNode;
        vector<char> circuit;
        bool loop = true;
        
        while (loop) //just loops incase the user gives a bad input and needs to try again
        {
            try
            {
                newGraph.setupGraph(getInputData()); //sens the user input for the graph to the setupGraph method
                cout << "Please enter the node you would like the circuit to beign at \n> ";
                cin >> startNode;
                circuit = newGraph.eulerCircuit(startNode);
                
                
                cout << "\n\n";
                for (char node : circuit)
                {
                    cout << node << " => ";
                }
                cout << "\n> ";
                
                loop = false;
            }
            
            
            catch (const exception)
            {
                cout << "Error, please input the correct graph and starting vertex \n\n\n\n>";
            }
            
            
        }
        
        
        
      
        
        
        // {{a,b},{b,c},{a,c},{a,d},{c,d},{a,e},{a,f},{e,f},{f,g},{g,c},{f,c},{c,h},{h,i},{i,j},{j,a}}    test graph, to use just paste into the interactions window when running
        
        
        
        
        return 0;
    }
