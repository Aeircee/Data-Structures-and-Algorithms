#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        // 1. Factorize t for 2, 3, 5, 7
        int req2 = 0, req3 = 0, req5 = 0, req7 = 0;
        long long temp = t;
        while (temp % 2 == 0) { req2++; temp /= 2; }
        while (temp % 3 == 0) { req3++; temp /= 3; }
        while (temp % 5 == 0) { req5++; temp /= 5; }
        while (temp % 7 == 0) { req7++; temp /= 7; }

        // If there are other prime factors, it's impossible
        if (temp > 1) return "-1"; 

        // 2. Precompute DP for min digits needed for factors of 2 and 3
        int dp[47][30];
        for (int i = 0; i <= 46; i++) {
            for (int j = 0; j <= 29; j++) {
                dp[i][j] = 1e9;
            }
        }
        dp[0][0] = 0;
        for (int i = 0; i <= 46; i++) {
            for (int j = 0; j <= 29; j++) {
                if (i == 0 && j == 0) continue;
                int res = 1e9;
                res = min(res, 1 + dp[max(0, i - 1)][j]);             // digit 2
                res = min(res, 1 + dp[i][max(0, j - 1)]);             // digit 3
                res = min(res, 1 + dp[max(0, i - 2)][j]);             // digit 4
                res = min(res, 1 + dp[max(0, i - 1)][max(0, j - 1)]); // digit 6
                res = min(res, 1 + dp[max(0, i - 3)][j]);             // digit 8
                res = min(res, 1 + dp[i][max(0, j - 2)]);             // digit 9
                dp[i][j] = res;
            }
        }

        // Map values of prime factors for digits 1-9
        vector<int> v2(10, 0), v3(10, 0), v5(10, 0), v7(10, 0);
        v2[2] = 1; v3[3] = 1; v2[4] = 2; v5[5] = 1;
        v2[6] = 1; v3[6] = 1; v7[7] = 1; v2[8] = 3; v3[9] = 2;

        int n = num.length();
        int z_idx = -1;
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') {
                z_idx = i;
                break;
            }
        }

        // 3. Check if current num is already valid
        if (z_idx == -1) {
            int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
            for (char c : num) {
                int d = c - '0';
                c2 += v2[d]; c3 += v3[d]; c5 += v5[d]; c7 += v7[d];
            }
            if (c2 >= req2 && c3 >= req3 && c5 >= req5 && c7 >= req7) {
                return num;
            }
        }

        // Calculate prefix accumulative prime factors
        vector<int> pref2(n + 1, 0), pref3(n + 1, 0), pref5(n + 1, 0), pref7(n + 1, 0);
        for (int i = 0; i < n; i++) {
            int d = num[i] - '0';
            pref2[i + 1] = pref2[i] + v2[d];
            pref3[i + 1] = pref3[i] + v3[d];
            pref5[i + 1] = pref5[i] + v5[d];
            pref7[i + 1] = pref7[i] + v7[d];
        }

        // Helper lambda to construct the smallest valid suffix
        auto build = [&](int r2, int r3, int r5, int r7, int len) {
            string res = "";
            for (int step = 1; step <= len; step++) {
                for (int d = 1; d <= 9; d++) {
                    int nr2 = max(0, r2 - v2[d]);
                    int nr3 = max(0, r3 - v3[d]);
                    int nr5 = max(0, r5 - v5[d]);
                    int nr7 = max(0, r7 - v7[d]);
                    // Check if it's possible to satisfy remaining factors in remaining length
                    if (nr5 + nr7 + dp[nr2][nr3] <= len - step) {
                        res += (char)('0' + d);
                        r2 = nr2; r3 = nr3; r5 = nr5; r7 = nr7;
                        break;
                    }
                }
            }
            return res;
        };

        // 4. Find largest prefix we can keep
        int start_i = (z_idx == -1) ? n - 1 : z_idx;
        for (int i = start_i; i >= 0; i--) {
            int min_d = (num[i] - '0') + 1;
            for (int d = min_d; d <= 9; d++) {
                int r2 = max(0, req2 - pref2[i] - v2[d]);
                int r3 = max(0, req3 - pref3[i] - v3[d]);
                int r5 = max(0, req5 - pref5[i] - v5[d]);
                int r7 = max(0, req7 - pref7[i] - v7[d]);
                int rem_len = n - 1 - i;
                
                if (r5 + r7 + dp[r2][r3] <= rem_len) {
                    return num.substr(0, i) + (char)('0' + d) + build(r2, r3, r5, r7, rem_len);
                }
            }
        }

        // 5. If no in-place replacement is possible, expand length
        int needed = req5 + req7 + dp[req2][req3];
        int new_len = max(n + 1, needed);
        return build(req2, req3, req5, req7, new_len);
    }
};