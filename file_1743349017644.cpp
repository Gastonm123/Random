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
    readint(n); readint(q);
    readvi(a, n);

    forn (i, q) {
        readint(k);
        map<ll, ll> events;
        ll suma = 0;
        forn (j, k) {
            readint(l); readint(r); readint(x);
            events[l]   += x;
            events[r+1] -= x;
            suma += x * (r - l + 1);
        }

        int ultimo = -1;
        bool found1 = false, found2 = false;
        ll   c = 0;
        ll  ac = 0;
        ll ans = 0;
        for (auto &[id, am] : events) {
            c  += ac * (id - ultimo);
            if (!found1 && c >= suma/2+1) {
                ans += a[id-1-(c-suma/2-1)/ac-1];
                found1 = true;
            }
            if (!found2 && (suma&1) == 0 && c >= suma/2) {
                ans += a[id-1-(c-suma/2)/ac-1];
                found2 = true;
            }
            ac += am;
            ultimo = id;
        }
        if ((suma&1) == 0) {
            cout << ans/2 << (ans&1 ? ".5" : "") << endl;
        }
        else {
            cout << ans << endl;
        }
    }
}