#include<stdio.h>
#define MAX 4
#define INF 9999

void calc( int a[MAX][MAX], int anext[MAX][MAX])
{
	int i,j,k;
    
 	for( k=0; k<MAX ; k++ )
	{
		for(i=0;i<MAX;i++)
		{
			for(j=0;j<MAX;j++)
			{
				if(i==k)
					anext[i][j]=a[i][j];

				else
				{
					if( a[i][k]+a[k][j] < a[i][j] )
						anext[i][j] = a[i][k]+a[k][j];	
					else
						anext[i][j] = a[i][j];
				}
				
			}
		}

		
		for(i=0;i<MAX;i++)
			for(j=0;j<MAX;j++)
				a[i][j]=anext[i][j];

	}

	
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			printf("%d ",a[i][j]);
		}
		printf("\n");
	}
}


int main()
{
    
    int a[MAX][MAX], anext[MAX][MAX] ;	
	int i,j;


	printf("Enter adjacency matrix Enter 0 for Infinity: \n");
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			scanf("%d",&a[i][j]);
			if(i!=j && a[i][j]==0)
				a[i][j]=INF;
		}
	}

    
	printf("\n");
	calc( a, anext );
	
	return 0;
}