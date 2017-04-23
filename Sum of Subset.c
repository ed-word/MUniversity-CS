#include <stdio.h>
int total, sum, n;


int ss( int set[], int prev )   //prev is the previous number index which was added to the set
{
	int i;
	int flag;
	
	for(i=prev+1 ;i<n; i++)
	{
		total+=set[i];

		printf("\nNumber: %d    Total: %d",set[i],total);

		if(total>sum)   //Backtrack
		{
			total-=set[i];
			printf("\tBacktrack   Total: %d",total);
			return 0;
		}
		if(total==sum)   //Found  a subset
		{
			printf("\nSuccess\n");
			printf(" %d ", set[i]);
			return 1;
		}
		if(i==(n-1))   //Last number, cant move further so backtrack
		{
			total-=set[i];
			return 0;
		}
		
		
		flag = ss(set,i);   //Returns 0 for backtracking, 1 for success
		if(flag==0)
		{
			total-=set[i];
			printf("\nBacktrack   Total: %d",total);
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
	
	sum=25;
	n=5;
	
	ss(set,-1);

	return 0;
}