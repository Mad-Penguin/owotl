/**
 * Author: Diego Garcia
 * Date: 2022-04-01
 * License: ???
 * Source: Folklore
 * Description: Interpolates polynomial P at x assuming sample = {P(1)...P(N)} and P has deg < n
 * Time: $O(N)$. Change mints to ints and care for modulo when using.
 * Status: Tested
 */
 mint interpolate(vector<mint> &sample, mint x) {
    int n = sz(sample);
    mint fac = fact[n - 1];
    vector<mint> pref(n), suf(n);
    pref[0] = mint(1);
    for(int i = 2; i <= n; i++) {
        pref[i - 1] = pref[i - 2] * (x - (i - 1));
    }
    suf[n - 1] = mint(1);
    for(int i = n - 2; i >= 0; i--)
        suf[i] = suf[i + 1] * (x - (i + 2));
    mint ans = 0;
    for(int i = 1; i <= n; i++) {
        mint term = invfact[i - 1] * invfact[n - i];
        if((n - i) % 2 == 1)
            term = term * mint(-1);
        term *= pref[i - 1] * suf[i - 1] * sample[i - 1];
        ans += term;
    }
    return ans;
}
