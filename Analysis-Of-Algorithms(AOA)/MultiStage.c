#include <stdio.h>
#define MAX 100	
#define INF 9999
int dist[MAX], parent[MAX]={0};
int n, stage[MAX][MAX], stages, slen[MAX];

void UpdateNeighbours( int G[MAX][MAX], int node )
{
	int i;
	for(i=0;i<n;i++)
	{
		if(G[node][i]!=0)
		{
			if( (dist[node]+G[node][i])<dist[i] )
			{
				dist[i] = dist[node]+G[node][i];
				parent[i] = node;
			}
		}
	}
}

void multistage( int G[MAX][MAX] )
{
    int i,j,node;
	dist[0] = 0;  //Source
	for(i=0;i<stages-1;i++)
	{
		for(j=0;j<slen[i];j++)
		{
			node = stage[i][j];
			UpdateNeighbours( G, node); //Updates the dist value of neighbours of node
		}
	}
}

void path(int node)            
{
    printf("T-");
    node = parent[node];
	while(parent[node])
	{
		printf("%c-",(char)(node+65-1));
		node = parent[node];
	}	 
    printf("%c-",(char)(node+65-1));
    printf("S\n");
}

int main()
{
    
    int G[MAX][MAX];	
	int i,j;

	printf("Enter no. of vertices & stages: ");
	scanf("%d %d",&n,&stages);
	
	//Here 1st node is source and last node is sink
	//Source is Stage 0  and  Sink is Stage (n-1) 
	stage[0][0] = 0;
	slen[0] = 1; 

	stage[stages-1][0] = n-1;
	slen[stages-1] = 1; 
	
	for(i=1;i<(stages-1);i++)
	{
		printf("\nEnter No. of Nodes for Stage %d:",i);
		scanf("%d",&slen[i]);
		printf("\nEnter Nodes for Stage %d:\n",i);		
		for(j=0;j<slen[i];j++)
			scanf("%d",&stage[i][j]);
	}

	printf("\nEnter adjacency matrix: \n");
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			scanf("%d",&G[i][j]);

	for(i=0;i<n;i++)
		dist[i]=INF;
    
	multistage(G);

	printf("\nCost is: %d\n",dist[n-1]); //Dist of sink from source
	path(n-1);

	return 0;
}

/*

Output:
Enter no. of vertices & stages: 7 4

Enter No. of Nodes for Stage 1: 3
Enter Nodes for Stage 1: 1 2 3

Enter No. of Nodes for Stage 2: 2
Enter Nodes for Stage 2: 4 5

Enter adjacency matrix: 
0 1 2 7 0 0 0
0 0 0 0 3 6 0
0 0 0 0 4 10 0
0 0 0 0 0 3 0
0 0 0 0 0 0 8
0 0 0 0 0 0 2
0 0 0 0 0 0 0

Cost is: 9
T-E-A-S

*/