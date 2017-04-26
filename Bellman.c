#include<stdio.h>
#define MAX 4	
#define INF 9999

void calc( int a[MAX][MAX], anext[MAX][MAX])
{
	int node = 0;
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
		printf("%c  ",(char)(i+65));
		printf("%d\n", dist[i]);
    }

}


int main()
{
    
    int a[MAX][MAX], anext[MAX][MAX] ;	
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

    
	printf("\n");
	calc( a, anext );
	
	return 0;
}