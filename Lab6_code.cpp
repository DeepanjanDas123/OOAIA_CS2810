#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(int i=a; i<b; i++)

typedef pair<int,int> pnt;

class Comparator{
    public:
        Comparator(bool b = 0) : b(b){}

        void change_bool(bool bl){
            b = bl;
        }

        bool operator()(int n1, int n2){
            if(!b) return (n1 <= n2);
            else return (n1 >= n2);
        }
    private:
        bool b;
};

class QuantumMatrix{
public:
    QuantumMatrix() : size(0){}     //default constructor
    void resize(int n){             //resizing the matrix
        size = n;
        matrix.resize(n, vector<int> (n));
        rep(i,0,n){
            rep(j,0,n) cin>>matrix[i][j];
        }
    }

    void display(){                 //display matrix
        rep(i,0,size){
            rep(j,0,size) cout<<matrix[i][j]<<' ';
            cout<<'\n';
        }
    }

    void custom_sort(int p, int left, int right, Comparator &c){        //custom sort 
        //base case
        if(left == right) return;

        //sort the two subarrays recursively
        int mid = (left + right)/2;
        custom_sort(p, left, mid, c);
        custom_sort(p, mid+1, right, c);

        //merge the two sorted subarrays
        vector<int> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;
        while(i <= mid && j <= right){
            if(c(matrix[p][i], matrix[p][j])){
                temp[k] = matrix[p][i];
                i++;
            }
            else{
                temp[k] = matrix[p][j];
                j++;
            }
            k++;
        }
        if(i <= mid){
            while(i <= mid) {temp[k] = matrix[p][i]; i++; k++;}
        }
        if(j <= right){
            while(j <= right) {temp[k] = matrix[p][j]; j++; k++;}
        }
        rep(it, 0, temp.size()){
            matrix[p][it + left] = temp[it];
        }
        return;
    }

    void sortRows(Comparator &c){       //sort rows to sort each row in the said order, using a custom Comparator functor
        rep(i,0,size){
            custom_sort(i, 0, size-1, c);
        }
    }

    void flattenmatrix(){               //generates the flatten vector
        flatten.resize(size * size);
        rep(i,0,size){
            rep(j,0,size) flatten[size*i + j] = matrix[i][j];
        }
    }

    int count(int l, int r){            //counting the number of inversions
        if(l >= r) return 0;
        int c = 0, mid = (l+r)/2;
        c += count(l, mid) + count(mid+1, r);
        int i = l, j = mid + 1, k = 0;
        vector<int> temp(r-l+1);
        while(i <= mid && j <= r){
            if(flatten[i] <= flatten[j]){
                temp[k] = flatten[i];
                i++;
            }
            else{
                temp[k] = flatten[j];
                c += mid - i + 1;
                j++;
            }
            k++;
        }
        if(i <= mid){
            while(i <= mid){
                temp[k] = flatten[i];
                i++;
                k++;
            }
        }
        if(j <= r){
            while(j <= r){
                temp[k] = flatten[j];
                j++;
                k++;
            }
        }
        rep(i, 0, temp.size()){
            flatten[i + l] = temp[i];
        }
        return c;
    }

    int countInversions(){              
        flattenmatrix();
        return count(0, size*size - 1);
    }

private:
    int size;
    vector<vector<int>> matrix;
    vector<int> flatten;
};

class custom{
    public:
        bool operator()(pair<int, int> p1, pair<int,int> p2){
            return p1.second <= p2.second;
        }
};

struct Minpnt{
    pnt p1, p2;
    int dis;
};

