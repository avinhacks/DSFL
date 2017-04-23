#include <iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
#define INF 999

class graph
{
	int n,e;
	int g[10][10];
	int u,v,w,nn;						// nn is used for next node
	int visited[10],dist[10],pred[10];
	public:
		void create();
		void print();
		void dj();
		void display();
		void  init()
		{
			int i,j;
			for(i=0;i<n;i++)
			{
				for(j=0;j<n;j++)
				{
					g[i][j]=INF;
				}
			}
		}
};

void graph::create()
{
	int i;
	cout<<"\nEnter the no of vertices: ";
	cin>>n;
	cout<<"\nEnter the no of edges: ";
	cin>>e;
	init();
	for(i=0;i<e;i++)
	{
		cout<<"\nEnter the starting vertex: ";
		cin>>u;
		cout<<"Enter the ending vertex: ";
		cin>>v;
		cout<<"Enter the weight: ";
		cin>>w;
		g[u][v]=g[v][u]=w;
	}
}

void graph::print()
{
	cout<<"\nAdjacency matrix\n------------------\n";
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			cout<<"  "<<g[i][j];
		}
		cout<<"\n";
	}
}

void graph:: dj()
{

	int i,k,min;
	cout<<"\nEnter starting vertex: ";
	cin>>u;
	for(i=0;i<n;i++)
	{
		visited[i]=0;
		dist[i]=g[u][i];
		pred[i]=u;
	}
	visited[u]=1;
	k=1;
	while(k<n-1)
	{
		min=INF;
		for(i=0;i<n;i++)
		{
			if(!visited[i]&&dist[i]<min)
			{
				min=dist[i];
				nn=i;


			}
		}
		visited[nn]=1;
		for(i=0;i<n;i++)
		{
			if(!visited[i]&& (min + g[nn][i])<dist[i])
			{
				dist[i]=min +g[nn][i];
				pred[i]=nn;
			}
		}
		k++;
	}

}

void graph::display()
{
	int i,j;
	for(i=0;i<n;i++)
	{
		if(i!=u)
		{
			cout<<"\n\nDistance of vertex "<<i<<"="<<dist[i];
			cout<<"\nPath ="<<i;
			j=i;
			do
			{
				j=pred[j];
				cout<<"<-"<<j;

			}while(j!=u);
		}
	}
}


int main()
{

	graph g;		//object of class graph
	int ch;
	cout<<"\n*****DIJKSTRA'S ALGORITHM***** ";
	cout<<"\n*****MENU*****";
	do
	{
		cout<<"\n1.Create\n2.Print\n3.Dijikstra's Algorithm\n4.Exit";
		cout<<"\nEnter your choice:";
		cin>>ch;
		switch(ch)
		{
			case 1:
				g.create();
				break;

			case 2: g.print();
				break;

			case 3: g.dj();
				cout<<"\nDijikstra's Algorithm-------> ";
				g.display();
				break;

			case 4:	exit(0);

			default: cout<<"\nWrong choice !";
		}

	}while(1);
}
