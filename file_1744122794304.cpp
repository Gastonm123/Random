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

const int MAXN=2e5+10;
int n;
ll pos[MAXN];
ll cant[MAXN];
char color[MAXN];

// Puede escapar este jugador si el otro jugador tiene extra2 turnos optimos iniciales
bool escape(char jugador, ll extra2) {
    list<int> state;
    ll state_jug = 0;
    ll state_oth = 0;
    dforn (i, n) {
        if (color[i] == jugador) state_jug += cant[i];
        else                     state_oth += cant[i];
        if (cant[i] > 0) state.pb(i);
        if (state_jug > state_oth) {
            ll dif = state_jug - state_oth;

            // calcular los turnos que jugara el otro
            vi state2;
            ll co_r = 0; // rojo ~ jugador
            ll turnos2 = 0;
            int fichas_en_mov = cant[i] - dif; // fichas que existen en i para este jugador
            cant[i] = dif;                     // fichas que existen en i para el otro jugador
            for (int it_oth = i; it_oth >= 0 && cant[i] > 0; it_oth--) {
                if (cant[it_oth] > 0) {
                    if (color[it_oth] != jugador) {
                        ll bache = min(co_r, cant[it_oth]);
                        cant[it_oth] -= bache;
                        while (bache > 0) {
                            ll fichas = min(bache, cant[state2.back()]);
                            turnos2 += (pos[state2.back()] - pos[it_oth]) * fichas;
                            bache  -= fichas;
                            cant[state2.back()] -= fichas;
                            co_r   -= fichas;
                            if (cant[state2.back()] == 0) {
                                state2.pop_back();
                            }
                        }
                    }
                    else {
                        state2.pb(it_oth);
                        co_r += cant[it_oth];
                    }
                }
            }
            
            turnos2 -= extra2;

            // calcular turnos que jugara el jugador
            ll co_a = 0; // azul ~ otro (other)
            vector<list<int>::iterator> pend;
            vector<list<int>::iterator> borrar;
            ll turnos1 = 0;
            cant[i] = fichas_en_mov;
            for (auto it = state.begin(); it != state.end(); it++) {
                int it_jug = *it; // feo pero funciona
                if (color[it_jug] == jugador) {
                    ll bache = cant[it_jug];
                    while (bache > 0) {
                        ll fichas  = min(bache, cant[*pend.back()]);
                        turnos1 += (pos[*pend.back()] - pos[it_jug]) * fichas;
                        bache   -= fichas;
                        cant[*pend.back()] -= fichas;
                        co_a    -= fichas;
                        // tambien se afecta el estado global
                        state_jug -= fichas;
                        state_oth -= fichas;
                        // fin estado global
                        if (cant[*pend.back()] == 0) {
                            borrar.pb(pend.back());
                            pend.pop_back();
                        }
                    }
                    cant[it_jug] = 0;
                    borrar.pb(it);
                } else {
                    pend.pb(it);
                    co_a += cant[it_jug];
                }
            }

            // fin de ronda
            if (turnos1 < turnos2) return true; // jugador escapo
            extra2 = turnos1 - turnos2;
            state_jug -= dif;
            for (auto it : borrar) state.erase(it);
        }
    }
    return false; // jugador no escapo
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    readint(t); while (t--) {
        cin >> n;
        ll suma_r = 0, suma_a = 0;
        forn (i, n) cin >> pos[i] >> cant[i] >> color[i], suma_r += color[i]=='R'?cant[i]:0, suma_a += color[i]=='B'?cant[i]:0;
        if (suma_a == suma_r) { cout << "Draw 0 0" << endl; continue; }
        if (suma_r > suma_a) {
            suma_r = suma_a = 0;
            bool found = false;
            int jugada;
            dforn (i, n) {
                suma_r += color[i]=='R'?cant[i]:0;
                suma_a += color[i]=='B'?cant[i]:0;
                if (suma_a > suma_r) {
                    found = true;
                }
                if (found && color[i]=='R') {
                    jugada = pos[i];
                    break;
                }
            }
            if (!found) cout << "First " << pos[n-1] << " -" << endl;
            else {
                bool sit2 = escape('B', 1);
                if (sit2) cout << "Draw " << jugada << " +" << endl;
                else cout << "First " << jugada << " +" << endl;
            }
        } else {
            bool sit1 = escape('R', 0);
            // cout << "sit1: " << sit1 << endl;
            if (sit1) {
                dforn (i, n) {
                    if (color[i] == 'R') {
                        cout << "Draw " << pos[i] << " +" << endl;
                        break;
                    }
                }
            } else {
                cout << "Second" << endl;
            }
        }
    }
}