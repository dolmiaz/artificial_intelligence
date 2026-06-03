# C++ Competitive Programming Template

競技プログラミング用の `main.cpp` です。基本型、入出力補助、数値処理、グリッド方向定数、累積和、二分探索、グラフ構築、DFS/BFS、連結成分、Dijkstra、再帰ラムダ、解答用スケルトンをまとめています。

## Environment

- Language: C++17
- Compiler assumption: GCC / Clang with GNU extension support
- Main dependency: standard library and `bits/stdc++.h`
- License: MIT License

`bits/stdc++.h` を使っているため、標準C++だけの環境ではそのままコンパイルできない場合があります。

## File

- `main.cpp`: テンプレート本体と、解答用の `solve()` / `main()` を含む単一ファイル
- `LICENSE`: MIT License

## Template Contents

### Basic Types

よく使う型とコンテナのエイリアスです。

| Name | Meaning |
| --- | --- |
| `ll` | `long long` |
| `ull` | `unsigned long long` |
| `ld` | `long double` |
| `V<T>` | `vector<T>` |
| `minpq<T>` | 昇順の `priority_queue` |
| `maxpq_ll` | `long long` 用の降順 `priority_queue` |
| `pii` | `pair<int, int>` |
| `pll` | `pair<long long, long long>` |

### Constants

| Name | Value / Role |
| --- | --- |
| `PI` | 円周率 |
| `INF` | `int` 用の大きな値 |
| `INF_L` | `long long` 用の大きな値 |
| `ABC` | 大文字アルファベット |
| `abc` | 小文字アルファベット |
| `modNum` | デフォルトの法 `998244353` |

### Loop and Range Macros

| Macro | Expansion |
| --- | --- |
| `rep(i, n)` | `0 <= i < n` |
| `rep1(i, n)` | `1 <= i <= n` |
| `rrep(i, n)` | `n - 1` から `0` まで |
| `rrep1(i, n)` | `n` から `1` まで |
| `all(x)` | `begin(x), end(x)` |
| `rall(x)` | `rbegin(x), rend(x)` |

### Utility Functions

| Function | Description |
| --- | --- |
| `chmin(a, b)` | `a > b` のとき `a = b` に更新し、更新有無を返す |
| `chmax(a, b)` | `a < b` のとき `a = b` に更新し、更新有無を返す |
| `sgn(x)` | 正なら `1`、ゼロなら `0`、負なら `-1` |
| `clampv(x, lo, hi)` | `x` を `[lo, hi]` に収める |
| `ceil_div(a, b)` | 整数の切り上げ除算 |
| `floor_div(a, b)` | 整数の切り下げ除算 |

`ceil_div` と `floor_div` は、負の値を含む整数除算でも数学的な切り上げ・切り下げになるようにしています。

### Grid Direction Helpers

グリッド上の上下左右・斜め移動に使う方向定数です。行方向を `DR`、列方向を `DC` として扱います。

| Name | Description |
| --- | --- |
| `DR4`, `DC4` | `U, D, R, L` の4方向に対応する行・列の差分 |
| `DIR4`, `dir4` | 4方向の大文字・小文字ラベル |
| `DR8`, `DC8` | `U, D, R, L, UR, UL, DR, DL` の8方向に対応する行・列の差分 |
| `DIR8`, `dir8` | 8方向の大文字・小文字ラベル |

### Output Helpers

| Function | Description |
| --- | --- |
| `print_one(...)` | 空白区切りで出力する内部補助 |
| `println(...)` | 複数値を空白区切りで出力し、末尾に改行 |
| `printAll(vec)` | `vector` の各要素を1行ずつ出力 |
| `yes(c)` | `Yes` / `No` を出力 |
| `YES(c)` | `YES` / `NO` を出力 |

### Math Helpers

| Function | Description |
| --- | --- |
| `tri0(x)` | `0 + 1 + ... + (x - 1)` |
| `tri1(x)` | `1 + 2 + ... + x` |

### Recursive Lambda

`yc()` は、ラムダ式で再帰を書くための y-combinator です。

```cpp
auto dfs = yc([&](auto self, int v, int p) -> void {
    for (auto e : g[v]) {
        if (e.to == p) continue;
        self(e.to, v);
    }
});
```

### Prefix Sums

| Function / Struct | Description |
| --- | --- |
| `prefix_sum_1d(vec)` | 1次元累積和。戻り値は長さ `n + 1` で、`ps[0] = 0` |
| `prefix_sum_2d(grid)` | 2次元累積和。戻り値は `(n + 1) x (m + 1)` |
| `Prefix_Max_Info<T>` | 左右からの累積最大値を持つ構造体 |
| `prefix_max_1d(vec)` | `L`, `R` に左右方向の累積最大値を構築 |

`prefix_sum_2d` に空の `grid` を渡した場合は、`1 x 1` のゼロ行列を返します。空でない場合は長方形の `grid` を前提にしています。

### Binary Search Helpers

ソート済み配列に対する探索補助です。

| Function | Description |
| --- | --- |
| `binary_search_index(vec, x)` | `x` の添字を返す。存在しなければ `-1` |
| `lower_bound_index(vec, l, r, x)` | `[l, r]` で `x` 以上となる最初の添字 |
| `last_less_index(vec, l, r, x)` | `[l, r]` で `x` 未満となる最後の添字 |
| `upper_bound_index(vec, l, r, x)` | `[l, r]` で `x` より大きい最初の添字 |
| `last_greater_index(vec, l, r, x)` | `[l, r]` で `x` より大きい最後の添字 |
| `binary_search_min(ok, ng, pred)` | 条件を満たす最小側の値を探索 |
| `binary_search_max(ok, ng, pred)` | 条件を満たす最大側の値を探索 |

