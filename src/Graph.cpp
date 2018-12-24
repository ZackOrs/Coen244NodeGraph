#include<stdlib.h>
#include "Graph.h"
#include<iostream>
#include <string>

using namespace std;


//Global members (used in all classes)

int nodes = 0;
int oldnodes = 0;


//############## NODE ##############

//default constructor
Node::Node()
{
	next = new Node[0];
	no_of_node = 0;
	data = 0;

}
//constructor
Node::Node(Node adj[])
{
	data = 0;

}


Node::Node(const Node& a)
{
	for (int i = 0; i<nodes; i++)
	{
		next[i] = a.next[i];

	}
	data = a.data;
	no_of_node = a.no_of_node;
}
Node::~Node()
{

}

//function to create nodes
void Node::addNode(int &nodes, int&no_of_nodes, int&oldnodes)
{
	int input = 0;
	try {
		oldnodes = nodes; //makes oldnodes be set to the value of nodes before (more) nodes are added
		cout << "Enter the number of nodes to be added: ";
		cin >> nodes; //creates x number of nodes
		if (nodes<0) {
			input = nodes;
			nodes = oldnodes;
			throw input;
		}
		nodes = nodes + oldnodes;	//sets the value of nodes as oldnodes + the number entered
		cout << endl;
		no_of_node = nodes;
	}
	catch (int i) {
		cout << "The number " << i << " is a negative number and cannot be added" << endl;
	}
}

//############## GRAPH ##############

//default constructor
Graph::Graph()
{
	head = new Node[5];
	nodes = 0;

}

Graph::Graph(Node *adj[], int no_of_node)
{

}

//Copy Constructor
Graph::Graph(const Graph& a)
{
	for (int i = 0; i<nodes; i++)
	{
		head[i] = a.head[i];

	}

}
//deconstructor
Graph::~Graph()
{


}
//adds object node to the graph
void Graph::add(const Node &obj)
{


	for (int i = oldnodes - 1; i <= nodes; i++) {

		head[nodes] = obj;

	}


}



//Function to add edges to nodes
void Graph::writegraph(Node *adj[], int no_of_node) {


	if (no_of_node == 0)
	{
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}
	for (int i = oldnodes; i <= no_of_node; i++)
	{
		adj[i] = 0;
	}


	cout << endl << "The current total number of nodes is: " << no_of_node << endl << endl;

	Node *new_node;
	Node *ptr;

	int i, j, k, id;

	for (i = oldnodes; i<no_of_node; i++)
	{
		Node *last = 0;

		cout << "Enter the amount of edges for node " << i + 1 << ": ";		//specify the number of edges connected to a specific node
		cin >> k;
		for (j = 0; j<k; j++)
		{

			cout << "Enter edge " << j + 1 << " attached to node " << i + 1 << ": ";		//Enter the first connection (Ex: Node 1 shares an edge with node 2)
			cin >> id;
			while (id > no_of_node)
			{
				cout << "This Node ID does not exist yet, please enter a new one: ";
				cin >> id;
			}
			ptr = adj[i];
			while (ptr != 0 || id > no_of_node)	//This loop will go through all of the edges for the i node and find repeated edges aswwell as check to see if the id entered is greater than the number of nodes
			{


				if (ptr->data == 0) //This means the edge does not exist so it will continue looking for edges on the vertex
				{
					ptr->data = 0;
					ptr = ptr->next;
				}
				else {				//Edge was found
					while (ptr->data == id) {	//if the ID for the edge that was found is the same as the ID entered then a repeated edge was found
						while (ptr->data == id) {

							cout << "Edge already exists, enter a new edge: ";
							cin >> id;
							while (id > no_of_node) {
								cout << "This Node ID does not exist yet, please enter a new one: ";
								cin >> id;
							}		//causes the user to cin a new edge
							ptr->next;		//verifies the new edge does not exist elsewhere
						}
					}
					ptr = ptr->next;	//this means the edge i,j was not found and will search the next edge of node i
				}
			}

			new_node = (Node *)malloc(sizeof(Node));	//Creates dynamic memory allocation in order to hold an unspecified number of edges per node
			new_node->data = id;		//sets the edge inputed into data
			new_node->next = 0;			//sets the next edge as 0, used for the last input (Will be overwritten in the loop)

			if (adj[i] == 0) {		//After the last input it sets it as the last
				adj[i] = new_node;
				last = new_node;

			}
			else {		//if it is not the last input, it allows more inputs and repeats the loop with the next memory allocation in mind

				last->next = new_node;
				last = new_node;

			}
		}
		cout << endl;
	}
}

