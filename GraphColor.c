#include <stdio.h>
#include <math.h>

int n;
int Colors;
int C[100];
int G[100][100];

int place(int node, int color)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(G[node][i]!=0)
		{
			if(C[i]==color)
				return 0;
		}
	}
	return 1;
}

int putColor( int node )
{
	int i, flag;
	for(i=0;i<Colors;i++)
	{
		if(place(node, i))   		  
		{
			C[node] = i;

			if( node==(n-1) )			//Nth node
				return 1;

			flag = putColor(node+1);    //Next node

			if(flag==1)
				return 1;
		}
	}

	if( i==Colors )   //Backtrack
		return 0;
	
	return 1;		
}

int main()
{
	int i,j;
	n=6;
	Colors=3;
	
	printf("Enter adjacency matrix: \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&G[i][j]);
		}
	}
	
	for(i=0;i<n;i++)
		C[i]=-1;
	
	putColor(0);

	printf("\nSolution:   ");
	for(i=0;i<n;i++)
		printf("%d ",C[i]);

	return 0;
}