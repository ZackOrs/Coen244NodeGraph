#include<iostream>
#include<stdlib.h>
#include "Graph.h"
#include <string>

using namespace std;
// By Zachary Orsoli
// April 2018



int main() {
	static const int a = 1;
	int nodes = 0;
	int oldnodes = 0;
	int no_of_node = 0;
	//Initialize objects and varibles to be used
	Node node;
	Node *adj[a];
//	Node* adj = new Node[nodes]
	int command = 0; 	//Allow user to input what will be done
	string weight[100];
	string value[100];
	for (int i = 0; i<100; i++) { //intialize all strings to 0
		weight[i] = "0";
		value[i] = "0";
	}

	cout << "Enter the number for the type of graph that will be made" << endl << endl;

	cout << "1. Undirected graph" << endl;
	cout << "2. Directed graph" << endl << endl;
	cout << "Enter the number for the type of graph: ";
	cin >> command;
	cout << endl;
	while (command != 1 || command != 2) { //If 1 is selected a undirected graph will be created


		if (command == 1) {
			Graph graph;	//undirected graph object is created
							//LIST OF COMMANDS Only appears once to avoid clutter
			cout << "Enter the number for the function to be executed" << endl << endl;
			cout << "1. Add node(s) to the graph with their corresponding edges" << endl;	//(Adds nodes to the graph, then writes edges for each node of the graph)
			cout << "2. Change the edges of a node" << endl;								//Allows user to change edges of a specific node
			cout << "3. Print all Nodes IDs and Edges for the graph" << endl;				//Prints all Vertices and Edges of the graph (How it's shown in the outline)Graph can be empty with no edges or vertices
			cout << "4. Print a specific Node and it's edges" << endl;					//Query a vertex to show all of it's edges
			cout << "5. Verify if an edge exists" << endl;								//Query an edge to see if it exists (In undirected if searching for an edge between 1,2 either (1,2) or (2,1) will be accepted
			cout << "6. Remove a Node" << endl;											//removes a node from the graph (Explained in better detail in the graph.cpp
			cout << "7. Add weights to all edges" << endl;								//adds weights to all the edges in the graph (as a string)
			cout << "8. Print all weights for edges" << endl;								//Prints all the above written weights (if no weights entered beforehand will show 0's)
			cout << "9. Verify if a weight exists" << endl;								//Verify if a weight exists and prints all edges with the weight
			cout << "10. Add Values to the nodes" << endl;								//Add values to the Vertices (as a string)
			cout << "11. Read all Values and Edges for the Graph" << endl;					//Similar to function 3 but now instead of printing ID's it will print with Values
			cout << "12. Path of a specific Value" << endl;								//Print the path of a node by entering it's value (prints the values of other nodes)
			cout << "999. To terminate the program" << endl << endl;						//close the program
			while (command != 999)	//Program will continue until exit command is called (or is closed)
			{
				cout << "------------------------------------------" << endl;
				cout << "0. See Master list of commands" << endl << endl;	//This line reappears at the end of each function in order to call back the list if needed
				cout << "Enter a command to execute a function: ";
				cin >> command;	//cin a new command
				cout << endl;

				switch (command)
				{

				case 0:	cout << "Enter the number for the function to be executed" << endl << endl;
					cout << "1. Add node(s) to the graph with their corresponding edges" << endl;
					cout << "2. Change the edges of a node" << endl;
					cout << "3. Print all nodes IDs and Edges for the graph" << endl;
					cout << "4. Print edges of a specific node" << endl;
					cout << "5. Verify if an edge exists" << endl;
					cout << "6. Remove a Node" << endl;
					cout << "7. Add weights to all edges" << endl;
					cout << "8. Print all weights for edges" << endl;
					cout << "9. Verify if a weight exists" << endl;
					cout << "10. Add Values to the nodes" << endl;
					cout << "11. Read all Values and Edges for the Graph" << endl;
					cout << "12. Path of a specific Value" << endl;
					cout << "999. To terminate the program" << endl << endl;
					cout << "Enter a number to execute a function: ";
					break;


				case 1: 	node.addNode(nodes, no_of_node, oldnodes);		//adds nodes to the graph, keeps tracks of total number of nodes and past nodes incase function is called back
					graph.add(adj[nodes]);		//adds the newly created nodes to the graph
					graph.writegraph(adj, nodes);	//allows to enter the number of edges per node as well as the edges they are connected to
					graph.deleterepeats(adj, nodes);	//only used in undirected graph: if for example edge (1,2) and (2,1) were created in writegraph. This function will remove the (2,1) node
					break;

				case 2:	graph.changeedge(adj, nodes);	//changes the edges of a specific node
					graph.deleterepeats(adj, nodes);	//same purpose as in case 1
					break;

				case 3:	graph.readgraph(adj, nodes);	//prints all the values and all their edges
					break;

				case 4:	graph.specificprint(adj, nodes);	//prints the edges from a specific node ID
					break;

				case 5: 	graph.printedge(adj, nodes);	//query's the edge to verify if it exists
					break;


				case 6: 	graph.removenode(adj, nodes);	//removes a node
					break;

				case 7:	graph.writeweight(adj, weight, nodes);	//adds weights to edges
					break;

				case 8:	graph.readweights(adj, weight, nodes);	//reads the weights
					break;

				case 9:		graph.checkweight(adj, weight, nodes);	//check what edges have a specific weight
					break;

				case 10:	graph.writevalue(adj, value, nodes);		//writes values to the Nodes of Graph
					break;

				case 11:	graph.readvalues(adj, value, nodes);		//Similar to function 3 but prints all information using Values instead of ID's
					break;

				case 12:	graph.specificvalue(adj, value, nodes);	//Query a value to print all of it's edges
					break;

				case 999:	cout << "Terminating the program";
					exit(1);
					break;

				default: cout << "This number does not represent a function" << endl << endl; //If anything other than the above cases are called, program will give this message



				}



			}
			break;
		}
		if (command == 2) { //works the same as above for for a directed graph (Same commands just different functionality)
			Directed dgraph;
			cout << "Enter the number for the function to be executed" << endl << endl;
			cout << "1. Add node(s) to the graph with their corresponding edges" << endl;
			cout << "2. Change the edges of a node" << endl;
			cout << "3. Print all Nodes IDs and Edges for the graph" << endl;
			cout << "4. Print a specific Node and it's edges" << endl;
			cout << "5. Verify if an edge exists" << endl;
			cout << "6. Remove a Node" << endl;
			cout << "7. Add weights to all edges" << endl;
			cout << "8. Print all weights for edges" << endl;
			cout << "9. Verify if a weight exists" << endl;
			cout << "10. Add Values to the nodes" << endl;
			cout << "11. Read all Values and Edges for the Graph" << endl;
			cout << "12. Path of a specific Value" << endl;
			cout << "999. To terminate the program" << endl << endl;
			while (command != 999)
			{
				cout << "------------------------------------------" << endl;
				cout << "0. See Master list of commands" << endl << endl;
				cout << "Enter a command to execute a function: ";
				cin >> command;
				cout << endl;

				switch (command)
				{

				case 0:	cout << "Enter the number for the function to be executed" << endl << endl;
					cout << "1. Add node(s) to the graph with their corresponding edges" << endl;
					cout << "2. Change the edges of a node" << endl;
					cout << "3. Print all Nodes IDs and Edges for the graph" << endl;
					cout << "4. Print a specific Node and it's edges" << endl;
					cout << "5. Verify if an edge exists" << endl;
					cout << "6. Remove a Node" << endl;
					cout << "7. Add weights to all edges" << endl;
					cout << "8. Print all weights for edges" << endl;
					cout << "9. Verify if a weight exists" << endl;
					cout << "10. Add Values to the nodes" << endl;
					cout << "11. Read all Values and Edges for the Graph" << endl;
					cout << "12. Path of a specific Value" << endl;
					cout << "999. To terminate the program" << endl << endl;
					cout << "Enter a number to execute a function: ";
					break;


				case 1: 	node.addNode(nodes, no_of_node, oldnodes);
					dgraph.add(adj[nodes]);
					dgraph.writegraph(adj, nodes);	//NOTE* in directed graph there is no remove repeated edges, since the edge (1,2) is not the same as (2,1)
					break;

				case 2:	dgraph.changeedge(adj, nodes);
					break;

				case 3:	dgraph.readgraph(adj, nodes);
					break;

				case 4:	dgraph.specificprint(adj, nodes);
					break;

				case 5: 	dgraph.printedge(adj, nodes);
					break;


				case 6: 	dgraph.removenode(adj, nodes);
					break;

				case 7:	dgraph.writeweight(adj, weight, nodes);
					break;

				case 8:	dgraph.readweights(adj, weight, nodes);
					break;

				case 9:		dgraph.checkweight(adj, weight, nodes);
					break;

				case 10:	dgraph.writevalue(adj, value, nodes);
					break;

				case 11:	dgraph.readvalues(adj, value, nodes);
					break;

				case 12:	dgraph.specificvalue(adj, value, nodes);
					break;

				case 999:	cout << "Terminating the program";
					exit(1);
					break;

				default: cout << "This number does not represent a function" << endl << endl;



				}



			}
			break;
		}

		else if (command != 1 || command != 2)
			cout << "Please enter 1 or 2" << endl;
	}
	cout << endl;



	return 0;
}
