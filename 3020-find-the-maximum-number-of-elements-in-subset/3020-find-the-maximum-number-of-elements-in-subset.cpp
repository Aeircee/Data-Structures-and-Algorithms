class Solution {
public:
    int maximumLength(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());

        unordered_map<int, int> cnt;
        for (int x : nums)
            ++cnt[x];

        int ans = cnt.count(1) ? cnt[1] - (cnt[1] % 2 == 0) : 1;

        for (int num : nums) {
            if (num == 1) continue;

            int len = 0;
            long long x = num;

            while (x <= maxNum && cnt.count((int)x) && cnt[(int)x] >= 2) {
                len += 2;
                x *= x;
            }

            ans = max(ans, len + (x <= maxNum && cnt.count((int)x) ? 1 : -1));
        }

        return ans;
    }
};