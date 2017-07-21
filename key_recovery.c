#include <stdio.h>
#include <stdlib.h>
#include "graph_functions.h"

void BFS(int id, int visited[], struct Graph* graph, int n_key,int V)
{
    struct AdjListNode* near = graph->array[id].head;
    int paired_key;
    //all nearby vertices with known keys - adj
    while(near)
    {
      if(near->key)
	{
         struct AdjListNode* adj = near;
	 struct AdjListNode* far = graph->array[adj->dest].head;
         //if adj has no near nodes except id continue to next adj node
         if((far->dest==id)&&(!far->next))
	   {
             visited[adj->dest]=1; // visited - all keys from this node are known
	     near = near->next;
             continue;
	   }
    	else
    	    {
             struct AdjListNode* far_prev = NULL;
	     struct AdjListNode* temp_prev = NULL; //2 nodes before current node
             paired_key = adj->key;
    	     while(far)
	       {
	        if (!visited[far->dest])
		  {
		     //node before id in list
           	     if(far->next!=NULL && (far->next)->dest==id)
 	   		{
			    far->key = (paired_key)^((far->next)->bc_key);
			    //undirected graph
			    struct AdjListNode* temp = graph->array[far->dest].head;
			    while(temp && temp->dest!=adj->dest)
				temp = temp->next;
			    temp->key = far->key;
             		    n_key++;
			    if(n_key >= V-1)      //all keys are known
				return;
			    //other keys that can be found with this key
                            if(far_prev)
			      {
				paired_key = far->key;
				id = far->dest;
				far_prev = temp_prev;
				far = far_prev;
				continue;
			      }
	  		 }
                     //node after id in list
           	     if(far_prev!=NULL && far_prev->dest==id)
	 	      {
             		    far->key =(paired_key)^(far->bc_key);
			    //undirected graph
			    struct AdjListNode* temp = graph->array[far->dest].head;
			    while(temp && temp->dest!=adj->dest)
				temp = temp->next;
			    temp->key = far->key;
            		    n_key++;
			    if(n_key >= V-1)      //all keys are known
				return;
			    //other pair that can be found with this key
			    if(far->next)
			      {
                                paired_key = far->key;
                                id = far->dest;
				far_prev = far;
				far = far->next;
				continue;
			      }
	  	       }
		  }
	          if(far->next == NULL)
		  {
		       visited[far->dest] =1;
                       break;
		  }
		  //next node attached to this adj node
		  temp_prev = far_prev;
		  far_prev = far;
	          far = far->next;
			
               }
		 //keys 3 steps away
                 visited[id] = 1;
		 if(!visited[adj->dest])
		 BFS(adj->dest,visited, graph,n_key,V);
		 visited[adj->dest]=1;
	    }
	  }
          near = near->next;
     }
}

void recover(struct Graph* graph,int V)
{
  int n_key = 0;
  int visited[V];
  //initialize visited
  for(int i =0;i<V;i++)
    visited[i]=0;
  int id = identity;
  if(n_key < V-1) 
  BFS(id,visited,graph,n_key,V);
}

