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
#define endl '\n'
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

__int128 abs(__int128 a) {
    if (a < 0 )return -a; return a;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    readint(t); while (t--) {
        readint(n); vector<int> b(2*n); forn (i, 2*n) cin >> b[i];
        sort(all(b)); ll s1 = 0, s2 = 0;
        forn (i, 2*n) {
            if (i < n+1) s1 += b[i];
            else s2 += b[i];
        }
        cout << s1 - s2 << " ";
        forn (i, n) {
            cout << b[i] << " " << b[n+1+i] << " ";
        }
        cout << endl;
    }
}