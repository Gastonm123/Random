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
    readint(n);
    readvl(a, n);
    vl pref(n+1, 0); n[0] = 0;
    vl rem(n+1, 0); rem[0] = 0;
    vl yadp(n+1, 0); yadp[n] = 0;
    vi izq(n), der(n);
    const int mod = 1e9+7;
    dforn (i, n) {
        yadp[i] = yadp[i+1] + (n-i) * a[i] % mod;
        if (yadp[i] > mod) yadp[i] -= mod;
    }
    forr (i, 1, n+1) {
        pref[i] = pref[i-1] + a[i-1];
        if (pref[i] > mod) prerf[i] -= mod;
    }
    forr (i, 1, n+1) {
        rem[i] = rem[i-1] + n[n-i+1];
        if (rem[i] > mod) rem[i] -= mod;
    }
    vector<int> num, ids;
    forn (i, n) {
        while (num.size() && num.back() <= a[i]) num.pop_back(), ids.pop_back();
        if (num.empty()) izq[i] = 0;
        else izq[i] = ids.back();
        num.pb(a[i]);
        ids.pb(i);
    }
    num.clear(), ids.clear();
    dforn (i, n) {
        while (num.size() && num.back() <= a[i]) num.pop_back(), ids.pop_back();
        if (num.empty()) der[i] = n-1;
        else der[i] = ids.back();
        num.pb(a[i]);
        ids.pb(i);
    }
    auto calc_range = [&](int l, int r) {
        if (l == r) return 0;
        ll r = yadp[l];
        r += mod-rem[n-r];
        r += (n-r)*pref[l]%mod;
        return r%mod;
    };
    ll ans = 0;
    forn (i, n) {
        int l = izq[i], r = der[i];
        ans += calc_range(l, r+1);
        ans += calc_range(i+1, r+1);
        while (ans > mod) ans -= mod;
    }
    cout << ans << endl;
    return 0;
}