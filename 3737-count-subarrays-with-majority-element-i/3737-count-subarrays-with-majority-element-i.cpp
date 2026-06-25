class Solution {
    class BIT {
    public:
        vector<int> bit;
        int n;

        BIT(int sz) {
            n = sz;
            bit.assign(n + 1, 0);
        }

        void update(int idx, int val) {
            while (idx <= n) {
                bit[idx] += val;
                idx += idx & -idx;
            }
        }

        int query(int idx) {
            int res = 0;
            while (idx > 0) {
                res += bit[idx];
                idx -= idx & -idx;
            }
            return res;
        }
    };

public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        BIT ft(2 * n + 5);

        int pref = n + 2;          // shift to avoid negative indices
        ft.update(pref, 1);

        long long ans = 0;

        for (int x : nums) {
            if (x == target)
                pref++;
            else
                pref--;

            ans += ft.query(pref - 1);
            ft.update(pref, 1);
        }

        return ans;
    }
};