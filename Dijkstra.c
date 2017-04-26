#include<stdio.h>
#define MAX 5	
#define INF 9999
int dist[MAX];
int min;
int visit[MAX]={0};


void dijkstra( int a[MAX][MAX])
{
	int node = 0;
	int i,j;
    
    dist[node] = 0;
 
  
  	for( i=0; i<MAX ; i++ )
	{
		visit[node]=1;
		
		for(j=0;j<MAX;j++)
		{
			if( a[node][j]!=INF )
			{
				if( (dist[node]+a[node][j]) < dist[j] )
				{
					dist[j] = dist[node]+a[node][j];
				}
			}
		}

		min=INF;
		for(j=0;j<MAX;j++)
		{
			if( visit[j]!=1 && dist[j]<min)
			{
				min=dist[j];
				node=j;
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
    
    int a[MAX][MAX], flag[MAX]={0}, edg[MAX]={0} ;	
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
	dijkstra( a );
	
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
