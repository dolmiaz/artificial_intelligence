#include <iostream>
#include <bits/stdc++.h>
#include <set>
#include <random>
using namespace std;

// ============== 基本型 ==============
using ll = long long;
using ull = unsigned long long;
using ld = long double;
template <typename T> using V = vector<T>;
template <typename T> using minpq = priority_queue<T, V<T>, greater<T>>;
using maxpq_ll = priority_queue<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

// ============== 定数 ==============
constexpr double PI = 3.141592653589793238L;
constexpr int INF = 1073741823;
constexpr ll INF_L = (1LL << 60);
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
int modNum = 998244353;

// ============== マクロ ==============
#define rep(i, n) for (int i = 0; i < n; i++)
#define rep1(i, n) for (int i = 1; i <= n; i++)
#define rrep(i, n) for (int i = n - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = n; i >= 1; i--)
#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)

// ============== ユーティリティ ==============
template <class T, class U> bool chmin(T &a, const U &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <class T, class U> bool chmax(T &a, const U &b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template <class T> T clampv(T x, T lo, T hi) { return x < lo ? lo : (x > hi ? hi : x); }
template <class T> T ceil_div(T a, T b) {
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return (a + b - 1) / b;
    return a / b;
}
template <class T> T floor_div(T a, T b) {
    if (b < 0)
        a = -a, b = -b;
    if (a >= 0)
        return a / b;
    return (a - (b - 1)) / b;
}

// ============== printヘルパ ==============
template <class T> void print_one(const T &x) { cout << x; }
template <class T, class... Ts> void print_one(const T &x, const Ts &...xs) {
    cout << x << ' ';
    print_one(xs...);
}
template <class... Ts> void println(const Ts &...xs) {
    print_one(xs...);
    cout << '\n';
}
template <class T> void printAll(const V<T> &t) {
    rep(i, t.size()) cout << t[i] << endl;
}
inline void yes(const bool c = true) { cout << (c ? "Yes" : "No") << '\n'; }
inline void YES(const bool c = true) { cout << (c ? "YES" : "NO") << '\n'; }

// ============== 数学ヘルパ ==============
// Sum of 0...(x-1)
template <class T> T tri0(T x) {
    return x * (x - 1) / 2;
}
// Sum of 1...x
template <class T> T tri1(T x) {
    return (x + 1) * x / 2;
}
// ============== 再帰ラムダ ==============
template <class F> struct y_combinator {
    F f;
    template <class... Args> decltype(auto) operator()(Args &&...args) const {
        return f(*this, std::forward<Args>(args)...);
    }
};
template <class F> y_combinator<F> yc(F &&f) { return {std::forward<F>(f)}; }

// ============== 累積和 ==============
// 1D --- 0, s[1], s[2], ...型
template <class T> V<T> prefix_sum_1d(const V<T> &vec) {
    const int n = static_cast<int>(vec.size());
    V<T> ps(n + 1, 0);
    rep(i, n) ps[i + 1] = ps[i] + vec[i];

    return ps;
}
// 2D
// 0 0       0       ...
// 0 s[1][1] s[1][2] ...
// 0 s[2][1] s[2][2] ...
// . ...     ...
template <class T> V<V<T>> prefix_sum_2d(const V<V<T>> &grid) {
    const int n = static_cast<int>(grid.size());
    if (n == 0) return V<V<T>>(1, V<T>(1, T{}));

    const int m = static_cast<int>(grid[0].size());
    V<V<T>> ps(n + 1, V<T>(m + 1, T{}));

    rep(i, n) ps[i + 1] = prefix_sum_1d(grid[i]);
    rep(i, n) {
        rep(j, m + 1) ps[i + 1][j] += ps[i][j];
    }

    return ps;
}
// 累積MAX
// A[0], A[1], A[2], ..., A[N - 1]
// lowest, L[0], L[1], L[2], ..., L[N - 1], lowest
// lowest, R[0], R[1], R[2], ..., R[N - 1], lowest
template <class T> struct Prefix_Max_Info {
    V<T> L, R;
};
template <class T> Prefix_Max_Info<T> prefix_max_1d(const V<T> &vec) {
    const int n = static_cast<int>(vec.size());
    Prefix_Max_Info<T> info;
    info.L.assign(n + 2, numeric_limits<T>::lowest());
    info.R.assign(n + 2, numeric_limits<T>::lowest());
    rep(i, n) info.L[i + 1] = max(info.L[i], vec[i]);
    rrep(i, n) info.R[i + 1] = max(info.R[i + 2], vec[i]);
    return info;
}
// ============== 二分探索 ==============
// return -> 0-indexed
template <class T, class F> int binary_search_index(const V<F> &vec, T x) {
    int pos = lower_bound(all(vec), x) - vec.begin();
    if (pos < static_cast<int>(vec.size()) && vec[pos] == x) return pos;
    return -1;
}
template <class T> int lower_bound_index(const V<T>& vec, int l, int r, T x) {
    auto it = lower_bound(vec.begin() + l, vec.begin() + r + 1, x);
    if (it == vec.begin() + r + 1) return -1;
    return static_cast<int>(it - vec.begin());
}
template <class T> int last_less_index(const V<T>& vec, int l, int r, T x) {
    auto it = lower_bound(vec.begin() + l, vec.begin() + r + 1, x);
    if (it == vec.begin() + l) return -1;
    --it;
    return static_cast<int>(it - vec.begin());
}
template <class T> int upper_bound_index(const V<T>& vec, int l, int r, T x) {
    auto it = upper_bound(vec.begin() + l, vec.begin() + r + 1, x);
    if (it == vec.begin() + r + 1) return -1;
    return static_cast<int>(it - vec.begin());
}
template <class T>
int last_greater_index(const V<T>& vec, int l, int r, const T& x) {
    if (upper_bound(vec.begin() + l, vec.begin() + r + 1, x) == vec.begin() + r + 1) return -1;
    return r;
}
template <class T, class F> T binary_search_min(T ok, T ng, F pred) {
    while (abs(ok - ng) > 1) {
        T mid = ng + (ok - ng) / 2;
        if (pred(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
template <class T, class F> T binary_search_max(T ok, T ng, F pred) {
    while (abs(ng - ok) > 1) {
        T mid = ok + (ng - ok) / 2;
        if (pred(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
// ============== DPテンプレ ==============

// ============== グラフテンプレ ==============
struct Edge {
    int to;
    ll w;
    Edge() : to{0}, w{1} {};
    Edge(int _to, ll _w): to{_to}, w(_w) {};
};
using Graph = V<V<Edge>>;
void add_edge(Graph &g, int a, int b, ll w = 1, bool undirected = true) {
    g[a].emplace_back(b, w);
    if (undirected) {
        g[b].emplace_back(a, w);
    }
};
Graph read_graph(int n, int m, bool undirected = true, bool weighted = false, bool one_indexed = true) {
    Graph g(n);
    int a, b;
    ll w = 1;
    rep(_, m) {
        if (weighted) {
            cin >> a >> b >> w;
        } else {
            cin >> a >> b;
        }
        if (one_indexed) {
            a--;
            b--;
        }
        add_edge(g, a, b, w, undirected);
    }
    return g;
}

// ============== グラフアルゴリズム ==============
// DFS
struct DFS_Info {
    V<int> used, parent, tin, tout, comp_id, order;
    int comp_cnt = 0, timer = 0;
};
DFS_Info dfs_all(const Graph &g) {
    DFS_Info info;
    int n = static_cast<int>(g.size());
    info.used.assign(n, 0);
    info.parent.assign(n, -1);
    info.tin.assign(n, -1);
    info.tout.assign(n, -1);
    info.comp_id.assign(n, -1);
    info.order.reserve(n);

    auto dfs = yc([&](auto self, int v, int p) -> void {
        info.used[v] = 1;
        info.parent[v] = p;
        info.tin[v] = info.timer++;
        info.comp_id[v] = info.comp_cnt;
        info.order.push_back(v);
        for (auto e : g[v]) {
            if (info.used[e.to]) continue;
            self(e.to, v);
        }
        info.tout[v] = ++info.timer;
    });
    for (int v = 0; v < n; v++) {
        if (info.used[v]) continue;
        dfs(v, -1);
        info.comp_cnt++;
    }
    return info;
}
// BFS
struct BFS_Info {
    V<int> used, parent, dist, comp_id, order;
    int comp_cnt = 0;
};
BFS_Info bfs_all(const Graph &g) {
    BFS_Info info;
    int n = static_cast<int>(g.size());
    info.used.assign(n, 0);
    info.parent.assign(n, -1);
    info.dist.assign(n, -1);
    info.comp_id.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    for (int v = 0; v < n; v++) {
        if (info.used[v]) continue;

        q.push(v);
        info.used[v] = 1;
        info.dist[v] = 0;
        info.comp_id[v] = info.comp_cnt;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            info.order.push_back(u);

            for (auto e : g[u]) {
                if (info.used[e.to]) continue;

                info.used[e.to] = 1;
                info.parent[e.to] = u;
                info.dist[e.to] = info.dist[u] + 1;
                info.comp_id[e.to] = info.comp_cnt;
                q.push(e.to);
            }
        }
        info.comp_cnt++;
    }
    return info;
}

// ============== 解答用 ==============
#ifndef MULTI_TEST_CASES
#define MULTI_TEST_CASES 0
#endif

void solve() {

}

int main() {
#if MULTI_TEST_CASES
    int T;
    if (!(cin >> T))
        return 0;
    while (T--)
        solve();
#else
    solve();
#endif
    return 0;
}
