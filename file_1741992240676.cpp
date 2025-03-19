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

const int MAXAXIS=30;
int grundy[MAXAXIS+1][MAXAXIS+1][MAXAXIS+1];
bool vis[MAXAXIS+1][MAXAXIS+1][MAXAXIS+1];

struct cube {
    int x, y, z;
};

int nim(cube c) {
    if (c.x==0 || c.y==0 || c.z==0) return 0;
    if (c.x==1 || c.y==1 || c.z==1) return 1;
    if (vis[c.x][c.y][c.z]) return grundy[c.x][c.y][c.z];

    vis[c.x][c.y][c.z] = true;

    hash_table<int,int> a;
    
    for (int cutx = 0; cutx <= (c.x-1)/2; cutx++) {
        for (int cuty = 0; cuty <= (c.y-1)/2; cuty++) {
            for (int cutz = 0; cutz <= (c.z-1)/2; cutz++) {
                int x = nim({cutx, cuty, cutz})
                    ^ nim({c.x-1-cutx, cuty, cutz})
                    ^ nim({cutx, c.y-1-cuty, cutz})
                    ^ nim({c.x-1-cutx, c.y-1-cuty, cutz})
                    ^ nim({cutx, cuty, c.z-1-cutz})
                    ^ nim({c.x-1-cutx, cuty, c.z-1-cutz})
                    ^ nim({cutx, c.y-1-cuty, c.z-1-cutz})
                    ^ nim({c.x-1-cutx, c.y-1-cuty, c.z-1-cutz});
                a[x] = 1;
            }
        }
    }

    int mex; for (mex = 0; a.find(mex) != a.end(); mex++);

    return grundy[c.x][c.y][c.z] = mex;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    nim({MAXAXIS, MAXAXIS, MAXAXIS});
    string jug[] = {"RUBEN", "ALBERT"};
    string primero; cin >> primero;
    string segundo = jug[primero == "RUBEN"];
    readint(n); int x=0;
    forn (i, n) {
        cube c; cin >> c.x >> c.y >> c.z;
        x ^= nim(c);
    }
    cout << (x>0 ? primero : segundo) << endl;
}