/**
 * @brief 记忆化搜索（网格最长递增路）
 * @complexity O(RC)
 * @index 网格 0-based
 * @idea 只走向更大的四邻格，用显式栈模拟记忆化搜索。每格的答案只算一次，之后直接查表。
 * @usage longest_increasing_grid_path(a) 返回最长路径的点数。
 * @pitfall 网格为矩形，空网格返回 0。
 */
#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

inline int longest_increasing_grid_path(const vector<vector<int>> &a) {
    if (a.empty() || a[0].empty())
        return 0;
    int rows = (int)a.size(), cols = (int)a[0].size();
    vector memo(rows, vector<int>(cols));
    constexpr int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
    struct Frame {
        int x, y, next = 0;
    };
    vector<Frame> stack;
    int answer = 0;
    for (int x = 0; x < rows; x++)
        for (int y = 0; y < cols; y++) {
            if (!memo[x][y]) {
                memo[x][y] = 1;
                stack.push_back({x, y});
            }
            while (!stack.empty()) {
                auto &cur = stack.back();
                if (cur.next == 4) {
                    int best = memo[cur.x][cur.y];
                    stack.pop_back();
                    if (!stack.empty()) {
                        auto p = stack.back();
                        memo[p.x][p.y] = max(memo[p.x][p.y], best + 1);
                    }
                    continue;
                }
                int d = cur.next++, u = cur.x + dx[d], v = cur.y + dy[d];
                if (u < 0 || u >= rows || v < 0 || v >= cols ||
                    a[u][v] <= a[cur.x][cur.y])
                    continue;
                if (memo[u][v]) {
                    memo[cur.x][cur.y] = max(memo[cur.x][cur.y], memo[u][v] + 1);
                } else {
                    memo[u][v] = 1;
                    stack.push_back({u, v});
                }
            }
            answer = max(answer, memo[x][y]);
        }
    return answer;
}
