/**
 * @brief PQ 树（连续区间约束）
 * @complexity 每条约束期望 O(n + k)，k 是输入组长度
 * @index 元素 0 到 n - 1
 * @idea P 节点儿子可重排，Q 节点只可整体反向。每次把选中元素收成一块，非根的混合子树要把选中块贴到端点。
 * @usage PQTree t(n); t.constrain(group) 要求 group 连续，成功返回 true。t.frontier() 取一个可行排列。
 * @pitfall 同一组可重复给出元素。失败时保留先前约束。此版每次扫描整树，适合中小规模。
 */
#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class PQTree {
    enum Kind { leaf, p_node, q_node };
    struct Node;
    using Ptr = shared_ptr<const Node>;
    struct Node {
        Kind kind;
        int id, size;
        vector<Ptr> children;
    };

    Ptr root;
    int n;

    // 深链不能靠 shared_ptr 的递归析构释放。
    static void release(Ptr old) {
        vector<Ptr> pending;
        if (old)
            pending.push_back(move(old));
        while (!pending.empty()) {
            auto u = move(pending.back());
            pending.pop_back();
            if (u.use_count() == 1)
                pending.insert(pending.end(), u->children.begin(),
                               u->children.end());
        }
    }

    static Ptr make(Kind kind, vector<Ptr> children) {
        if (children.empty())
            return {};
        if (children.size() == 1)
            return children.front();
        int size = 0;
        for (const auto &u : children)
            size += u->size;
        return make_shared<Node>(Node{kind, -1, size, move(children)});
    }

    struct Reduction {
        enum State { empty, mixed, full };
        using Strip = list<Ptr>;
        unordered_map<const Node *, int> chosen;

        int count(const Ptr &u, const vector<bool> &marked) {
            vector<Ptr> order{u};
            for (size_t i = 0; i < order.size(); i++) {
                auto v = order[i];
                order.insert(order.end(), v->children.begin(), v->children.end());
            }
            for (auto it = order.rbegin(); it != order.rend(); ++it) {
                const auto &v = *it;
                int answer = v->kind == leaf ? marked[v->id] : 0;
                for (const auto &child : v->children)
                    answer += chosen.at(child.get());
                chosen.emplace(v.get(), answer);
            }
            return chosen.at(u.get());
        }

        State state(const Ptr &u) const {
            int selected = chosen.at(u.get());
            if (!selected)
                return empty;
            return selected == u->size ? full : mixed;
        }

        // 返回从空侧到满侧的有序条带，供父节点拼接。
        optional<Strip> boundary(Ptr u) const {
            Strip result, suffix;
            while (u) {
                Strip before, after;
                Ptr partial;
                if (u->kind == p_node) {
                    vector<Ptr> unselected, selected;
                    for (const auto &v : u->children) {
                        State s = state(v);
                        if (s == empty)
                            unselected.push_back(v);
                        else if (s == full)
                            selected.push_back(v);
                        else if (partial)
                            return nullopt;
                        else
                            partial = v;
                    }
                    if (auto group = make(p_node, move(unselected)))
                        before.push_back(group);
                    if (auto group = make(p_node, move(selected)))
                        after.push_back(group);
                } else {
                    auto order = u->children;
                    auto fits = [&] {
                        State last = empty;
                        for (const auto &v : order) {
                            State s = state(v);
                            if (s < last || (s == mixed && last == mixed))
                                return false;
                            last = s;
                        }
                        return true;
                    };
                    if (!fits()) {
                        reverse(order.begin(), order.end());
                        if (!fits())
                            return nullopt;
                    }
                    for (const auto &v : order) {
                        if (state(v) == mixed)
                            partial = v;
                        else
                            (partial ? after : before).push_back(v);
                    }
                }
                result.splice(result.end(), before);
                suffix.splice(suffix.begin(), after);
                u = move(partial);
            }
            result.splice(result.end(), suffix);
            return result;
        }

        Ptr reduce_here(const Ptr &u) const {
            int total = chosen.at(u.get());
            if (total == 0 || total == u->size)
                return u;
            auto children = u->children;
            if (u->kind == p_node) {
                vector<Ptr> outside, inside, partial;
                for (const auto &v : children) {
                    State s = state(v);
                    if (s == empty)
                        outside.push_back(v);
                    else if (s == full)
                        inside.push_back(v);
                    else
                        partial.push_back(v);
                }
                if (partial.size() > 2)
                    return {};
                Strip block;
                if (!partial.empty()) {
                    auto left = boundary(partial.front());
                    if (!left)
                        return {};
                    block.splice(block.end(), *left);
                }
                if (auto group = make(p_node, move(inside)))
                    block.push_back(group);
                if (partial.size() == 2) {
                    auto right = boundary(partial.back());
                    if (!right)
                        return {};
                    right->reverse();
                    block.splice(block.end(), *right);
                }
                outside.push_back(make(q_node, {block.begin(), block.end()}));
                return make(p_node, move(outside));
            }

            int l = 0, r = (int)children.size() - 1;
            while (state(children[l]) == empty)
                l++;
            while (state(children[r]) == empty)
                r--;
            Strip order;
            for (int i = 0; i < (int)children.size(); i++) {
                const auto &v = children[i];
                State s = state(v);
                if (i < l || i > r || s == full) {
                    order.push_back(v);
                } else {
                    if (s == empty || (i != l && i != r))
                        return {};
                    auto side = boundary(v);
                    if (!side)
                        return {};
                    if (i == r)
                        side->reverse();
                    order.splice(order.end(), *side);
                }
            }
            return make(q_node, {order.begin(), order.end()});
        }

        Ptr reduce(Ptr u) const {
            vector<pair<Ptr, int>> path;
            while (true) {
                int total = chosen.at(u.get()), next = -1;
                if (!total || total == u->size)
                    break;
                for (int i = 0; i < (int)u->children.size(); i++)
                    if (chosen.at(u->children[i].get()) == total) {
                        next = i;
                        break;
                    }
                if (next == -1)
                    break;
                path.emplace_back(u, next);
                u = u->children[next];
            }
            auto answer = reduce_here(u);
            if (!answer)
                return {};
            for (auto it = path.rbegin(); it != path.rend(); ++it) {
                auto [parent, child] = *it;
                auto children = parent->children;
                children[child] = move(answer);
                answer = make(parent->kind, move(children));
            }
            return answer;
        }
    };

  public:
    explicit PQTree(int n) : n(n) {
        vector<Ptr> elements;
        for (int i = 0; i < n; i++)
            elements.push_back(make_shared<Node>(Node{leaf, i, 1, {}}));
        root = make(p_node, move(elements));
    }

    PQTree(const PQTree &) = default;
    PQTree(PQTree &&) noexcept = default;
    PQTree &operator=(PQTree other) {
        swap(root, other.root);
        swap(n, other.n);
        return *this;
    }
    ~PQTree() { release(move(root)); }

    bool constrain(const vector<int> &group) {
        if (!root)
            return group.empty();
        vector<bool> marked(n);
        for (int u : group) {
            assert(0 <= u && u < n);
            marked[u] = true;
        }
        Reduction work;
        work.count(root, marked);
        auto next = work.reduce(root);
        if (!next)
            return false;
        root.swap(next);
        release(move(next));
        return true;
    }

    vector<int> frontier() const {
        vector<int> result;
        vector<Ptr> pending;
        if (root)
            pending.push_back(root);
        while (!pending.empty()) {
            auto u = move(pending.back());
            pending.pop_back();
            if (u->kind == leaf) {
                result.push_back(u->id);
            } else {
                pending.insert(pending.end(), u->children.rbegin(),
                               u->children.rend());
            }
        }
        return result;
    }
};
