#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Eliminacion gaussiana en GF(2)
vector<long long> find_basis(vector<long long> nums) {
    sort(nums.begin(), nums.end(), greater<long long>());
    vector<long long> basis;
    for (long long num : nums) {
        long long x = num;
        for (long long b : basis) {
            x = min(x, x ^ b);
        }
        if (x > 0) {
            basis.push_back(x);
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
    for (int i = 0; i < n; ++i) {
        gifts[i] ^= (x&gifts[i]);
    }

    vector<long long> basis = find_basis(gifts);
    int basis_size = basis.size();

    long long x1 = 0;
    for (int i = 0; i < basis_size; ++i) {
        if ((x1>>msb(basis[i]))&1) continue;
        x1 ^= basis[i];
    }
    
    cout << x + 2*x1 << endl;

    return 0;
}