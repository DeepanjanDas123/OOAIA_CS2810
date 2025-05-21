#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a; i<b; i++)

const long long int P = 1e9 + 7;

class Complex{
    protected:
        double r, c;
    public:
        Complex(double real, double complex) : r(real), c(complex) {}

        Complex add(Complex &cn){
            r += cn.r;
            c += cn.c;
            return *this;
        }

        Complex subtract(Complex &cn){
            r -= cn.r;
            c -= cn.c;
            return *this;
        }

        Complex multiply(Complex &cn){
            double temp_r = r * cn.r - c * cn.c;
            double temp_c = r * cn.c + c * cn.r;
            r = temp_r;
            c = temp_c;
            return *this;
        }

        virtual void print(){
            cout<<setiosflags(ios::fixed)<<setprecision(3)<<r<<' '<<c<<'\n';
        }
};

class Rational : public Complex{
    protected:
        int p, q;
    public:
        Rational(int p, int q) : Complex((double)p/(double)q, 0), p(p), q(q) {}

        int findgcd(int p, int q){
            if(p == 0) return q;
            return findgcd(q%p, p);
        }

        void Reduce(){
            int gd = findgcd(abs(p), abs(q));
            p /= gd;
            q /= gd;
            if(q < 0) { p *= -1; q = abs(q); }
        }
        void print(bool b){
            if(!b) cout<<setiosflags(ios::fixed)<<setprecision(3)<<r<<'\n';
            else cout<<p<<' '<<q<<'\n';
        }

};

class Natural : public Rational{
    public:
        Natural(int x) : Rational(x, 1) {}

        bool isPrime(){
            rep(i,2,sqrt(p) + 1){           //iterates from 1 to sqrt(p)+1 to find a possible factor
                if(p % i == 0) return 0;
            }
            return 1;
        }

        int Inverse(){          
            // unsigned long long nw = 1, old = 0, q = P, r, h;
            // int pos = 0;
            // while (p > 0) {
            //     r = q%p;
            //     q = q/p;
            //     h = q*nw + old;
            //     old = nw;
            //     nw = h;
            //     q = p;
            //     p = r;
            //     pos = !pos;
            // }
            // return pos ? old : (P - old);
            unsigned long long exp = P-2, a = (unsigned long long)p, b = 1;
            while(exp > 0){
                if(exp & 1){
                    b = (a*b) % P;
                }
                a = (a*a)%P;
                exp /= 2;
            }
            return b;
        }
};

int main(){
    int n; cin>>n;
    string s;
    while(n--){
        cin>>s;
        if(s == "complex"){
            string t;
            cin>>t;
            if(t == "add"){
                double r1, r2, c1, c2;
                cin>>r1>>c1>>r2>>c2;
                Complex cm1(r1, c1);
                Complex cm2(r2, c2);
                cm1.add(cm2);
                cm1.print();
            }
            if(t == "sub"){
                double r1, r2, c1, c2;
                cin>>r1>>c1>>r2>>c2;
                Complex cm1(r1, c1);
                Complex cm2(r2, c2);
                cm1.subtract(cm2);
                cm1.print();
            }
            if(t == "mult"){
                double r1, r2, c1, c2;
                cin>>r1>>c1>>r2>>c2;
                Complex cm1(r1, c1);
                Complex cm2(r2, c2);
                cm1.multiply(cm2);
                cm1.print();
            }
        }
        if(s == "rational"){
            string t;
            cin>>t;
            if(t == "add"){
                int p1, q1, p2, q2;
                cin>>p1>>q1>>p2>>q2;
                Rational r1(p1, q1);
                Rational r2(p2, q2);
                r1.add(r2);
                r1.print(0);
            }
            if(t == "sub"){
                int p1, q1, p2, q2;
                cin>>p1>>q1>>p2>>q2;
                Rational r1(p1, q1);
                Rational r2(p2, q2);
                r1.subtract(r2);
                r1.print(0);
            }
            if(t == "mult"){
                int p1, q1, p2, q2;
                cin>>p1>>q1>>p2>>q2;
                Rational r1(p1, q1);
                Rational r2(p2, q2);
                r1.multiply(r2);
                r1.print(0);
            }
            if(t == "reduce"){
                int p1, q1;
                cin>>p1>>q1;
                Rational r(p1, q1);
                r.Reduce();
                r.print(1);
            }
        }
        if(s == "natural"){
            string t;
            cin>>t;
            if(t == "isprime"){
                int x;
                cin>>x;
                Natural n1(x);
                cout<<n1.isPrime()<<'\n';
            }
            if(t == "inverse"){
                int x;
                cin>>x;
                Natural n1(x);
                cout<<n1.Inverse()<<'\n';
            }
        }
    }
}