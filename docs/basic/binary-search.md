二分查找用于在有序序列中寻找目标值。每次根据中间位置的结果舍弃一半搜索区间，因此时间复杂度为 $O(\log n)$。

> **前提条件：** 二分的对象必须具有单调性。对无序序列直接二分，通常会得到错误结果。

## 整数二分模板

```cpp
int lower_bound_index(const std::vector<int>& a, int target) {
    int left = 0, right = static_cast<int>(a.size());
    while (left < right) {
        int middle = left + (right - left) / 2;
        if (a[middle] < target) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}
```

## 判定条件

设判定函数为 `check(x)`。如果存在一个分界点，使分界点一侧恒为真、另一侧恒为假，就可以用它来缩小答案区间：

$$
\begin{cases}
\text{check}(x)=\text{true}, & x < p,\\
\text{check}(x)=\text{false}, & x \ge p.
\end{cases}
$$

## 常见易错点

- 区间是左闭右开还是闭区间，需要从头到尾保持一致。
- 计算 `middle` 时优先写成 `left + (right - left) / 2`。
- 更新边界后必须确认区间确实缩小，避免死循环。

| 写法 | 区间含义 | 返回位置 |
| --- | --- | --- |
| `[left, right)` | 左闭右开 | 第一个满足条件的位置 |
| `[left, right]` | 闭区间 | 需要明确收敛条件 |
