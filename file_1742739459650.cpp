#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define forn(i, n) for (int i = 0; i < (n); i++)
#define forr(i, a, n) for (int i = (a); i < (n); i++)
#define dforn(i, n) for (int i = (n)-1; i >= 0; i--)
#define mp make_pair
#define pb push_back
#define all(a) begin(a),end(a)
#define sz(a) ((int)a.size())
#define readint(a) ll a; cin >> a
#define readflt(a) double a; cin >> a
#define readstr(a) string a; cin >> a
#define readvi(a, n) vector<int> a(n); forn (i, n) cin >> a[i];
// #define endl '\n'
#define debug if (DEBUG) cout
#define print cout
#define DEBUG 1
using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using hash_table = gp_hash_table<K, V>;
template<class T> using pq = priority_queue<T>;
using ll = long long;
using vi = vector<int>;
using vb = vector<bool>;
using vll = vector<long long>;
using vii = vector<pair<int,int>>;
using ii = pair<int,int>;
using ull = unsigned long long;

struct ev {
    int j1, j2, e1, e2, t;
    bool operator <(const ev &o) const {
        return t < o.t || (t == o.t && max(e1, e2) > max(o.e1, o.e2));
    }
};

set<ev> events;
set<ii> elos;
int jid;
int now;
vector<bool> match;
vector<int> entrada;

void inicializar(int n) {
    match.resize(n, false);
    entrada.resize(n, 0);
    elos.clear();
    events.clear();
    jid = 0;
    now = 0;
}

vector<int> tiempo(int t) {
    vi r;
    while (events.size() && begin(events)->t <= now+t) {
        ev active = *begin(events);
        events.erase(begin(events));
        int e1 = active.e1;
        int e2 = active.e2;
        int j1 = active.j1;
        int j2 = active.j2;
        assert(e1 > e2);
        if (match[j1]) continue;
        if (match[j2]) {
            auto j3 = elos.lower_bound(mp(e2,-1));
            if (j3 != elos.end() && j3->first == e2) {
                match[j1] = true;
                match[j3->second] = true;
                r.pb(e2);
                r.pb(e1);
                elos.erase({e1, j1});
                elos.erase(j3);
            }
            else if (j3 != elos.begin()) {
                j3--;
                events.insert({j1, j3->second,
                    e1, j3->first,
                    now + e2 - j3->first});
            }
            continue;
        }
        match[j1] = true;
        match[j2] = true;
        r.pb(e2);
        r.pb(e1);
        elos.erase({e1, j1});
        elos.erase({e2, j2});
    }
    now += t;
    return r;
}

vector<int> jugador(int e) {
    vi r;
    int  j1 = jid++;
    auto j2 = elos.lower_bound(mp(e, -1));
    entrada[j1] = now;

    // si hay algun jugador de mismo elo MATCH inmediato
    // si no, se busca el primer jugador con mas elo y se intenta
    // la regla de la diferencia
    if (j2 != elos.end() && j2->first == e) {
        match[j1] = true;
        match[j2->second] = true;
        r.pb(e);
        r.pb(e);
        elos.erase(j2);
        return r;
    }

    if (j2 != elos.begin()) {
        j2--;
        events.insert({j1, j2->second,
            e, j2->first,
            now + e - j2->first});
    }

    auto j3 = elos.upper_bound(mp(e, -1));
    if (j3 != elos.end()) {
        if (j3->first - (now - entrada[j3->second]) <= e) {
            match[j1] = true;
            match[j3->second] = true;
            r.pb(e);
            r.pb(j3->first);
            elos.erase(j3);
            return r;
        }
        int dif = (j3->first - (now - entrada[j3->second])) - e;
        events.insert({j3->second, j1, j3->first, e, now + dif});
    }

    match[j1] = false;
    elos.insert({e, j1});
    return r;
}


#if DEBUG
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    readint(n); inicializar(n);
    forn (i, n) {
        readint(t); readint(x);
        if (t == 1) {
            vi r = tiempo(x);
            cout << r.size() << " ";
            forn (i, r.size()) cout << r[i] << " ";
            cout << endl;
        }
        if (t == 2) {
            vi r = jugador(x);
            cout << r.size() << " ";
            forn (i, r.size()) cout << r[i] << " ";
            cout << endl;
        }
    }
}
#endif