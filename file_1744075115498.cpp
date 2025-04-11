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

const int MAXN=2e5+10;
int n;
int a[MAXN];
const int mod=1e9+7;

inline int powm(ll a, int e) {ll r=1; while(e>0) {if (e&1) r = r*a%mod; a = a*a%mod; e>>=1;} return r;}
inline int add(ll a, int b) {a += b; return a>=mod?a-mod:a;}
inline int sub(ll a, int b) {return add(a, mod-b);}
inline int mul(ll a, int b) {return a*b%mod;}
inline int divm(ll a, int b) {return mul(a, powm(b, mod-2));}

bool ok(int base) {
    ll co = 1, li = 0;
    forn (i, n) {
        li = sub(a[i]-base, mul(2ll, li));
        co = sub(0ll, mul(2ll, co));
    }
    int f0 = divm(li, sub(1, co));
    // f0 es valido?
    int fnext = (a[0]-base)-2*f0;
    forr (i, 1, n) {
        if (fnext < 0) return false;
        fnext = (a[i]-base)-2*fnext;
    }
    return fnext == f0;
}

int main() {
    readint(t); while (t--) {
        cin >> n;
        forn (i, n) cin >> a[i];
        int mini = *min_element(a, a+n);
        ll suma = 0;
        forn (i, n) suma += a[i];
        bool found = false;
        forn (k, min(mini,2)+1) {
            if ((suma-k*n)%3 == 0) {
                int a = -1, b = ((mini-k)/3)+1;
                while (b-a>1) {
                    int m = (a+b)/2;
                    if (ok(k+3*m)) {
                        a = m;
                    } else {
                        b = m;
                    }
                }
                if (a>=0) {
                    found = true;
                    cout << k+3*a << endl;
                    break;
                }
            }
        }
        if (!found) cout  << 0 << endl;
    }
}