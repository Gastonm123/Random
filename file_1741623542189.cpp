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
    readint(t); while (t--) {
        readint(n); vector<ii> l(n), r(n);
        forn (i, n) {
            forn (j, 2) {
                char o; int a; cin >> o >> a;
                if (j == 0) l[i] = mp(o=='x', a);
                else        r[i] = mp(o=='x', a);
            }
        }
        ll cl = 1, cr = 1, global = 2, flotante = 0;
        forn (i, n) {
            ll total_i = 0;
            if (l[i].first) {
                if (l[i] == r[i]) {
                    total_i += flotante * (l[i].second - 1);
                }
                else if (l[i] > r[i]) {
                    cl += flotante;
                    flotante = 0;
                }
                else {
                    cr += flotante;
                    flotante = 0;
                }
            } else if (r[i].first) {
                cr += flotante;
                flotante = 0;
            }
            if (l[i].first) total_i += ll(l[i].second - 1) * cl;
            else            total_i += l[i].second;
            if (r[i].first) total_i += ll(r[i].second - 1) * cr;
            else            total_i += r[i].second;
            flotante += total_i;
            // cout << global << " " << total_i << endl;
            global += total_i;
        }
        cout << global << endl;
    }
}