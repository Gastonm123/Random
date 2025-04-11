#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<long long> find_basis(const vector<long long>& nums) {
    vector<long long> basis;
    for (long long num : nums) {
        long long x = num;
        for (long long b : basis) {
            x = min(x, x ^ b);
        }
        if (x > 0) {
            basis.push_back(x);
            sort(basis.begin(), basis.end(), greater<long long>());
        }
    }
    return basis;
}

int msb(long long x) { // -1 si x = 0
    return 63-__builtin_clzll(x);
}

int main() {
    int n;
    cin >> n;

    vector<long long> gifts(n);
    long long x = 0;
    for (int i = 0; i < n; ++i) {
        cin >> gifts[i];
        x ^= gifts[i];
    }

    vector<long long> basis = find_basis(gifts);
    int basis_size = basis.size();

    long long max_sum = 0;
    long long x1 = 0;

    for (int i = 0; i < basis_size; ++i) {
        if ((x1>>msb(basis[i]))&1) continue;
        x1 ^= basis[i];
    }

    cout << (x^x1)+x1 << endl;

    return 0;
}