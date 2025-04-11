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

int main() {
	// your code goes here
    readint(t); while (t--) {
        readint(n); readint(k);
        readstr(s); readvi(costos, n);
        int maxi = *max_element(all(costos));
        int a = 0, b = maxi;
        auto posible = [&](int tope) {
            bool franja = false; int c = 0;
            forn (i, n) {
                if (s[i] == 'R') {
                    if (costos[i] > tope) {
                        franja = false;
                    }
                }
                else {
                    if (costos[i] > tope) {
                        if (!franja) c++;
                        franja = true;
                    }
                }
            }
            debug << tope << " " << c << endl;
            return (c <= k);
        };
        while (b - a > 1) {
            int m = (a+b)/2;
            if (posible(m)) {
                b = m;
            } else {
                a = m;
            }
        }
        debug << a << " " << b << endl;
        debug << s << endl;
        if (posible(a)) cout << a << endl;
        else if (posible(b)) cout << b << endl;
        else {
            debug << "?" << endl;
        }
    }
}
