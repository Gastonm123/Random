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
using ull = unsigned long long;
using ll = long long;
using vi = vector<int>;
using ii = pair<int,int>;

int base = 10, digits = 1;

struct bigint {
    vector<int> dig;
    bigint() {}
    bigint(string s) { read(s); }
    void read(string s) {
        int exp = 1, d = 0;
        dig.clear();
        dforn (i, s.size()) {
            d += (s[i]-'0') * exp;
            exp *= 10;
            if (exp == base) {
                dig.pb(d);
                exp = 1;
                d = 0;
            }
        }
        if (d > 0) dig.pb(d);
    }
    bigint operator*(bigint o) {
		vector<ll> a(all(dig));
		vector<ll> b(all(o.dig));
		while (a.size() < b.size())
			a.push_back(0);
		while (b.size() < a.size())
			b.push_back(0);
		while (a.size() & (a.size() - 1))
			a.push_back(0), b.push_back(0);
		vector<ll> c = multiply(a, b);
		bigint res;
		for (int i = 0, carry = 0; i < (int) c.size() || carry > 0; i++) {
			long long cur = (i<(int)c.size() ? c[i] : 0) + carry;
			res.dig.push_back((int) (cur % 10));
			carry = (int) (cur / 10);
		}
        res.remove_tz();
		return res;
    }
    vector<ll> multiply(vector<ll> &a, vector<ll> &b) {
        int n = a.size();
        vector<ll> res(n + n);
        if (n <= 32) {
            forn (i, n) forn (j, n) res[i + j] += a[i] * b[j];
            return res;
        }

        int m = a.size() / 2;
        vector<ll> a1(a.begin(), a.begin()+m), a2(a.begin()+m, a.end());
        vector<ll> b1(b.begin(), b.begin()+m), b2(b.begin()+m, b.end());
        
        vector<ll> a1b1 = multiply(a1, b1);
        vector<ll> a2b2 = multiply(a2, b2);

        forn (i, m)
            a1[i] += a2[i];
        forn (i, m)
            b1[i] += b2[i];
        
        vector<ll> e = multiply(a1, b1);
        forn (i, n)
            e[i] -= (a1b1[i] + a2b2[i]);
        forn (i, n)
            res[n+i] = a2b2[i];
        forn (i, n)
            res[m+i] += e[i];
        forn (i, n)
            res[i] += a1b1[i];
        return res;
    }
    void remove_tz() {
        int i; for (i = dig.size()-1; i>0 && dig[i]==0; i--);
        dig.resize(i+1);
    }
    friend ostream &operator<<(ostream &stream, bigint v) {
        if (v.dig.size() > 0) {
            stream << v.dig[v.dig.size()-1];
            for (int i = v.dig.size()-2; i >= 0; i--) {
                stream << setw(digits) << setfill('0') << v.dig[i];
            }
        } else {
            stream << 0;
        }
        return stream;
    }
    friend istream &operator>>(istream &stream, bigint &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
};

int main(){
	ios::sync_with_stdio(0), cin.tie(0);
    bigint a, b; cin >> a >> b;
    cout << a * b << endl;
}