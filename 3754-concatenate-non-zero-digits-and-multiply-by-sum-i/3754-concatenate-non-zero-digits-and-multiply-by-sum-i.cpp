class Solution {
public:
    long long sumAndMultiply(int n) {
        if (n == 0) return 0;

        long long x = 0;
        int sum = 0;

        long long p = 1;
        int t = n;

        while (t) {
            int d = t % 10;
            if (d) {
                x += 1LL * d * p;
                sum += d;
                p *= 10;
            }
            t /= 10;
        }

        return x * sum;
    }
};