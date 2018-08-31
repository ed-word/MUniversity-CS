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
    int dist,max,index;
    int x,i=1,k;
    int *stream = (int*)malloc(sizeof(int)*1);
    
    while(cin>>x)
    {
        stream = (int*)realloc(stream,sizeof(int)*i);
        stream[i-1] = x;
        i++;
    }
    int stream_len = i-1;
    
    for(int j=0;j<stream_len;j++)
    {
        x = stream[j];
        cout<<"\n\nValue is: "<<x<<" ";
        for(i=0;i<f;i++)
        {
            if(frames[i]==x)
            {
                cout<<"\nCache Hit";
                break;
            }
        }
        if(i==f)
        {
            cout<<"\nPage Fault";
            max=0;
            for(i=0;i<f;i++)
            {
                for(k=j+1;k<stream_len;k++)
                {
                    if(frames[i]==0)    //Empty
                    {
                        index=i;
                        goto Outer;
                    }
                    if(frames[i]==stream[k])
                        break;
                }
                dist = k-j;
                if(dist > max)
                {
                    max = dist;
                    index = i;
                }
                cout<<"\nDistance for "<<frames[i]<<" is "<<dist;
            }
            Outer: frames[index] = x;
        }
        
        cout<<"\n";
        for(i=0;i<f;i++)
            cout<<frames[i]<<" ";
    }
    return 0;
}

/*
Output:
Enter number of frames: 3
2 3 2 1 5 2 4 5 3 2 5 2 
end


Value is: 2 
Page Fault
2 0 0 

Value is: 3 
Page Fault
Distance for 2 is 1
2 3 0 

Value is: 2 
Cache Hit
2 3 0 

Value is: 1 
Page Fault
Distance for 2 is 2
Distance for 3 is 5
2 3 1 

Value is: 5 
Page Fault
Distance for 2 is 1
Distance for 3 is 4
Distance for 1 is 8
2 3 5 

Value is: 2 
Cache Hit
2 3 5 

Value is: 4 
Page Fault
Distance for 2 is 3
Distance for 3 is 2
Distance for 5 is 1
4 3 5 

Value is: 5 
Cache Hit
4 3 5 

Value is: 3 
Cache Hit
4 3 5 

Value is: 2 
Page Fault
Distance for 4 is 3
Distance for 3 is 3
Distance for 5 is 1
2 3 5 

Value is: 5 
Cache Hit
2 3 5 

Value is: 2 
Cache Hit
2 3 5 
*/