#include <bits/stdc++.h>
using namespace std;

class Job
{
    public:
        int id;
        int arr_time;
        int burst_time;
        int waiting_time;
        int execution_time;
   
    Job()
    {
        int id = -1;
        arr_time = 0;
        burst_time = 0;
        waiting_time = 0;
        execution_time = 0;
    }
};

void display(vector<Job> &v)
{
    cout<<"Id "<<"  A "<<"  B "<<"  E "<<"  W "<<endl;
    for(int i=0;i<v.size();i++)
    {
        cout<<v[i].id<< "   "<<v[i].arr_time<<"   "<<v[i].burst_time<<"   "<<v[i].execution_time<<"   "<<v[i].waiting_time<<endl;      
    }
}


vector<Job> fcfs(vector<Job> &v)
{
    v[0].execution_time = v[0].burst_time;
   
    for(int i=1; i < v.size(); i++)
    {
        v[i].execution_time = v[i-1].execution_time + v[i].burst_time ;
        v[i].waiting_time = v[i].execution_time - (v[i].arr_time + v[i].burst_time);
    }
    display(v);
    return v;
}


void sjf(vector<Job> &jb)
{  
    vector<Job> v = fcfs(jb);
    vector<pair<int,int>> ans;
    for(int i=0;i<v.size();i++)
    {
        ans.push_back({v[i].execution_time, v[i].id});
    }
   
    vector<Job> temp;
   
    temp.push_back(v[0]);
   
    sort(ans.begin(), ans.end());
   
    for(int i=1;i<ans.size();i++)
    {
        if(ans[i].second != v[0].id)
            temp.push_back(v[ans[i].second - 1]);
    }
   
    cout<<"The SJF order of the job is: "<<endl;
    for(int i=0;i<temp.size();i++)
    {
        cout<<"Process "<<temp[i].id<<" "<<endl;    
    }
    return;
}

void round_robin(vector<Job> &jb)
{
    vector<Job> v = fcfs(jb);
   
    unordered_map<int, vector<Job>> mp;
   
    int j = v.size() - 1;
   
    for(int i=0; i < v.size() and j>=0; i++)
    {
        vector<Job> vv;
        for(int k = 0; k <= j; k++)
        {
            vv.push_back(v[k]);
        }
        mp[v[j].execution_time] = vv;
        j--;
    }
   
    for(auto i : mp)
    {
        cout<<"The round robins according to the execution time "<<i.first<<" minute"<<endl;
        for(auto j : i.second)
        {
            cout<<"Process"<<j.id<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main()
{
    cout<<"Enter the count of tasks to process: ";
    int n, arr_time, burst_time, id;
    cin>>n;
    vector<Job> v;
   
    for(int i=0;i<n;i++)
    {
        cout<<"Give the id of job ";
        cin>>id;
        cout<<"Enter the arrival time ";
        cin>>arr_time;
        cout<<"Enter the burst time ";
        cin>>burst_time;
        Job j;
        j.id = id;
        j.arr_time = arr_time;
        j.burst_time = burst_time;
        v.push_back(j);
        cout<<"\n\n";
    }
   
    vector<Job> ans;
   
    int choice;
    while(true)
    {
        cout<<"1.FCFS\t2.SJF\t3.Round Robin\t4.EXIT"<<endl;
        cin>>choice;
       
        switch(choice)
        {
            case 1:
                ans = fcfs(v);
                break;
            case 2:
                sjf(v);
                break;
            case 3:
                round_robin(v);
                break;
            case 4:
                return 0;
        }
    }
    return 0;
}