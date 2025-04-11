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
#define endl '\n'
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
// Inicializamos un generador de números aleatorios y un motor Mersenne Twister.
std::random_device rd;
std::mt19937_64 gen(rd()); // motor de 64 bits
// Definimos el rango para el número aleatorio. En este caso, todo el rango de 64 bits.
std::uniform_int_distribution<ull> dist;

// mínimo entero de f en (l,r)
ll ternary(auto f, ll l, ll r) {
    for (ll d = r-l; d > 2; d = r-l) {
        ll a = l+d/3, b = r-d/3;
        if (f(a) > f(b)) l = a; else r = b;
    }
    return l+1; // retorna un punto, no un resultado de evaluar f
}

int main() {
    readint(t); while (t--) {
        // el problema se reduce a resolver un sistema de ecuaciones
        readint(n); readvi(a, n);
        int mini = *min_element(all(a));
        bool found = false;
        forn (k, min(mini, 2)+1) {
            // ternary en el valor de f0
            vector<int> val_f(n);
            
            auto calc_off = [&](int f0) {
                // cout << a << endl;
                val_f[0] = f0;
                int fnext = a[0]-2*f0;
                forr (i, 1, n) {
                    val_f[i] = fnext;
                    fnext = max(0, a[i]-2*fnext);
                }
                
                int max_off = 0;
                forn (i, n) {
                    max_off = max(max_off,
                        abs(a[i] - (2*val_f[i]+val_f[(i+1)%n])));
                }
                return max_off;
            };
            auto run_ternary = [&](int base) {
                forn (i, n) a[i] -= base;
                int f0 = ternary(calc_off, -1, a[0]/2+1);
                int r  = calc_off(f0);
                forn (i, n) a[i] += base;
                return r;
            };
            
            /*
            forn (i, n) a[i] -= k;
            forn (i, a[0]/2+1) {
                cout << i << " ";
                cout << calc_off(i) << endl;
            }
            forn (i, n) a[i] += k;
            */
            
            int min_off = run_ternary(k);
            // cout << "min_off: " << min_off << endl;
            // cout << f0 << " " << calc_off(f0) << endl;
            if (min_off == 0) {
                found = true;
                int a = 0, b = (mini-k)/3+1;
                while (b - a > 1) {
                    int m = (a+b)/2;
                    int min_off = run_ternary(k+3*m);
                    if (min_off == 0) a = m;
                    else b = m;
                }
                cout << k+3*a << endl;
                break;
            }
        }
        if (!found) cout << 0 << endl;
    }
}