#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i,a,b) for(int i=a; i<b; i++)

const int MOD = 1e9 + 7;

class CurrencySorter{
    public:
        //CurrencySorter() {}
        void operator()(vector<int> &a){
            quick_sort(a, 0, a.size()-1);
        }

    private:

        int partition(vector<int> &a, int l, int r){
            int i = l, j = r;
            while(i < j){
                while(!(i >= j || a[i] >= a[r])) i++;
                while(!(i >= j || a[j] <= a[r])) j++;
                if(i < j) swap(a[i], a[j]);
            }
            swap(a[i], a[r]);
            return i;
        }

        void quick_sort(vector<int> & a, int l, int r){
            if(l>=r) return;
            int rk = partition(a, l, r);
            quick_sort(a, l, rk-1);
            quick_sort(a, rk+1, r);
        }
};

class FibonacciGenerator{
    public:
        int operator()(int n){
            return fibonacci(n).first;
        }

        pair<int, int> fibonacci(int i){
            if(i == 0) return {0,1};
            pair<int, int> p = fibonacci(i/2);
            int fib = 2 * p.second - p.first;
            if(fib < 0) fib += MOD;
            fib = (fib * p.first) % MOD;
            int fib1 = (p.second * p.second + p.first * p.first) % MOD;
            if(i & 1) return {fib1, fib + fib1};
            else return {fib, fib1};
        }
};

class PrimeCalculator{
    public:

        PrimeCalculator(){
            prePrimeCalculator();
        }
        
        void prePrimeCalculator(){                      //calculates all primes till 1e6
            vector<bool> is_prime(1e6, true);
            is_prime[0] = false; is_prime[1] = false;
            for(int i = 2; i * i < 1e6; i++){
                if(is_prime[i]){
                    for(int j = i*i; j < 1e6; j += i) is_prime[j] = false;
                }
            }
            for(int i = 0; i < 1e6; i++){
                if(is_prime[i]) primes_till_1e6.push_back(i);
            }
        }

        void operator()(int l, int r){
            vector<bool> primes_reqd(r-l+1, true);
            if(l == 1) primes_reqd[0] = false;      //base case when l = 1, as 1 is not prime
            for(int p : primes_till_1e6){
                if(p * p > r) break;
                int start = max(p*p, (l+p-1)/p * p);
                for(int j = start; j <= r; j += p) primes_reqd[j - l] = false;
            }
            reqd_primes.clear();
            rep(i, 0, primes_reqd.size()){
                if(primes_reqd[i]) {reqd_primes.push_back(i + l);}
            }
        }

        void printPrimes(){
            rep(i,0,reqd_primes.size()) cout<<reqd_primes[i]<<' ';
            cout<<'\n';
        }

        void printPrimeSum(){
            int sum = 0;
            for(int p : reqd_primes) sum += p;
            cout<<sum<<'\n';
        }

    private:

        vector<int> primes_till_1e6;
        vector<int> reqd_primes;   
};

class NumberAnalyzer{
    public:
        map<int, int> primeFactorization(int x){
            map<int, int> mp;
            rep(i,2,sqrt(x) + 1){
                while(x % i == 0) { mp[i]++; x /= i; } 
            }
            if(x > 2) mp[x]++;
            return mp;
        }
        bool isSquareFree(int x){
            map<int, int> mp = primeFactorization(x);
            for(auto i : mp){
                if(i.second > 1) return 0;
            }
            return 1;
        }

        int countDivisors(int x){
            int cnt = 1;
            map<int, int> mp = primeFactorization(x);
            for(auto i : mp) cnt *= (i.second + 1);
            return cnt;
        }

        int sumOfDivisors(int x){
            int sum = 1;
            map<int, int> mp = primeFactorization(x);
            for(auto i : mp){
                int s= 1;
                rep(j, 1, i.second + 1){
                    s *= i.first;
                    s++;
                }
                sum *= s;
            }
            return sum;
        }
};


signed main(){
    CurrencySorter c;
    FibonacciGenerator f;
    PrimeCalculator p;
    NumberAnalyzer n;
    int type;
    cin>>type;
    if(type == 1){
        int t;
        cin>>t;
        while(t--){
            int n;
            cin>>n;
            vector<int> a(n);
            rep(i,0,n) cin>>a[i];
            c(a);
            rep(i,0,n) cout<<a[i]<<' ';
            cout<<'\n';
        }
    }
    if(type == 2){
        int t;
        cin>>t;
        while(t--){
            int i;
            cin>>i;
            cout<<f(i)<<'\n';
        }
    }   
    if(type == 3){
        int t;
        cin>>t;
        while(t--){
            string s;
            cin>>s;
            int l, r;
            cin>>l>>r;
            p(l,r);
            if(s == "printPrimes"){
                p.printPrimes();
            }
            if(s == "printPrimeSum"){
                p.printPrimeSum();
            }
        }
    }
    if(type == 4){
        int t;
        cin>>t;
        NumberAnalyzer n;
        while(t--){
            string s;
            int x;
            cin>>s>>x;
            if(s == "isSquareFree"){
                if(n.isSquareFree(x)) cout<<"yes\n";
                else cout<<"no\n";
            }
            if(s == "countDivisors"){
                cout<<n.countDivisors(x)<<'\n';
            }
            if(s == "sumOfDivisors"){
                cout<<n.sumOfDivisors(x)<<'\n';
            }
        }
    }
}