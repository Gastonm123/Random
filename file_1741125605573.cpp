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
        readint(n); readint(x); readint(k);
        readstr(s);
        int t = 0, c = 0, ult_rep = -1;
        forn (i, n) {
            if (s[i] == 'L') x--;
            if (s[i] == 'R') x++;
            if (x == 0) {
                i = 0;
                c++;
                if (ult_rep == -1) ult_rep = t;
                else {
                    c += (k - t - 1) / (i - ult_rep);
                    break;
                }
                i = 0;
            }
            t++; if (t == k) break;
        }
        cout << c << endl;
    }
}
