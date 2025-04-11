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
const int MAXN=2e5+1;
bool visitados[MAXN][4][4];
bool ordenado[MAXN];
int dp[MAXN][4][4];
int a[MAXN], b[MAXN];
int n;

inline int add(ll a, int b) {a+=b; return (a>=mod?a-mod:a);}

int mover(int,int,int&);

int mover_todo (int i, int pos, int &pos_pila) {
    if (i == 0) return 0;
    if (!ordenado[i]) {
        ll r = mover(i, pos, pos_pila);
        r = add(r, mover_todo(i-1, pos, pos_pila));
        ordenado[i] = true;
        pos_pila = pos;
        return r;
    }
    
    if (visitados[i][pos_pila][pos]) {
        int r = dp[i][pos_pila][pos];
        pos_pila = pos;
        return r;
    }

    int pos_pila1 = pos_pila;

    ll r = mover(i, pos, pos_pila);
    r = add(r, mover_todo(i-1, pos, pos_pila));
    
    visitados[i][pos_pila1][pos] = true;
    dp[i][pos_pila1][pos] = r;
    pos_pila = pos;

    return r;
}

int mover (int i, int pos, int &pos_pila) {
    if (i == 0) return 0;
    int from = (ordenado[i] ? pos_pila : a[i]);
    ll ops;
    if (pos == from) return 0;
    if (abs(pos-from) == 2) {
        ops = mover_todo(i-1, pos, pos_pila);
        ops = add(ops, mover_todo(i-1, from, pos_pila));
        ops = add(ops, 2);
    }
    else {
        ops = add(mover_todo(i-1, pos^from, pos_pila), 1);
    }
    return ops;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    readint(t); while (t--) {
        cin >> n;
        forr (i, 1, n+1) cin >> a[i];
        forr (i, 1, n+1) cin >> b[i];
        forr (i, 1, n+1) ordenado[i]=false;
        ll ans = 0; int pos_pila;
        forn (i, n) {
            ans = add(ans, mover(n-i, b[n-i], pos_pila));
        }
        cout << ans << endl;
    }
}