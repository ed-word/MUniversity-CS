#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(int arr[], int n, int burst[])
{
   int i, j;
   for (i = 0; i < n-1; i++) 
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
           {
              swap(&arr[j], &arr[j+1]);
              swap(&burst[j], &burst[j+1]);
           }
}

int main()
{
    int i,counter=0,index=0,x,n;
    cout << "Enter no. of inputs: ";
    cin >> n;
    int arrival[n],burst[n],WT[n],TAT[n],CT[n];
    cout << "Enter Arrival and Burst time: \n";
    for(i=0;i<n;i++)
        cin >> arrival[i];
    for(i=0;i<n;i++)
        cin >> burst[i];
    
    bubbleSort(arrival, n, burst);
    
    for(i=0;i<n;i++)
    {
        if(counter<arrival[i])
            counter=arrival[i];
        WT[i] = counter-arrival[i];
        counter += burst[i];
        TAT[i] = counter-arrival[i];
        CT[i] = counter;
    }
    
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for(i=0;i<n;i++)
        cout <<i<<"\t"<<arrival[i]<<"\t"<<burst[i]<<"\t"<<CT[i]<<"\t"<<TAT[i]<<"\t"<<WT[i]<<"\n";
    return 0;
}

/*
Output:
Enter no. of inputs: 5
Enter Process ID, Arrival and Burst time: 
0 1 2 3 4
2 5 1 0 4
6 2 8 3 4

Process	AT	BT	CT	TAT	WT
3	0	3	3	3	0
2	1	8	11	10	2
0	2	6	17	15	9
4	4	4	21	17	13
1	5	2	23	18	16
*/