int dist(pnt p1, pnt p2){
    int ans = (p1.first-p2.first)*(p1.first-p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
    return ans;
}

pair<pnt, pnt> findMinpntPair (pair<pnt, pnt> p1, pair<pnt, pnt> p2){
    return (p1 <= p2) ? p1 : p2;
}

Minpnt bruteforce(vector<pnt> &pntx){
    if(pntx.size() == 2){
        return {pntx[0], pntx[1], dist(pntx[0], pntx[1])};
    }
    else{
        int min = LONG_LONG_MAX;
        pnt p1, p2;
        rep(i,0,2){
            rep(j,i+1,3){
                if(dist(pntx[i], pntx[j]) < min){
                    p1 = pntx[i]; p2 = pntx[j];
                    min = dist(pntx[i], pntx[j]);
                }

                //tie break for equal distances
                if(dist(pntx[i], pntx[j]) == min){
                    pair<pnt, pnt> p = findMinpntPair({p1, p2}, {pntx[i], pntx[j]});
                    p1 = p.first;
                    p2 = p.second;
                }
            }
        }
        return {p1, p2, min};
    }
}

Minpnt find_closest(vector<pnt> &pntx, vector<pnt> &pnty){
    if(pntx.size() <= 3) return bruteforce(pntx);
    
    int mid = pntx.size()/2 - 1;
    vector<pnt> pxleft;
    vector<pnt> pxright;
    vector<pnt> pyleft;
    vector<pnt> pyright;
    
    rep(i,0,pntx.size()){
        if(pxleft.size() < pntx.size()/2) pxleft.push_back(pntx[i]);
        else pxright.push_back(pntx[i]);

        if(pnty[i].first <= pntx[mid].first && pyleft.size() < pntx.size()/2) pyleft.push_back(pnty[i]);
        else pyright.push_back(pnty[i]);
    }
    Minpnt left = find_closest(pxleft, pyleft);
    Minpnt right = find_closest(pxright, pyright);
    if(left.p1 == left.p2) left.dis = LONG_LONG_MAX;
    if(right.p1 == right.p2) right.dis = LONG_LONG_MAX;
    int min_d = min(left.dis, right.dis);
    pair<pnt, pnt> minpair;
    if(left.dis == right.dis) minpair = findMinpntPair({left.p1, left.p2}, {right.p1, right.p2});
    else if(min_d < left.dis) minpair = {right.p1, right.p2};
    else minpair = {left.p1, left.p2};

    vector<pnt> strip;

    rep(i,0,pntx.size()){
        int d = pnty[i].first - pntx[mid].first;
        d *= d;
        if(d <= min_d){
            strip.push_back(pnty[i]);
        }
    }
    rep(i,0,strip.size()){
        rep(j,i+1, min(i+7, (int)strip.size())){
            int dis = dist(strip[i], strip[j]);
            if(dis < min_d){
                minpair = {strip[i], strip[j]};
                //if(strip[i].first > strip[j].first) swap(minpair.first, minpair.second);
                min_d = dis;
            }
            else if(dis == min_d){
                pair<pnt, pnt> potential = {strip[i], strip[j]};
                //if(strip[i].first > strip[j].first) swap(potential.first, potential.second);
                minpair = findMinpntPair(minpair, potential);
            }
        }
    }
    return {minpair.first, minpair.second, min_d};
}

void closest_pair(vector<pnt> &points){
    vector<pnt> pntx(points.size());
    vector<pnt> pnty(points.size());
    map<pnt, int> mp;
    rep(i,0,points.size()){
        pntx[i] = pnty[i] = points[i];
        assert(mp[points[i]] == 0);
        mp[points[i]] = i+1;
    }
    sort(pntx.begin(), pntx.end());
    sort(pnty.begin(), pnty.end(), custom());
    Minpnt ans = find_closest(pntx, pnty);
    //print in order
    if(mp[ans.p1] > mp[ans.p2]) swap(ans.p1, ans.p2);
    cout<<ans.p1.first<<' '<<ans.p1.second<<' '<<ans.p2.first<<' '<<ans.p2.second<<'\n';
}

signed main(){
    QuantumMatrix m;
    while(true){
        string s;
        cin>>s;
        if(s == "END") break;
        else if(s == "CREATE_2D"){
            int n;
            cin>>n;
            m.resize(n);
        }
        else if(s == "DISPLAY_2D"){
            m.display();
        }
        else if(s == "INVERSION_2D"){
            cout<<m.countInversions()<<'\n';
        }
        else if(s == "SORT_2D"){
            Comparator c;
            string s;
            cin>>s;
            if(s == "descending") c.change_bool(1);
            m.sortRows(c);
        }
        else if(s == "CLOSEST_2D"){
            int num;
            cin>>num;
            vector<pnt> points;
            rep(i,0,num){
                int a, b;
                cin>>a>>b;
                points.push_back({a, b});
            }
            closest_pair(points);
        }
    }
}