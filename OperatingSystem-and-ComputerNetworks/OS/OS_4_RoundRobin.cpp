// ROUND ROBINNNN
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

void bubbleSort(int arr[], int n, int burst[], int pid[])
{
   int i, j;
   for (i = 0; i < n-1; i++) 
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
           {
              swap(&arr[j], &arr[j+1]);
              swap(&burst[j], &burst[j+1]);
              swap(&pid[j], &pid[j+1]);
           }
}

int main()
{
    int i,counter=0,index=0,x,n,quant;
    
    cout << "Define Quant: ";
    cin >> quant;
    cout << "Enter no. of inputs: ";
    cin >> n;
    
    int arrival[n],burst[n],burstcopy[n],WT[n]={0},TAT[n],CT[n], prevQuant[n],pid[n];
    bool complete[n] = {false};

    cout << "Enter Process ID, Arrival and Burst time: \n";
    for(i=0;i<n;i++)
        cin >> pid[i];
    for(i=0;i<n;i++)
        cin >> arrival[i];
    for(i=0;i<n;i++)
        cin >> burst[i];
  
    bubbleSort(arrival, n, burst, pid);
    for(i=0;i<n;i++)
        burstcopy[i] = burst[i];
    
    counter = arrival[0];
    for(i=0;i<n;i++)
        prevQuant[i] = arrival[i];
    i=0;
    int completeCount=0;
    while(completeCount!=n)
    {
        index = i%n;
        if(!complete[index])
        {
            WT[index] = WT[index] + (counter - prevQuant[index]);
            
            if(burst[index]<=quant)
            {
                complete[index]=true;
                --WT[index];
                completeCount++;
                counter += burst[index];
                TAT[index] = counter - arrival[index] -1;
                CT[index] = counter;
            }
            else
            {
                counter += quant;
                prevQuant[index] = counter;
                burst[index] -= quant;
            }
        }
        i++;
    }
    
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for(i=0;i<n;i++)
        cout <<pid[i]<<"\t"<<arrival[i]<<"\t"<<burstcopy[i]<<"\t"<<CT[i]<<"\t"<<TAT[i]<<"\t"<<WT[i]<<"\n";
    
    return 0;
}



/*
Output:

Define Quant: 2
Enter no. of inputs: 5
Enter Process ID, Arrival and Burst time:
0 1 2 3 4
2 5 1 0 4
6 2 8 3 4

Process	AT	BT	CT	TAT	WT
3	0	3	11	10	7
2	1	8	23	21	13
0	2	6	21	18	12
4	4	4	17	12	8
1	5	2	10	4	2
*/
