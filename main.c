#include <stdio.h>
#include <time.h>
#include "graph_functions.h"

/*must be changed for each node*/
int identity = 1; //the identity of the node
int keys[] = {0xC,0,0x3,0xA,0,0x8}; //n-1 pairwise keys with k keys between each edge are hardcoded 

int k = 2;  //number of keys between each pair of nodes

struct GraphArr* sp_tree(int n_edge);  //lists edge-disjoint spanning trees for all the nodes
void comm(struct Graph *graph,int V);     //broadcast and receive sums of pairwise keys
void recover(struct Graph* graph,int V);  //recover pairwise keys from sum
struct Graph* primMST(int Adj_temp[n][n],int V);

int main()
{
	struct Edgewt adj[n][n];
	
	int i=0,j=0;
	int select = 0;
	//initialize adjacency matrix
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			adj[i][j].n_reuse=0;
			adj[i][j].weight=0;
		}
	}
	struct GraphArr* span = sp_tree(k);
	i=0;
	while(i<span->N)
   	{
		printf("TREE %d\n",i);
		printGraph(&(span->arr[i]));
		comm(&(span->arr[i]),n);
		recover(&(span->arr[i]),n);
		printKeys(&(span->arr[i++]));
		printf("\n");
		//Renew group key after a delay
		unsigned int retTime = time(0) + 4;   // Get finishing time.
    		while (time(0) < retTime);
		printf("To continue with same group enter 0\n");
		scanf("%d",&select);
		if(!select)   
		{	
			/*if(i==span->N)  //loop through the existing list of spanning trees
				i=0;*/
			continue;
		}
		else     //for the new group find MST 
		break;
	}
	int V;
	printf("enter # nodes in new group:\n");
	scanf("%d",&V);
	int nodes[V];
	for(i=0;i<V;i++)
	{
		printf("enter node number %d\n",i);
		scanf("%d", &nodes[i]);
	}
	int Adj_temp[V][V];   //adjacency matrix of the nodes in new group
	//while(1)    //find MST repeatedly for the new group
	//{
		for(i=0;i<V;i++)
		{
			for(j=0;j<V;j++)
			{		
				Adj_temp[i][j] = adj[nodes[i]][nodes[j]].weight;
			}
		}
		struct Graph *graph = primMST(Adj_temp,V);
		printGraph(graph);
		printKeys(graph);
		comm(graph,V);
		recover(graph,V);
		printKeys(graph);
		printf("\n");
	//}
	
			
	return 0;
}
