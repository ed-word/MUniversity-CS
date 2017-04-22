#include <stdio.h>
int total, sum, n;


int ss( int set[],int level )   //Level is the level in state space tree
{
	int i;
	int flag;
	for(i=level;i<n;i++)
	{
		
		total+=set[i];
		if(total>sum)   //Backtrack
		{
			total-=set[i];
			return 0;
		}
		if(total==sum)   //Found  a subset
		{
			printf("\nSuccess\n");
			printf(" %d ", set[i]);
			return 1;
		}
		
		
		flag = ss(set,++level);   //Returns 0 for backtracking, 1 for success
		if(flag==0)
		{
			total-=set[i];
		}
		if(flag==1)
		{
			printf("%d ", set[i]);
			return 1;
		}
	
	}		
}

int main()
{
	
	int set[]={ 2,3,5,7,10 };
	
	sum=17;
	n=5;
	
	ss(set,0);

	return 0;
}