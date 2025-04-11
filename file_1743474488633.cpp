#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define forn(i, n) for (int i = 0; i < (n); i++)
#define forr(i, a, n) for (int i = (a), aux = (n); i < aux; i++)
#define dforn(i, n) for (int i = (n)-1; i >= 0; i--)
#define mp make_pair
#define pb push_back
#define all(a) begin(a),end(a)
#define sz(a) ((int)a.size())
#define readint(a) ll a; cin >> a
#define readflt(a) long double a; cin >> a
#define readstr(a) string a; cin >> a
#define readvi(a, n) vector<int> a(n); forn (i, n) cin >> a[i];
#define readvl(a, n) vector<long long> a(n); forn (i, n) cin >> a[i];
// #define endl '\n'
#define debug if (DEBUG) cout
#define print cout
#define fst first
#define snd second
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
using vl = vector<long long>;
using vii = vector<pair<int,int>>;
using ii = pair<int,int>;
using ull = unsigned long long;
template<class T> ostream &operator<<(ostream &s, vector<T> &v) { s << '['; forn (i, sz(v)) s << v[i] << (i<sz(v)-1 ? ", " : ""); return s << ']'; }
template<class T, class K> ostream &operator<<(ostream &s, pair<T, K> &p) { return s << '(' << p.fst << ", " << p.snd << ')'; }

struct fl {
    ll base, pend;
};

inline void calc_dp(vi &izq, vi &der, vl &a) {
    vi num, ids;
    int n = sz(a);
    forn (i, sz(a)) {
        while (num.size() && num.back() <= a[i])
            num.pop_back(), ids.pop_back();
        if (num.empty()) izq[i] = -1;
        else izq[i] = ids.back();
        num.pb(a[i]);
        ids.pb(i);
    }
    num.clear(), ids.clear();
    dforn (i, sz(a)) {
        while (num.size() && num.back() <= a[i])
            num.pop_back(), ids.pop_back();
        if (num.empty()) der[i] = n;
        else der[i] = ids.back();
        num.pb(a[i]);
        ids.pb(i);
    }
}

constexpr ll mod = 1e9+7;
inline ll add(ll a, ll b) {a+=b; return a>mod?a-mod:a;}
inline ll sub(ll a, ll b) {return add(a,mod-b);}
inline ll mul(ll a, ll b) {return a*b%mod;}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    readint(n);
    readvl(a, n);
    // nueva idea: hacer como ese problema que saltaba siempre
    // al siguiente mayor o igual (en este caso, que este a la
    // izquierda) y guardar cuanto suma la secuencia de saltos
    // despues del salto
    // despues, sumar para cada posicion la dp las mas cercano
    // mayor o igual a la izquierda y a la derecha, y tambien
    // sumar en la posicion actual
    // lo que se tiene que calcular
    vector<vector<fl>> add1(n+1), erase(n+1);
    vi izq(n), der(n);
    calc_dp(izq, der, a);
    forn (i, n) {
        int bordes_i = i - izq[i];
        int bordes_d = der[i] - i;
        // cout << i << " " << bordes_i << " " << bordes_d << endl;
        // cout << izq[i]+1 << endl;
        add1[izq[i]+1].pb({bordes_d, bordes_d});
        erase[i+1].pb({mul(bordes_d, (bordes_i+1)), bordes_d});
        add1[i+1].pb({mul(bordes_i, (bordes_d-1)), -bordes_i});
        erase[der[i]].pb({0, -bordes_i});
    }
    ll pend = 0, acc = 0; __int128 ans = 0;
    forn (i, n) if (a[i]<0) a[i] += mod;
    forn (i, n) {
        // debug << i << endl;
        while (add1[i].size()) {
            auto [b, p] = add1[i].back();
            add1[i].pop_back();
            // debug << "add " << b << " " << p << endl;
            acc  = add(acc, b);
            pend = add(pend, p);
        }
        while (erase[i].size()) {
            auto [b, p] = erase[i].back();
            erase[i].pop_back();
            // debug << "erase " << b << " " << p << endl;
            acc  = sub(acc, b);
            pend = sub(pend, p);
        }
        ans = ans + acc * a[i];
        acc = add(acc, pend);
    }
    cout << (ll)(ans%mod) << endl;
    return 0;
}