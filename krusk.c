#include<stdio.h>
#define MAX 7
int min,max,e1,e2;

int BFS(int tree[MAX][MAX], int start)
{
    int visited[MAX] = {0};
	int j;
    int q[MAX];
    int front=-1;
    int rear=0;
    q[0]=e1;
    visited[j]=1;
    while( front!=rear )
    {
        start=q[++front];
        for(j=0;j<MAX;j++)
        {
            if(tree[start][j]>0 && visited[j]==0)
            {
                visited[j]=1;
                q[++rear]=j;
                if(j==e2)
                    return 1;
            }
        }
    }
            
    return 0;
}


void minfunc(int a[MAX][MAX],int flag[MAX][MAX])
{
	int i,j;
	min=max+1;
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if( (flag[i][j]==0) && (a[i][j]!=0) && (a[i][j]<min) )
			{
				min = a[i][j];
				e1=i; e2=j;
			}
		}
	}
	flag[e1][e2]=1;
	flag[e2][e1]=1;
}

void addEdge(int tree[MAX][MAX])
{
	tree[e1][e2]=min;
	tree[e2][e1]=min;
    printf("\n%c ", (char)(e1+65) );
    printf("%c ", (char)(e2+65) );
    printf("%d ", tree[e1][e2]);
}

int main()
{
	max=0;
	
	int a[MAX][MAX], flag[MAX][MAX]={0}, tree[MAX][MAX]={0};
	int nodeList[MAX]={0};
	int i,j,nodes;
	int weight=0;
	int f;



	printf("Enter adjacency matrix: \n");
	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			scanf("%d",&a[i][j]);
			
			if(a[i][j]>max)
				max=a[i][j];
			
		}
	}

    printf("\nMinimum Spanning Tree is: ");
	nodes=MAX-1;
	while(nodes!=0)
	{
		minfunc(a,flag);
		
					
		if( (nodeList[e1]==1) && (nodeList[e2]==1) )
		{	
			while( BFS( tree, e1 ) )
				minfunc(a,flag);
		}
		
		addEdge(tree);
		nodes--;
		
		nodeList[e1]=1;
		nodeList[e2]=1;
		weight=weight+min;
		
	}

	
	printf("\nWeight is: %d",weight);

    
	return 0;
}