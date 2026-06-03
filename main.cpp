#include <iostream>
#include <bits/stdc++.h>
#include <set>
#include <random>
#include <unordered_set>
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
constexpr ld PI = 3.141592653589793238L;
constexpr int INF = 1073741823;
constexpr ll INF_L = (1LL << 60);
constexpr double INF_D = 1e100;
const string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string abc = "abcdefghijklmnopqrstuvwxyz";
constexpr ll modNum = 998244353;

// ============== マクロ ==============
#define rep(i, n) for (int i = 0, i##_n = static_cast<int>(n); i < i##_n; i++)
#define rep1(i, n) for (int i = 1, i##_n = static_cast<int>(n); i <= i##_n; i++)
#define rrep(i, n) for (int i = static_cast<int>(n) - 1; i >= 0; i--)
#define rrep1(i, n) for (int i = static_cast<int>(n); i >= 1; i--)
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

// ============== グリッド方向 ==============
inline constexpr array<int, 4> DR4 = {-1, 1, 0, 0};
inline constexpr array<int, 4> DC4 = {0, 0, 1, -1};
inline constexpr array<char, 4> DIR4 = {'U', 'D', 'R', 'L'};
inline constexpr array<char, 4> dir4 = {'u', 'd', 'r', 'l'};
inline constexpr array<int, 8> DR8 = {-1, 1, 0, 0, -1, -1, 1, 1};
inline constexpr array<int, 8> DC8 = {0, 0, 1, -1, 1, -1, 1, -1};
inline const array<string, 8> DIR8 = {"U", "D", "R", "L", "UR", "UL", "DR", "DL"};
inline const array<string, 8> dir8 = {"u", "d", "r", "l", "ur", "ul", "dr", "dl"};
// ============== printヘルパ ==============
template <class T> void print_one(const T &x) { cout << x; }
template <class T, class... Ts> void print_one(const T &x, const Ts &...xs) {
    cout << x << ' ';
    print_one(xs...);
}
inline void println() {
    cout << '\n';
}
template <class T, class... Ts> void println(const T &x, const Ts &...xs) {
    cout << x;
    ((cout << ' ' << xs), ...);
    cout << '\n';
}
template <class T> void printAll(const V<T> &t) {
    rep(i, t.size()) cout << t[i] << '\n';
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
    V<T> ps(n + 1, T{});
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
template <class T>
int first_ge(const V<T>& a, T x) {
    return lower_bound(all(a), x) - a.begin();
}
template <class T>
int first_gt(const V<T>& a, T x) {
    return upper_bound(all(a), x) - a.begin();
}
template <class T>
int last_lt(const V<T>& a, T x) {
    int p = lower_bound(all(a), x) - a.begin();
    return p - 1;
}
template <class T>
int last_le(const V<T>& a, T x) {
    int p = upper_bound(all(a), x) - a.begin();
    return p - 1;
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
    Edge() : to(0), w(1) {}
    Edge(int _to, ll _w = 1) : to(_to), w(_w) {}
};

struct Graph {
    V<V<Edge>> graph;
    bool undirected = true;
    bool weighted = false;
    bool one_indexed = true;

    Graph() = default;

    explicit Graph(const int n, const bool _undirected = true, const bool _weighted = false, const bool _one_indexed = true)
        : graph(n),
          undirected(_undirected),
          weighted(_weighted),
          one_indexed(_one_indexed) {}

    [[nodiscard]] int size() const {
        return static_cast<int>(graph.size());
    }

    [[nodiscard]] int to_internal(int v) const {
        return one_indexed ? v - 1 : v;
    }

    [[nodiscard]] int to_external(int v) const {
        return one_indexed ? v + 1 : v;
    }
};

void add_edge_internal(Graph &g, int a, int b, ll w = 1) {
    g.graph[a].emplace_back(b, w);
    if (g.undirected) {
        g.graph[b].emplace_back(a, w);
    }
}

void add_edge(Graph &g, int a, int b, ll w = 1) {
    a = g.to_internal(a);
    b = g.to_internal(b);
    add_edge_internal(g, a, b, w);
}

Graph read_graph(
    const int n,
    const int m,
    const bool undirected = true,
    const bool weighted = false,
    const bool one_indexed = true
) {
    Graph g(n, undirected, weighted, one_indexed);

    rep(_, m) {
        int a, b;
        ll w = 1;

        if (weighted) {
            cin >> a >> b >> w;
        } else {
            cin >> a >> b;
        }

        add_edge(g, a, b, w);
    }

    return g;
}

// ============== グラフアルゴリズム ==============
// ============== DFS ==============
struct DFS_Info {
    V<int> used, parent, tin, tout, comp_id, order;
    int comp_cnt = 0;
    int timer = 0;
};

DFS_Info dfs_all(const Graph &graph) {
    DFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

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

        for (const auto &e : g[v]) {
            const int to = e.to;
            if (info.used[to]) continue;
            self(to, v);
        }

        info.tout[v] = info.timer;
    });

    rep(v, n) {
        if (info.used[v]) continue;
        dfs(v, -1);
        info.comp_cnt++;
    }

    return info;
}
// ============== BFS ==============
struct BFS_Info {
    V<int> dist, parent;
    V<int> order, source;
};

