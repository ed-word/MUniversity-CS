#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

int main()
{
    int i;
    cout << "Enter frames: ";
    string frames,output;
    getline (cin, frames);
    
    output.push_back('#');
    for(i=0;i<frames.length();i++)
    {
        if(frames[i]!=' ')
        {
            if(frames[i]=='#'||frames[i]=='$')
                output.push_back('$');
            output.push_back(frames[i]);
        }
        else
        {
            output.push_back('#');
            output.push_back('#');
        }
    }
    output.push_back('#');
    cout <<"\n"<<output<<"\n";
    
    for(i=0;i<output.length();i++)
    {
        if(output[i]=='#')
        {
            i++;
            while(output[i]!='#')
            {
                if(output[i]=='$')
                    i++;
                cout << output[i];
                i++;
            }
            cout << ' ';
        }
    }
    return 0;
}
/*
Output:
Enter frames: ABC AB#C$

#ABC##AB$#C$$#
ABC AB#C$
*/