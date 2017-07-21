#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "graph_functions.h"
 
int minKey(int key[], int mstSet[],int V)
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < V; v++)
     if (mstSet[v] == 0 && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed MST stored in parent[]
struct Graph* createMST(int parent[],int V)
{
	struct Graph* graph = createGraph(V);
   	for (int i = 1; i < V; i++)
        addEdge(graph->array, parent[i],i,(adj[parent[i]][i].n_reuse)%k+1);
	return graph;
}
 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
struct Graph* primMST(int Adj_temp[n][n],int V)
{
    int parent[V]; // Array to store constructed MST
    int key[V];   // Key values used to pick minimum weight edge in cut
    int mstSet[V];  // To represent set of vertices not yet included in MST
	int i,j;
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < V-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet,V);
        // Add the picked vertex to the MST Set
        mstSet[u] = 1;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < V; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (mstSet[v] == 0 && Adj_temp[u][v] <  key[v])
		  {
             parent[v]  = u;
			 key[v] = Adj_temp[u][v];	
		  }
     }
 
     // create MST
     return(createMST(parent,V));
}
 
