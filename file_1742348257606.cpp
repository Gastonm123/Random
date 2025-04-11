// desalambrando

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define forn(i, n) for (int i = 0; i < (n); i++)
#define forr(i, a, n) for (int i = (a); i < (n); i++)
#define dforn(i, n) for (int i = (n)-1; i >= 0; i--)
#define mp make_pair
#define pb push_back
#define all(a) begin(a),end(a)
#define sz(a) ((int)a.size())
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
using vii = vector<pair<int,int>>;
using ii = pair<int,int>;
template<class T> using pq = priority_queue<T>;

const int MAXN=1e5+1;
vii g[MAXN];

void add_edge(int a, int b, int c) {
    g[a-1].pb(mp(b-1, c)); g[b-1].pb(mp(a-1, c));
}

ll all_minus_prim(int v, vector<bool> &visitados) {
    visitados[v] = true;
    pq<tuple<int,int,int>> aristas;
    ll total = 0;
    ll prim  = 0;
    for (auto [v1, c1] : g[v]) {
        aristas.push({c1,v,v1});
        total += c1;
    }
    while (aristas.size()) {
        auto [c, v1, v2] = aristas.top();
        aristas.pop();

        if (visitados[v1] && visitados[v2])
            continue;

        if (visitados[v2])
            swap(v1, v2);
        
        prim += c;
        visitados[v2] = true;
        for (auto [v3, c3] : g[v2]) {
            aristas.push({c3,v2,v3});
            total += c3;
        }
    }
    return (total / 2) - prim;
}

int desalambrando(int n, vi a, vi b, vi c) {
    forn (i, sz(a)) {
        add_edge(a[i], b[i], c[i]);
    }

    // crear el maximum spanning tree de cada componente conexa
    vector<bool> visitados(n, 0);
    ll ans = 0;
    forn (i, n) {
        if (!visitados[i]) {
            ans += all_minus_prim(i, visitados);
        }
    }

    return ans;
}

#if DEBUG
int main() {
    readint(n); readint(m); vi a(m), b(m), c(m);
    forn (i, m) cin >> a[i] >> b[i] >> c[i];
    cout << desalambrando(n,a,b,c) << endl;
}
#endif