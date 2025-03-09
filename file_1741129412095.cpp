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
// #define endl '\n'
#define debug if (DEBUG) cout
#define print cout
#define DEBUG 0
using namespace std;
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

// 10
// 0010010011

// el primer jugador gana si hay dos ceros o dos ceros y un uno
// o si hay n ceros, ...
// el segundo jugador gana si hay cero o un ceros y dos o un uno,
// respectivamente
// si hay mas unos que ceros, el segundo jugador siempre tiene estrategia
// ganadora: hacer que la cantidad de ceros sea impar y luego tomar los
// unos de a dos hasta que el primer jugador se quede sin jugadas
// si hay mas ceros que unos, el segundo jugador tiene (cantidad de unos)
// jugadas y tiene que lograr que el primer jugador se quede sin jugadas antes
// las jugadas del primer jugador son: 
//      n : cantidad de ceros,   m : cantidad de unos
//  cant de jugadas = min (m, n / 3)
// el primer jugador gana si n>=2 && m < (n-2)/3
// osea que n >= 2 && 3*m < (n - 2)
//                    3m + 2  < n
//                    n       > 3m + 2
// n - (3m + 2) > 0
// si n == 2, el primer jugador gana si m < 2
// m - n/3 > 1     ==> segundo gana
// 3m - (n - n%3) - 3 <= 0
// 3m - (n - n%3)  > 3
// 3m - (n - n%3) - 3 > 0  ==> segundo gana
// 3m - (n - n%3) - 3 <= 0 ==> segundo pierde
// 3m - n - 3 <= n%3
// m - n/3 <= 1
// n%3 == 2 && m - n/3 > 1
// n%3 == 1
// n%3 == 0
// m - n/3 > 1      ==> segundo gana
// m - n/3 - 2 >= 0 ==> segundo gana
// m - n/3 - 2 < 0  ==> segundo pierde


// 00000111 pierde
// 0000011  gana
// 000001   gana
// 00001    pierde
// 0001     pierde
int main() {
	// your code goes here
    readint(n); readstr(s);
    vector<int> fr[3]; forn (i, 3) fr[i].resize(2e6, 0); int fr_offset = 1000000;
    list<ii> pending;
    ll ans = 0; int mod = 0, base = 0, suma = 0;
    forn (i, n) {
        if (s[i] == '0') {
            for (auto it = pending.begin(); it != pending.end(); ) {
                auto &[j, z] = *it;
                int o = i - j - z;
                if (z == 1) {
                    debug << "inserting " << j << " en " << base + 3*o - z << endl;
                    fr[(mod+1)%3][fr_offset + base + 3*o - z]++;
                    if (3*o-z < -1) suma += 1;
                    it++; pending.erase(prev(it));
                } else {
                    z++; it++;
                }
            }
            pending.pb(mp(i, 1));
        } else {
            pending.pb(mp(i, 0));
        }

        if (s[i] == '0') { // sumar uno a la cantidad de ceros == restar uno al acumulado de todos en `t` == sumar uno a base
            forn (i, 3) debug << fr[i][fr_offset+base-1] << " ";
            debug << endl;
            forn (i, 3) suma += fr[i][fr_offset+base-1];
            base += 1;
            mod = (mod-1+3) % 3;
        }
        else { // sumar uno a la cantidad de unos == sumar 3 al acumulado de todos en `t` == restar 3 a la base
            forn (i, 3) forn (j, 3) suma -= fr[i][fr_offset+base-j-2];
            base -= 3;
        }
        
        debug << "base " << base << endl;
        debug << i+1 << " " << suma << endl;
        debug << fr[(mod+2)%3][fr_offset+base] << " " << fr[(mod+2)%3][fr_offset+base+1] << endl;
        ans += suma;
        ans += fr[(mod+2)%3][fr_offset+base] + fr[(mod+2)%3][fr_offset+base+1];

        debug << "\t" << ans << endl;
    }
    cout << ans << endl;
}
