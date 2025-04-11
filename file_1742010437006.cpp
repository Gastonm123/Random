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

const int SV_SIZE=1e6+1;
int sv[SV_SIZE];

void init_sv() {
    for (ll i=2; i < SV_SIZE; i++) {
        if (!sv[i]) {
            sv[i] = i;
            for (ll j = i * i; j < SV_SIZE; j += i) {
                sv[j] = i;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    init_sv();
    readint(t); while(t--) {
        readint(n); readvi(a, n);
        int x = 0; forn (i, n) {
            int fact = 0;
            while (a[i] > 1) {
                a[i] /= sv[a[i]];
                fact++;
            }
            x ^= fact;
        }
        cout << (x > 0 ? 1 : 2) << endl;
    }
}