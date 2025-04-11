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
#define printvi(a, n, d) if (d && DEBUG) forn (i, n) cout << a[i] << " "
#define printii(a, d) if (d && DEBUG) cout << a.first << " " << b.first
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

int main() {
    // Inicializamos un generador de números aleatorios y un motor Mersenne Twister.
    std::random_device rd;
    std::mt19937_64 gen(rd()); // motor de 64 bits

    // Definimos el rango para el número aleatorio. En este caso, todo el rango de 64 bits.
    std::uniform_int_distribution<uint64_t> dist;

    int n = 1; while (n--) {
        // Generamos el número aleatorio.
        ll random_number = dist(gen) % (1ll<<63);
        vector<ll> factores;
        factorizar(random_number, factores);
        cout << "n: " << random_number << endl;
        cout << "factores: "; printvi(factores, sz(factores), 0);
    }
}