BFS_Info bfs(const Graph &graph, int s) {
    BFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    s = graph.to_internal(s);

    info.dist.assign(n, -1);
    info.parent.assign(n, -1);
    info.source.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    info.dist[s] = 0;
    info.source[s] = s;
    q.push(s);

    while (!q.empty()) {
        const int v = q.front();
        q.pop();

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            if (info.dist[to] != -1) continue;

            info.dist[to] = info.dist[v] + 1;
            info.parent[to] = v;
            info.source[to] = info.source[v];

            q.push(to);
        }
    }

    return info;
}
V<int> restore_path(const Graph &graph, const V<int> &parent, int s, int t) {
    V<int> path;

    s = graph.to_internal(s);
    t = graph.to_internal(t);

    if (s == t) {
        path.push_back(s);
    } else {
        if (parent[t] == -1) return {};

        for (int v = t; v != -1; v = parent[v]) {
            path.push_back(v);
            if (v == s) break;
        }

        if (path.back() != s) return {};

        reverse(all(path));
    }

    for (auto &v : path) {
        v = graph.to_external(v);
    }

    return path;
}
BFS_Info bfs_multi(const Graph &graph, const V<int> &starts) {
    BFS_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.dist.assign(n, -1);
    info.parent.assign(n, -1);
    info.source.assign(n, -1);
    info.order.reserve(n);

    queue<int> q;

    for (int s : starts) {
        s = graph.to_internal(s);

        if (info.dist[s] != -1) continue;

        info.dist[s] = 0;
        info.source[s] = s;
        q.push(s);
    }

    while (!q.empty()) {
        const int v = q.front();
        q.pop();

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;

            if (info.dist[to] != -1) continue;

            info.dist[to] = info.dist[v] + 1;
            info.parent[to] = v;
            info.source[to] = info.source[v];

            q.push(to);
        }
    }

    return info;
}
// ============== 連結成分 ==============
struct CC_Info {
    V<int> comp_id;
    V<int> comp_size;
    int comp_cnt = 0;
};

CC_Info connected_components(const Graph &graph) {
    CC_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    info.comp_id.assign(n, -1);

    rep(s, n) {
        if (info.comp_id[s] != -1) continue;

        queue<int> q;
        q.push(s);
        info.comp_id[s] = info.comp_cnt;

        int sz = 0;

        while (!q.empty()) {
            const int v = q.front();
            q.pop();

            sz++;

            for (const auto &e : g[v]) {
                const int to = e.to;

                if (info.comp_id[to] != -1) continue;

                info.comp_id[to] = info.comp_cnt;
                q.push(to);
            }
        }

        info.comp_size.push_back(sz);
        info.comp_cnt++;
    }

    return info;
}
// ============== Dijkstra ==============
struct Dijkstra_Info {
    V<ll> dist;
    V<int> parent;
    V<int> order;
};

Dijkstra_Info dijkstra(const Graph &graph, int s) {
    Dijkstra_Info info;

    const auto &g = graph.graph;
    const int n = graph.size();

    s = graph.to_internal(s);

    info.dist.assign(n, INF_L);
    info.parent.assign(n, -1);
    info.order.reserve(n);

    minpq<pair<ll, int>> pq;

    info.dist[s] = 0;
    pq.emplace(0, s);

    while (!pq.empty()) {
        const auto [d, v] = pq.top();
        pq.pop();

        if (d != info.dist[v]) continue;

        info.order.push_back(v);

        for (const auto &e : g[v]) {
            const int to = e.to;
            const ll nd = info.dist[v] + e.w;

            if (info.dist[to] <= nd) continue;

            info.dist[to] = nd;
            info.parent[to] = v;

            pq.emplace(nd, to);
        }
    }

    return info;
}

