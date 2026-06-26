class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {

        string &s = strs[0];

        for(int i = 0; i < s.size(); i++) {

            char c = s[i];

            for(int j = 1; j < strs.size(); j++) {

                if(i >= strs[j].size() || strs[j][i] != c)
                    return s.substr(0, i);
            }
        }

        return s;
    }
};