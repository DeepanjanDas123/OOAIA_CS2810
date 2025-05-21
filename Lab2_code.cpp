//using adjacency matrix

#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)

class Graph
{
private:
    int n;
    vector<vector<int>> adj_m;

public:

    Graph() {}

    void addEdge(int a, int b)
    {
        if(a < n && b < n) adj_m[a][b] = adj_m[b][a] = 1;
    }

    void operator+(Graph &g)
    {
        int nk = max(n, g.n);
        vector<vector<int>> tmp_adj_m(n, vector<int>(n,0));
        rep(i,0,n){
            rep(j,0,n) tmp_adj_m[i][j] = adj_m[i][j];
        }
        adj_m.resize(nk, vector<int>(nk,0));
        rep(i,0,nk){
            rep(j,0,nk){
                if(i < n && j < n && i < g.n && j < g.n) adj_m[i][j] = tmp_adj_m[i][j] || g.adj_m[i][j];
                else if(i < n && j < n) adj_m[i][j] = tmp_adj_m[i][j];
                else adj_m[i][j] = g.adj_m[i][j];
            }
        }
        n = nk;
    }

    void operator-(Graph &g)
    {
        int nk = max(n, g.n);
        vector<vector<int>> tmp_adj_m(n, vector<int>(n,0));
        rep(i,0,n){
            rep(j,0,n) tmp_adj_m[i][j] = adj_m[i][j];
        }
        adj_m.resize(nk, vector<int>(nk,0));
        rep(i,0,nk){
            rep(j,0,nk){
                if(i < n && j < n && i < g.n && j < g.n) adj_m[i][j] = tmp_adj_m[i][j] && g.adj_m[i][j];
                else adj_m[i][j] = 0;
            }
        }
        n = nk;
    }

    void operator!()
    {
        rep(i, 0, n)
        {
            rep(j, 0, n) {
                if(i == j) continue;
                adj_m[i][j] = 1 - adj_m[i][j];
            }
        }
    }

    string printGraph()
    {
        string s;
        rep(i, 0, n)
        {
            s += "Vertex ";
            s += to_string(i);
            s += ":";
            rep(j, 0, n)
            {
                if (adj_m[i][j]){
                    s += " ";
                    s += to_string(j);
                }
            }
            s += "\n";
        }
        return s;
    }

    void removeEdge(int a, int b)
    {
        if(a < n && b < n) adj_m[a][b] = adj_m[b][a] = 0;
    }

    bool dfs(int a, int b, vector<int> &vis){
        vis[a] = 1;
        if(adj_m[a][b]) return true;
        rep(i,0,n){
            if(!vis[i] && adj_m[i][a] && dfs(i, b, vis)) return true;
        }
        return false;
    }

    bool isReachable(int i, int j)
    {
        vector<int> vis(n, 0);
        return dfs(i, j, vis);
    }

    friend void operator>>(istream &stream, Graph &g);
    friend ostream& operator <<(ostream &stream, Graph &g);
};

void operator>>(istream &stream, Graph &g)
{
    int n, m;
    stream >> n >> m;
    g.n = n;
    g.adj_m.resize(n, vector<int>(n,0));
    rep(i,0,m){
        int a, b;
        stream>>a>>b;
        g.addEdge(a,b);
    }
}

ostream& operator <<(ostream &stream, Graph &g)
{
    string str = g.printGraph();
    return stream << str;
}

int main()
{
    Graph g;

    while (true)
    {
        string s;
        cin >> s;

        if (s == "Graph")
        {
            cin >> g;
        }
        else if (s == "printGraph")
            cout << g;

        else if (s == "isReachable")
        {
            int a, b;
            cin >> a >> b;
            if (g.isReachable(a, b))
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        else if (s == "remove_edge")
        {
            int a, b;
            cin >> a >> b;
            g.removeEdge(a, b);
        }
        else if (s == "add_edge")
        {
            int a, b;
            cin >> a >> b;
            g.addEdge(a, b);
        }
        else if (s == "complement")
            !g;
        else if (s == "union")
        {
            string t;
            cin >> t;
            Graph g1;
            cin >> g1;
            g + g1;
        }
        else if (s == "intersection")
        {
            string t;
            cin >> t;
            Graph g1;
            cin >> g1;
            g - g1;
        }
        else
            break;
    }
}