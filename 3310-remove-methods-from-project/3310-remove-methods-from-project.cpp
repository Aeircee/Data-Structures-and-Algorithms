class Solution {
public:
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n), rev(n);

        for (auto &e : invocations) {
            adj[e[0]].push_back(e[1]);
            rev[e[1]].push_back(e[0]);
        }

        vector<int> suspicious(n, 0);

        function<void(int)> dfs = [&](int u) {
            suspicious[u] = 1;
            for (int v : adj[u]) {
                if (!suspicious[v])
                    dfs(v);
            }
        };

        dfs(k);

        for (int i = 0; i < n; i++) {
            if (!suspicious[i]) {
                for (int v : adj[i]) {
                    if (suspicious[v]) {
                        vector<int> ans;
                        for (int j = 0; j < n; j++)
                            ans.push_back(j);
                        return ans;
                    }
                }
            }
        }

        vector<int> ans;
        for (int i = 0; i < n; i++) {
            if (!suspicious[i])
                ans.push_back(i);
        }

        return ans;
    }
};