#include <stdio.h>
#include <math.h>

int n;
int pos[8]={-1};

int place(int level, int col)
{
	int i;
	for(i=0;i<level;i++)
	{
		if(pos[i]==col)
			return 0;

		if( abs(level-i) == abs(col-pos[i]) )
			return 0;
	}
	return 1;
}

int queen( int level )
{
	int i, flag;
	for(i=0;i<n;i++)
	{
		if(place(level, i))   		  
		{
			pos[level] = i;

			if( level==(n-1) )			//Nth Queen
				return 1;

			flag = queen(level+1);    //Next Queen

			if(flag==1)
				return 1;
		}
	}

	if( i==n )   //Backtrack
		return 0;
	
	return 1;		
}

int main()
{
	int i;
	n=8;
	
	queen(0);

	printf("/n/n/nSolution:   ")
	for(i=0;i<n;i++)
		printf("%d ",pos[i]+1);

	return 0;
}