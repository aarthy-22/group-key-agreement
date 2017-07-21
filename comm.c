/*temporary udp broadcast communication procedure using netcat and socat to test the protocol*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include "main.h"
#include "graph_functions.h"

//save the broadcast keys in the corresponding nodes
void save_keys(int broadcast[],struct Graph* graph)
{
	struct AdjListNode *temp;
	int node;
	int n_key = 0;
	 for(node=0; node<identity; node++)
	{
		temp = graph->array[node].head;
		while(temp->next)
		{
			printf("%d\n", (temp->next)->dest);
			(temp->next)->bc_key = broadcast[n_key];
			temp = temp->next;
			n_key++;
		}
	}
}

void save_keys_(int broadcast[],struct Graph* graph)
{
	struct AdjListNode *temp;
	int node;
	int n_key = 0;
	 for(node=identity+1; node<n; node++)
	{
		temp = graph->array[node].head;
		while(temp->next)
		{
			(temp->next)->bc_key = broadcast[n_key];
			temp = temp->next;
			n_key++;
		}
	}
}

//convert char returned by netcat to integer
void char_to_int(char data[],int broadcast[])
{
	int n_key = 0;
	int j=0,ct=0,i=0;
	int space_posn=-1;
	while(data[i])
	{
		while(data[i++]!=10);     //asccii of NL = 10
		ct=0;
		for(j=i-2;j>space_posn;j--)
		{
			broadcast[n_key]+=(data[j]-48)*pow(10,ct);  //ascii value
			ct++;
		}
		space_posn=i;
		n_key++;
	}
}

//gets values from shell function
void get_popen(int n_key, int broadcast[])
{
	FILE *pf;       //stream between the shell script and this pgm
    	char data[20];  //received broadcast values are stored here
	char command[20]; //command line arguments
	//shell script that listens for broadcast values using netcat
	char *base_ = "bash receive.sh ";
	sprintf(command, "%s", base_);  //1st argument is the name of the script
	sprintf(command, "%s%d ", command, n_key-1);	
	pf = popen(command, "r");  //calls the receive.sh script and opens a stream
	fgets(data, 20 , pf);   //stores output in array data as characters
	char_to_int(data,broadcast);
}


void comm(struct Graph *graph,int V)
{
	//Listen for broadcast values of previous nodes
	int n_key = 0;
	struct AdjListNode *temp;
	int node;
	int broadcast[] = {0,0,0,0,0}; //stores braodcast values as integers
	//# values broadcast values to be received from previous nodes
	for(node=0; node<identity; node++)
	{
		temp = graph->array[node].head;
		while(temp->next)
		{
			n_key++;
			temp = temp->next;
		}
	}
	if(n_key)
	{
	
		get_popen(n_key, broadcast);	
		save_keys(broadcast,graph);
	}

	//Add delay to synchronize communication
	unsigned int retTime = time(0) + 1;   // Get finishing time.
    	while (time(0) < retTime);  

  	//XOR sums are broadcast
	//shell script which broadcasts arguments using socat
	char *base = "bash broadcast.sh ";
	char command[20]; //command line arguments
	sprintf(command, "%s", base);
  	temp = graph->array[identity].head;
  	int bc;   //the XOR sum to be broadcast
	while(temp->next)
	{
		bc = (temp->key)^((temp->next)->key);
		sprintf(command, "%s%d ", command, bc);
		temp = temp->next;
	}
	system(command);

	//remaining keys are received
	//# values broadcast by nodes before this node - 2nd argument
	n_key = 0;
	int broadcast_[]={0,0,0,0,0};
	for(node=identity+1; node<n; node++)
	{
		temp = graph->array[node].head;
		while(temp->next)
		{
		n_key++;
		temp = temp->next;
		}
	}
	if(n_key)
	{
		get_popen(n_key, broadcast_);	
		save_keys_(broadcast_,graph);
	}
	
	//Delay
	retTime = time(0) + 1;   // Get finishing time.
    	while (time(0) < retTime);  
}

