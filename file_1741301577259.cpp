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

ll pow_mod(ll base, ll exp, ll mod) {
    ll p = 1;
    while (exp > 0) {
        if (exp & 1) p = (__int128)p * base % mod;
        base = (__int128)base * base % mod;
        exp >>= 1;
    }
    return p;
}

bool check_composite(ll n, ll base, ll d, ll r) {
    ll x = pow_mod(base, d, n);
    if (x == 1 || x == n-1) return false;
    forr (i, 1, r) {
        x = (__int128)x * x % n;
        if (x == n-1)
            return false;
    }
    return true;
}

bool is_prime(ll n) {
    if (n < 2) return false;
    ll r = 0, d = n-1;
    while ((d&1) == 0) r++, d >>= 1;
    for (int a : {2,3,5,7,11,13,17,19,23,29,31,37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}

ll f(ll x, ll c, ll mod) {
    return ((__int128)x * x % mod + c) % mod;
}



// Inicializamos un generador de números aleatorios y un motor Mersenne Twister.
std::random_device rd;
std::mt19937_64 gen(rd()); // motor de 64 bits

// Definimos el rango para el número aleatorio. En este caso, todo el rango de 64 bits.
std::uniform_int_distribution<ll> dist;

ll rho(ll n) {
    if (!(n&1)) return 2;
    ll x = abs(dist(gen))%n, y = x, g = 1;
    ll c = abs(dist(gen))%n;
    while (g == 1) {
        x = f(x, c, n);
        y = f(y, c, n);
        y = f(y, c, n);
        g = gcd(abs(x-y), n);
    }
    return g == n ? rho(n) : g;
}

long long mult(long long a, long long b, long long mod) {
    return (__int128)a * b % mod;
}


void factorizar(ll n, map<ll, int> &f) {
    if (n < 2) return;
    while (n > 1 && !is_prime(n)) {
        ll p = rho(n);
        n /= p;
        factorizar(p, f);
    }
    if (n > 1) f[n]++;
}

int main() {
    // thread t(alarma);
    
    auto inicio = std::chrono::high_resolution_clock::now();
    int n = 100; while (n--) {
        // Generamos el número aleatorio.
        ll random_number = dist(gen) % ll(1e12);
        map<ll, int> factores;
        
        auto ahora = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duracion = ahora - inicio;
        cout << "tiempo: " << duracion << endl;
        cout << random_number << endl;
        fflush(stdout);
        factorizar(random_number, factores);
    }
    // t.detach();
    debug << "saliendo desde main" << endl;
}