void Graph::deleterepeats(Node *adj[], int no_of_node) {


	Node *ptr;
	Node *ptr2;
	int i;
	int check; //int to check if values are repeated

	for (i = 0; i<no_of_node; i++) {	//a for loop that prints all the edges in the graph
		ptr = adj[i];	//initialize what node it must search edges for



		while (ptr != 0) {	//a while loop that keeps going until the node's edge = 0 (edge = last)

			if (ptr->data == 0)	//if user inputs 0 (no edge) this will cause it still check the next input
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {			//an edge exists

				check = ptr->data;//set check to the 2nd node of the edge (ex: if (1,3) check = 3) (Node 3 will be used for the next if as an example)

				if (check != i + 1) {		//makes sure that 3 != 1 (incase of a node with an edge pointing to itself)

					ptr2 = adj[check - 1];	//Set ptr2 to node 3 (ID of node 3 is 2)

					while (ptr2 != 0) {	//if edge of node 3 == 0 then move on to the next edge

						if (ptr2->data == 0)
						{
							ptr2->data = 0;
							ptr2 = ptr2->next;
						}

						else if (i + 1 == ptr2->data)	//this statements means if 1 is equivalent with an edge of node 3 (meaning that (3,1) exists) it will go through this statement
						{
							cout << "Edge (" << check << "," << i + 1 << ") is a repeated edge, it is being removed from graph" << endl;
							ptr2->data = 0;		//then (3,1) will be set to (3,0) therefore removing it
							ptr2 = ptr2->next;	//move on the the next edge of 3
						}
						else {	//if the edge is not 3 nor 0 then it moves to the next edge of 3
							ptr2 = ptr2->next;
						}
					}
				}//if statement ends, meaning if there was a repeated edge between 3 and 1, it was removed
				ptr = ptr->next;//moves on to the next edge of the original node 1
			}
		}

	}//outer for loop ends, moves on to node 2 and repeats the process


}

//function to print all the vertices and edges made in the graph
void Graph::readgraph(Node *adj[], int no_of_node) {
	Node *ptr = 0;
	int i;
	cout << "#### PRINTING ALL THE EDGES FOR ALL THE NODES ####" << endl;

	cout << "V = {";	//simple for loop that print 1 to the last node in the graph
	for (int k = 0; k< no_of_node; k++)
	{
		cout << k + 1;
		if (k + 1 == no_of_node)
			break;
		else
			cout << ",";
	}
	cout << "}" << endl;

	cout << "E = { ";
	for (i = 0; i<no_of_node; i++) {	//a for loop that prints all the edges in the graph
		ptr = adj[i];	//initialize what node it must search edges for



		while (ptr != 0) {	//a while loop that keeps going until the node's edge = 0 (edge = last)

			if (ptr->data == 0)	//incase user inputs 0 this will cause it to check the next input
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {			//prints out the edge
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") ";
				ptr = ptr->next;  //cause to the next edge

				if (i + 1 < no_of_node)	//make commas in the output
					cout << ", ";
			}


		}

	}
	cout << "}";
	cout << endl;
}

//Function to print a specific Node and all it's edges
void Graph::specificprint(Node *adj[], int no_of_node)
{

	if (no_of_node == 0)
	{
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	Node *ptr = 0;
	int i;
	cout << "Enter the specific node ID to print: ";
	cin >> i;	//cin the node ID to view
	while (i>no_of_node || i <= 0) {	//Checks to make sure user doesn't input a value greater or less than the current number of nodes in graph
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> i;
	}




	ptr = adj[i - 1];
	cout << "Printing the Edges of Node " << i << ": ";
	cout << "E = { ";	//similar to the function to readgraph (prints all edges for all vertices) but no for loop, instead it prints a single node's edges
	while (ptr != 0) {
		if (ptr->data == 0)
		{
			ptr->data = 0;
			ptr = ptr->next;
		}
		else {
			cout << "(" << i << ",";
			cout << ptr->data << ") ";
			ptr = ptr->next;
			if (i + 1 < no_of_node)
				cout << ", ";
		}
	}

	for (int j = 0; j<no_of_node; j++) { //since it is undirected, the side the node is on for the edge doesn't matter so the function
		ptr = adj[j];				   //will print the edge regardless of the side it is on EX: if searching for node ID 1, (1,2) will be printed
		while (ptr != 0) {			   //As well as another node (4,1). For undirected the position of the 1 does not matter
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				if (i == ptr->data && i - 1 != j) { //conditional statements to be met in order for it to print (makes sure A,B hasnt been printed yet)
					cout << "(" << j + 1 << ",";
					cout << ptr->data << ") ";
					if (j + 1 < no_of_node)
						cout << ", ";
				}
				ptr = ptr->next;
			}


		}

	}
	cout << "}";
	cout << endl << endl;
}