// ============== 解答用 ==============
#ifndef MULTI_TEST_CASES
#define MULTI_TEST_CASES 0
#endif

constexpr double  r_normal = -0.04;
constexpr double  r_jewelry = 1.0;
constexpr double  r_goal_exit = 10.0;
constexpr double  r_danger_exit = -10.0;

constexpr double t_normal = 0.8;
constexpr double t_error = 0.2;


struct Grid {
    int N{}, M{};
    V<string> grid;

    V<V<double>> value;
};

Grid read_grid() {
    Grid g;
    cin >> g.N >> g.M;

    g.grid.resize(g.N);

    g.value.assign(g.N, V<double>(g.M, 0));

    rep(i, g.N) cin >> g.grid[i];

    return g;
}

// a方向に確率1で動いた時に動けるかを返す
bool can_move(const Grid &g, const int i, const int j, const int a) {
    if (g.grid[i][j] == '#') return false;
    int i_ = i + DR4[a];
    int j_ = j + DC4[a];

    if (i_ < 0 || i_ >= g.N || j_ < 0 || j_ >= g.M) return false;
    if (g.grid[i_][j_] == '#') return false;

    return true;
}

// a方向に確率1で動かす
pair<int, int> move_to(const Grid &g, const int i, const int j, const int a) {
    if (!can_move(g, i, j, a)) return {i,j};
    return {i + DR4[a], j + DC4[a]};
}

// (i, j)からa方向に遷移した時の価値を返す
double calc_action_value(const Grid &g, const int i, const int j, const int a) {
    double res = 0.0;

    rep(k, 4) {
        if (k == 2) continue;

        const int a_ = (a + k) % 4;
        const auto [i_, j_] = move_to(g, i, j, a_);
        if (k == 0) {
            res += t_normal * g.value[i_][j_];
        } else {
            res += (t_error / 2.0) * g.value[i_][j_];
        }
    }

    return res + r_normal;
}

// aを全方向試して最大値とaを返す
pair<int, double> calc_next_value(const Grid &g, const int i, const int j) {
    int max_a = 0;
    double max_value = -INF_D;

    rep(a, 4) {
        double cur_val = calc_action_value(g, i, j, a);

        if (cur_val > max_value) {
            max_a = a;
            max_value = cur_val;
        }
    }

    return {max_a, max_value};
}

// V1を求める関数
void initialize_value(Grid &g) {
    rep(i, g.N) rep(j, g.M) {
        char c = g.grid[i][j];

        if (c == '#') continue;

        if (c == '.' || c == 'S') {
            g.value[i][j] = r_normal;
        } else if (c == 'J') {
            g.value[i][j] = r_jewelry;
        } else if (c == 'G') {
            g.value[i][j] = r_goal_exit;
        } else if (c == 'D') {
            g.value[i][j] = r_danger_exit;
        } else {
            cerr << "Invalid input: " << c << " at (" << i <<"," << j << ")\n";
            exit(1);
        }
    }
}

void update_value(Grid &g) {
    auto next_value = g.value;
    rep(i, g.N) rep(j, g.M) {
        const char c = g.grid[i][j];

        if (c == '#' || c == 'J' || c == 'D' || c == 'G') continue;

        next_value[i][j] = calc_next_value(g, i, j).second;
    }

    g.value = next_value;
}

void print_all(const Grid &g) {
    rep(i, g.N) rep(j, g.M) {
        cout << fixed << setprecision(5) << setw(10) << g.value[i][j] << " ";
        if (j == g.M - 1) cout << "\n";
    }
}

void solve() {
    Grid g = read_grid();
    initialize_value(g);

    int iter = 1;

    cout << "V" << iter << "\n";
    print_all(g);

    while (true) {
        cout << "\ncommand: ";

        string cmd;
        cin >> cmd;

        if (cmd == "q" || cmd == "Q") {
            break;
        }

        if (cmd == "p" || cmd == "P") {
            cout << "V" << iter << "\n";
            print_all(g);
            continue;
        }

        if (cmd == "a" || cmd == "A") {
            int cnt;
            cin >> cnt;

            rep(_, cnt) {
                update_value(g);
                iter++;

                cout << "V" << iter << "\n";
                print_all(g);
                cout << "\n";
            }

            continue;
        }

        // 数字だけ入力された場合: その回数だけ進めて、最後だけ表示
        int cnt = stoi(cmd);

        rep(_, cnt) {
            update_value(g);
            iter++;
        }

        cout << "V" << iter << "\n";
        print_all(g);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
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
