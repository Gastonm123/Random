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

int consulta(int, int, int);

int solve(vi &xx, vi &yy) {
    int n = sz(xx);
    int a = 0;
    int b = n;
    vi ids(n);
    iota(all(ids), 0);
    sort(all(ids), [&](int i, int j) {
        return xx[i] < xx[j] || (xx[i] == xx[j] && yy[i] < yy[j]);
    });
    vi aux(n);
    forn (i, n) aux[i] = xx[ids[i]];
    xx = aux;
    forn (i, n) aux[i] = yy[ids[i]];
    yy = aux;
    set<int> vistos;
    while (b - a > 1) {
        int m = (b+a)>>1;
        int w = (xx[m] - xx[a]) * 2;
        int h = w>0 ? 2e9 : (yy[m]-yy[a])*2;
        if (w>0 && vistos.count(xx[m])) {
            if (consulta(m+1, 1, 2e9)) {
                int mini = n, maxi = 0;
                forr (i, a, b) {
                    if (xx[i] == xx[m]) {
                        mini = min(mini, i);
                        maxi = max(maxi, i);
                    }
                }
                a = mini, b = maxi+1;
            } else {
                int mini = n, maxi = 0;
                forr (i, a, b) {
                    if (abs(xx[i] - xx[m]) > 0) {
                        mini = min(mini, i);
                        maxi = max(maxi, i);
                    }
                }
                a = mini, b = maxi+1;
            }
        }
        else if (consulta(a+1, w, h)) {
            int mini = n, maxi = 0;
            forr (i, a, b) {
                if (xx[i] <= xx[a] + w/2 && yy[i] <= yy[a] + h/2) {
                    mini = min(mini, i);
                    maxi = max(maxi, i);
                }
            }
            a = mini, b = maxi+1;
        }
        else {
            int mini = n, maxi = 0;
            forr (i, a, b) {
                if (xx[i] > xx[a] + w/2 || yy[i] > yy[a] + h/2) {
                    mini = min(mini, i);
                    maxi = max(maxi, i);
                }
            }
            a = mini, b = maxi+1;
        }
        vistos.insert(xx[m]);
    }
    return a+1;
}

#if DEBUG
int secret;
vi x, y;

int consulta(int i, int w, int h) {
    cout << "consulta(" << i << ", " << w << ", " << ")" << endl;
    return (abs(x[secret] - x[i-1]) <= w/2 && abs(y[secret] - y[i-1]) <= h/2);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    readint(n); x.resize(n); y.resize(n);
    forn (i, n) {
        cin >> x[i] >> y[i];
    }
    secret = rand() % n;
    cout << "secret: " << secret << endl;
    cout << "solve: " << solve(x, y) << endl;
}
#endif