//function to change the edges of a specific node
void Graph::changeedge(Node *adj[], int no_of_node)
{

	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}
	int i;
	int k;
	int j;
	int id;

	cout << "Enter the node ID which will have its edges changed: ";
	cin >> i;
	while (i>no_of_node || i <= 0) {	//Checks to make sure user doesn't input a value greater or less than the current number of nodes in graph
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> i;
	}
	i--;

	Node *ptr = 0;

	ptr = adj[i];
	cout << "NOTE, The previous edges for node " << i + 1 << " were: ";
	cout << "E = { ";
	while (ptr != 0) {				//prints out the previous edges of the node, so that the user can be reminded
		if (ptr->data == 0)
		{
			ptr->data = 0;
			ptr = ptr->next;
		}
		else {
			cout << "(" << i + 1 << ",";
			cout << ptr->data << ") ";
			ptr = ptr->next;
			if (i + 1 < no_of_node)
				cout << ", ";
		}
	}
	cout << "}";
	cout << endl << endl;

	adj[i] = 0;

	Node *new_node;	//similar to the writegraph function but rewrites the edges for a specific node (Again, same format just without the for loop since it is only 1 node)
	Node *last = 0;


	cout << "Enter the amount of edges for node " << i + 1 << ": ";
	cin >> k;
	for (j = 0; j<k; j++)
	{

		cout << "Enter the new edge " << j + 1 << " attached to node " << i + 1 << ": ";
		cin >> id;
		while (id > no_of_node)
		{
			cout << "This Node ID does not exist yet, please enter a new one: ";
			cin >> id;
		}
		ptr = adj[i];
		while (ptr != 0 || id > no_of_node)	//This loop will go through all of the edges for the i node and find repeated edges aswwell as check to see if the id entered is greater than the number of nodes
		{


			if (ptr->data == 0) //This means the edge does not exist so it will continue looking for edges on the vertex
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {				//Edge was found
				while (ptr->data == id) {	//if the ID for the edge that was found is the same as the ID entered then a repeated edge was found
					while (ptr->data == id) {

						cout << "Edge already exists, enter a new edge: ";
						cin >> id;
						while (id > no_of_node) {
							cout << "This Node ID does not exist yet, please enter a new one: ";
							cin >> id;
						}		//causes the user to cin a new edge
						ptr->next;		//verifies the new edge does not exist elsewhere
					}
				}
				ptr = ptr->next;	//this means the edge i,j was not found and will search the next edge of node i
			}
		}
		new_node = (Node *)malloc(sizeof(Node));
		new_node->data = id;
		new_node->next = 0;


		if (adj[i] == 0) {
			adj[i] = new_node;
			last = new_node;

		}
		else {

			last->next = new_node;
			last = new_node;

		}
	}
	cout << endl;




}

//Function to see if an edge exists in the graph
void Graph::printedge(Node *adj[], int no_of_node)
{
	if (no_of_node == 0) {	//prevents the function being done if no nodes exist in the graph
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	Node *ptr = 0;
	int i, j, n, m;
	cout << "Enter the two node to see if there is an edge: ";
	cin >> j;
	while (j>no_of_node || j <= 0) {	//Checks to make sure user doesn't input a value greater or less than the current number of nodes in graph
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> j;
	}
	cin >> i;
	while (i>no_of_node || i <= 0) {	//Checks to make sure user doesn't input a value greater or less than the current number of nodes in graph
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> i;
	}

	--i;
	--j;

	cout << "Checking if the edge (" << j + 1 << "," << i + 1 << ") exists" << endl;

	ptr = adj[i];

	while (ptr != 0)	//This loop will go through all of the edges for the i node and see if j is an edge
	{

		if (ptr->data == j + 1)
		{
			n = 1;		//if n=1 that means that the edge i,j was found in node i therfore n is set to 1 inorder to print a message and will break out of the loop
			ptr = ptr->next;
			break;
		}
		else
		{
			ptr = ptr->next;	//this means the edge i,j was not found and will search the next edge of node i
			n = 2;
		}
	}

	ptr = adj[j];

	while (ptr != 0)	//works similiarly to the above loop, but now will search the node j for the edge j,i (This is only for undirected graph)
	{

		if (ptr->data == i + 1)
		{
			m = 1;
			ptr = ptr->next;
			break;
		}
		else
		{
			ptr = ptr->next;
			m = 2;
		}
	}

	if (n == 1 || m == 1)
		cout << "The edge (" << j + 1 << "," << i + 1 << ") exists" << endl;	//if N or M is 1 then it will print out the edge was found in the graph

	else
		cout << "This edge does not exist" << endl;	//N nor M are 1 therefore the edge was not found in the graph

	cout << endl;
}



//function to remove a node from the graph
void Graph::removenode(Node *adj[], int& no_of_node)
{
	if (no_of_node == 0) {	//cannot remove a node if no nodes exist
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}
	cout << "Enter the Node to be removed: ";
	int i;
	int k = no_of_node;
	int j = 0;
	int removednode;

	cin >> i;
	if (i>no_of_node || i <= 0) {

		while (i>no_of_node || i <= 0) {	//Checks to make sure user doesn't input a value greater or less than the current number of nodes in graph
			cout << "Node does not exist, enter a new Node ID: ";
			cin >> i;
		}
	}
	removednode = i;
	--i;

	Node *ptr = 0;	//used for node ID
	Node *tmp = 0;	//create a temporary pointer to node in order to swap values
	for (i; i <= no_of_node; i++)	//loop to swap the ID's of nodes so that the node to be removed becomes the last node in the list
	{

		ptr = adj[i];
		adj[i] = tmp;
		adj[i] = adj[i + 1];
		adj[i + 1] = tmp;



	}


	no_of_node = no_of_node - 1;	//removes the no of nodes by 1 so that the to be deleted node (Now the last node) gets deleted

	for (j = 0; j<no_of_node; j++) {	//This will fix the edges of the nodes
		ptr = adj[j];

		while (ptr != 0) {
			if (ptr->data == removednode)	//if an edge existed with the now removed node, it will be removed
			{
				ptr->data = 0;
			}
			else if (ptr->data > removednode)	//if an edge existed with a node that was greater than the deleted node it will be reduced by 1 (explained better bellow)
			{
				ptr->data = ptr->data - 1;
				ptr = ptr->next;
			}
			else	//if an edge is below the deleted node's ID then it remains the same
				ptr = ptr->next;
		}

	}
	cout << endl;
	//For the functionality of this program it works as such:
	//V=1,2,3,4
	//E={ (1,2) , (1,4) , (2,3) ,(3,1) , (4,2) }
	//if we were to remove node 3 then any node that was greater than 3 will be reduced by 1, so node ID 4 becomes node ID 3
	//and  then all the edges above that contain a 3 will be removed ( 2,3 ) (3,1)
	//then it will reduce any edge that contained a number greater than 3 by 1 (1,4) ---> (1,3) 	(4,2) ---> (3,2) this happens since node 4 now becomes node 3
}

//Function to add weight values to the edges
void Graph::writeweight(Node *adj[], string weight[], int no_of_node)
{
	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}
	Node *ptr = 0;
	string val;	//the weight value will be a string so that anyvalue can be inputed
	int i;
	int j = 0;

	cout << "Will add weights to E = {";
	for (i = 0; i<no_of_node; i++) {//shows all the edges in the graph
		ptr = adj[i];



		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") ";
				ptr = ptr->next;

				if (i + 1 < no_of_node)
					cout << ", ";
			}


		}
	}
	cout << "}";
	cout << endl;

	for (i = 0; i<no_of_node; i++) {//same loop as above but after it prints each edge can enter a value for weight
		ptr = adj[i];


		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				cout << "Enter weight for edge ";
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") : ";
				cin >> val;//weight can be added here
				weight[j] = val;//weight value is put into an array so it can be called in other functions
				j = j + 1;	//causes it to shift to the next value of the array to be inputed in the future
				ptr = ptr->next;
			}


		}
	}
	cout << endl;
}

