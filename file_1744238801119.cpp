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
#define endl '\n'
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
using vll = vector<long long>;
using vii = vector<pair<int,int>>;
using ii = pair<int,int>;
using ull = unsigned long long;
template<class T> ostream &operator<<(ostream &s, vector<T> &v) { s << '['; forn (i, sz(v)) s << v[i] << (i<sz(v)-1 ? ", " : ""); return s << ']'; }
template<class T, class K> ostream &operator<<(ostream &s, pair<T, K> &p) { return s << '(' << p.fst << ", " << p.snd << ')'; }
// Inicializamos un generador de números aleatorios y un motor Mersenne Twister.
std::random_device rd;
std::mt19937_64 gen(rd()); // motor de 64 bits
// Definimos el rango para el número aleatorio. En este caso, todo el rango de 64 bits.
std::uniform_int_distribution<ull> dist;

const int mod=998244353;

inline int addm(ll a, int b) {a+=b; return (a>=mod)?a-mod:a;}
inline int pow_mod(ll a, int e) {ll r = 1; while (e>0) { if (e&1) r=r*a%mod; a=a*a%mod; e>>=1; } return r; }
inline int mulm(ll a, int b) {return a*b%mod;}

int ciclo(int v, int k) {
    if (v == 0) return 0;
    if (v == 1) return k;
    // elevar una matriz a la (v-1)
    v--;
    ll m11 = (k-1), m12 = 0, m21 = (k-1), m22 = mod-1;
    ll r11 = 1, r12 = 0, r21 = 0, r22 = 1;
    while (v>0) {
        if (v&1) {
            ll a11 = addm(mulm(r11, m11), mulm(r12, m21));
            ll a12 = addm(mulm(r11, m12), mulm(r12, m22));
            ll a21 = addm(mulm(r21, m11), mulm(r22, m21));
            ll a22 = addm(mulm(r21, m12), mulm(r22, m22));
            r11 = a11;
            r12 = a12;
            r21 = a21;
            r22 = a22;
        }
        
        // cout << m11 << " " << m12 << endl;
        // cout << m21 << " " << m22 << endl;
        ll a11 = addm(mulm(m11, m11), mulm(m12, m21));
        ll a12 = addm(mulm(m11, m12), mulm(m12, m22));
        ll a21 = addm(mulm(m21, m11), mulm(m22, m21));
        ll a22 = addm(mulm(m21, m12), mulm(m22, m22));
        m11 = a11;
        m12 = a12;
        m21 = a21;
        m22 = a22;
        v>>=1;
    }
    // cout << r11 << " " << r12 << endl;
    // cout << r21 << " " << r22 << endl;
    return mulm(k, r21);
}

int calc(int n, int m, int k, vector<ii> aristas) {
    const int borde = (int)pow_mod(mulm(k, k-1), mod-2);
    ll r = 1;
    vi visitados(m, false);
    forn (i, sz(aristas)) {
        if (visitados[i]) continue;

        stack<ii> scope;
        auto [a, b] = aristas[i];
        int vert = b-a+1;
        n = n - vert + 2;
        scope.push({i, vert});
        int vertices_int = 2;
        int max_idx = i;

        while (scope.size()) {
            auto [curr, vert] = scope.top();
            scope.pop();
            vert = vert - vertices_int + 2;
            auto [a,b] = aristas[curr];
            auto next = upper_bound(&aristas[max_idx+1], &aristas[m], mp(a,(int)2e9));
            while (next != &aristas[m] && next->first < b) {
                scope.push({curr, vert});
                curr = next-&aristas[0];
                assert(max_idx < curr);
                max_idx = curr;
                tie(a, b) = aristas[curr];
                vert = b-a+1;
                next = upper_bound(&aristas[max_idx+1], &aristas[m], mp(a,(int)2e9));
            }
            visitados[curr] = true;
            // cout << vert << endl;
            // cout << ciclo(vert, k) << endl;
            r = mulm(r, (int)ciclo(vert, k));
            r = mulm(r, borde);
            vertices_int = vert;
        }
    }
    // cout << n << endl;
    r = mulm(r, (int)ciclo(n, k));
    return r;
}

int main() {
    readint(t); while (t--) {
        readint(n); readint(m); readint(k);
        vector<ii> aristas;
        forn (i, m) { readint(a); readint(b); aristas.pb({a, b}); }
        cout << calc(n, m, k, aristas) << endl;
    }
}