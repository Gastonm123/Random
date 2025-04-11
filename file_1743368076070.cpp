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
long double INF=1e100;
long double EPS=1e-9;
struct pt {
    tipo x, y;
    // tipo x, y, z; // only for 3d
    pt() {}
    pt(tipo _x, tipo _y) : x(_x), y(_y) {}
    // pt(tipo _x, tipo _y, tipo _z) : x(_x), y(_y), z(_z) {} // for 3d
    tipo norm2(){return *this**this;}
    tipo norm(){return sqrt(norm2());}
    pt operator+(pt o){return pt(x+o.x,y+o.y);}
    pt operator-(pt o){return pt(x-o.x,y-o.y);}
    pt operator*(tipo u){return pt(x*u,y*u);}
    pt operator/(tipo u) {
        if (u == 0) return pt(INF,INF);
        return pt(x/u,y/u);
    }
    tipo operator*(pt o){return x*o.x+y*o.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
    tipo operator^(pt o){return x*o.y-y*o.x;}
    tipo angle(pt o){return atan2(*this^o,*this*o);}
	pt unit(){return *this/norm();}
    bool left(pt p, pt q){ // is it to the left of directed line pq?
		return ((q-p)^(*this-p))>EPS;}
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
    bool collinear(pt p, pt q){return fabs((p-*this)^(q-*this))<EPS;}
	pt rot(pt r){return pt(*this^r,*this*r);}
	pt rot(tipo a){return rot(pt(sin(a),cos(a)));}      
};

ostream &operator<<(ostream &s, pt &p) { return s << '(' << p.x << ", " << p.y << ')'; }
pt ccw90(1,0);
pt cw90(-1,0);

struct circle {
	pt o;tipo r;
	circle(pt o, tipo r):o(o),r(r){}
	vector<pt> operator^(circle c){ // ccw
		vector<pt> s;
		tipo d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		tipo x=(r*r-c.r*c.r+d*d)/(2*d);
		tipo y=sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		s.pb(o+v*x-v.rot(ccw90)*y);
		if(y>EPS)s.pb(o+v*x+v.rot(ccw90)*y);
		return s;
	}
};

struct comp {
    pt o;
    comp(pt _o) : o(_o) {}
    int cuad(pt a) {
        a = a - o;
        if (a.x > EPS  && a.y >= -EPS) return 1;
        if (a.x <=EPS  && a.y >  EPS)  return 2;
        if (a.x < -EPS && a.y <= EPS)  return 3;
        if (a.x >=-EPS && a.y <  -EPS) return 4;
        return -1;
    }
    bool operator()(pt a, pt b) {
        int ca = cuad(a), cb = cuad(b);
        return ca < cb || (ca == cb && a.left(o,b));
    }
};

int main() {
    ios::sync_with_stdio(false);
	readint(n);
	vector<tuple<ll,ll,ll>> puntos;
	int max_cost = 0, idx_max;
	forn (i, n) {
		readint(a);
		readint(b);
		readint(c);
		if (c > max_cost) {
			max_cost = c;
			idx_max = i;
		}
		puntos.pb({a,b,c});
	}

	
	auto [x_max, y_max, c_max] = puntos[idx_max];
	pt center_max(x_max,y_max);
	comp orden(center_max);
	
	auto ok = [&](double p) {
		vector<pt> arco;
		long double r_max = p/c_max;
	    circle circ_max(center_max, p/c_max);
		for (auto [x,y,c] : puntos) {
		    long double r = p/c;
			ll dist2 = (x_max-x)*(x_max-x) + (y_max-y)*(y_max-y);
			if (sqrtl(dist2) + r_max <= r + EPS) {
				continue;
			}
			
			circle circ(pt(x,y), p/c);
			vector<pt> inter = circ_max^circ;
			
			if (inter.empty()) return false;
			if (arco.empty()) {
			    arco = inter;
				continue;
			}
			
			bool pre = arco[0].left(center_max,arco[1]);
			if ((pre && arco[1].left(center_max,inter[0])) && (pre && inter[1].left(center_max, arco[0])))
				assert(false);
			if (inter[0].left(center_max,arco[0]) || (pre && arco[1].left(center_max,inter[0]))) {
			    arco[0] = inter[0];
			}
			if (arco[1].left(center_max,inter[1]) || (pre && inter[1].left(center_max, arco[0]))) {
			    arco[1] = inter[1];
			}
			if (!pre && arco[0].left(center_max,arco[1])) return false;
			continue;
		}
		return true;
	};
	
	long double a = 0, b = 1e9;
	while (b - a > 1e-4) {
		long double m = (a+b)/2;
		if (ok(m)) {
			b = m;
		} else {
			a = m;
		}
	}
	cout << b << endl;
}
