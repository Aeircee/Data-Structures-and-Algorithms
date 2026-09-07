class Solution {
public:
    int distinctSubseqII(string s) {
        const long long MOD = 1e9 + 7;

        long long dp = 1;  // includes empty subsequence
        long long last[26] = {};

        for (char c : s) {
            int idx = c - 'a';

            long long newDp = (2 * dp) % MOD;

            // Remove duplicates created by the previous occurrence of c
            newDp = (newDp - last[idx] + MOD) % MOD;

            // For future occurrences of c
            last[idx] = dp;

            dp = newDp;
        }

        return (dp - 1 + MOD) % MOD; // remove empty subsequence
    }
};