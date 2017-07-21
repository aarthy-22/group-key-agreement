/*Contains all the functions needed by graphs and other data structures used*/
#include "graph_functions.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->bc_key = 0;
    newNode->next = NULL;
    newNode->key = 0;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}

//Function that creates an GraphArr
struct GraphArr* createGraphArr(int V, int n_edge)
{
		struct GraphArr* graphArr = (struct GraphArr*)malloc(sizeof(struct GraphArr));
	
		//# spanning trees is the greatest integer less than #vertices*#edges/2
		graphArr->N = V*n_edge/2;

		//create an array of graphs(trees) of size N
		graphArr->arr = (struct Graph*) malloc(V*n_edge/2 * sizeof(struct Graph));
		//initialize all the graphs 
		int i;
		  for (i = 0; i < graphArr->N; ++i)
		      graphArr->arr[i] = *createGraph(V);
	 
		  return graphArr;
}
 
// Adds an edge to an undirected graph
void addEdge(struct AdjList* array, int src, int dest, int n_edge)
{
	    // add an edge from src to dest.  a new node is added to the adjacency
	    // list of src.  the node is added at the begining
	    struct AdjListNode* newNode = newAdjListNode(dest);
			struct AdjListNode* newNode_ = newAdjListNode(dest);
	    newNode->next = array[src].head;
	    array[src].head = newNode;
			// since graph is undirected, add an edge from dest to src also
	    newNode_ = newAdjListNode(src);
	    newNode_->next = array[dest].head;
	    array[dest].head = newNode_;

			//update adjacency matrix
			adj[src][dest].n_reuse++;
			if(adj[src][dest].n_reuse>(k-1))
				adj[src][dest].weight = pow((adj[src][dest].n_reuse-(k-1)),2);

			adj[dest][src].n_reuse++;
			if(adj[dest][src].n_reuse>(k-1))
				adj[dest][src].weight = pow((adj[dest][src].n_reuse-(k-1)),2);
	
			//save values of known keys in the nodes
			if(src == identity)
			{ 
				newNode->key = keys[dest+(n_edge-1)*n];
				newNode_->key = newNode->key;
			} 
			if(dest == identity)
			{
				newNode_->key = keys[src+(n_edge-1)*n];
				newNode->key = newNode_->key;
			}
}

//print Graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("Nodes adjacent to %d\n", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
        
    }
}

//print keys
void printKeys(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("Keys of node %d\n", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->key);
            pCrawl = pCrawl->next;
        }
        printf("\n");
        
    }
}

void printbcKeys(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        
        printf("Keys of node %d\n", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->bc_key);
            pCrawl = pCrawl->next;
        }
        printf("\n");
        
    }
}
