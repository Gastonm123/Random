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
#define debug if (DEBUG)
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

using u64 = uint64_t;
using u128 = __uint128_t;
using i128 = __int128_t;


ostream& operator<<(ostream &stream, u128 n) {
    ull hi = n / (ull)1e18, lo = n % (ull)1e18;
    if (hi > 0)
        stream << hi;
    stream << lo;
    return stream;
}

istream& operator>>(istream &stream, u128 &v) {
    string s; stream >> s;
    v = 0;
    forn (i, s.size()) {
        v *= 10;
        v += s[i]-'0';
    }
    return stream;
}

struct u256 {
    u128 high, low;

    static u256 mult(u128 x, u128 y) {
        u64 a = x >> 64, b = x;
        u64 c = y >> 64, d = y;
        // (a*2^64 + b) * (c*2^64 + d) =
        // (a*c) * 2^128 + (a*d + b*c)*2^64 + (b*d)
        u128 ac = (u128)a * c;
        u128 ad = (u128)a * d;
        u128 bc = (u128)b * c;
        u128 bd = (u128)b * d;
        u128 carry = (u128)(u64)ad + (u128)(u64)bc + (bd >> 64u);
        u128 high = ac + (ad >> 64u) + (bc >> 64u) + (carry >> 64u);
        u128 low = (ad << 64u) + (bc << 64u) + bd;
        return {high, low};
    }
};

struct Montgomery {
    Montgomery(u128 n) : mod(n), inv(1), r2(-n % n) {
        for (int i = 0; i < 7; i++)
            inv *= 2 - n * inv;

        for (int i = 0; i < 4; i++) {
            r2 <<= 1;
            if (r2 >= mod)
                r2 -= mod;
        }
        for (int i = 0; i < 5; i++)
            r2 = mult(r2, r2);
        cout << n << " " << inv << " " << r2 << endl;
    }

    u128 init(u128 x) {
        return mult(x, r2);
    }

    u128 reduce(u256 x) {
        u128 q = x.low * inv;
        i128 a = x.high - u256::mult(q, mod).high;
        if (a < 0)
            a += mod;
        return a;
    }

    u128 mult(u128 a, u128 b) {
        return reduce(u256::mult(a, b));
    }

    u128 mod, inv, r2;
};

// Inicializamos un generador de números aleatorios y un motor Mersenne Twister.
std::random_device rd;
std::mt19937_64 genh(rd()); // motor de 64 bits
std::mt19937_64 genl(rd()); // motor de 64 bits

// Definimos el rango para el número aleatorio. En este caso, todo el rango de 64 bits.
std::uniform_int_distribution<ull> dist;

u128 get_rand() {
    vector<ull> aux = {dist(genh), dist(genl)};
    return (u128)aux[0] << 64u + (u128)aux[1];
}

u128 gcd(u128 a, u128 b) {
    return a?gcd(b%a,a):b;
}

u128 ms_pow_mod(u128 base, u128 exp, Montgomery &ms) {
    u128 p = ms.init(1);
    base = ms.init(base);
    while (exp > 0) {
        if (exp&1) p = ms.mult(p, base);
        base = ms.mult(base, base);
        exp >>= 1;
    }
    return p;
}

bool check_composite(u128 n, u128 base, u128 d, int r, Montgomery &ms) {
    u128 x = ms_pow_mod(base, d, ms);
    u128 u = ms.init(1), n1 = ms.init(n-1); // n1 = (n-1)*2^64%n
    cout << n << " " << x << " " << u << " " << n1 << endl;
    if (x == u || x == n1) return false;
    forr (i, 1, r) {
        x = ms.mult(x, x);
        if (x == n1)
            return false;
    }
    return true;
}

bool is_prime(u128 n, Montgomery &ms) {
    if (n < 2) return false;
    int r = 0; u128 d = n-1;
    while (!(d&1)) r++, d >>= 1;
    forn (i, 100) {
        u128 a = 2 + get_rand() % (n-3);
        if (check_composite(n, a, d, r, ms)) {
            cout << "??? " << n << " " << a << endl;
            return false;
        }
    }
    return true;
}

u128 f(u128 x, u128 c, Montgomery &ms) {
    u128 v = ms.mult(x, x) + c;
    if (v > ms.mod)
        v -= ms.mod;
    return v;
}

u128 rho(u128 n, Montgomery &ms) {
    if (!(n&1)) return 2;
    u128 u = ms.init(1);
    u128 x = ms.init(2), y = x, g, d;
    u128 c = ms.init(1);
    cout << n << endl;
    do {
        c = ms.mult(c, x);
        g = 1;
        while (g == 1) {
            x = f(x, c, ms);
            y = f(y, c, ms);
            y = f(y, c, ms);
            i128 d = (i128)x-(i128)y;
            if (d < 0)
                d += n;
            g = gcd(ms.reduce({0,d}), n);
        }
    } while (g == n);
    return g;
}

void factorizar(u128 n, map<u128, int> &f) {
    debug cout << n << " ? "<< endl;
    if (n < 2) return;
    static int ar[] = {2,3,5,7,11,13,17,19,21,23,29,31};
    for (int p : ar) {
        while ((n % (u128)p) == (u128)0) {
            f[p]++;
            n /= p;
        }
    }
    Montgomery ms(n);
    while (!is_prime(n, ms)) {
        u128 p = rho(n, ms);
        debug cout << p << endl;
        n /= p;
        ms = Montgomery(n);
        factorizar(p, f);
    }
    if (n > 1) f[n]++;
}


int main() {
    u128 a; map<u128, int> f;
    while (cin >> a && a > 0) {
        debug cout << a << endl;
        f.clear();
        factorizar(a,f);
        
        for (auto [p,fr] : f) {
            cout << p << "^" << fr << " ";
        }
        cout << endl;
    }
}