//function to print the weights of all edges
void Graph::readweights(Node *adj[], string weight[], int no_of_node) {

	Node *ptr = 0;
	int i = 0;
	int j = 0;

	cout << endl << "Printing the weights for all the edges" << endl << endl;
	for (i = 0; i<no_of_node; i++) {//loop to print all edges
		ptr = adj[i];
		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				cout << "The weight for edge ";
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") = " << weight[j];	//this part of the loop, the edges weight will be printed
				j = j + 1;	//causes it to shift to the next value of the array for the next time it prints
				ptr = ptr->next;
				cout << endl;
			}


		}
	}
}

//Function to check if a specific weight exists
void Graph::checkweight(Node *adj[], string weight[], int no_of_node) {

	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	string check;
	Node *ptr = 0;
	int i = 0;
	int j = 0;

	cout << "Enter the weight to check if exists: ";
	cin >> check;

	for (i = 0; i<no_of_node; i++) {//for loop to go through all the edges of all the nodes
		ptr = adj[i];
		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				if (check == weight[j]) { //checks if the inputed weight is found in an edge
					cout << "weight exists at edge (" << i + 1 << "," << ptr->data << ")" << endl; //will cout the edge that contains this weight
					ptr = ptr->next;//loop will continue to see if other edges share the same weight
					j = j + 1;
				}
				else {
					ptr = ptr->next;
					j = j + 1;
				}
			}
		}
	}


	cout << endl;
}


//adds values to the Vertices of graph
void Graph::writevalue(Node *adj[], string value[], int no_of_node) {

	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	Node *ptr = 0;
	string val;	//create a string value that will be inputed by the user for the value of the node
	int i;
	for (i = 0; i<no_of_node; i++)
	{
		value[i] = "0";
	}
	cout << "Adding values to V = {";
	for (int k = 0; k< no_of_node; k++)	//loop to print out the vertices that will have values added (all vertices)
	{
		cout << k + 1;
		if (k + 1 == no_of_node)
			break;
		else
			cout << ",";
	}
	cout << "}" << endl;

	for (i = 0; i<no_of_node; i++) {	//for each node a string can be inputed to give it a value
		ptr = adj[i];
		cout << "Enter the value for node " << i + 1 << ": ";
		cin >> val;
		for (int j = 0; j<no_of_node; j++) {
			if (val == value[j])
			{
				cout << "Value already exists enter a new value: ";
				cin >> val;
				j = -1;
			}

		}
		value[i] = val;  //value entered is stored into an array so that it can be called back for specific nodes
	}
	cout << endl;



}

//function to print all the vertices and edges made in the graph using values instead of ID's
void Graph::readvalues(Node *adj[], string value[], int no_of_node) {
	Node *ptr = 0;
	int i = 0;
	int j = 0;


	cout << endl << "Printing all edges using values" << endl << endl;


	cout << "V(using values) = {";
	for (int k = 0; k< no_of_node; k++)
	{
		cout << value[k]; //refers to the values that were added in the writevalues function
		if (k + 1 == no_of_node)
			break;
		else
			cout << ",";
	}

	cout << "}" << endl;

	cout << "E(using values) = {";
	for (i = 0; i<no_of_node; i++) { //prints all edges in the graph but using values instead of ID's
		ptr = adj[i];
		while (ptr != 0) {


			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {

				cout << "(" << value[i] << ","; //refers to the values in the writevalue function
				cout << value[ptr->data - 1] << ") "; //refers to the values in the writevalue function
				if (i + 1 < no_of_node)
					cout << ", ";
				ptr = ptr->next;
			}


		}
	}
	cout << "}" << endl;
}

