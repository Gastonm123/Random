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

int base = 1000000000, digits = 9;

struct bigint {
    vector<int> dig;
    bigint() {}
    bigint(string s) { read(s); }
    bigint(vector<int> _dig) : dig(_dig) {
        remove_tz();
    }
    bigint(int n) {
        dig.resize(2);
        dig[1] = n/base;
        dig[0] = n%base;
        remove_tz();
    }
    bigint(ll n) {
        dig.resize(3);
        dig[2] = (n/base)/base;
        dig[1] = n/base;
        dig[0] = n%base;
        remove_tz();
    }
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
    bigint& operator=(bigint o) {
        dig = o.dig;
        return *this;
    }
    bigint& operator=(int n) {
        dig.resize(2);
        dig[1] = n/base;
        dig[0] = n%base;
        remove_tz();
        return *this;
    }
    bigint& operator=(ll n) {
        dig.resize(3);
        dig[2] = (n/base)/base;
        dig[1] = n/base;
        dig[0] = n%base;
        remove_tz();
        return *this;
    }
    bigint operator+(bigint o) {
        int carry = 0; vector<int> s;
        int ts = dig.size(), os = o.dig.size();
        forn (i, max(ts, os)) {
            int sum;
            if (i < ts && i < os) {
                sum = dig[i] + o.dig[i] + carry;
            } else {
                sum = (i < ts ? dig[i] : o.dig[i]) + carry;
            }

            if (sum >= base) {
                sum -= base;
                carry = 1;
            }
            else {
                carry = 0;
            }
            s.pb(sum);
        }
        if (carry > 0) {
            s.pb(1);
        }
        return bigint(s);
    }
    vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
		vector<long long> p(max(old_digits, new_digits) + 1);
		p[0] = 1;
		for (int i = 1; i < (int) p.size(); i++)
			p[i] = p[i - 1] * 10;
		vector<int> res;
		long long cur = 0;
		int cur_digits = 0;
		for (int i = 0; i < (int) a.size(); i++) {
			cur += a[i] * p[cur_digits];
			cur_digits += old_digits;
			while (cur_digits >= new_digits) {
				res.push_back(int(cur % p[new_digits]));
				cur /= p[new_digits];
				cur_digits -= new_digits;
			}
		}
		res.push_back((int) cur);
		while (res.size()>1 && !res.back())
			res.pop_back();
		return res;
	}
    bigint operator*(bigint o) {
		vector<int> t6 = convert_base(this->dig, digits, 5);
		vector<int> o6 = convert_base(o.dig, digits, 5);
		vector<ll> a(t6.begin(), t6.end());
		vector<ll> b(o6.begin(), o6.end());
		while (a.size() < b.size())
			a.push_back(0);
		while (b.size() < a.size())
			b.push_back(0);
		while (a.size() & (a.size() - 1))
			a.push_back(0), b.push_back(0);
		vector<ll> c = multiply(a, b);
		bigint res;
		for (int i = 0, carry = 0; i < (int) c.size() || carry > 0; i++) {
			long long cur = (i<(int)c.size()?c[i]:0) + carry;
			res.dig.push_back((int) (cur % 100000));
			carry = (int) (cur / 100000);
		}
		res.dig = convert_base(res.dig, 5, digits);
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
    bool comp(bigint o, int order) {
        int ts = dig.size(), os = o.dig.size();
        // compare two bigints for one of the orders <=, <, >, >=, ==, identified
        // by an integer between 0 and 4, respectively.
        if (ts < os) return (order < 2);
        if (ts > os) return (order > 1 && order < 4);
        dforn (i, ts) {
            int exp = (base / 10), d1 = dig[i], d2 = o.dig[i];
            while (exp > 0) {
                int dec1 = d1 / exp, dec2 = d2 / exp;
                if (dec1 != dec2) {
                    if (order < 2) return dec1 < dec2;
                    if (order < 4) return dec1 > dec2;
                    return false;
                }
                d1 %= exp; d2 %= exp; exp /= 10;
            }
        }
        return (order == 0 || order == 3 || order == 4);
    }
    bool comp(int o, int order) {
        int ts = dig.size();
        if (ts == 0) return false;
        if (ts == 1) {
            switch (order) {
                case 0: return dig[0] <= o;
                case 1: return dig[0] < o;
                case 2: return dig[0] > o;
                case 3: return dig[0] >= o;
                case 4: return dig[0] == o;
            }
        }
        // e > 1
        if (order < 2) return false;
        if (order < 4) return true;
        return false;
    }
    bool operator<=(bigint o) {
        return comp(o, 0);
    }
    bool operator<=(int o) {
        return comp(o, 0);
    }
    bool operator<(bigint o) {
        return comp(o, 1);
    }
    bool operator<(int o) {
        return comp(o, 1);
    }
    bool operator>(bigint o) {
        return comp(o, 2);
    }
    bool operator>(int o) {
        return comp(o, 2);
    }
    bool operator>=(bigint o) {
        return comp(o, 3);
    }
    bool operator>=(int o) {
        return comp(o, 3);
    }
    bool operator==(bigint o) {
        return comp(o, 4);
    }
    bool operator==(int o) {
        return comp(o, 4);
    }
    bigint operator-(bigint o) {
        if (*this < o) return bigint(0);
        bigint res(dig);
        dforn (i, o.dig.size()) {
            int &d1 = res.dig[i], d2 = o.dig[i];
            if  (d1 >= d2) d1 = d1 - d2;
            else {
                int j = i+1; while (res.dig[j] == 0) j++;
                do {
                    res.dig[j]--;
                    res.dig[j-1] += base;
                    j--;
                } while (j > i);
                d1 = d1 - d2;
            }
        }
        res.remove_tz();
        return res;
    }
    pair<bigint, bigint> division(bigint o) {
        if (o == (bigint)0)
            throw runtime_error("Division by 0");
        if (*this == (bigint)0)
            return mp(0, 0);

        vector<int> div(dig.size(), 0), aux(dig.size(), 0);
        bigint resto = *this;
        int os = o.dig.size();
        
        while (o <= resto) {
            int rs = resto.dig.size();
            if (rs > os) {
                ll msd = (ll)resto.dig[rs-1] * base + resto.dig[rs-2];
                ll d   = msd / (o.dig[os-1] + 1);
                div[rs - os - 1] += d % base;
                div[rs - os]     += d / base;
                if (div[rs - os - 1] >= base) div[rs - os] += 1, div[rs - os - 1] -= base;
                if (div[rs - os] >= base) div[rs - os + 1] += 1, div[rs - os] -= base;
                // multiplicar o por (d * base^(rs-os-1))
                aux[rs - os - 1] = d % base;
                aux[rs - os]     = d / base;
                resto = resto - bigint(aux) * o;
                aux[rs - os - 1] = 0;
                aux[rs - os]     = 0;
            } else {
                int d;
                if (resto.dig[rs-1] == o.dig[os-1]) d = 1;
                else d = resto.dig[rs-1] / (o.dig[os-1] + 1);
                div[0] += d;
                if (div[0] >= base) div[1] += 1, div[0] -= base;
                resto = resto - (bigint) d * o;
            }
        }

        bigint i(div);
        i.remove_tz();
        return mp(i, resto);
    }
    bigint operator/(bigint o) {
        return this->division(o).first;
    }
    bigint operator%(bigint o) {
        return this->division(o).second;
    }
    void remove_tz() {
        int i; for (i=dig.size()-1; i>0 && dig[i]==0; i--);
        dig.resize(i + 1);
    }
    ull to_ull() {
        ull v = 0;
        dforn (i, dig.size()) {
            v += dig[i];
            v *= base;
        }
        return v;
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