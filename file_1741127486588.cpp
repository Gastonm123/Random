#include <bits/stdc++.h>
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
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

const int MOD = 998244353;
const int MAXN = 3e5+1;
vector<int> G[MAXN];
vector<vi> l;
int DP[MAXN];
int DP1[MAXN];

void add_vertex(int u, int v) {
    G[u].pb(v);
}

void clear(int n) {
    forn (i, n) G[i].clear();
    l.clear();
}

void levels(int u, int d) {
    if (d >= l.size()) l.pb(vi());
    l[d].pb(u);
    for (auto v : G[u]) levels(v, d+1);
}

int main() {
	// your code goes here
    readint(t); while (t--) {
        readint(n); readvi(padre, n-1);
        clear(n);
        forn (i, n-1) add_vertex(padre[i]-1, i+1);
        levels(0, 0); debug << "levels" << endl;
        dforn(i, l.size()) {
            DP1[i] = 0;
            for (auto v : l[i]) {
                if (i == l.size()-1) DP[v] = 1;
                else {
                    DP[v] = 1 + DP1[i+1];
                    for (auto v1 : G[v]) {
                        DP[v] = (0ll + DP[v] - DP[v1] + MOD) % MOD;
                    }
                }
                DP1[i] = (0ll + DP1[i] + DP[v]) % MOD;
            }
        }
        cout << (1 + DP1[1]) % MOD << endl;
    }
}
