#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(int i = a; i < b;  i++)
#define rev(i,a,b) for(int i = a; i >= b; i--)

class Node{
    public:

    int dis = LONG_LONG_MAX;

    Node(string s, bool b) : ID(s), even(b) {}
    void al_insert(Node* name, int w){
        al.push_back({name, w});
    }

    bool operator < (Node& n1){
        return (dis < n1.dis);
    }
    string ID;
    vector<pair<Node*, int>> al;
    bool vis = 0;
    bool even;
};

// class custom_comp{
//     public:
//         bool operator ()(Node* n1, Node* n2){
//             return n1->dis > n2->dis;
//         }
// };

template<class T>
class custom_min_heap{
    public:
        custom_min_heap(){
            heap.clear();
        }
        void push(T &val){
            heap.push_back(val);
            percolate_up();
        }
        bool empty(){
            return (heap.empty());
        }

        T& top(){
            return heap[0];
        }
        void pop(){
            heap[0] = heap[heap.size()-1];
            heap.erase(heap.end()-1);
            percolate_down();
        }

        void percolate_up(){
            int hole = heap.size() - 1;
            T e = heap[hole];
            while(hole > 0 && *e < *heap[(hole-1)/2]){
                heap[hole] = heap[(hole-1)/2];
                hole = (hole-1)/2;
            }
            heap[hole] = e;
        }

        void percolate_down(){
            int hole = 0;
            T e = heap[hole];
            while(2*hole + 1 < heap.size()){
                int child1 = 2*hole + 1, child2 = 2*hole + 2;
                int childmin = child1;
                if(child2 < heap.size() && *heap[child2] <  *heap[child1]){
                    childmin = child2;
                }
                if(*e < *heap[childmin]){
                    break;
                }
                heap[hole] = heap[childmin];
                hole = childmin;
            }
            heap[hole] = e;
        }

    private:
        vector<T> heap;
};

signed main(){
    int n, m;
    cin>>n>>m;
    map<pair<string,bool>, Node*> mp;
    rep(i,0,n){
        string s;
        cin>>s;
        Node *n1 = new Node(s, 0);
        Node *n2 = new Node(s, 1);
        mp[{s,0}] = n1;
        mp[{s,1}] = n2;
    }
    rep(i,0,m){
        string a, b;
        int w;
        cin>>a>>b>>w;
        mp[{a,0}]->al_insert(mp[{b,1}], w);
        mp[{a,1}]->al_insert(mp[{b,0}], w);
        mp[{b,0}]->al_insert(mp[{a,1}], w);
        mp[{b,1}]->al_insert(mp[{a,0}], w);
    }
    custom_min_heap<Node*> pq;
    string source, dest;
    cin>>source>>dest;
    pq.push(mp[{source,0}]);
    mp[{source,0}]->dis = 0;
    while(!pq.empty()){
        Node* curr = pq.top();
        pq.pop();
        if(curr->ID == dest && !curr->even){
            cout<<curr->dis<<'\n';
            return 0;
        }
        if(curr->vis) continue;
        curr->vis = 1;
        for(auto[n, w] : curr->al){
            if(n->dis > curr->dis + w){
                n->dis = curr->dis + w;
                pq.push(n);
            }
        }
    }
    cout<<-1<<'\n';
}