#include <bits/stdc++.h>
using namespace std;

#define int long long
#define float long double
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rev(i,a,b) for(int i = a; i>=b; i--)

string operator *(string &s1, int x){
    string ans;
    while(x--) ans += s1;
    return ans;
}

template <typename T>
class Complex {
  public:
    T real, img;

    Complex() : real(0), img(0) {}
    Complex(T val) : real(val), img(0) {}
    Complex(T val1, T val2) : real(val1), img(val2) {}

    Complex<T> operator+(const Complex<T> &c1) const {
        return Complex<T>(real + c1.real, img + c1.img);
    }

    Complex<T> operator-(const Complex<T> &c1) const {
        return Complex<T>(real - c1.real, img - c1.img);
    }

    Complex<T> operator*(const Complex<T> &c1) const {
        return Complex<T>(real * c1.real - img * c1.img, real * c1.img + img * c1.real);
    }

    void print() const {
        cout << real << " " << img << " ";
    }

    bool isZero() const {
        return (real == 0 && img == 0);
    }
};

template <typename T>
class PolyMult {
  public:
    vector<T> mult(const vector<T> &a, const vector<T> &b) {
        int n = 1;
        while (n < a.size() + b.size() - 1) n <<= 1;

        vector<T> A(n), B(n);
        rep(i, 0, a.size()) A[i] = a[i];
        rep(i, 0, b.size()) B[i] = b[i];

        vector<T> res = karatsuba(A, B);
        res.resize(a.size() + b.size() - 1);
        return res;
    }

  private:
    vector<T> karatsuba(const vector<T> &a, const vector<T> &b) {
        int n = a.size();
        vector<T> res(n * 2 - 1);

        if (n == 1) {
            res[0] = a[0] * b[0];
            return res;
        }

        int k = n / 2;
        vector<T> a0(a.begin(), a.begin() + k);
        vector<T> a1(a.begin() + k, a.end());
        vector<T> b0(b.begin(), b.begin() + k);
        vector<T> b1(b.begin() + k, b.end());

        vector<T> y0 = karatsuba(a0, b0);
        vector<T> y1 = karatsuba(a1, b1);

        vector<T> a0a1(k), b0b1(k);
        rep(i, 0, k) {
            a0a1[i] = a0[i] + a1[i];
            b0b1[i] = b0[i] + b1[i];
        }

        vector<T> y2 = karatsuba(a0a1, b0b1);

        rep(i, 0, y0.size()) res[i] = res[i] + y0[i];
        rep(i, 0, y1.size()) res[i + n] = res[i + n] + y1[i];
        rep(i, 0, y2.size()) res[i + k] = res[i + k] + y2[i] - y0[i] - y1[i];

        return res;
    }
};

template<class T>

class PolyEval{
public:
    T eval(vector<T> &a, int x){
        //returns the value of the polynomial a at x
        T ans = a[a.size()-1] * pow(x, a.size()-1);
        rev(i,a.size()-2,0) ans += a[i] * pow(x,i);
        return ans;
    }
};

template<class T>

class PolyDiff{
public:
    vector<T> diff(vector<T> &a){
        //returns the coeff vector of the polynomial obtained by differentiating a
        vector<T> ans(a.size()-1);
        rep(i,1,a.size()) ans[i-1] = a[i] * i;
        return ans;
    }
};

template<class T>

class Polynomial{
    public:
        Polynomial(vector<T> &a) : coeff(a) {}
        //overloading the * operator for multiplication of two polynomials
        vector<T> operator*(Polynomial &p2){
            PolyMult<T> p;
            return p.mult(coeff, p2.coeff);
        }
    private:
        vector<T> coeff;
};

signed main(){
    int q;
    cin>>q;
    while(q--){
        int op;
        cin>>op;
        if(op == 1){
            string type;
            cin>>type;

            if(type == "integer"){
                int deg1; cin>>deg1;
                vector<int> a(deg1);
                rep(i,0,deg1) cin>>a[i];
                int deg2; cin>>deg2;
                vector<int> b(deg2);
                rep(i,0,deg2) cin>>b[i];
                Polynomial<int> p1(a), p2(b);
                vector<int> ans = p1 * p2;
                rep(i,0,ans.size()) cout<<ans[i]<<' ';
                cout<<'\n';
            }

            if(type == "float"){
                int deg1; cin>>deg1;
                vector<float> a(deg1);
                rep(i,0,deg1) cin>>a[i];
                int deg2; cin>>deg2;
                vector<float> b(deg2);
                rep(i,0,deg2) cin>>b[i];
                Polynomial<float> p1(a), p2(b);
                vector<float> ans = p1 * p2;
                rep(i,0,ans.size()) cout<<fixed<<setprecision(6)<<ans[i]<<' ';
                cout<<'\n';
            }

            if(type == "complex") {
                int deg1;
                cin>>deg1;
                vector<Complex<int>> a;
                rep(i,0,deg1){
                    int a1, a2;
                    cin>>a1>>a2;
                    Complex<int> c(a1, a2);
                    a.push_back(c);
                }
                int deg2;
                cin>>deg2;
                vector<Complex<int>> b;
                rep(i,0,deg2){
                    int a1, a2;
                    cin>>a1>>a2;
                    Complex<int> c(a1, a2);
                    b.push_back(c);
                }
                Polynomial<Complex<int>> p1(a), p2(b);
                vector<Complex<int>> ans = p1 * p2;
                rep(i,0,ans.size()) ans[i].print();
                cout<<'\n';
            }
        }

        if(op == 2){        //evaluating the value of the polynomial for a given integer
            string type;
            cin>>type;
            
            if(type == "integer"){
                int deg;
                cin>>deg;
                vector<int> a(deg);
                rep(i,0,deg) cin>>a[i];
                int x; cin>>x;
                PolyEval<int> p1;
                cout<<p1.eval(a, x)<<'\n';
            }

            if(type == "float"){
                int deg;
                cin>>deg;
                vector<float> a(deg);
                rep(i,0,deg) cin>>a[i];
                int x; cin>>x;
                PolyEval<float> p1;
                cout<<fixed<<setprecision(6)<<p1.eval(a, x)<<'\n';
            }

            if(type == "string"){  
                int deg;
                cin>>deg;
                vector<string> a(deg);
                rep(i,0,deg) cin>>a[i];
                int x; cin>>x;
                PolyEval<string> p1;
                cout<<p1.eval(a,x)<<'\n';
            }
        }

        if(op == 3){
            string type;
            cin>>type;

            if(type == "integer"){
                int deg;
                cin>>deg;
                vector<int> a(deg);
                rep(i,0,deg) cin>>a[i];
                PolyDiff<int> p1;
                vector<int> ans = p1.diff(a);
                rep(i,0,ans.size()) cout<<ans[i]<<' ';
                cout<<'\n';
            }

            if(type == "float"){
                int deg;
                cin>>deg;
                vector<float> a(deg);
                rep(i,0,deg) cin>>a[i];
                PolyDiff<float> p1;
                vector<float> ans = p1.diff(a);
                rep(i,0,ans.size()) cout<<fixed<<setprecision(6)<<ans[i]<<' ';
                cout<<'\n';
            }
        }
    }
}