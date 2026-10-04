class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();

        // Pass 1: left se right, '*' ko '(' maano
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '(' || s[i] == '*') {
                count++;
            } else {
                count--;
            }
            if (count < 0) return false; // zyada ')' aa gaye
        }

        // Pass 2: right se left, '*' ko ')' maano
        count = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == ')' || s[i] == '*') {
                count++;
            } else {
                count--;
            }
            if (count < 0) return false; // zyada '(' aa gaye
        }

        return true;
    }
};