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
template <class T> void printAll(const V<T> t) {
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
// -INF, L[0], L[1], L[2], ..., L[N - 1], -INF
// -INF, R[0], R[1], R[2], ..., R[N - 1], -INF
template <class T> struct Prefix_Max_Info {
    V<T> L, R;
};
template <class T> Prefix_Max_Info<T> prefix_max_1d(const V<T> &vec) {
    const int n = static_cast<int>(vec.size());
    Prefix_Max_Info<T> info;
    info.L.assign(n + 2, -1 * INF);
    info.R.assign(n + 2, -1 * INF);
    rep(i, n) info.L[i + 1] = max(info.L[i], vec[i]);
    rrep(i, n) info.R[i + 1] = max(info.R[i + 2], vec[i]);
    return info;
}
// ============== 二分探索 ==============
// return -> 0-indexed
template <class T, class F> int binary_search(const V<F> &vec, T x) {
    int pos = lower_bound(all(vec), x) - vec.begin();
    if (pos <= static_cast<int>(vec.size()) && vec[pos] == x) return pos;
    return -1;
}
template <class T> int first_less_index(const V<T>& vec, int l, int r, T x) {
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
template <class T> int first_greater_index(const V<T>& vec, int l, int r, T x) {
    auto it = upper_bound(vec.begin() + l, vec.begin() + r + 1, x);
    if (it == vec.begin() + r + 1) return -1;
    return static_cast<int>(it - vec.begin());
}
template <class T>
int last_greater_index(const V<T>& vec, int l, int r, const T& x) {
    auto it = upper_bound(vec.begin() + l, vec.begin() + r + 1, x);
    if (it == vec.begin() + r + 1) return -1;
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

int D;
V<ll> c(27, 0);
V<V<ll>> s(366, V<ll>(27, 0));

V<int> initialSolution() {
    V<int> t(D + 1,0);

    rep1(d, D) {
        int curMaxIndex = 1;
        rep1(i, 26) {
            if (s[d][curMaxIndex] <= s[d][i]) {
                curMaxIndex = i;
            }
        }
        t[d] = curMaxIndex;
    }
    return t;
}

V<int> initialSolution2() {
    V<int> t(D + 1, 0);
    V<int> last(27, 0);

    rep1(d, D) {
        int bestType = 1;
        ll bestValue = -INF_L;

        rep1(type, 26) {
            ll value = s[d][type];

            V<int> tmpLast = last;
            tmpLast[type] = d;
            rep1(i, 26) {
                value -= c[i] * (d - tmpLast[i]);
            }
            if (value > bestValue) {
                bestValue = value;
                bestType = type;
            }
        }
        t[d] = bestType;
        last[bestType] = d;
    }
    return t;
}

ll calcScore(const V<int> &t) {
    ll score = 0;
    V<int> last(27, 0);

    rep1(d, D) {
        const int type = t[d];
        score += s[d][type];
        last[type] = d;

        rep1(i, 26) {
            score -= c[i] * (d - last[i]);
        }
    }
    return score;
}

struct State {
    V<int> t = V<int>(27, 0);
    ll score = 0;
    V<set<int>> days = V<set<int>>(27); // type1...26が実施される日を持つ

    State() = default;

    explicit State(const V<int> &init) {
        t = init;
        score = calcScore(t);

        rep1(i, 26) {
            days[i].insert(0);
            days[i].insert(D + 1);
        }
        rep1(d, D) {
            days[t[d]].insert(d);
        }
    }

    static ll penaltyCost(const int type, int gap) {
        return c[type] * tri0(gap);
    }

    ll deltaRemove(const int type, int day) {
        auto it = days[type].find(day);

        const auto prv = *prev(it);
        const auto nxt = *next(it);

        const ll before = penaltyCost(type, day - prv) + penaltyCost(type, nxt - day);
        const ll after = penaltyCost(type, nxt - prv);

        return -(after - before);
    }

    ll deltaAdd(const int type, int day) {
        const auto it = days[type].lower_bound(day);

        const auto nxt = *it;
        const auto prv = *prev(it);

        const ll before = penaltyCost(type, nxt - prv);
        const ll after = penaltyCost(type, day - prv) + penaltyCost(type, nxt - day);

        return -(after - before);
    }

    ll calcDiff(int day, int newType) {
        const int oldType = t[day];
        if (newType == oldType) return 0;

        ll diff = 0;
        diff += s[day][newType] - s[day][oldType];
        diff += deltaAdd(newType, day) + deltaRemove(oldType, day);

        return diff;
    }

    void applyChange(int day, int newType) {
        const int oldType = t[day];

        if (oldType == newType) return;

        ll diff = calcDiff(day, newType);
        score += diff;

        days[oldType].erase(day);
        days[newType].insert(day);
        t[day] = newType;
    }
};

bool trySwap(State &state, const int d1, const int d2) {
    if (d1 == d2) return false;

    const int t1 = state.t[d1];
    const int t2 = state.t[d2];

    if (t1 == t2) return false;

    ll oldScore = state.score;
    state.applyChange(d1, t2);
    state.applyChange(d2, t1);
    ll newScore = state.score;

    if (newScore >= oldScore) {
        return true;
    }
    state.applyChange(d1, t1);
    state.applyChange(d2, t2);
    return false;
}

void hillClimb(State &state) {
    mt19937 rng(1);
    auto start = chrono::steady_clock::now();

    int iter = 0;
    int acceptedChange = 0;
    int acceptedSwap = 0;
    ll gainChange = 0;
    ll gainSwap = 0;

    while (true) {
        auto now = chrono::steady_clock::now();
        double elapsed = chrono::duration<double>(now - start).count();

        if (elapsed > 1.7) break;

        iter++;

        int mode = rng() % 10;
        if (mode <= 5) {
            int day = rng() % D + 1;
            int newType = rng() % 26 + 1;

            ll before = state.score;
            ll diff = state.calcDiff(day, newType);
            if (diff >= 0) {
                state.applyChange(day, newType);
                acceptedChange++;
                gainChange += state.score - before;
            }
        } else {
            const int day1 = rng() % D + 1;
            const int width = 60;

            const int l = max(1, day1 - width);
            const int r = min(D, day1 + width);
            const int day2 = l + rng() % (r - l + 1);

            ll before = state.score;
            if (trySwap(state, day1, day2)) {
                acceptedSwap++;
                gainSwap += state.score - before;
            }
        }
    }

    cerr << "iter = " << iter << endl;
    cerr << "acceptedChange = " << acceptedChange << endl;
    cerr << "acceptedSwap = " << acceptedSwap << endl;
    cerr << "gainChange = " << gainChange << endl;
    cerr << "gainSwap = " << gainSwap << endl;
    cerr << "state.score = " << state.score << endl;
    cerr << "real score  = " << calcScore(state.t) << endl;
}

void simulatedAnnealing(State &state) {
    mt19937 rng(0);
    uniform_real_distribution dist01(0.00, 1.00);

    auto start = chrono::steady_clock::now();

    const double timeLimit = 1.7;
    const double startTemp = 2000;
    const double endTemp = 50;

    int iter = 0;
    int acceptedChange = 0;
    int acceptedSwap = 0;
    int acceptedBadChange = 0;
    int acceptedBadSwap = 0;

    State bestState = state;
    ll bestScore = state.score;

    while (true) {
        auto now = chrono::steady_clock::now();
        const double elapsed = chrono::duration<double>(now - start).count();

        if (elapsed >= timeLimit) break;

        iter++;

        const double progress = elapsed / timeLimit;
        const double temp = startTemp + (endTemp - startTemp) * progress;

        const int mode = rng() % 10;

        if (mode <= 5) {
            const int day = rng() % D + 1;
            const int newType = rng() % 26 + 1;
            bool accept = false;

            const ll diff = state.calcDiff(day, newType);

            if (diff >= 0) {
                accept = true;
            } else {
                const double prob = exp(static_cast<double>(diff) / temp);
                if (dist01(rng) < prob) {
                    acceptedBadChange++;
                    accept = true;
                }
            }

            if (accept) {
                state.applyChange(day, newType);
                acceptedChange++;
                if (state.score >= bestScore) {
                    bestScore = state.score;
                    bestState = state;
                }
            }
        } else {
            const int day1 = rng() % D + 1;

            constexpr int width = 60;
            const int l = max(1, day1 - width);
            const int r = min(D, day1 + width);
            const int day2 = l + rng() % (r - l + 1);

            const int type1 = state.t[day1];
            const int type2 = state.t[day2];

            const ll oldScore = state.score;

            state.applyChange(day1, type2);
            state.applyChange(day2, type1);

            const ll newScore = state.score;
            const ll diff = newScore - oldScore;

            bool accept = false;

            if (diff >= 0) {
                accept = true;
            } else {
                const double prob = exp(static_cast<double>(diff) / temp);
                if (dist01(rng) < prob) {
                    accept = true;
                    acceptedBadSwap++;
                }
            }

            if (accept) {
                acceptedSwap++;

                if (state.score >= bestScore) {
                    bestScore = state.score;
                    bestState = state;
                }
                continue;
            }
            state.applyChange(day1, type1);
            state.applyChange(day2, type2);
        }
    }

    if (state.score <= bestScore) {
        state = bestState;
    }

    cerr << "iter = " << iter << endl;
    cerr << "acceptedChange = " << acceptedChange << endl;
    cerr << "acceptedBadChange = " << acceptedBadChange << endl;
    cerr << "acceptedSwap = " << acceptedSwap << endl;
    cerr << "acceptedBadSwap = " << acceptedBadSwap << endl;
    cerr << "state.score = " << state.score << endl;
    cerr << "real score  = " << calcScore(state.t) << endl;
}

void polish(State &state) {
    bool updated = true;

    while (updated) {
        updated = false;

        rep1(day, D) {
            int bestType = state.t[day];
            ll bestDiff = 0;

            rep1(type, 26) {
                ll diff = state.calcDiff(day, type);

                if (diff > bestDiff) {
                    bestDiff = diff;
                    bestType = type;
                }
            }

            if (bestDiff > 0) {
                state.applyChange(day, bestType);
                updated = true;
            }
        }
    }
}

void solve() {
    cin >> D;
    rep1(i, 26) cin >> c[i];
    rep1(d, D) rep1(i, 26) cin >> s[d][i];

    const V<int> t = initialSolution2();
    cerr << "Score : "<< calcScore(t) << endl;

    State state(t);
    simulatedAnnealing(state);
    polish(state);

    rep1(i, D) cout << state.t[i] << endl;
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
