#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

/*
SOLUTION

use a markov chain; S_k = neither 6 or 7, T_k = 6 but no 7, U_k = 6 and 7, all are after exactly k steps
[9  8  0 ] [S_k] = [S_{k+1}]
[1  1  1 ] [T_k] = [T_{k+1}]
[0  1  10] [U_k] = [U_{k+1}]

at the beginning (k=0), S_k = 1 and T_k = U_k = 0
use matrix exp to compute this to a high power and get U_N
*/

vector<vector<ll>> multiply(vector<vector<ll>> a, vector<vector<ll>> b) {
    ll p = a.size(), q = b.size(), r = b[0].size();
    assert(a[0].size() == q);

    vector<vector<ll>> c(p, vector<ll>(r, 0));
    for (ll i = 0; i < p; i++) {
        for (ll j = 0; j < q; j++) {
            for (ll k = 0; k < r; k++) {
                c[i][k] += a[i][j] * b[j][k];
                c[i][k] %= MOD;
            }
        }
    }
    return c;
}

vector<vector<ll>> mat_pow(vector<vector<ll>> a, ll b) {
    vector<vector<ll>> ans(a.size(), vector<ll>(a.size(), 0));
    for (ll i = 0; i < a.size(); i++) ans[i][i] = 1;
    vector<vector<ll>> temp = a;

    while (b) {
        if (b & 1) ans = multiply(ans, temp);
        b >>= 1;
        temp = multiply(temp, temp);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N;
    cin >> N;
    vector<vector<ll>> magic = {{9, 8, 0}, {1, 1, 0}, {0, 1, 10}};
    magic = mat_pow(magic, N);
    cout << magic[2][0] << endl;

    return 0;
}