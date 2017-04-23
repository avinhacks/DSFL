#include<iostream>
#include<stdlib.h>
int visited[10];
using namespace std;

class Graph {
    int edges,min_cost;
    int min;
    int a,b,u,v,n,i,j,arr[20][20];
    string arr1[10];
public:
    Graph() {
        edges=1;
        min_cost=0;
    }
    void ent_node()
    {
        cout<<"\nEnter no of Cities";
        cin>>n;
        cout<<"\nEnter City names:";
        for(i=0;i<n;i++)
        {
            cin>>arr1[i];
        }
    }
    void kruskal(int arr[20][20],int n);
    void read()
    {
        ent_node();
        //cout<<"\nEnter the no of vertices: "<<endl;
       // cin>>n;
        cout<<"\nEnter the distance between cities in kms : ";
        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                cin>>arr[i][j];
                arr[j][i]=arr[i][j];
                if(arr[i][j]==0)
                    arr[i][j]=arr[j][i]=999;
           	}
        }
        for(i=0;i<n;i++)                // for initialing diagonal with 0
            for(j=0;j<n;j++)
                if(i==j)
            		arr[i][j]=0;

        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                cout<<"\t\t"<<arr[i][j];
            }
            cout<<"\n";
        }
        kruskal(arr, n);
    }
};

void Graph::kruskal(int arr[20][20],int n)
{
    while(edges<n)
    {
        min=999;

        for(i=0;i<n;i++)
        {
            for(j=i+1;j<n;j++)
            {
                if(arr[i][j]<min)
                {
                    min=arr[i][j];
                    a=u=i;
                    b=v=j;
                }
            }
        }

    if(u!=v)
    {
        edges++;
        cout<<"\nDistance between city : "<<arr1[a]<<"->"<<arr1[b]<<" = " <<min<<" kms";
        min_cost=min_cost+min;
    }
    arr[a][b]=arr[b][a]=999;

    }
    cout<<"\nMinimum cost : "<<min_cost;
}

int main()
{
    Graph G;
    G.read();
}
