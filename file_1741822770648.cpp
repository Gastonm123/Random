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
#define readvi(a, n) vector<int> a(n); forn (i, n) cin >> a[i]
#define printvi(a, n, d) if (!d || DEBUG) { forn (i, n) cout << a[i] << " "; cout << endl; }
#define printii(a, d) if (!d || DEBUG) { cout << a.first << " " << b.first << endl; }
// #define endl '\n'
#define debug if (DEBUG) cout
#define print cout
#define DEBUG 0
using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using hash_table = gp_hash_table<K, V>;
using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    readint(n); readvi(a, n);
    if (n == 2) {
        cout << 1 << endl;
        return 0;
    }
    vi b(n);
    iota(all(b), 0);
    sort(all(b), [&](int i, int j){
        return a[i] < a[j];
    });
    bool ok = true;
    int dif  = a[b[1]] - a[b[0]];
    int dif1 = a[b[2]] - a[b[0]];
    int dif2 = a[b[2]] - a[b[1]];
    int omicion = -1;
    forn (i, n) debug << a[b[i]] << " ";
    debug << endl;
    forn (i, n - 1) {
        if (omicion == i) continue;
        if (a[b[i+1]] - a[b[i]] != dif) {
            if (omicion != -1) ok = false;
            else {
                omicion = i + 1;
                if (i < n-2 && a[b[i+2]] - a[b[i]] != dif) ok = false;
            }
        }
    }
    if (ok) {
        if (omicion != -1) cout << b[omicion]+1 << endl;
        else cout << b[n-1]+1 << endl;
        return 0;
    }
    ok = true;
    forr (i, 2, n-1) {
        if (a[b[i+1]] - a[b[i]] != dif1) {
            ok = false;
        }
    }
    if (ok) {
        cout << b[1]+1 << endl;
        return 0;
    }
    ok = true;
    forr (i, 1, n-1) {
        if (a[b[i+1]] - a[b[i]] != dif2) {
            ok = false;
        }
    }
    if (ok) {
        cout << b[0]+1 << endl;
    } else {
        cout << -1 << endl;
    }
}