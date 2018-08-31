#include<stdio.h>
#define MAX 5	
#define INF 9999
int dist[MAX];
parent[MAX]={0};

void path(int node)            
{
    if(parent[node]==0)
    {
        printf("%c-",(char)(node+65));
        printf("%c\n",(char)(65));
    }
    else
    {
        printf("%c-",(char)(node+65));
        path(parent[node]);
    }
}

void bellman( int a[MAX][MAX])
{
	int node = 0;
	int i,j,k;
    
    	dist[node] = 0;
 
 	for( k=0; k<MAX-1 ; k++ )
	{
		for(i=0;i<MAX;i++)
		{
			node=i;
			for(j=0;j<MAX;j++)
			{
				if( dist[j] > (dist[node]+a[node][j]) )
				{
					dist[j] = (dist[node]+a[node][j]);
					parent[j]=node;
				}
			}
		}
	}

	
	for(i=0;i<MAX;i++)
	{
		printf("%c  ",(char)(i+65));
		printf("%d\n", dist[i]);
    	}

}


int main()
{
    
    	int a[MAX][MAX];
	int i,j;
	
	printf("Enter adjacency matrix: \n");
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			scanf("%d",&a[i][j]);
			if(a[i][j]==0)
				a[i][j]=INF;
		}
	}

	for(i=0;i<MAX;i++)
		dist[i]=INF;
    
	printf("\n");
	bellman( a );
	
	printf("\nPath for nodes:\n");
    	for(i=1;i<MAX;i++)
    		path(i);
    
	return 0;
}

/*
Output:

Enter adjacency matrix: 
0 10 0 5 0
0 0 1 2 0
0 0 0 0 4
0 3 9 0 2
7 0 6 0 0

A  0
B  8
C  9
D  5
E  7

Path for nodes:
B-D-A
C-B-D-A
D-A
E-D-A
*/
