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
using tipo=long double;

double golden(auto f, double l, double r, int iters) {
    constexpr double ratio = (3-sqrt(5))/2;
    double x1 = l+(r-l)*ratio, f1 = f(x1);
    double x2 = r-(r-l)*ratio, f2 = f(x2);
    while (iters--) {
        if (f1 > f2) l=x1, x1=x2, f1=f2, x2=r-(r-l)*ratio, f2=f(x2);
        else         r=x2, x2=x1, f2=f1, x1=l+(r-l)*ratio, f1=f(x1);
    }
    return (l+r)/2; // retorna un punto, no un resultado de evaluar f
}

constexpr double PI = 4*atan(1.0);

int main() {
    ios::sync_with_stdio(false);
	readint(n);
	vector<tuple<ll,ll>> puntos;
	forn (i, n) {
		readint(a);
		readint(b);
		puntos.pb({a,b});
	}

	auto costo_xy = [&](double x, double y) {
		double maximo = 0;
		for (auto [x1,y1,c1] : puntos) {
			double dist2 = (x-x1)*(x-x1) + (y-y1)*(y-y1);
			maximo = max(maximo, dist2);
		}
		return PI*maximo;
	};
	auto f = [&costo_xy](double x) {
		auto f1 = [&x, &costo_xy](double y) {
			return costo_xy(x, y);
		};
		return costo_xy(x, golden(f1, -1e9,1e9,70));
	};
	
	double best_x = golden(f, -1e9, 1e9, 70);

	auto f1 = [&best_x, &costo_xy](double y) {
		return costo_xy(x, y);
	};

	cout << costo_xy(best_x, golden(f1, -1e9, 1e9, 70)) << endl;
}
