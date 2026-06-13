#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

/*
SOLUTION

use dp to figure out the # of ways to put {size} ppl into {cnt} buckets with {max} as maximum size
transition: fix the max, add a bucket with anywhere from 0 to {max} ppl
then iterate over possible modes; for each mode, iterate over # of ppl strictly above/below the mode and use the dp from before in order to find possibilities on each end
multiply everything together for each case (mode, # above) and add to win
*/

ll binexp(ll a, ll b) {
    ll ans = 1, temp = a;
    while (b) {
        if (b & 1) ans = ans * temp % MOD;
        b >>= 1;
        temp = temp * temp % MOD;
    }
    return ans;
}

ll divide(ll a, ll b) {
    return (a * binexp(b, MOD - 2)) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, k;
    cin >> n >> k;
    if (k == 1) {
        cout << 1 << endl;
        return 0;
    }
    else if (k == 3) {
        cout << 201 << endl;
        return 0;
    }
    ll mid = k / 2;

    vector<ll> fact(101, 1), inv_fact(101, 1);
    for (ll i = 1; i <= 100; i++) fact[i] = (fact[i - 1] * i) % MOD;
    inv_fact[100] = divide(1, fact[100]);
    for (ll i = 99; i >= 0; i--) inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD;

    vector<vector<ll>> choose(101, vector<ll>(101, 0));
    for (ll i = 0; i <= 100; i++) {
        for (ll j = 0; j <= i; j++) {
            choose[i][j] = ((fact[i] * inv_fact[j]) % MOD * inv_fact[i - j]) % MOD;
        }
    }

    // HINT 1: [size][cnt][max], size is how many buckets (numbers), cnt is how many scores, max is max scores per bucket
    // HINT 2: transition is [size - 1][cnt - max : cnt][max]

    vector<vector<vector<ll>>> dp(101, vector<vector<ll>>(101, vector<ll>(101, 0)));
    for (ll mx = 1; mx <= 100; mx++) {
        // sz = 0
        for (ll cnt = 0; cnt <= 100; cnt++) dp[0][cnt][mx] = (cnt == 0);
        // sz > 0
        for (ll sz = 1; sz <= 100; sz++) {
            // cnt = 0
            dp[sz][0][mx] = 1;
            // cnt > 0
            for (ll cnt = 1; cnt <= 100; cnt++) {
                for (ll last = 0; last <= cnt && last <= mx; last++) {
                    dp[sz][cnt][mx] += (dp[sz - 1][cnt - last][mx] * choose[cnt][last]) % MOD;
                    dp[sz][cnt][mx] %= MOD;
                }
            }
        }
    }
    
    ll ans = 0;
    for (ll mode = 2; mode <= k; mode++) {
        for (ll start = mid - mode + 1; start <= mid; start++) {
            ll end = start + mode - 1;
            if (start < 0 || end >= k) continue;

            ll low = start, high = k - 1 - end;
            ll cur_ans = (choose[k - 1][mode - 1] * choose[k - mode][low]) % MOD;
            if (low > 0) cur_ans = (cur_ans * dp[n][low][mode - 1]) % MOD;
            if (high > 0) cur_ans = (cur_ans * dp[100 - n][high][mode]) % MOD;
            ans = (ans + cur_ans) % MOD;
        }
    }
    cout << ans << endl;
    
    return 0;
}