//Searches for the value of a node and prints it's edges
void Graph::specificvalue(Node *adj[], string value[], int no_of_node)
{
	Node *ptr = 0;
	string str;
	cout << "Enter the value to be queried: ";
	cin >> str;

	cout << "E (" << str << ") = { ";
	for (int i = 0; i<no_of_node; i++) {
		ptr = adj[i];
		if (str == value[i]) //will only search the edges of the inputed string
		{
			while (ptr != 0) {

				if (ptr->data == 0)
				{
					ptr->data = 0;
					ptr = ptr->next;
				}

				else {
					cout << "(" << value[i] << ",";
					cout << value[ptr->data - 1] << ") ";
					if (i + 1 < no_of_node)
						cout << ", ";
					ptr = ptr->next;
				}


			}
		}
	}
	for (int i = 0; i<no_of_node; i++) //For an undirected graph, it doesnt matter the connection so will check for the value on both sides EX: (A,B) is the same as (B,A) so it will also look for (B,A)
	{
		ptr = adj[i];
		while (ptr != 0) {

			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {

				if (str == value[ptr->data - 1] && value[i] != "0" && value[i] != str) { //conditional statements to be met in order for it to print (makes sure A,B hasnt been printed yet)
					cout << "(" << value[i] << ",";
					cout << value[ptr->data - 1] << ") ";
					if (i + 1 < no_of_node)
						cout << ", ";
				}
				ptr = ptr->next;
			}


		}
	}
	cout << "}" << endl;
}


//############## DIRECTED GRAPH ##############

//default constructor
Directed::Directed()
{
	head = new Node[5];
	nodes = 0;
}



//Copy Constructor
Directed::Directed(const Directed& a)
{
	for (int i = 0; i<nodes; i++)
	{
		head[i] = a.head[i];

	}
}
//deconstructor
Directed::~Directed()
{


}
//adds object node to the graph
void Directed::add(const Node &obj)
{


	for (int i = oldnodes - 1; i <= nodes; i++) {

		head[nodes] = obj;
	}


}



