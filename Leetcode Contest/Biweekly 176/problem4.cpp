/*
    You are given an undirected tree with n nodes labeled 0 to n - 1. 
    This is represented by a 2D array edges of length n - 1, 
    where edges[i] = [ui, vi] indicates an undirected edge between nodes ui and vi.

    You are also given a string s of length n consisting of lowercase English letters, 
    where s[i] represents the character assigned to node i.

    You are also given a string array queries, where each queries[i] is either:

    "update ui c": Change the character at node ui to c. Formally, update s[ui] = c.
    "query ui vi": Determine whether the string formed by the characters on 
    the unique path from ui to vi (inclusive) can be rearranged into a palindrome.
    Return a boolean array answer, where answer[j] is true if the jth query of type 
    "query ui vi"​​​​​​​ can be rearranged into a palindrome, and false otherwise.

    A palindrome is a string that reads the same forward and backward.
    
    Example 1:
    Input: n = 3, edges = [[0,1],[1,2]], s = "aac", queries = ["query 0 2","update 1 b","query 0 2"]
    Output: [true,false]
    Explanation:
    "query 0 2": Path 0 → 1 → 2 gives "aac", which can be rearranged to form "aca", a palindrome. Thus, answer[0] = true.
    "update 1 b": Update node 1 to 'b', now s = "abc".
    "query 0 2": Path characters are "abc", which cannot be rearranged to form a palindrome. Thus, answer[1] = false.
    Thus, answer = [true, false].

    Example 2:
    Input: n = 4, edges = [[0,1],[0,2],[0,3]], s = "abca", 
    queries = ["query 1 2","update 0 b","query 2 3","update 3 a","query 1 3"]
    Output: [false,false,true]
    Explanation:
    "query 1 2": Path 1 → 0 → 2 gives "bac", which cannot be rearranged to form a palindrome. Thus, answer[0] = false.
    "update 0 b": Update node 0 to 'b', now s = "bbca".
    "query 2 3": Path 2 → 0 → 3 gives "cba", which cannot be rearranged to form a palindrome. Thus, answer[1] = false.
    "update 3 a": Update node 3 to 'a', s = "bbca".
    "query 1 3": Path 1 → 0 → 3 gives "bba", which can be rearranged to form "bab", a palindrome. Thus, answer[2] = true.
    Thus, answer = [false, false, true].

    Constraints:
        1 <= n == s.length <= 5 * 104
        edges.length == n - 1
        edges[i] = [ui, vi]
        0 <= ui, vi <= n - 1
        s consists of lowercase English letters.
        The input is generated such that edges represents a valid tree.
        1 <= queries.length <= 5 * 104​​​​​​​
        queries[i] = "update ui c" or
        queries[i] = "query ui vi"
        0 <= ui, vi <= n - 1
        c is a lowercase English letter.
*/

#include <iostream>
#include <vector>

using namespace std;

#define ll long long
#define mod 1000000007

class Solution {
public:
    int n;
    vector<vector<int>> adj;
    vector<int> parent, depth, heavy, head, pos, subtree;
    vector<int> base;
    int curPos;

    // -------- Segment Tree (XOR) --------
    struct SegTree {
        int n;
        vector<int> tree;

        SegTree(int n) : n(n) {
            tree.assign(4*n, 0);
        }

        void build(vector<int>& arr, int idx, int l, int r) {
            if (l == r) {
                tree[idx] = arr[l];
                return;
            }
            int mid = (l + r) / 2;
            build(arr, 2*idx, l, mid);
            build(arr, 2*idx+1, mid+1, r);
            tree[idx] = tree[2*idx] ^ tree[2*idx+1];
        }

        void update(int idx, int l, int r, int p, int val) {
            if (l == r) {
                tree[idx] = val;
                return;
            }
            int mid = (l + r) / 2;
            if (p <= mid)
                update(2*idx, l, mid, p, val);
            else
                update(2*idx+1, mid+1, r, p, val);

            tree[idx] = tree[2*idx] ^ tree[2*idx+1];
        }

        int query(int idx, int l, int r, int ql, int qr) {
            if (qr < l || r < ql) return 0;
            if (ql <= l && r <= qr) return tree[idx];
            int mid = (l + r) / 2;
            return query(2*idx, l, mid, ql, qr)
                 ^ query(2*idx+1, mid+1, r, ql, qr);
        }
    };

    // -------- Build HLD Iteratively --------
    void buildHLD(string &s) {
        parent.assign(n, -1);
        depth.assign(n, 0);
        heavy.assign(n, -1);
        subtree.assign(n, 0);

        // DFS iterative (avoid stack overflow)
        stack<int> st;
        vector<int> order;
        st.push(0);

        while (!st.empty()) {
            int v = st.top(); st.pop();
            order.push_back(v);

            for (int u : adj[v]) {
                if (u == parent[v]) continue;
                parent[u] = v;
                depth[u] = depth[v] + 1;
                st.push(u);
            }
        }

        // Post-order for subtree size
        for (int i = n-1; i >= 0; i--) {
            int v = order[i];
            subtree[v] = 1;
            int maxSize = 0;

            for (int u : adj[v]) {
                if (u == parent[v]) continue;
                subtree[v] += subtree[u];

                if (subtree[u] > maxSize) {
                    maxSize = subtree[u];
                    heavy[v] = u;
                }
            }
        }

        head.assign(n, 0);
        pos.assign(n, 0);
        base.assign(n, 0);
        curPos = 0;

        stack<pair<int,int>> st2;
        st2.push({0, 0});

        while (!st2.empty()) {
            auto [v, h] = st2.top();
            st2.pop();

            int curr = v;
            while (curr != -1) {
                head[curr] = h;
                pos[curr] = curPos;
                base[curPos++] = 1 << (s[curr] - 'a');

                for (int u : adj[curr]) {
                    if (u != parent[curr] && u != heavy[curr])
                        st2.push({u, u});
                }

                curr = heavy[curr];
            }
        }
    }

    int queryPath(int a, int b, SegTree &seg) {
        int res = 0;

        while (head[a] != head[b]) {
            if (depth[head[a]] < depth[head[b]])
                swap(a, b);

            res ^= seg.query(1, 0, n-1, pos[head[a]], pos[a]);
            a = parent[head[a]];
        }

        if (depth[a] > depth[b])
            swap(a, b);

        res ^= seg.query(1, 0, n-1, pos[a], pos[b]);
        return res;
    }

    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        this->n = n;
        adj.assign(n, {});
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        buildHLD(s);

        SegTree seg(n);
        seg.build(base, 1, 0, n-1);

        vector<bool> ans;

        for (auto &q : queries) {
            if (q[0] == 'u') {
                int u = 0;
                int i = 7;
                while (q[i] != ' ') {
                    u = u*10 + (q[i]-'0');
                    i++;
                }
                char c = q.back();

                s[u] = c;
                seg.update(1, 0, n-1, pos[u], 1 << (c - 'a'));
            }
            else {
                int u = 0, v = 0;
                int i = 6;

                while (q[i] != ' ') {
                    u = u*10 + (q[i]-'0');
                    i++;
                }
                i++;

                while (i < q.size()) {
                    v = v*10 + (q[i]-'0');
                    i++;
                }

                int mask = queryPath(u, v, seg);
                bool ok = (mask == 0) || ((mask & (mask-1)) == 0);
                ans.push_back(ok);
            }
        }

        return ans;
    }
};
