#include <stdio.h>

int a[4][4]={{1,2,3,4},{5,6,0,8},{9,10,7,11},{13,14,15,12}};
int target[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}};

int row,col;
int i,j,temp[4][4], x;	
char globMove;

int inversions()
{
	int count=0;

	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if( temp[i][j]!=0 && (temp[i][j]!=target[i][j]) )
				count++;
		}
	}
	return count;
}


void swap(int *a,int *b)
{
	x = *a;
	*a = *b;
	*b = x;
}

int moveX(int flag, char move)
{
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			temp[i][j]=a[i][j];
	
	
	if(move=='U'){

		if(flag){
			swap( &a[row][col], &a[row-1][col] );
			row--;
		}

		swap( &temp[row][col], &temp[row-1][col] );
		return inversions();
	}

	if(move=='D'){

		if(flag){
			swap( &a[row][col], &a[row+1][col] );
			row++;
		}

		swap( &temp[row][col], &temp[row+1][col] );
		return inversions();
	}

	if(move=='R'){

		if(flag){
			swap( &a[row][col], &a[row][col+1] );
			col++;
		}

		swap( &temp[row][col], &temp[row][col+1] );
		return inversions();
	}

	if(move=='L'){
		
		if(flag){
			swap( &a[row][col], &a[row][col-1] );
			col--;
		}

		swap( &temp[row][col], &temp[row][col-1] );
		return inversions();
	}

}


int min( int hxup,int hxdown,int hxrt,int hxlft )
{
	int minimum = (hxup < hxdown) ? ((hxup < hxrt) ? hxup : hxrt) : ((hxdown < hxrt) ? hxdown : hxrt);
	minimum = (minimum < hxlft)? minimum : hxlft;

	if(minimum==hxup)
	{
		moveX(1, 'U');
		globMove='U';
		printf("UP  ");
	}
	else if(minimum==hxdown)
	{
		moveX(1, 'D');
		globMove='D';
		printf("DOWN  ");
	}
	else if(minimum==hxrt)
	{
		moveX(1, 'R');
		globMove='R';
		printf("RIGHT  ");
	}
	else
	{
		moveX(1, 'L');
		globMove='L';
		printf("LEFT  ");
	}

	if(minimum==0)			//Target 
		return 1;

	return 0;
}

void puzzle( char move )
{
	int hxup=9999,hxdown=9999,hxrt=9999,hxlft=9999, var;
	
	if( move!='D' && row!=0 )		//Move UP
		hxup = moveX(0, 'U');

	if( move!='U' && row!=3 )		//Move DOWN
		hxdown = moveX(0, 'D');
	
	if( move!='L' && col!=3 )		//Move RIGHT
		hxrt = moveX(0, 'R');
	
	if( move!='R' && col!=0 )		//Move LEFT
		hxlft = moveX(0, 'L');


	var = min( hxup, hxdown, hxrt ,hxlft );   	//Calc optimal move
	
	if(var)			//No. of inversions is zero (Target)
		return;	

	puzzle(globMove);
}


int main()
{
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(a[i][j]==0)
			{
				row=i;
				col=j;
			}
		}
	
	puzzle('0');
	return 0;
}
