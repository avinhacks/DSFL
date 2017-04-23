#include<iostream>
#include<string.h>
#define MAX 10
#define INFINITY 999

using namespace std;

class Graph
{
	string name[MAX];
	int nodes, cost[MAX][MAX], from[MAX], distance[MAX], spanning[MAX][MAX], visited[MAX];
	int source;

public:
	Graph();
	void initialise();
	void accept();
	void display();
	int position(string);
	int prims();
};

Graph::Graph()
{
	source = 0;
	nodes = 0;
	for(int i=0; i<MAX; i++)
	{
		for(int j=0; j<MAX; j++)
		{
			if(i==j)
				cost[i][j] = 0;
			else
				cost[i][j] = INFINITY;
			spanning[i][j] = 0;
		}
	}
}
void Graph::initialise()
{
	for(int i=0; i<nodes; i++)
	{
		visited[i] = 0;
		from[i] = source;
		distance[i] = cost[source][i];
	}
	distance[source] = 0;
	visited[source] = 1;
}
void Graph::accept()
{
	string start, end, temp;
	int wt, j, k, edges;
	cout<<"\nEnter no of vertices: ";
	cin>>nodes;
	cout<<"\nEnter names of nodes: ";
	for(int i=0; i<nodes; i++)
	{
		cin>>name[i];
	}

	cout<<"Enter no. of edges: ";
	cin>>edges;
	for(int i=0; i<edges; i++)
	{
		cout<<"\nEnter source and destination: ";
		cin>>start>>end;
		cout<<"Enter weight: ";
		cin>>wt;

		j = position(start);
		k = position(end);

		cost[j][k] = cost[k][j] = wt;
	}

	cout<<"\nEnter source vertex: ";
	cin>>temp;

	source = position(temp);

	while((source<0) || (source>nodes-1))
	{
		cout<<"\nWrong vertex reenter source :";
		cin>>temp;
		source = position(temp);
	}
}
void Graph::display()
{
	int i, j;
	cout<<"\nAdjacency Matrix: \n";
	for(i=0; i<nodes; i++)
		cout<<"\t\t"<<name[i];
	for(i=0; i<nodes; i++)
	{
		cout<<"\n"<<name[i];
		for(j=0; j<nodes; j++)
		{
			cout<<"\t\t"<<cost[i][j];
		}
	}
}
int Graph::position(string str)
{
	int i;
	for(i=0; i<nodes; i++)
	{
		if(name[i] == str)
			break;
	}
	return i;
}
int  Graph :: prims()
{
	int u,edges, v, i,mindistance, mincost;
	initialise();
	edges = nodes-1;
	mincost = 0;

	cout<<"\nMinimum Spanning Tree:\n";
	while(edges > 0)
	{
		mindistance = INFINITY;

		//Find minimum distance vertex from tree in distance array
		for( i=0; i<nodes; i++)
		{
			if(visited[i]==0 && distance[i]<mindistance)
			{
				mindistance = distance[i];
				v = i;
			}
		}
		u = from[v];

		//insert edge in spanning tree
		spanning[u][v] = distance[v];
		spanning[v][u] = distance[v];
		edges--;
		visited[v] = 1;

		//update distance array
		for(i=0; i<nodes; i++)
		{
			if(visited[i]==0 && cost[i][v]<distance[i])
			{
				distance[i] = cost[i][v];
				from[i] = v;
			}
		}

		// Display the edge
		cout<<"\nEdge("<<name[u]<<","<<name[v]<<") = "<<cost[u][v];
		mincost+=cost[u][v];
	}
	return mincost;
}

int main()
{
	Graph g;
	int cost;
	g.accept();
	g.display();
	cost = g.prims();
	cout<<"\nCost of MST: "<<cost;
	return 0;
}
