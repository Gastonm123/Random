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

const int mod = 998244353;
const int maxn = 101;
const int maxm = 1<<16;
int dp[maxn][maxm][8][2];
bool visitados[maxn][8][2];

inline int add(ll a, ll b) {/*a += b; if (a>=mod)a-=mod; return a;*/return (a+b)%mod;}
inline int mul(__int128 a, ll b) {return a*b%mod;}

void solve(int i, int max, int mask, bool present, int target, int k) {
    if (visitados[i][mask][present]) return;
    visitados[i][mask][present] = true;
    if (i == max) {
        dp[i][0][mask][present] = (present||mask==target);
        return;
    }
    int uno  = ((mask<<1)+1)&((1<<k)-1);
    int cero = ((mask<<1)+0)&((1<<k)-1);
    int present1 = present||(i>=k&&mask==target);
    solve(i+1, max, uno, present1, target, k);
    solve(i+1, max, cero, present1, target, k);
    if (i >= k) {
        forn (j, (1<<(1<<(k+1)))) {
            dp[i][j|(1<<((mask<<1)+1))][mask][present] = 
                add(dp[i][j|(1<<((mask<<1)+1))][mask][present], dp[i+1][j][uno][present1]);
            dp[i][j|(1<<((mask<<1)+0))][mask][present] =
                add(dp[i][j|(1<<((mask<<1)+0))][mask][present], dp[i+1][j][cero][present1]);
        }
    } else {
        forn (j, (1<<(1<<(k+1)))) {
            dp[i][j][mask][present] = 
                add(dp[i+1][j][uno][present1], dp[i+1][j][cero][present1]);
        }
    }
    // cout << i << " " << mask << " " << present << endl;
    // forn (j, (1<<(1<<(k+1)))) cout << dp[i][j][mask][present] << " ";
    // cout << endl;
    return;
}

int main() {
    readint(n); readint(m); readint(k); readstr(w);
    
    int target = 0;
    forn (i, sz(w)) if (w[sz(w)-1-i]=='1') target += (1<<i);
    
    solve(0, n, 0, 0, target, k);
    vi copia1(1<<(1<<(k+1)));
    forn (i, (1<<(1<<(k+1)))) copia1[i] = dp[0][i][0][0];
    
    memset(visitados, 0, sizeof(visitados));
    memset(dp, 0, sizeof(dp));
    solve(0, m, 0, 0, target, k);
    vi copia2(1<<(1<<(k+1)));
    forn (i, (1<<(1<<(k+1)))) copia2[i] = dp[0][i][0][0];
    
    if (m == k) {
        ll ans = 0;
        forn (i, (1<<(1<<(k+1)))) {
            ans = add(ans, mul(copia1[i], copia2[0]));
        }
        cout << ans << endl;
        return 0;
    }
    if (n == k) {
        ll ans = 0;
        forn (i, (1<<(1<<(k+1)))) {
            ans = add(ans, mul(copia2[i], copia1[0]));
        }
        cout << ans << endl;
        return 0;
    }
    
    vi acc2(1<<(1<<(k+1)));
    forn (i, (1<<(1<<(k+1)))) {
        acc2[i] = copia2[i];
        /*forn (j, (1<<k+1)) {
            if ((i>>j)&1) acc2[i] = add(acc2[i], acc2[i^(1<<j)]);
        }*/
        int co = __builtin_popcount(i);
        for (int sb = (i-1)&i; sb; sb = (sb-1)&i) {
            acc2[i] = 
                add(acc2[i], (((co-__builtin_popcount(sb))&1) ? acc2[sb] : mod-acc2[sb]));
        }
    }
    
    // forn (i, (1<<(1<<(k+1)))) cout << copia1[i] << " ";
    // cout << endl; forn (i, (1<<(1<<(k+1)))) cout << acc2[i] << " ";
    // cout << endl;
    assert(copia1[0] == 0); assert(copia2[0] == 0);
    
    ll ans = 0;
    forn (i, (1<<(1<<(k+1)))) {
        int complemento = ((1<<(1<<(k+1)))-1) ^ i;
        ans = add(ans, mul(copia1[i], acc2[complemento]));
    }
    
    cout << ans << endl;
}