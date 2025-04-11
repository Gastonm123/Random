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

int maquina(int t, vector<string> &lineas, vector<string> &orden) {
    sort(all(lineas));
    int n = sz(lineas);
    orden = lineas;
    ll r = sz(lineas[0]) + 1;
    forn (i, n-1) {
        int lp = 0;
        forn (j, min(sz(lineas[i]), sz(lineas[i+1]))) {
            if (lineas[i][j] != lineas[i+1][j]) break;
            lp++;
        }
        r += min(
            t+sz(lineas[i+1]),
            sz(lineas[i])-lp+sz(lineas[i+1])-lp) + 1;
    }
    return r;
}

#if DEBUG
int main() {
    readint(n); readint(t);
    vector<string> lineas(n);
    forn (i, n) cin >> lineas[i];
    vector<string> orden(n);
    int ans = maquina(t, lineas, orden);
    cout << ans << endl;
    forn (i, n) cout << orden[i] << " ";
    cout << endl;
}
#endif