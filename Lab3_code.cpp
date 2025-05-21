#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a; i<b; i++)

class QNS{
private:
    int p, d, e, h;

public:
    QNS(int pk = 1000, int dk = 500, int ek = 300, int hk = 0) : p(min(pk, 5000)), d(dk), e(ek), h(hk) {}

    QNS(const QNS &q) : p(min(q.p, 5000)), d(q.d), e(q.e), h(q.h) {}

    void operator +(QNS &q){
        p = min(p + q.e, 5000);
        d += q.d;
        e += q.p;
    }

    void operator -(int x){
        d -= x;
        e += x;
        h += x;
    }

    void operator *(int x){
        p = min(p + p*x/100, 5000);
        e += 5*x;
        h += x;
    }

    void operator /(int x){
        d += x;
        h -= x;
        if(h < 0) h = 0;
    }

    void boostPower(int factor){
        this->operator*(factor);
    }

    void boostPower(QNS &q){
        this->operator+(q);
    }

    bool operator ==(QNS &q){
        return (p == q.p && d == q.d);
    }

    bool operator <(QNS &q){
        return (p + d < q.p + q.d);
    }

    int getp(){ return p;}
    int getd(){ return d;}
    int gete(){ return e;}
    int geth(){ return h;}
};

class Avenger
{
private:
    string name;
    QNS suit;
    int attackStrength;

public:
    Avenger(string avname, QNS avsuit, int strength) : name(avname), suit(avsuit), attackStrength(strength) {}

    Avenger() {}

    void attack(Avenger &enemy)
    {
        enemy.suit - attackStrength;
    }

    void upgradeSuit(QNS &othersuit)
    {
        suit + othersuit;
    }

    void repair(int x)
    {
        suit / x;
    }

    void printStatus()
    {
        cout << name << ' ' << suit.getp() << ' ' << suit.getd() << ' ' << suit.gete() << ' ' << suit.geth() << '\n';
    }

    QNS& getsuit() { return suit; }
};

class Battle
{
private:
    vector<Avenger> heroes;
    vector<Avenger> enemies;
    vector<string> battleLog;
    map<string, Avenger*> mp;
    queue<QNS> suits;

public:
    void printBattleLog()
    {
        for (string s : battleLog)
            cout << s << '\n';
    }

    int Result()
    {
        int hsum = 0, esum = 0;
        for (Avenger h : heroes)
        {
            if (h.getsuit().getd() > 0)
                hsum += h.getsuit().getp() + h.getsuit().getd();
        }
        for (Avenger e : enemies)
        {
            if (e.getsuit().getd() > 0)
                esum += e.getsuit().getp() + e.getsuit().getd();
        }
        if (hsum > esum)
            return 1;
        else if (hsum < esum)
            return -1;
        else
            return 0;
    }

    void startBattle()
    {
        int k, n, m;
        cin >> k >> n >> m;
        heroes.resize(n);
        enemies.resize(m);
        rep(i, 0, k)
        {
            int p, d, e, h;
            cin >> p >> d >> e >> h;
            QNS q(p, d, e, h);
            suits.push(q);
        }

        bool b = 0;

        rep(i, 0, n)
        {
            string n1;
            int as;
            cin >> n1 >> as;
            if (!suits.empty())
            {
                QNS q = suits.front();
                Avenger a(n1, q, as);
                suits.pop();
                heroes[i] = a;
                mp[n1] = &(heroes[i]);
            }
            else
            {
                cout << n1 << " is out of fight\n";
                if(!b) {heroes.resize(i); b = 1;}
            }
        }

        b = 0;

        rep(i, 0, m)
        {
            string n1;
            int as;
            cin >> n1 >> as;
            if (!suits.empty())
            {
                QNS q = suits.front();
                Avenger a(n1, q, as);
                suits.pop();
                enemies[i] = a;
                mp[n1] = &enemies[i];
            }
            else
            {
                cout << n1 << " is out of fight\n";
                if(!b) {enemies.resize(i); b = 1;}
            }
        }

        string s = "start";
        while (s != "End")
        {
            cin >> s;
            if (s == "End")
                break;
            if (s == "Attack")
            {
                string n1, n2;
                cin >> n1 >> n2;
                Avenger *a = mp[n1];
                Avenger *b = mp[n2];
                if (a->getsuit().getd() > 0 && a->getsuit().geth() <= 500 && b->getsuit().getd() > 0)
                {
                    string t = "";
                    t += n1 + " attacks " + n2;
                    battleLog.push_back(t);
                    a->attack(*b);
                    if (b->getsuit().getd() <= 0)
                    {
                        string tr = "";
                        tr += n2 + " suit destroyed";
                        battleLog.push_back(tr);
                    }

                    else if (b->getsuit().geth() > 500)
                    {
                        string tr = "";
                        tr += n2 + " suit overheated";
                        battleLog.push_back(tr);
                    }
                }
            }

            if (s == "Repair")
            {
                string n1;
                int x;
                cin >> n1 >> x;
                Avenger *a = mp[n1];
                // if(a -> getsuit()->destroyed) continue;
                a->repair(x);
                string t = "";
                t += n1 + " repaired";
                battleLog.push_back(t);
            }

            if (s == "BoostPowerByFactor")
            {
                string n1;
                int y;
                cin >> n1 >> y;
                Avenger *a = mp[n1];
                // if(a -> getsuit()->destroyed) continue;
                string t = "";
                t += n1 + " boosted";
                battleLog.push_back(t);
                a->getsuit().boostPower(y);
                if (a->getsuit().geth() > 500)
                {
                    string tr = "";
                    tr += n1 + " suit overheated";
                    battleLog.push_back(tr);
                }
            }

            if (s == "BoostPower")
            {
                string n1;
                int p, d, e, h;
                cin >> n1 >> p >> d >> e >> h;
                Avenger *a = mp[n1];
                // if(a -> getsuit()->destroyed) continue;
                QNS q(p, d, e, h);
                a->upgradeSuit(q);
                string t = "";
                t += n1 + " boosted";
                battleLog.push_back(t);
            }

            if (s == "Upgrade")
            {
                string n1;
                cin >> n1;
                Avenger *a = mp[n1];
                // if(a -> getsuit()->destroyed) continue;
                if (!suits.empty())
                {
                    QNS q = suits.front();
                    suits.pop();
                    a->upgradeSuit(q);
                    string tr = "";
                    tr += n1 + " upgraded";
                    battleLog.push_back(tr);
                }
                else{
                    battleLog.push_back(n1 + " upgrade Fail");
                }
            }

            if (s == "AvengerStatus")
            {
                string n1;
                cin >> n1;
                Avenger *a = mp[n1];
                a->printStatus();
            }

            if (s == "PrintBattleLog")
            {
                printBattleLog();
            }

            if (s == "BattleStatus")
            {
                int a = Result();
                if (a == 1)
                    cout << "heroes are winning\n";
                else if (a == -1)
                    cout << "enemies are winning\n";
                else
                    cout << "tie\n";
            }

            else
                continue;
        }
    }
};

signed main()
{
    Battle b;
    b.startBattle();
}