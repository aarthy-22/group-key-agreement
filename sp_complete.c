//Enumeration of edge disjoint spanning trees for a complete unweighted multigraph

/* The vertex set of n vertices is divided into 2 partitions and n/2 matchings are chosen to form spanning trees for even n.
The number of edges between each pair of vertices is k
For odd values of n, [n/2] matchings are chosen 
e.g. n = 5 , k = 2
0 -- 2
1 -- 3
     4
Spanning trees are
0 -- 2  1 -- 3
0 -- 3  1 -- 4
0 -- 4  1 -- 0
2 -- 1, 3 -- 2
and
4 -- 3 and 4 -- 2 are unused
Consider,
0 -- 3
1 -- 4
2
Spanning trees are
0 -- 3  1 -- 4 
0 -- 4  4 -- 2
3 -- 1  1 -- 0
3 -- 2, 4 -- 3 
and
2 -- 1 and 2 -- 0 are unused
and the 2 edges that were unused in the first and 2nd combinations,
4 -- 3
2 -- 1
4 -- 2
2 -- 0 */

#include<stdio.h>
#include<stdlib.h>
#include "graph_functions.h"

//function to find all edge disjoint spanning trees and store them as an array of graphs
//returns a pointer to the GraphArray
struct GraphArr* sp_tree(int n_edge)
{
  int ini = n_edge;
  int n_tree=0;
  struct GraphArr* graph = createGraphArr(n, n_edge);
  int gp1, gp2, pivot;             //pivot - last element of the 1st partition, gp1 and gp2 - corresponding matchings in the 2 partitions   
  while(n_edge>0)
  {
    int arr[n];
    int i;
	for(i=0;i<n;i++)
		arr[i] = i;
	gp1 = 0;
	int mid;                //maximum num of elements in a partition
    if(n%2 == 0)
		mid = n/2;   
    else if(n%2 !=0)
		mid = n/2 +1;         
	if((n%2!=0) && (n_edge%2==0))     //partitions change for odd n and even k
	{
		gp2 = gp1+mid-1;
		pivot = mid-2;
	}
		    
	else
	{
		gp2 = gp1+mid;
		pivot = mid-1;
	}
	while(gp1<n/2)
	{
		addEdge(graph->arr[n_tree].array, gp1, gp2,n_edge);
		int r_node = gp2+1;
		int l_node = gp1+1;
		while(l_node<mid)
		{
            if(r_node<n)
			//edges b/w node of the matching from partition 1 and all remaining nodes of 2nd partition
				addEdge(graph->arr[n_tree].array, gp1,r_node,n_edge);     
			if(l_node<=pivot)
			 //edges b/w node of the matching from partition 2 and all remaining nodes of 1st partition
				addEdge(graph->arr[n_tree].array,gp2,l_node,n_edge);    
			l_node++;
            r_node++;
		}
	    int ul_node = gp1-1;
		int ur_node = gp2-1;
		while(ul_node>=0)
		{
			//edges b/w node of the matching from partition 1 and all previous nodes of 1st partition
			addEdge(graph->arr[n_tree].array, gp1,ul_node,n_edge);            
			addEdge(graph->arr[n_tree].array, gp2,ur_node,n_edge);
			ul_node--;
			ur_node--;
		}
		// next matching
		gp1++;               
		gp2++;
		n_tree++;
		
	}
	n_edge--;                     
	int k=1;
	//for odd nodes, left out edges are built into a tree for n_edge>=2 
	if(((ini-n_edge)%2!=0) && (n%2!=0) && (n_edge>0))                  
	{
		while(gp1-k>=0)
		{ 
 		   if((ini%2)==0)
  			addEdge(graph->arr[n_tree].array,gp2,gp2-k,n_edge+1);          
		   else if((ini%2)!=0)
			addEdge(graph->arr[n_tree].array, gp2-1,gp2-k-1,n_edge+1);
			addEdge(graph->arr[n_tree].array, gp1,gp1-k,n_edge);
			k++;
		}
    	n_tree++;
		
  	}
  }
  return graph;

}

