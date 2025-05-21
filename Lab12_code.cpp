#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(int i = a; i < b; i++)
#define rev(i,a,b) for(int i = a; i>= b; i--)

class Sentinel{
    public:
        Sentinel(int id, string name, int rank) : id(id), name(name), rank(rank) {}
        virtual int countHigherRanked() = 0;
        int id;
        string name;
        int rank;
};

class Senapati : public Sentinel{
    public:
        Senapati(int id, string name) : Sentinel(id, name, 0) {}
        int countHigherRanked(){
            return 0;
        }
};

class Dandanayaka : public Sentinel{
    public:
        Dandanayaka(int id, string name) : Sentinel(id, name, 1) {}
        int countHigherRanked(){
            return 1;
        }
};

class Chaturangini : public Sentinel{
    public:
        Chaturangini(int id, string name) : Sentinel(id, name, 2) {}
        int countHigherRanked(){
            return 2;
        }
};

class custom_comp{
    public:
        bool operator() (Sentinel* s1, Sentinel *s2){
            if(s1->rank < s2-> rank) return 1;
            else if(s1->rank == s2->rank && s1->id < s2->id) return 1;
            else return 0;
        }
};

template <class T>

class Kingdom{
    public:
        Kingdom(int size = 0){
            al.resize(size);
            dp.resize(size);
            rep(i,0,dp.size()) {
                dp[i].resize(2);
                dp[i][0] = -1;
                dp[i][1] = -1;
            }
        }
        void add_edge(int a, int b){
            edge++;
            al[a].push_back(b);
            al[b].push_back(a);
        }
        void add_sentinel(T s){
            sentinel_map[s->id] = s;
            sentinels.push_back(s);
            cnt[s->rank] ++;
        }
        void return_sorted(){
            sort(sentinels.begin(), sentinels.end(), custom_comp());
            rep(i,0,sentinels.size()) cout<<sentinels[i]->id<<' ';
            cout<<'\n';
        }
        pair<int,int> rec(int i, int par){
            if(al[i].size() == 1 && par != -1) return {0,1};
            if(dp[i][0] != -1) return {dp[i][0], dp[i][1]};     //memoization
            int aa = 0, bb = 0;
            for(int k : al[i]){
                if(k == par) continue;
                auto [a, b] = rec(k, i);
                aa += b;
                bb += min(a, b);
            }
            bb ++;
            dp[i][0] = aa;
            dp[i][1] = bb;
            return {aa, bb};
        }
        pair<int,int> countMinVertexCover(){
            //if(al.size() == 1) return {1, 1};
            //vector<bool> vis(al.size(), 0);
            return rec(0, -1);
        }
        int countHigherRanked(int targetID){
            int targetRank = sentinel_map[targetID]->rank;
            int count = 0;
            rep(i,0,targetRank) count += cnt[i];
            return count;
        }
    private:
        vector<vector<int>> al;
        vector<vector<int>> dp;
        map<int, T> sentinel_map;
        vector<T> sentinels;
        vector<int> cnt = {0,0,0};
        int edge = 0;
};

signed main(){
    int n;
    cin>>n;
    Kingdom<Sentinel*> ashoka(n); 
    rep(i,0,n-1){
        int a, b;
        cin>>a>>b;
        ashoka.add_edge(a, b);
    }
    rep(i,0,n){
        string s, t;
        cin>>s>>t;
        if(t == "SENAPATI"){
            Senapati *se = new Senapati(i, s);
            ashoka.add_sentinel(se);
        }
        if(t == "DANDANAYAKA"){
            Dandanayaka *d = new Dandanayaka(i, s);
            ashoka.add_sentinel(d);
        }
        if(t == "CHATURANGINI"){
            Chaturangini *c = new Chaturangini(i, s);
            ashoka.add_sentinel(c);
        }
    }
    int q;
    cin>>q;
    while(q --){
        int type;
        cin>>type;
        if(type == 1){
            pair<int,int> p = ashoka.countMinVertexCover();
            cout<<min(p.first, p.second)<<'\n';
        }
        else if(type == 2){
            ashoka.return_sorted();
        }
        else if(type == 3){
            int targetID;
            cin>>targetID;
            cout<<ashoka.countHigherRanked(targetID)<<'\n';
        }
    }
}