class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int,int> mp;

        for(auto &x:reservedSeats)
            if(x[1]>=2 && x[1]<=9)
                mp[x[0]] |= 1<<(x[1]-2);

        long long ans=2LL*(n-mp.size());

        for(auto &[row,mask]:mp) {
            bool left  = !(mask&15);
            bool mid   = !(mask&60);
            bool right = !(mask&240);

            if(left&&right) ans+=2;
            else if(left||mid||right) ans++;
        }

        return ans;
    }
};