//Function to add edges to nodes
void Directed::writegraph(Node *adj[], int no_of_node) {


	if (no_of_node == 0)
	{
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	for (int i = oldnodes; i <= no_of_node; i++)
	{
		adj[i] = 0;
	}

	Node *new_node;
	Node *new_val;
	Node *ptr;
	cout << endl << "The current total number of nodes is: " << no_of_node << endl << endl;
	int i, j, k, id;

	for (i = oldnodes; i<no_of_node; i++)
	{
		Node *last = 0;

		cout << "Enter the amount of edges for node " << i + 1 << ": ";		//specify the number of edges connected to a specific node
		cin >> k;
		for (j = 0; j<k; j++)
		{

			cout << "Enter edge " << j + 1 << " attached to node " << i + 1 << ": ";		//Enter the first connection (Ex: Node 1 shares an edge with node 2)
			cin >> id;
			while (id > no_of_node)
			{
				cout << "This Node ID does not exist yet, please enter a new one: ";
				cin >> id;
			}
			ptr = adj[i];
			while (ptr != 0 || id > no_of_node)	//This loop will go through all of the edges for the i node and find repeated edges aswwell as check to see if the id entered is greater than the number of nodes
			{


				if (ptr->data == 0) //This means the edge does not exist so it will continue looking for edges on the vertex
				{
					ptr->data = 0;
					ptr = ptr->next;
				}
				else {				//Edge was found
					while (ptr->data == id) {	//if the ID for the edge that was found is the same as the ID entered then a repeated edge was found
						while (ptr->data == id) {

							cout << "Edge already exists, enter a new edge: ";
							cin >> id;
							while (id > no_of_node) {
								cout << "This Node ID does not exist yet, please enter a new one: ";
								cin >> id;
							}		//causes the user to cin a new edge
							ptr->next;		//verifies the new edge does not exist elsewhere
						}
					}
					ptr = ptr->next;	//this means the edge i,j was not found and will search the next edge of node i
				}
			}
			new_node = (Node *)malloc(sizeof(Node));	//Creates dynamic memory allocation in order to hold an unspecified number of edges per node
			new_node->data = id;		//sets the edge inputed into data
			new_node->next = 0;			//sets the next edge as 0 (Will be overwritten in the loop)

			if (adj[i] == 0) {		//After the last input it sets it as the last
				adj[i] = new_node;
				last = new_node;

			}
			else {		//if it is not the last input, it allows more inputs and repeats the loop with the next memory allocation in mind

				last->next = new_node;
				last = new_node;

			}
		}
		cout << endl;
	}
}

//function to print all the vertices and edges made in the graph
void Directed::readgraph(Node *adj[], int no_of_node) {
	Node *ptr = 0;
	int i;
	cout << "#### PRINTING ALL THE EDGES FOR ALL THE NODES ####" << endl;

	cout << "V = {";	//simple for loop that print 1 to the last node in the graph
	for (int k = 0; k< no_of_node; k++)
	{
		cout << k + 1;
		if (k + 1 == no_of_node)
			break;
		else
			cout << ",";
	}
	cout << "}" << endl;

	cout << "E = { ";
	for (i = 0; i<no_of_node; i++) {	//a for loop that prints all the edges in the graph
		ptr = adj[i];	//initialize what node it must search edges for



		while (ptr != 0) {	//a while loop that keeps going until the node's edge = 0 (edge = last)

			if (ptr->data == 0)	//incase user inputs 0 this will cause it to check the next input
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {			//prints out the edge
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") ";
				ptr = ptr->next;  //cause to the next edge

				if (i + 1 < no_of_node)	//make commas in the output
					cout << ", ";
			}


		}

	}
	cout << "}";
	cout << endl;
}

//Function to print a specific Node and all it's edges
void Directed::specificprint(Node *adj[], int no_of_node)
{

	if (no_of_node == 0)
	{
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	Node *ptr = 0;
	int i;
	cout << "Enter the specific node ID to print: ";
	cin >> i;	//cin the node ID to view
	while (i>no_of_node) {
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> i;
	}

	while (i > no_of_node) //Checks to make sure user doesn't input a value greater than the current number of nodes
	{
		if (i > no_of_node)
		{
			cout << "Node is greater than " << no_of_node << " enter a new node: ";
			cin >> i;
		}

	}

	ptr = adj[i - 1];
	cout << "Printing the Edges of Node " << i << ": ";
	cout << "E = { ";	//similar to the function to readgraph (prints all edges for all vertices) but no for loop, instead it prints a single node's edges
	while (ptr != 0) {
		if (ptr->data == 0)
		{
			ptr->data = 0;
			ptr = ptr->next;
		}
		else {
			cout << "(" << i << ",";
			cout << ptr->data << ") ";
			ptr = ptr->next;
			if (i + 1 < no_of_node)
				cout << ", ";
		}
	}
	//NOT NEEDED FOR DIRECTED GRAPH
	//	for(int j=0;j<no_of_node;j++){ //since it is undirected, the side the node is on for the edge doesn't matter so the function
	//       ptr=adj[j];				   //will print the edge regardless of the side it is on EX: if searching for node ID 1, (1,2) will be printed
	//    	while(ptr!=0){			   //As well as another node (4,1). For undirected the position of the 1 does not matter
	//			if (ptr->data == 0)
	//        		{
	//        			ptr->data = 0;
	//        			ptr=ptr->next;
	//        		}
	//
	//				else{
	//					if(i==ptr->data){ //conditional statements to be met in order for it to print (makes sure A,B hasnt been printed yet)
	//						cout << "(" <<j+1 << ",";
	//						cout << ptr->data <<") ";
	//						if(j + 1 < no_of_node)
	//   							cout << ", ";
	//					}
	//       				ptr=ptr->next;
	//				}
	//
	//
	//    	}
	//
	//    }
	cout << "}";
	cout << endl << endl;
}

//function to change the edges of a specific node
void Directed::changeedge(Node *adj[], int no_of_node)
{

	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	int i;
	int k;
	int j;
	int id;

	cout << "Enter the node ID which will have its edges changed: ";
	cin >> i;
	while (i>no_of_node || i <= 0) {
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> i;
	}
	i--;

	Node *ptr = 0;

	ptr = adj[i];
	cout << "NOTE, The previous edges for node " << i + 1 << " were: ";
	cout << "E = { ";
	while (ptr != 0) {				//prints out the previous edges of the node, so that the user can be reminded
		if (ptr->data == 0)
		{
			ptr->data = 0;
			ptr = ptr->next;
		}
		else {
			cout << "(" << i + 1 << ",";
			cout << ptr->data << ") ";
			ptr = ptr->next;
			if (i + 1 < no_of_node)
				cout << ", ";
		}
	}
	cout << "}";
	cout << endl << endl;

	adj[i] = 0;

	Node *new_node;	//similar to the writegraph function but rewrites the edges for a specific node (Again, same format just without the for loop since it is only 1 node)
	Node *last = 0;


	cout << "Enter the amount of edges for node " << i + 1 << ": ";
	cin >> k;
	for (j = 0; j<k; j++)
	{

		cout << "Enter the new edge " << j + 1 << " attached to node " << i + 1 << ": ";
		cin >> id;
		while (id > no_of_node)
		{
			cout << "This Node ID does not exist yet, please enter a new one: ";
			cin >> id;
		}
		ptr = adj[i];
		while (ptr != 0 || id > no_of_node)	//This loop will go through all of the edges for the i node and find repeated edges aswwell as check to see if the id entered is greater than the number of nodes
		{


			if (ptr->data == 0) //This means the edge does not exist so it will continue looking for edges on the vertex
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {				//Edge was found
				while (ptr->data == id) {	//if the ID for the edge that was found is the same as the ID entered then a repeated edge was found
					while (ptr->data == id) {

						cout << "Edge already exists, enter a new edge: ";
						cin >> id;
						while (id > no_of_node) {
							cout << "This Node ID does not exist yet, please enter a new one: ";
							cin >> id;
						}		//causes the user to cin a new edge
						ptr->next;		//verifies the new edge does not exist elsewhere
					}
				}
				ptr = ptr->next;	//this means the edge i,j was not found and will search the next edge of node i
			}
		}
		new_node = (Node *)malloc(sizeof(Node));
		new_node->data = id;
		new_node->next = 0;


		if (adj[i] == 0) {
			adj[i] = new_node;
			last = new_node;

		}
		else {

			last->next = new_node;
			last = new_node;

		}
	}
	cout << endl;




}

//Function to see if an edge exists in the graph
void Directed::printedge(Node *adj[], int no_of_node)
{
	if (no_of_node == 0) {	//prevents the function being done if no nodes exist in the graph
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	Node *ptr = 0;
	int i, j, n;
	cout << "Enter the two node to see if there is an edge: ";
	cin >> j;
	while (j>no_of_node || j <= 0) {
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> j;
	}
	cin >> i;
	while (i>no_of_node || i <= 0) {
		cout << "Node does not exist, enter a new Node ID: ";
		cin >> i;
	}
	--i;
	--j;

	cout << "Checking if the edge (" << j + 1 << "," << i + 1 << ") exists" << endl;

	ptr = adj[j];

	while (ptr != 0)	//This loop will go through all of the edges for the i node and see if j is an edge
	{

		if (ptr->data == i + 1)
		{
			n = 1;		//if n=1 that means that the edge i,j was found in node i therfore n is set to 1 inorder to print a message and will break out of the loop
			ptr = ptr->next;
			break;
		}
		else
		{
			ptr = ptr->next;	//this means the edge i,j was not found and will search the next edge of node i
			n = 2;
		}
	}
	//NOT NEEDED FOR DIRECTED GRAPH
	//    ptr=adj[j];
	//
	//	while(ptr!=0)	//works similiarly to the above loop, but now will search the node j for the edge j,i (This is only for undirected graph)
	//	{
	//
	//		if ( ptr->data == i + 1)
	//		{
	// 			m=1;
	// 			ptr=ptr->next;
	// 			break;
	//		}
	//       	else
	//			{
	//			ptr=ptr->next;
	//			m=2;
	//			}
	//	}
	//
	if (n == 1)
		cout << "The edge (" << j + 1 << "," << i + 1 << ") exists" << endl;	//if N is 1 then it will print out the edge was found in the graph

	else
		cout << "This edge does not exist" << endl;	//N is not 1 therefore the edge was not found in the graph

	cout << endl;
}



//function to remove a node from the graph
void Directed::removenode(Node *adj[], int& no_of_node)
{
	if (no_of_node == 0) {	//cannot remove a node if no nodes exist
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}
	cout << "Enter the Node to be removed: ";
	int i;
	int k = no_of_node;
	int j = 0;
	int removednode;

	cin >> i;
	if (i>no_of_node || i <= 0) {

		while (i>no_of_node || i <= 0) {
			cout << "Node does not exist, enter a new Node ID: ";
			cin >> i;
		}
	}
	removednode = i;
	--i;

	Node *ptr = 0;
	Node *tmp = 0;	//create a temporary pointer to node in order to swap values

	for (i; i <= no_of_node; i++)	//loop to swap the ID's of nodes so that the node to be removed becomes the last node in the list
	{

		ptr = adj[i];
		adj[i] = tmp;
		adj[i] = adj[i + 1];
		adj[i + 1] = tmp;



	}


	no_of_node = no_of_node - 1;	//removes the no of nodes by 1 so that the to be deleted node (Now the last node) gets deleted

	for (j = 0; j<no_of_node; j++) {	//This will fix the edges of the nodes
		ptr = adj[j];

		while (ptr != 0) {
			if (ptr->data == removednode)	//if an edge existed with the now removed node, it will be removed
			{
				ptr->data = 0;
			}
			else if (ptr->data > removednode)	//if an edge existed with a node that was greater than the deleted node it will be reduced by 1 (explained better bellow)
			{
				ptr->data = ptr->data - 1;
				ptr = ptr->next;
			}
			else	//if an edge is below the deleted node's ID then it remains the same
				ptr = ptr->next;
		}

	}
	cout << endl;
	//For the functionality of this program it works as such:
	//V=1,2,3,4
	//E={ (1,2) , (1,4) , (2,3) ,(3,1) , (4,2) }
	//if we were to remove node 3 then any node that was greater than 3 will be reduced by 1, so node ID 4 becomes node ID 3
	//and  then all the edges above that contain a 3 will be removed ( 2,3 ) (3,1)
	//then it will reduce any edge that contained a number greater than 3 by 1 (1,4) ---> (1,3) 	(4,2) ---> (3,2) this happens since node 4 now becomes node 3
}

//Function to add weight values to the edges
void Directed::writeweight(Node *adj[], string weight[], int no_of_node)
{
	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}
	Node *ptr = 0;
	string val;	//the weight value will be a string so that anyvalue can be inputed
	int i;
	int j = 0;

	cout << "Will add weights to E = {";
	for (i = 0; i<no_of_node; i++) {//shows all the edges in the graph
		ptr = adj[i];



		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}
			else {
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") ";
				ptr = ptr->next;

				if (i + 1 < no_of_node)
					cout << ", ";
			}


		}
	}
	cout << "}";
	cout << endl;

	for (i = 0; i<no_of_node; i++) {//same loop as above but after it prints each edge can enter a value for weight
		ptr = adj[i];


		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				cout << "Enter weight for edge ";
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") : ";
				cin >> val;//weight can be added here
				weight[j] = val;//weight value is put into an array so it can be called in other functions
				j = j + 1;	//causes it to shift to the next value of the array to be inputed in the future
				ptr = ptr->next;
			}


		}
	}
	cout << endl;
}

