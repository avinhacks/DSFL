#include<iostream>
#include<iomanip>
#include<string.h>
using namespace std;
#define INFINITY 999;

class graph
{
	char vnames[10][10];
	int nodes,cost[10][10],spanning[10][10];
	int visited[10],distance[10], from[10];
    int source;
	public:
	graph();
	int position(char s[10]);
	void create_graph();
	void display();
	void initialize();
	int prims();
};

graph::graph()
{
	nodes=0;
	source = 0;
	for(int i=0;i<10;i++)
	for(int j=0;j<10;j++)
	{
		if(i==j)
		cost[i][j]=0;
		else
		cost[i][j]=999;

		spanning[i][j] =0;
	}
}

void graph::create_graph()
{
	char start[10],end[10];
	int wt,i,j, edges;
	cout<<"Enter no of nodes:";
	cin>>nodes;
	cout<<"\n Enter vertex name: ";
	for(i=0;i<nodes;i++)
	{
		cin>>vnames[i];
	}
	cout<<"\nEnter Number of Edges: ";
	cin>>edges;
	for(int k=0; k<edges; k++)
	{
		cout<<"Enter start and end vertex of the edge: ";
		cin>>start>>end;
		cout<<"Enter the weight: ";
		cin>>wt;
		i=position(start);
		j=position(end);
		cost[j][i]=cost[i][j]=wt;
	}
}

void graph::display()
{
	int i,j;
	cout<<"\n Adjacency matrix\n\t";
	for(i=0;i<nodes;i++)
		cout<<"\t"<<i;
	for(i=0;i<nodes;i++)
	{
		cout<<"\n\t"<<i;
		for(j=0;j<nodes;j++)
		cout<<"\t"<<cost[i][j];
	}
	cout << "\n";
}

int graph::position(char s[10])
{
	int i;
	for(i=0;i<nodes;i++)
		if(strcmp(vnames[i],s)==0)
			break;
	return i;
}

void graph::initialize()
{
            for(int i=0;i<nodes;i++)
            {
            	from[i] = source;
                visited[i] = 0;
                distance[i] = cost[source][i];
            }
            distance[source]= 0;
            visited[source]=1;
}

int graph :: prims()
{
    int u,v,min_distance;
    int no_of_edges,i,min_cost;
    char str[10];
    cout<<"Enter the source vertex\n";
    cin>>str;
    source = position(str);
    while((source<0) || (source>nodes-1)) {
    	   cout<<"Source vertex should be between 0 and"<<nodes-1<<endl;
    	   cout<<"Enter the source vertex again\n";
    	   cin>>str;
    	   source = position(str);
    }
    initialize();
    min_cost=0;        //cost of spanning tree
    no_of_edges=nodes-1;        //no. of edges to be added
    cout << "\n Minimum Spanning Tree:";
    // MAIN LOGIC
    while(no_of_edges>0)
    {
        //find the vertex at minimum distance from the tree
        min_distance=INFINITY;
        for(i=0;i<nodes;i++)
            if(visited[i]==0&&distance[i]<min_distance)
            {
                v=i;
                min_distance=distance[i];
            }

        u=from[v];

        //insert the edge in spanning tree
        spanning[u][v]=distance[v];
        spanning[v][u]=distance[v];
        no_of_edges--;
        visited[v]=1;

        //updated the distance[] array
        for(i=0;i<nodes;i++)
            if(visited[i]==0&&cost[i][v]<distance[i])
            {
                distance[i]=cost[i][v];
                from[i]=v;
            }
        cout << "\n edge(" << u <<"," << v << ")" << cost[u][v];


        min_cost=min_cost+cost[u][v];
    }

    return(min_cost);
}



int main()
{
	graph sp;
	sp.create_graph();
	sp.display();
	int cost = sp.prims();

	cout << "\n Cost of minimum spanning tree:"<<cost;
	return 0;
}






