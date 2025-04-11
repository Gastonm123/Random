#include <bits/stdc++.h>
#include <ext/pb_ds/detail/standard_policies.hpp>
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
#define readvi(a, n) vector<int> a(n); forn (i, n) cin >> a[i];
#define endl '\n'
#define debug if (DEBUG) cout
#define print cout
#define DEBUG 0
using namespace std;
using namespace __gnu_pbds;
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<class K, class V> using hash_table = gp_hash_table<K, V>;
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

int main() {
    readint(n); readstr(s);
    vector<int> fr[3]; forn (i, 3) fr[i].resize(2e6, 0); int fr_offset = 1000000;
    list<ii> pending;
    ll ans = 0; int mod = 0, base = 0, suma = 0;
    forn (i, n) {
        if (s[i] == '0') {
            for (auto it = pending.begin(); it != pending.end(); ) {
                auto &[j, z] = *it;
                int o = i - j - z;
                if (z == 1) {
                    fr[(mod+1)%3][fr_offset + base + 3*o - z]++;
                    if (3*o-z < -1) suma += 1;
                    it++; pending.erase(prev(it));
                } else {
                    z++; it++;
                }
            }
            pending.pb(mp(i, 1));
        } else {
            pending.pb(mp(i, 0));
        }

        if (s[i] == '0') {
            forn (i, 3) suma += fr[i][fr_offset+base-1];
            base += 1;
            mod = (mod-1+3) % 3;
        }
        else {
            forn (i, 3) forn (j, 3) suma -= fr[i][fr_offset+base-j-2];
            base -= 3;
        }

        ans += suma;
        ans += fr[(mod+2)%3][fr_offset+base] + fr[(mod+2)%3][fr_offset+base+1];
    }
    cout << ans << endl;
}
