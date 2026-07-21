class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        int ans = 0, mx = 0, pre = INT_MIN;

        for (int i = 0; i < s.size();) {
            int j = i;
            while (j < s.size() && s[j] == s[i]) j++;
            int len = j - i;

            if (s[i] == '1') {
                ans += len;
            } else {
                mx = max(mx, pre + len);
                pre = len;
            }

            i = j;
        }

        return ans + mx;
    }
};