#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define forn(i, n) for (int i = 0; i < (n); i++)
#define forr(i, a, n) for (int i = (a); i < (n); i++)
#define dforn(i, n) for (int i = (n)-1; i >= 0; i--)
#define mp make_pair
#define pb push_back
#define all(a) begin(a),end(a)
#define sz(a) a.size()
#define readint(a) ll a; cin >> a
#define readflt(a) double a; cin >> a
#define readstr(a) string a; cin >> a
#define readvi(a, n) vector<int> a(n); forn (i, n) cin >> a[i];
#define endl '\n'
#define debug if (DEBUG) cout
#define print cout
#define DEBUG 0
using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using hash_table = gp_hash_table<K, V>;
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

const int MAXN=2001;
vi G[MAXN];

void clear(int n) {
    forn (i, n) G[i].clear();
}
void add_edge(int u, int v) {
    G[u-1].pb(v-1); G[v-1].pb(u-1);
}

ll pow_mod(ll base, ll exp, ll mod) {
    ll p = 1;
    while (exp > 0) {
        if (exp & 1) p = (__int128)p * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return p;
}

bool check_composite(ll n, int base, int d, int r) {
    ll x = pow_mod(base, d, n);
    if (x == 1 || x == n-1) return false;
    forr (i, 1, r) {
        x = (__int128)x * x % n;
        if (x == n-1)
            return false;
    }
    return true;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    int r = 0, d = n-1;
    while ((d&1) == 0) r++, d >>= 1;
    for (int a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}

ll f(ll x, ll c, ll mod) {
    return (ll((__int128)x * x % mod) + c) % mod;
}

ll rho(ll n) {
    ll x = 2, y = 2, g = 1;
    ll c = rand()%n+1;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x-y), n);
    }
    return g==n?rho(n):g;
}

void factorizar(ll n, vector<ll> &factores) {
    if (n < 2) return;
    // la mayoria de los numeros enteros son divisibles por algun primo chiquito, asi que
    // podemos ahorrar tiempo probando algunos
    int primos[] = {2,3,5,7,11,13,17,19,23,29};
    forn (i, 10) {
        if (p % primos[i] == 0) {
            // aca voy a usar indices, en lugar de los primos en si, porque facilita
            // calcular el mex
            factores.pb(i);
            while (p % primos[i] == 0) p /= primos[i];
        }
    }
    // el mex nunca va a ser mayor a 10 asi que los primos hasta 31 alcanzan
    return;
    // en otro problema usariamos pollard-rho
    while (n > 1 && !is_prime(n)) {
        ll p = rho(n);
        n /= p;
        factorizar(p, factores);
    }
    if (n > 1) factores.pb(n);
}

int main() {
    readint(t); while (t--) {
        readint(n);
        readvi(a, n);
        clear(n);
        forn (i, n-1) {
            readint(u); readint(v);
            add_edge(u, v);
        }
        vector<vector<ll>> factores(n);
        forn (i, n) {
            int m = a[i];
            factorizar(m, factores[i]);
        }
        vector<int> camino(40, 0); int mex = 0; ll ans = 0;
        function<void(int,int,int)> dfs = [&](int v, int p, int d) {
            for (auto f : factores[v]) if (f < camino.size()) camino[f]++;
            for (mex = 0; camino[mex] == d; mex++);
            ans += primos[mex];
            for (auto v1 : G[v]) {
                if (v1 != p) {
                    dfs(v1, v, d+1);
                }
            }
            for (auto f : factores[v]) if (f < camino.size()) camino[f]--;
        };
        forn (i, n) {
            ans = 0;
            dfs(i,-1,1);
            cout << ans << " ";
        }
        cout << endl;
    }
}