//function to print the weights of all edges
void Directed::readweights(Node *adj[], string weight[], int no_of_node) {

	Node *ptr = 0;
	int i = 0;
	int j = 0;

	cout << endl << "Printing the weights for all the edges" << endl << endl;
	for (i = 0; i<no_of_node; i++) {//loop to print all edges
		ptr = adj[i];
		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				cout << "The weight for edge ";
				cout << "(" << i + 1 << ",";
				cout << ptr->data << ") = " << weight[j];	//this part of the loop, the edges weight will be printed
				j = j + 1;	//causes it to shift to the next value of the array for the next time it prints
				ptr = ptr->next;
				cout << endl;
			}


		}
	}
}

//Function to check if a specific weight exists
void Directed::checkweight(Node *adj[], string weight[], int no_of_node) {

	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	string check;
	Node *ptr = 0;
	int i = 0;
	int j = 0;

	cout << "Enter the weight to check if exists: ";
	cin >> check;

	for (i = 0; i<no_of_node; i++) {//for loop to go through all the edges of all the nodes
		ptr = adj[i];
		while (ptr != 0) {
			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {
				if (check == weight[j]) { //checks if the inputed weight is found in an edge
					cout << "weight exists at edge (" << i + 1 << "," << ptr->data << ")" << endl; //will cout the edge that contains this weight
					ptr = ptr->next;//loop will continue to see if other edges share the same weight
					j = j + 1;
				}
				else {
					ptr = ptr->next;
					j = j + 1;
				}
			}
		}
	}


	cout << endl;
}


