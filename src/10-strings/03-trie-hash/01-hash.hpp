/**
 * @brief 字符串哈希
 * @complexity 预处理 O(n)，查询 O(1)
 * @index 字符串下标 0-based，区间 [l,r)
 * @idea 双模数滚动哈希，字节按 0 到 255 编号后加 1，避免零字节没有贡献。
 * @usage Hash h(s); h.sub(l,r) 返回子串的哈希对。
 * @pitfall 比子串时先比长度。哈希相同仍可能碰撞，固定底数也可能被构造数据卡。
 *          需要确定相等时，再比较原串。
 *
 * 例：
 *   Hash h(s);
 *   bool same_length = r1 - l1 == r2 - l2;
 *   bool same_hash = h.sub(l1, r1) == h.sub(l2, r2);
 *   // 两者都为真时，两段大概率相等。
 */
#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Hash {
    static constexpr ll M1 = 1000000007, M2 = 1000000009;
    static constexpr ll B1 = 911382323, B2 = 972663749;

    vector<ll> h1, h2, p1, p2;

    explicit Hash(const string &s) {
        int n = s.size();
        h1.assign(n + 1, 0), h2.assign(n + 1, 0);
        p1.assign(n + 1, 1), p2.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            int ch = (unsigned char)s[i] + 1;
            h1[i + 1] = (h1[i] * B1 + ch) % M1;
            h2[i + 1] = (h2[i] * B2 + ch) % M2;
            p1[i + 1] = p1[i] * B1 % M1;
            p2[i + 1] = p2[i] * B2 % M2;
        }
    }

    pair<ll, ll> sub(int l, int r) const { // s[l..r)
        ll a = (h1[r] - h1[l] * p1[r - l] % M1 + M1) % M1;
        ll b = (h2[r] - h2[l] * p2[r - l] % M2 + M2) % M2;
        return {a, b};
    }
};
