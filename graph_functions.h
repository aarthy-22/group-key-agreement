#include "main.h"

//structure to represesnt the edge weight
struct Edgewt
{
	int n_reuse;
	int weight;
};
struct Edgewt adj[n][n]; //global adjacency matrix

struct AdjListNode
{
    int dest;             //node number
    int bc_key;          //received value - XOR of keys of prev node and this node
    int key;              //pairwise key of this node and head node
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};

//Structure to store all the generated spanning trees as an array of graphs
//N is the number of spanning trees
struct GraphArr
{
	int N;
	struct Graph* arr;
};

// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest);

// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V);

//Function that creates an GraphArr
struct GraphArr* createGraphArr(int V, int n_edge);

// Adds an edge to an undirected graph
void addEdge(struct AdjList* array, int src, int dest, int V);

//print Graph
void printGraph(struct Graph* graph);

//print keys
void printKeys(struct Graph* graph);
void printbcKeys(struct Graph* graph);
