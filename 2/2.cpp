#include <bits/stdc++.h>
using namespace std;

class Page {
  int page_frame;

 public:
  Page(int count) {
    page_frame = count;
  }
 
  void display(vector<int> &v) {
      for(auto i : v) {
          cout<<i<<" ";
      }
      cout<<"\n\n";
      return;
  }
 
  void display(deque<int> &q) {
      for(auto i : q) {
          cout<< i <<" ";
      }
      cout<<"\n\n";
      return;
  }
 
 
  bool search(int key, vector<int> &v) {
    for (auto i : v)
      if (i == key) return true;
    return false;
  }

  int future(vector<int> &page, vector<int> &v, int index) {
    int res = -1, farthest = index;
    for (int i = 0; i < page.size(); i++) {
      int j;
      for (j = index; j < v.size(); j++) {
        if (page[i] == v[j]) {
          if (j > farthest) {
            farthest = j;
            res = i;
          }
        }
      }
      if (j == v.size()) return i;
    }
    return res == -1 ? 0 : res;
  }
 
  void MRU(vector<int> &v) {
    vector<int> page(page_frame);
    unordered_map<int, int> mp;

    int last_index;

    for (int i = 0; i < page_frame; i++) {
      page[i] = v[i];
      mp[page[i]] = i;
      last_index = i;
    }

    for (int i = page_frame; i < v.size(); i++) {
      if (mp.count(v[i]) and mp[v[i]]>0) {
        last_index = mp[v[i]];
        continue;
      }
      mp[page[last_index]] = -1;
      mp[v[i]] = last_index;
      page[last_index] = v[i];
    }
   
    cout<<"MRU"<<endl;
    display(page);
  }

  void LRU(vector<int> &v) {
    vector<int> page(page_frame);
    queue<pair<int,int>> q;
    unordered_map<int,bool> mp;
   
    for(int i=0; i < page_frame; i++)
    {
        page[i] = v[i];
        mp[page[i]] = true;
        q.push({v[i], i});
    }
   
    for(int i=0; i < v.size() - page_frame; i++)
    {
        if(mp[v[i]] == true){
            pair<int,int> temp = q.front();
            q.pop();
            q.push(temp);
            continue;
        }
        mp[q.front().first] = false;
        mp[v[i]] = true;
        page[q.front().second] = v[i];
        q.pop();
    }
   
    cout<<"LRU"<<endl;
    display(page);
  }

  void FIFO(vector<int> &v) {
    deque<int> q;
    for (auto i : v) {
      auto itr = find(q.begin(), q.end(), i);
      if (itr == q.end()) {
        if (q.size() == page_frame) {
          q.pop_front();
        }
        q.push_back(i);
      }
    }
    cout<<"FIFO"<<endl;
    display(q);
  }

  void optimal_page_replacement(vector<int> &v) {
    vector<int> page;

    for (int i = 0; i < v.size(); i++) {
      if (search(v[i], page)) {
        continue;
      }

      if (page.size() < page_frame) {
        page.push_back(v[i]);
      } else {
        int j = future(page, v, i + 1);
        page[j] = v[i];
      }
    }
    cout<<"OPTIMAL"<<endl;
    display(page);
  }
};

int main() {
    int page_frame;
    cout<<"Enter page frame size"<<endl;
    cin>>page_frame;
    Page p(page_frame);
   
    // std::vector<int> v = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    // p.FIFO(v);
    // p.MRU(v);
    // p.LRU(v);
    // p.optimal_page_replacement(v);
   
    int n;
    cout<<"Enter the page count"<<endl;
    cin>>n;
    vector<int> v(n);
    for(int i = 0; i < n; i++)
    {
        cout<<"Enter page no "<<i+1<<" ";
        cin>>v[i];
    }
    cout<<endl;
   
    char choice;
    while(true){
        cout << "Choose a page replacement algorithm:\n";
        cout << "1. FIFO\n";
        cout << "2. MRU\n";
        cout << "3. LRU\n";
        cout << "4. Optimal\n";
        cout << "Enter your choice ";
        cin >> choice;

       
       
        switch (choice) {
            case '1':
                cout<<"The output is "<<endl;
                p.FIFO(v);
                break;
            case '2':
                cout<<"The output is "<<endl;
                p.MRU(v);
                break;
            case '3':
                cout<<"The output is "<<endl;
                p.LRU(v);
                break;
            case '4':
                cout<<"The output is "<<endl;
                p.optimal_page_replacement(v);
                break;
            default:
                std::cout << "Invalid choice!"<<endl;
                break;
        }
    }

    return 0;
}