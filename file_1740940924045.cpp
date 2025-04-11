#include <bits/stdc++.h>
#define forn(i, n) for (int i = 0; i < (n); i++)
#define dforn(i, n) for (int i = (n)-1; i >= 0; i--)
#define mp make_pair
#define pb push_back
#define all(a) begin(a),end(a)
#define readint(a) ll a; cin >> a
#define readstr(a) string a; cin >> a
#define debug if (DEBUG) cout
#define print cout
#define DEBUG 0
using namespace std;
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

const int MAXN=2000;
int D[MAXN][MAXN], E[MAXN][MAXN];
vector<ii> G[MAXN];

int main() {
	// your code goes here
    int n; while (cin >> n) {
        forn (i, n) forn (j, n) cin >> D[i][j];

        set<pair<int, ii>> s; vector<bool> visitados(n, false);
        forn (i, n) s.insert(mp(D[0][i], mp(0,i))); visitados[0] = true;

        vector<ii> ans;
        forn (i, n-1) {
            auto closest = *s.begin();
            auto [u, v] = closest.second;
            while (visitados[u] && visitados[v]) {
                s.erase(s.begin());
                closest = *s.begin();
                tie(u, v) = closest.second;
            }
            G[u].pb(mp(v, closest.first));
            G[v].pb(mp(u, closest.first));
            if (!visitados[u]) forn (i, n) s.insert(mp(D[u][i], mp(u,i)));
            if (!visitados[v]) forn (i, n) s.insert(mp(D[v][i], mp(v,i)));
            visitados[u] = visitados[v] = true;
            ans.pb(mp(u, v));
        }
        
        forn (i, n) {
            function<void(int,int,int)> dfs = [&](int v, int p, int d) {
                E[i][v] = d;
                for (auto [v1, w] : G[v]) {
                    if (p == v1) continue;
                    dfs(v1, v, d+w);
                }
            };
            dfs(i, -1, 0);
        }

        ll minimo = 1e18; ii opt;
        forn (i, n) forn (j, n) {
            if (D[i][j] != E[i][j] && minimo > D[i][j]) {
                opt = mp(i, j);
                minimo = D[i][j];
            }
        }

        if (minimo == 1e18) { // copy the first edge
            auto [u, v] = ans[0];
            cout << u+1 << " " << v+1 << " " << D[u][v] << endl;
        } else {
            auto [u, v] = opt;
            cout << u+1 << " " << v+1 << " " << D[u][v] << endl;
        }
        forn (i, n-1) {
            auto [u, v] = ans[i];
            cout << u+1 << " " << v+1 << " " << D[u][v] << endl;
        }
        cout << endl;

        forn (i, n) G[i].clear();
    }
}
