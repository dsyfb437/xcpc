线段树把区间递归划分成若干层，每个结点维护一个区间的信息。它能高效支持区间查询和区间修改。

如果父结点的信息可以由两个子结点合并得到，就可以用线段树维护这类可合并的信息。

## 单点修改与区间查询

```cpp
struct SegmentTree {
    int n;
    std::vector<long long> tree;

    explicit SegmentTree(const std::vector<int>& values)
        : n(static_cast<int>(values.size())), tree(4 * n, 0) {
        build(1, 0, n - 1, values);
    }

    void build(int node, int left, int right,
               const std::vector<int>& values) {
        if (left == right) {
            tree[node] = values[left];
            return;
        }
        int middle = (left + right) / 2;
        build(node * 2, left, middle, values);
        build(node * 2 + 1, middle + 1, right, values);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }
};
```

## 复杂度

单次操作的递归树高度是 $O(\log n)$，所以：

- 单点修改：$O(\log n)$
- 区间查询：$O(\log n)$
- 建树：$O(n)$

> 数组通常开到 `4n`，这是最简单的完全二叉树下标表示方法。
