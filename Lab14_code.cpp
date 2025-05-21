#include <bits/stdc++.h>

using namespace std;

#define int long long
#define float long double
#define rep(i,a,b) for(int i = a; i < b; i++)
#define rev(i,a,b) for(int i = a; i >= b; i--)

const float EPS = 1e-9;

float dist(pair<int,int> p1, pair<int,int> p2){
    int x1 = p1.first, y1 = p1.second, x2 = p2.first, y2 = p2.second;
    int x_diff = x1 - x2, y_diff = y1 - y2;
    float ans = x_diff * x_diff + y_diff * y_diff;
    ans = sqrtl(ans);
    return ans;
}

float dis_centroid(int x1, int y1, int x2, int y2, int x3, int y3){
    pair<int, int> centroid = {(x1 + x2 + x3)/3, (y1 + y2 + y3)/3};
    float d = dist(centroid, {x1, y1});
    d = max(d, dist(centroid, {x2, y2}));
    d = max(d, dist(centroid, {x3, y3}));
    return d;
}

class Island{
    public:
        Island(int x1, int y1, float reach, string ID) : centre({x1,y1}), reach(reach), ID(ID) {}
        pair<int,int> getC(){
            return centre;
        }
        float getR(){
            return reach;
        }
    private:
        pair<int,int> centre;
        float reach;
        string ID;

    // friend istream& operator >> (istream &stream, Island* is){

    // }

    // virtual void takeInput(istream &stream) = 0;

    friend ostream & operator << (ostream &stream, Island* is){
        stream << is->ID;
        return stream;
    }
};

class Rectangle : public Island{
    public:
        Rectangle(string ID, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : Island((x1 + x2 + x3 + x4)/4, (y1 + y2 + y3 + y4)/4, dist({x1, y1}, {x3, y3})/2.0, ID) {}
};

class Triangle : public Island{
    public:
        Triangle(string ID, int x1, int y1, int x2, int y2, int x3, int y3) : Island((x1 + x2 + x3)/3, (y1 + y2 + y3)/3, dis_centroid(x1, y1, x2, y2, x3, y3), ID) {}
};

class Circle : public Island{
    public:
        Circle(string ID, int x, int y, int radius) : Island(x, y, radius, ID) {} 
};

// Rectangle readRectangle(istream &stream){

// }

// Triangle readTriangle(istream &stream){

// }

// Circle readCircle(istream &stream){

// }

class Archipelago{
    public:
        Archipelago(int size){
            islands.clear();
            al.resize(size);
        }
        void insertIsland(Island* is){
            rep(i,0,islands.size()){
                if(dist(islands[i]->getC(), is->getC()) <= islands[i]->getR() + is->getR() + EPS){
                    al[i].push_back(islands.size());
                    al[islands.size()].push_back(i);
                }
            }
            islands.push_back(is);
        }

        void printLongestPath(){
            int n = islands.size();
            vector<vector<int>> dp(n, vector<int>((1<<n), -1e9));
            vector<vector<int>> par(n, vector<int>((1<<n), -1));
            rep(i,0,n) {
                dp[i][1<<i] = 1;
            }
            rep(mask, 0, (1<<n)){
                rep(i, 0, n){
                    if(dp[i][mask] < 1) continue;
                    for(int k : al[i]){
                        if(!(mask & (1 << k))){
                            int next_mask = mask | (1 << k);
                            if(dp[k][next_mask] < dp[i][mask] + 1){
                                dp[k][next_mask] = dp[i][mask] + 1;
                                par[k][next_mask] = i;
                            }
                        }
                    }
                }
            }
            int len = -1, best = 0, best_mask = 0;
            rep(i,0,n){
                rep(mask,0,(1<<n)){
                    if(dp[i][mask] > len){
                        len = dp[i][mask];
                        best = i;
                        best_mask = mask;
                    }
                }
            }
            int mask = best_mask, i = best;
            vector<int> sol;
            while(mask){
                sol.push_back(i);
                int prev = par[i][mask];
                mask ^= (1 << i);
                i = prev;
            }
            if(len == n) cout<<"YES\n";
            else cout<<"NO\n"<<len<<'\n';
            rep(i, 0, sol.size()) cout<<islands[sol[i]]<<' ';
            cout<<'\n';
        }

    private:
        vector<Island*> islands;
        vector<vector<int>> al;
};

signed main(){
    int n;
    cin>>n;
    Archipelago* a = new Archipelago(n);
    rep(i,0,n){
        string type, ID;
        cin>>type>>ID;
        if(type == "RECTANGLE"){
            int x1, y1, x2, y2, x3, y3, x4, y4;
            cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
            Rectangle* r = new Rectangle(ID, x1, y1, x2, y2, x3, y3, x4, y4);
            a->insertIsland(r);
        }
        if(type == "TRIANGLE"){
            int x1, y1, x2, y2, x3, y3;
            cin>>x1>>y1>>x2>>y2>>x3>>y3;
            Triangle* t = new Triangle(ID, x1, y1, x2, y2, x3, y3);
            a->insertIsland(t);
        }
        if(type == "CIRCLE"){
            int x1, y1, radius;
            cin>>x1>>y1>>radius;
            Circle *c = new Circle(ID, x1, y1, radius);
            a->insertIsland(c);
        }
    }
    a->printLongestPath();
}