区間指定関数は、`0 <= l <= r < vec.size()` を前提にしています。

### Graph Template

重み付きグラフを扱うためのテンプレートです。重みなしグラフも、重み `1` のグラフとして扱います。

`Graph` が `undirected`、`weighted`、`one_indexed` の設定を持ち、入力や `add_edge` で使う頂点番号をグラフ側で内部表現に変換します。`one_indexed = true` の場合は外部入力を 1-indexed として受け取り、内部では 0-indexed で保持します。`one_indexed = false` の場合は入力をそのまま 0-indexed として扱います。

| Name | Description |
| --- | --- |
| `Edge` | 行き先 `to` と重み `w` を持つ辺 |
| `Graph` | 隣接リスト `graph` と、無向/有向・重み付き・index設定を持つ構造体 |
| `Graph(n, undirected, weighted, one_indexed)` | 頂点数とグラフ設定を指定して構築 |
| `g.size()` | 頂点数を返す |
| `g.to_internal(v)` | 外部の頂点番号を内部の 0-indexed に変換 |
| `g.to_external(v)` | 内部の 0-indexed を外部の頂点番号に戻す |
| `add_edge(g, a, b, w)` | グラフ設定に従って頂点番号を変換し、辺を追加 |
| `add_edge_internal(g, a, b, w)` | 内部の 0-indexed 頂点番号で辺を追加 |
| `read_graph(n, m, undirected, weighted, one_indexed)` | 入力からグラフを構築 |

`read_graph` はデフォルトで、無向・重みなし・1-indexed 入力として読み込みます。重み付きグラフでは `weighted = true` を指定します。

### Graph Algorithms

| Function / Struct | Description |
| --- | --- |
| `DFS_Info` | DFSの訪問情報、親、入出時刻、連結成分ID、訪問順を保持 |
| `dfs_all(g)` | 全頂点を対象にDFSし、連結成分も数える |
| `BFS_Info` | BFSの距離、親、訪問順、探索元を保持 |
| `bfs(g, s)` | 単一起点BFSを行う |
| `bfs_multi(g, starts)` | 複数始点BFSを行う |
| `restore_path(g, parent, s, t)` | BFSやDijkstraの `parent` から `s` から `t` への経路を復元 |
| `CC_Info` | 連結成分ID、各成分サイズ、成分数を保持 |
| `connected_components(g)` | グラフ全体の連結成分を数える |
| `Dijkstra_Info` | Dijkstraの最短距離、親、確定順を保持 |
| `dijkstra(g, s)` | 重み付きグラフの単一起点最短路を求める |

`DFS_Info::tin` / `tout` はDFS順の時刻です。`BFS_Info::dist` は始点からの辺数で、到達不能な頂点は `-1` です。`Dijkstra_Info::dist` は始点からの最短距離で、到達不能な頂点は `INF_L` です。

`bfs`、`bfs_multi`、`dijkstra` の始点や、`restore_path` の `s` / `t` は `Graph::one_indexed` の設定に従って解釈されます。`restore_path` の戻り値も同じ外部indexに戻して返します。

## Solution Skeleton

`main.cpp` の末尾には、問題ごとに書き換えるための解答用スケルトンが含まれています。現在の `solve()` は、重み付き無向グラフを読み込んで頂点 `1` からのDijkstraを実行し、各頂点への最短距離を出力する形になっています。

| Name | Description |
| --- | --- |
| `MULTI_TEST_CASES` | 複数テストケースを使うかどうかのコンパイル時フラグ |
| `solve()` | 問題ごとの実装を書く関数。現在はDijkstraの使用例を含む |
| `main()` | `MULTI_TEST_CASES` に応じて `solve()` を1回または `T` 回呼び出す |

デフォルトでは `MULTI_TEST_CASES` は `0` です。複数テストケース形式の問題では、コンパイル時に `-DMULTI_TEST_CASES=1` を指定します。

## Usage

`solve()` に問題ごとの実装を書き、`main()` から呼び出します。複数テストケースを使う場合は、コンパイル時に `MULTI_TEST_CASES=1` を定義します。

```bash
g++ -std=gnu++17 -O2 -Wall -Wextra main.cpp -o main
```

```bash
g++ -std=gnu++17 -O2 -Wall -Wextra -DMULTI_TEST_CASES=1 main.cpp -o main
```

## Recent Graph Updates

- BFSを単一起点 `bfs` と複数始点 `bfs_multi` に整理しました。
- `restore_path` を追加し、`parent` 配列から経路を復元できるようにしました。
- `connected_components` を追加し、連結成分数と各頂点の成分ID、成分サイズを取れるようにしました。
- `Graph` が `one_indexed` 設定を持つようにし、1-indexed / 0-indexed の切り替えをグラフ側で扱えるようにしました。
- `dijkstra` を追加し、重み付きグラフの単一起点最短路を求められるようにしました。

## Notes

- グラフの外部indexは `Graph::one_indexed` に従います。アルゴリズム内部の配列添字は 0-indexed です。
- 二分探索補助は、対象区間がソート済みであることを前提にしています。
- `LOCAL` やデバッグ出力を追加する場合は、提出先に応じて出力先や制限時間を確認してください。
- `solve()` は問題ごとに書き換えて使ってください。
