#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(int i = a; i < b; i++)

class GraphAlgorithm{
    public:
        virtual void Query(vector<vector<int>> &al, vector<int> &hype, vector<int> ed) = 0;
};

class isCycle : public GraphAlgorithm{
    public:
        void Query(vector<vector<int>> &al, vector<int> &hype, vector<int> ed){
            int n = hype.size();
            vector<int> vis(n, 0);
            rep(i,0,n){
                if(!vis[i]){
                    if(dfs(i, al, vis)) {cout<<"YES\n"; return;}
                }
            }
            cout<<"NO\n";
        }

        bool dfs(int i, vector<vector<int>> &al, vector<int> &vis){
            vis[i] = 1;
            for(int j : al[i]){
                if(vis[j] == 1) return 1;
                else if(!vis[j]){
                    if(dfs(j, al, vis)) return 1;
                }
            }
            vis[i] = 2;
            return 0;
        }
};

class indepComponent : public GraphAlgorithm{
    public:

        void dfs(int i, vector<vector<int>> &al, vector<int> &vis, stack<int> &st){
            vis[i] = 1;
            for(int k : al[i]){
                if(!vis[k]) dfs(k, al, vis, st);
            }
            st.push(i);
        }

        int dfs2(int i, vector<vector<int>> &rev_al, vector<int> &vis){
            vis[i] = 1;
            int cnt = 1;
            for(int k : rev_al[i]){
                if(!vis[k]) cnt += dfs2(k, rev_al, vis);
            }
            return cnt;
        }

        void Query(vector<vector<int>> &al, vector<int> &hype, vector<int> ed){
            int n = hype.size();
            vector<int> vis(n,0);
            stack<int> st;
            rep(i,0,n){
                if(!vis[i]) dfs(i, al, vis, st);
            }
            vector<vector<int>> rev_al(n);
            rep(i,0,n){
                vis[i] = 0;
                for(int k : al[i]){
                    rev_al[k].push_back(i);
                }
            }
            int scc = 0, maxm = 0;
            while(!st.empty()){
                int curr = st.top();
                st.pop();
                if(!vis[curr]){
                    scc++;
                    maxm = max(maxm, dfs2(curr, rev_al, vis));
                }
            }
            cout<<scc<<' '<<maxm<<'\n';
        }
};

class validOrder : public GraphAlgorithm{
    public:

        void Query(vector<vector<int>> &al, vector<int> &hype, vector<int> ed){
            int n = hype.size();
            vector<int> vis(n, 0);
            vector<int> ans;
            priority_queue<int, vector<int>, greater<int>> q;
            rep(i,0,n){
                if(!ed[i]) {
                    q.push(i);
                }
            }
            while(!q.empty()){
                int curr = q.top();
                q.pop();
                if(vis[curr]) continue;
                vis[curr] = 1;
                ans.push_back(curr);
                for(int k : al[curr]){
                    if(--ed[k] == 0) q.push(k);
                }
            }
            if(ans.size() != n) {cout<<"NO\n"; return;}
            rep(i,0,ans.size()) cout<<ans[i]+1<<' ';
            cout<<'\n';
        }
};

class maxHype : public GraphAlgorithm{
    public:
        void dfs(int i, vector<vector<int>> &al, vector<int> &vis, stack<int> &st){
            vis[i] = 1;
            for(int k : al[i]){
                if(!vis[k]) dfs(k, al, vis, st);
            }
            st.push(i);
        }

        void dfs2(int i, vector<vector<int>> &rev_al, vector<int> &vis, vector<int> &tmp){
            tmp.push_back(i);
            vis[i] = 1;
            for(int k : rev_al[i]){
                if(!vis[k]) dfs2(k, rev_al, vis, tmp);
            }
        }

        int dfs_new(int i, vector<vector<int>> &condensedAL, vector<bool> &vis, vector<int> &dp){
            vis[i] = 1;
            int maxm = 0;
            for(int k : condensedAL[i]){
                if(!vis[k]) maxm = max(maxm, dfs_new(k, condensedAL, vis, dp));
                else maxm = max(maxm, dp[k]);
            }
            dp[i] += maxm;
            return dp[i];
        }

        void Query(vector<vector<int>> &al, vector<int> &hype, vector<int> ed){
            int n = hype.size();
            vector<int> vis(n,0);
            stack<int> st;
            rep(i,0,n){
                if(!vis[i]) dfs(i, al, vis, st);
            }
            vector<vector<int>> rev_al(n);
            rep(i,0,n){
                vis[i] = 0;
                for(int k : al[i]){
                    rev_al[k].push_back(i);
                }
            }
            vector<vector<int>> sccs;
            while(!st.empty()){
                int curr = st.top();
                st.pop();
                if(!vis[curr]){
                    vector<int> tmp;
                    dfs2(curr, rev_al, vis, tmp);
                    sccs.push_back(tmp);
                }
            }
            vector<int> scc_no(n);
            vector<int> sccHype(sccs.size());
            rep(i,0,sccs.size()){
                for(int k : sccs[i]) {scc_no[k] = i; sccHype[i] += hype[k];}
            }

            vector<vector<int>> condensedAL(sccs.size());
            rep(i,0,n){
                for(int k : al[i]){
                    if(scc_no[k] != scc_no[i]) condensedAL[scc_no[i]].push_back(scc_no[k]);
                }
            }

            vector<int> ed_new(sccs.size(), 0);
            rep(i,0,sccs.size()){
                for(int k : condensedAL[i]) ed_new[k]++;
            }

            vector<int> dp(sccs.size(), 0);
            rep(i,0,sccs.size()) dp[i] = sccHype[i];

            vector<bool> vis_new(sccs.size(), 0);

            int maxm = 0;
            
            rep(i,0,sccs.size()){
                if(!vis_new[i]) maxm = max(maxm, dfs_new(i, condensedAL, vis_new, dp));
            }

            cout<<maxm<<'\n';
        }
};

signed main(){
    int n, m, q;
    cin>>n>>m;
    vector<int> hype(n);
    rep(i,0,n) cin>>hype[i];
    vector<int> ed(n, 0);
    vector<vector<int>> al(n);
    rep(i,0,m){
        int a, b;
        cin>>a>>b;
        a--; b--;
        al[a].push_back(b);
        ed[b]++;
    }
    cin>>q;
    while(q--){
        int type;
        cin>>type;
        if(type == 1){
            isCycle c;
            c.Query(al, hype, ed);
        }
        if(type == 2){
            indepComponent ic;
            ic.Query(al, hype, ed);
        }
        if(type == 3){
            validOrder v;
            v.Query(al, hype, ed);
        }
        if(type == 4){
            maxHype m;
            m.Query(al, hype, ed);
        }
    }
}
