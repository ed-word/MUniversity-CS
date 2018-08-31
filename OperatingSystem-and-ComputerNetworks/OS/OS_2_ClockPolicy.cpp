#include <cstdio>
#include <iostream>
#include <malloc.h>

using namespace std;


int main()
{
    int f;
    cout << "Enter number of frames: ";
    cin >> f;
    int *frames = (int*)malloc(sizeof(int)*f);
    int *u = (int*)malloc(sizeof(int)*f);
    int x,i;
    
    while(cin>>x)
    {
        cout<<"\n\nValue is: "<<x<<" ";
        for(i=0;i<f;i++)
        {
            if(frames[i]==x)
            {
                cout<<"\nCache Hit\n";
                break;
            }
        }
        if(i==f)
        {
            cout<<"\nPage Fault\n";
            for(i=0;i<f;i++)
            if(u[i]==0)
                break;
        
            if(i==f)
            {
                for(i=0;i<f;i++)
                    u[i]=0;
                i=0;
            }
        }
        
        frames[i] = x;
        u[i]=1;
        for(i=0;i<f;i++)
        {
            cout<<frames[i];
            if(u[i]==1)
                cout<<"*";
            cout<<" ";
        }
    }
    return 0;
}

/*
Output:
Enter number of frames: 3
2 3 2 1 5 2 4 5 3 2 5 2


Value is: 2 
Page Fault
2* 0 0 

Value is: 3 
Page Fault
2* 3* 0 

Value is: 2 
Cache Hit
2* 3* 0 

Value is: 1 
Page Fault
2* 3* 1* 

Value is: 5 
Page Fault
5* 3 1 

Value is: 2 
Page Fault
5* 2* 1 

Value is: 4 
Page Fault
5* 2* 4* 

Value is: 5 
Cache Hit
5* 2* 4* 

Value is: 3 
Page Fault
3* 2 4 

Value is: 2 
Cache Hit
3* 2* 4 

Value is: 5 
Page Fault
3* 2* 5* 

Value is: 2 
Cache Hit
3* 2* 5* 
*/