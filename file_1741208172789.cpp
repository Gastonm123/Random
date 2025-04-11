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

const int MAXN=2001;
vi G[MAXN];

void clear(int n) {
    forn (i, n) G[i].clear();
}
void add_edge(int u, int v) {
    G[u-1].pb(v-1); G[v-1].pb(u-1);
}

int main() {
	// your code goes here
	vi criba(1e5, 0); vi primos;
	for (int i = 2; i * i <= 1e9; i++) {
	    if (criba[i] == 0) {
	        primos.pb(i);
	        for (int j = i*i; j < 1e5; j += i) {
	            criba[j] = 1;
	        }
	    }
	}
	
    readint(t); while (t--) {
        readint(n);
        readvi(a, n);
        clear(n);
        forn (i, n-1) {
            readint(u); readint(v);
            add_edge(u, v);
        }
        vector<vector<int>> factores(n);
        forn (i, n) {
            int m = a[i];
            forn (j, primos.size()) {
                int p = primos[j];
                if (m % p == 0) {
                    factores[i].pb(j);
                    while (m % p == 0) m /= p;
                }
                if (m == 1) break;
            }
            if (m > 1) factores[i].pb(m);
        }
        vector<int> camino(40, 0); int mex = 0; ll ans = 0;
        function<void(int,int,int)> dfs = [&](int v, int p, int d) {
            for (auto f : factores[v]) if (f < camino.size()) camino[f]++;
            for (mex = 0; camino[mex] == d; mex++);
            ans += primos[mex];
            for (auto v1 : G[v]) {
                if (v1 != p) {
                    dfs(v1, v, d+1);
                }
            }
            for (auto f : factores[v]) if (f < camino.size()) camino[f]--;
        };
        forn (i, n) {
            ans = 0;
            dfs(i,-1,1);
            cout << ans << " ";
        }
        cout << endl;
    }
}
