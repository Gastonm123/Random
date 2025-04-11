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

int main() {
    ios::sync_with_stdio(false);
	readint(n);
    readvl(a, n);
    int n1 = n;
    ll x = 0;
    forn (i, n) {
        x ^= a[i];
    }
    forn (i, n) {
        a[i] = (~x)&a[i];
    }
    
    sort(all(a));
    a.erase(unique(all(a)), end(a));
    n = sz(a);

    int start = 0;
    while (start < n && a[start] == 0) start++;

    vi generadores; ll mask = 0;
    vi c(51, 0);
    forr (i, start, n) {
        bool found = false;
        forn (j, 51) {
            if ((a[i]>>j)&1) if ((c[j]&1) == 0) found = true;
        }
        if (!found) continue;
        generadores.pb(a[i]);
        forn (j, 51) {
            if ((a[i]>>j)&1) c[j]++;
        }
    }
    
    if (sz(generadores) == n1) {
        vi c(51, 0);
        ll m = 0;
        forn (i,n) {
            m = max(m, mask^a[i]);
        }
        mask = m;
    }
    cout << x + 2 * mask << endl;
    
}
