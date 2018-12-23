#pragma once
#include<iostream>
#include<string>

#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Node
{


protected:
	int no_of_node;


public:
	Node();
	Node(Node *);
	Node (const Node&);
	~Node();

	int data;
	void addNode(int &, int &, int &);
	Node *next;


};


class Graph:public Node
{
protected:
	Node *head;

public:
	Graph();
	Graph(Node *adj[],int);
	Graph(const Graph&);
	virtual ~Graph();

	virtual void writegraph(Node *adj[], int);
	void deleterepeats(Node *adj[], int);
	virtual void readgraph(Node *adj[], int);

	virtual void add(const Node&);
	virtual void specificprint(Node *adj[],int);
	virtual void removenode(Node *adj[], int&);

	virtual void changeedge(Node *adj[], int);
	virtual void printedge(Node *adj[],int);

	virtual void writeweight(Node *adj[], string [], int);
	virtual void readweights(Node *adj[],string [],int);
	virtual void checkweight(Node *adj[], string [], int);

	virtual void writevalue(Node *adj[], string [], int);
	virtual void readvalues(Node *adj[], string [], int);
	virtual void specificvalue(Node *adj[], string [], int);

};

class Directed: public Graph
{
public:
	Directed();
	Directed(const Directed&);
	virtual ~Directed();

	void writegraph(Node *adj[], int);
	void readgraph(Node *adj[], int);

	void add(const Node&);
	void specificprint(Node *adj[],int);
	void removenode(Node *adj[], int&);

	void changeedge(Node *adj[], int);
	void printedge(Node *adj[],int);

	void writeweight(Node *adj[], string [], int);
	void readweights(Node *adj[],string [],int);
	void checkweight(Node *adj[], string [], int);

	void writevalue(Node *adj[], string [], int);
	void readvalues(Node *adj[], string [], int);
	void specificvalue(Node *adj[], string [], int);










};


#endif
