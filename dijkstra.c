#include<stdio.h>
#define MAX 5	
#define INF 9999
int beta[MAX]={0};

int minfunc(int node,int a[MAX][MAX],int edg[MAX],int flag[MAX], int dist[MAX])		
{
	int i,j;
	int min = INF;
	int edge;
    
	for(i=0;i<MAX;i++)
	{
		if( flag[i]==0 && edg[i]==0 && a[node][i]!=0 )
        {
			edg[i] = dist[node] + a[node][i];
            beta[i] = node;
        }
		
        else if( flag[i]==0 && edg[i]!=0 && a[node][i]!=0 ) 
		{
			if( dist[node]+a[node][i] < edg[i] )
            {
                edg[i] = dist[node]+a[node][i];
                beta[i] = node;
            }
        } 
	
    }

	for(i=0;i<MAX;i++)
	{
		if( edg[i] < min && edg[i]!=0 )
		{
			min = edg[i];
			edge = i;
        }	
	}
	flag[edge] = 1;
	edg[edge] = 0;
	dist[edge] = min;

	return edge;
}

void path(int node)
{
    if(beta[node]==0)
    {
        printf("%c-",(char)(node+65));
        printf("%c\n",(char)(65));
    }
    else
    {
        printf("%c-",(char)(node+65));
        path(beta[node]);
    }
}

void dijkstra( int a[MAX][MAX], int edg[MAX], int flag[MAX] )
{
	int dist[MAX]={0};
	int node = 0;
	int i;
    dist[node] = 0;
    flag[node] = 1;
	for( i=0; i<MAX-1 ; i++ )
	{
		node = minfunc( node, a, edg, flag, dist);
	}

	for(i=0;i<MAX;i++)
	{
		printf("%c  ",(char)(i+65));
		printf("%d\n", dist[i]);
    }

}


int main()
{
    
    int a[MAX][MAX], flag[MAX]={0}, edg[MAX]={0} ;	
	int i,j;


	printf("Enter adjacency matrix: \n");
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			scanf("%d",&a[i][j]);			
		}
	}

	printf("\n");
	dijkstra( a, edg, flag );
	
    printf("\nPath for nodes:\n");
    for(i=1;i<MAX;i++)
    {
        path(i);
    }
    
	return 0;
}


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