//adds values to the Vertices of graph
void Directed::writevalue(Node *adj[], string value[], int no_of_node) {

	if (no_of_node == 0) {
		cout << "No nodes exist yet, add nodes to the graph first" << endl << endl;
		return;
	}

	Node *ptr = 0;
	string val;	//create a string value that will be inputed by the user for the value of the node
	int i;

	for (i = 0; i<no_of_node; i++)
	{
		value[i] = "0";
	}
	cout << "Adding values to V = {";
	for (int k = 0; k< no_of_node; k++)	//loop to print out the vertices that will have values added (all vertices)
	{
		cout << k + 1;
		if (k + 1 == no_of_node)
			break;
		else
			cout << ",";
	}
	cout << "}" << endl;

	for (i = 0; i<no_of_node; i++) {	//for each node a string can be inputed to give it a value
		ptr = adj[i];
		cout << "Enter the value for node " << i + 1 << ": ";
		cin >> val;
		for (int j = 0; j<no_of_node; j++) {
			if (val == value[j])
			{
				cout << "Value already exists enter a new value: ";
				cin >> val;
				j = -1;
			}

		}
		value[i] = val;  //value entered is stored into an array so that it can be called back for specific nodes
	}
	cout << endl;



}

//function to print all the vertices and edges made in the graph using values instead of ID's
void Directed::readvalues(Node *adj[], string value[], int no_of_node) {
	Node *ptr = 0;
	int i = 0;
	int j = 0;


	cout << endl << "Printing all edges using values" << endl << endl;


	cout << "V(using values) = {";
	for (int k = 0; k< no_of_node; k++)
	{
		cout << value[k]; //refers to the values that were added in the writevalues function
		if (k + 1 == no_of_node)
			break;
		else
			cout << ",";
	}

	cout << "}" << endl;

	cout << "E(using values) = {";
	for (i = 0; i<no_of_node; i++) { //prints all edges in the graph but using values instead of ID's
		ptr = adj[i];
		while (ptr != 0) {


			if (ptr->data == 0)
			{
				ptr->data = 0;
				ptr = ptr->next;
			}

			else {

				cout << "(" << value[i] << ","; //refers to the values in the writevalue function
				cout << value[ptr->data - 1] << ") "; //refers to the values in the writevalue function
				if (i + 1 < no_of_node)
					cout << ", ";
				ptr = ptr->next;
			}


		}
	}
	cout << "}" << endl;
}

//Searches for the value of a node and prints it's edges
void Directed::specificvalue(Node *adj[], string value[], int no_of_node)
{
	Node *ptr = 0;
	string str;
	cout << "Enter the value to be queried: ";
	cin >> str;

	cout << "E (" << str << ") = { ";
	for (int i = 0; i<no_of_node; i++) {
		ptr = adj[i];
		if (str == value[i]) //will only search the edges of the inputed string
		{
			while (ptr != 0) {

				if (ptr->data == 0)
				{
					ptr->data = 0;
					ptr = ptr->next;
				}

				else {
					cout << "(" << value[i] << ",";
					cout << value[ptr->data - 1] << ") ";
					if (i + 1 < no_of_node)
						cout << ", ";
					ptr = ptr->next;
				}


			}
		}
	}
	cout << "}" << endl;
}
