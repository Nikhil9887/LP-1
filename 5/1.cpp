#include <bits/stdc++.h>
using namespace std;

void firstFit(vector<int> blockSize, vector<int> processSize)
{
    int n = processSize.size();
    vector<int> allocation(n,-1);
   
    cout<<"FIRSTFIT"<<endl;
   
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<blockSize.size();j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] = blockSize[j] - processSize[i];
                break;
            }
           
        }
    }
   
    cout<<"PNo.     "<<"processSize"<<"Status"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i+1<<"    ";
        cout<<processSize[i]<<"     ";
        if(allocation[i]!=-1)
        {
            cout<<allocation[i] + 1<<endl;
        }
        else
        {
            cout<<"Memory Not Allocated"<<endl;
        }
    }
   
    cout<<"\n\n"<<endl;
}

void nextFit(vector<int> blockSize, vector<int> processSize)
{
    int n = processSize.size();
    vector<int> allocation(n,-1);
   
    cout<<"NEXTFIT"<<endl;
   
    for(int i=0;i<n;i++)
    {
        bool is = false;
        for(int j=0;j<blockSize.size();j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] = blockSize[j] - processSize[i];
            }
            if(blockSize[j] == processSize[i] and allocation[i]!=-1)
            {
                allocation[i] = j;
                blockSize[j] = blockSize[j] - processSize[i];
                is = true;
                break;
            }
        }
       
        if(!is)
        {
            allocation[i] = -1;
        }
    }
   
    cout<<"PNo.     "<<"processSize"<<"Status"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i+1<<"    ";
        cout<<processSize[i]<<"     ";
        if(allocation[i]!=-1)
        {
            cout<<allocation[i] + 1<<endl;
        }
        else
        {
            cout<<"Not Next fit"<<endl;
        }
    }
   
    cout<<"\n\n"<<endl;
}

void bestFit(vector<int> blockSize, vector<int> processSize)
{
    int n = processSize.size();
    vector<int> allocation(n,-1);
   
    cout<<"BESTFIT"<<endl;
   
    for(int i=0;i<n;i++)
    {
        int ind = -1;
        for(int j=0;j<blockSize.size();j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                if(ind == -1)
                {
                    ind = j;
                }
                else if(blockSize[ind] > blockSize[j])
                {
                    ind = j;
                }
            }
        }
       
        if(ind != -1)
        {
            allocation[i] = ind;
            blockSize[ind] = blockSize[ind] - processSize[i];
        }
    }
   
    cout<<"PNo.     "<<"processSize"<<"Status"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i+1<<"    ";
        cout<<processSize[i]<<"     ";
        if(allocation[i]!=-1)
        {
            cout<<allocation[i] + 1<<endl;
        }
        else
        {
            cout<<"Not Best fit"<<endl;
        }
    }
   
    cout<<"\n\n"<<endl;
}

void worstFit(vector<int> blockSize, vector<int> processSize)
{
    int n = processSize.size();
    vector<int> allocation(n,-1);
   
    cout<<"WORSTFIT"<<endl;
   
    for (int i=0; i<n; i++)
    {
        int ind = -1;
        for (int j=0; j<blockSize.size(); j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (ind == -1)
                    ind = j;
                else if (blockSize[ind] < blockSize[j])
                    ind = j;
            }
        }

        if (ind != -1)
        {
            allocation[i] = ind;
            blockSize[ind] -= processSize[i];
        }
    }
   
    cout<<"PNo.     "<<"processSize"<<"Status"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<i+1<<"    ";
        cout<<processSize[i]<<"     ";
        if(allocation[i]!=-1)
        {
            cout<<allocation[i] + 1<<endl;
        }
        else
        {
            cout<<"Memory Not Allocated"<<endl;
        }
    }
    cout<<"\n\n"<<endl;
   
}

int main()
{
    vector<int> blockSize = {30,50,20,10,40}, processSize = {80,20,30,15};
    // int n,m;
    // cout<<"Enter the count of memory blocks"<<endl;
    // cin>>m;
    // cout<<"Enter the count of process"<<endl;
    // cin>>n;
   
    // vector<int> blockSize(m), processSize(n);
    // for(int i=0;i<m;i++)
    // {
    //     cout<<"The size of "<<i+1<<" th block is ";
    //     cin>>blockSize[i];
    //     cout<<endl;
    // }
   
    // for(int i=0;i<n;i++)
    // {
    //     cout<<"The size of "<<i+1<<" th process is ";
    //     cin>>processSize[i];
    //     cout<<endl;
    // }
   
    firstFit(blockSize,processSize);
    nextFit(blockSize,processSize);
    bestFit(blockSize,processSize);
    worstFit(blockSize,processSize);
    return 0;
}