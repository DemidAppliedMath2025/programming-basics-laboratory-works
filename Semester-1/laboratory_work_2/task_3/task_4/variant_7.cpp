#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

struct Cell {
    int row;
    int c;
    int colPos;
};

int* build_row_template(int n, int &rowsCount) {
    if (n <= 0) { rowsCount = 0; return nullptr; }
    if (n == 1) { rowsCount = 1; int *r = new int[1]; r[0] = 1; return r; }

    int *tmp = new int[n + 6];
    int t = 0;
    int total = 0;

    tmp[t++] = 1; total += 1;
    if (total == n) { rowsCount = t; int *rows = new int[rowsCount]; for (int i=0;i<rowsCount;++i) rows[i]=tmp[i]; delete[] tmp; return rows; }

    if (total + 3 <= n) { tmp[t++] = 3; total += 3; }
    else { int rem = n - total; if (rem>0) tmp[t++]=rem; rowsCount = t; int *rows = new int[rowsCount]; for (int i=0;i<rowsCount;++i) rows[i]=tmp[i]; delete[] tmp; return rows; }

    if (n < 8) {
        int rem = n - total;
        while (rem > 0) { int take = (rem >= 4) ? 4 : rem; tmp[t++] = take; rem -= take; }
        rowsCount = t; int *rows = new int[rowsCount]; for (int i=0;i<rowsCount;++i) rows[i]=tmp[i]; delete[] tmp; return rows;
    }

    int k = (n - 8) / 4;
    for (int i = 0; i < k; ++i) { tmp[t++] = 4; total += 4; }
    tmp[t++] = 3; total += 3;
    tmp[t++] = 1; total += 1;

    int rem = n - total;
    int orderIdx = t - 2;
    while (rem > 0 && orderIdx >= 0) {
        int canAdd = 4 - tmp[orderIdx];
        if (canAdd > 0) {
            int add = (rem <= canAdd) ? rem : canAdd;
            tmp[orderIdx] += add;
            rem -= add;
        }
        if (orderIdx == t - 2) orderIdx = t - 1; else --orderIdx;
    }
    while (rem > 0) { int take = (rem >= 4) ? 4 : rem; tmp[t++] = take; rem -= take; }

    rowsCount = t;
    int *rows = new int[rowsCount];
    for (int i = 0; i < rowsCount; ++i) rows[i] = tmp[i];
    delete[] tmp;
    return rows;
}

int main() {
    int n;
    if (!(std::cin >> n)) return 0;
    int piece; std::cin >> piece; // 1 king, 2 knight
    int start, target; std::cin >> start >> target;

    if (n <= 0 || start < 1 || start > n || target < 1 || target > n) {
        std::cout << "Bad input\n"; return 0;
    }

    int rowsCount = 0;
    int *rows = build_row_template(n, rowsCount);

    int maxLen = 0;
    for (int r = 0; r < rowsCount; ++r) { if (rows[r] > maxLen) maxLen = rows[r]; }

    int *offset = new int[rowsCount];
    for (int r = 0; r < rowsCount; ++r) { offset[r] = (maxLen - rows[r]); }

    Cell *cells = new Cell[n + 1];
    int cur = 1;
    for (int r = 0; r < rowsCount; ++r) {
        for (int c = 0; c < rows[r]; ++c) {
            if (cur > n) break;
            cells[cur].row = r;
            cells[cur].c = c;
            cells[cur].colPos = offset[r] + c;
            ++cur;
        }
    }

    int *deg = new int[n + 1];
    for (int i = 1; i <= n; ++i) deg[i] = 0;

    auto kingNeighbor = [&](int u, int v)->bool {
        int dr = std::abs(cells[u].row - cells[v].row);
        int dx = std::abs(cells[u].colPos - cells[v].colPos);
        return ((dr == 0 && dx == 2) || (dr == 1 && dx <= 1));
    };

    auto knightNeighbor = [&](int u, int v)->bool {
        int ru = cells[u].row;
        int rv = cells[v].row;
        int dr = std::abs(ru - rv);
        int dc = std::abs(cells[u].colPos - cells[v].colPos);

        if (ru == 0 || ru == rowsCount - 1) {
            if (dr != 2) return false;
            int targetRow = (ru == 0) ? (ru + 2) : (ru - 2);
            if (targetRow < 0 || targetRow >= rowsCount) return false;
            int bigDc = std::abs(offset[ru] - offset[targetRow]);
            if (dc == 0 || dc == bigDc) return true;
            return false;
        } else {
            if ((dr == 1 && dc == 2) || (dr == 2 && dc == 1)) return true;
            return false;
        }
    };

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            bool nb = false;
            if (piece == 1) nb = kingNeighbor(i, j);
            else nb = knightNeighbor(i, j);
            if (nb) deg[i] += 1;
        }
    }

    int totalDeg = 0;
    for (int i = 1; i <= n; ++i) totalDeg += deg[i];
    int *nbrs = new int[ (totalDeg>0) ? totalDeg : 1 ];
    int *nbrIdx = new int[n + 2];
    nbrIdx[1] = 0;
    for (int i = 2; i <= n + 1; ++i) nbrIdx[i] = nbrIdx[i-1] + deg[i-1];

    for (int i = 1; i <= n; ++i) {
        int base = nbrIdx[i];
        int ptr = 0;
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            bool nb = false;
            if (piece == 1) nb = kingNeighbor(i, j);
            else nb = knightNeighbor(i, j);
            if (nb) {
                nbrs[base + ptr] = j;
                ++ptr;
            }
        }
    }

    int *dist = new int[n + 1];
    int *parent = new int[n + 1];
    for (int i = 1; i <= n; ++i) { dist[i] = -1; parent[i] = -1; }
    int *queue = new int[n + 5];
    int qh = 0, qt = 0;
    dist[start] = 0; queue[qt++] = start;
    while (qh < qt) {
        int u = queue[qh++];
        if (u == target) break;
        int base = nbrIdx[u];
        int d = deg[u];
        for (int k = 0; k < d; ++k) {
            int v = nbrs[base + k];
            if (dist[v] == -1) { dist[v] = dist[u] + 1; parent[v] = u; queue[qt++] = v; }
        }
    }

    bool *onPath = new bool[n + 1];
    for (int i = 1; i <= n; ++i) onPath[i] = false;
    if (dist[target] != -1) {
        int p = target;
        while (p != -1) { onPath[p] = true; p = parent[p]; }
    }

    int *dist2 = new int[n + 1];
    for (int i = 1; i <= n; ++i) dist2[i] = -1;
    qh = qt = 0;
    dist2[start] = 0; queue[qt++] = start;
    while (qh < qt) {
        int u = queue[qh++];
        if (dist2[u] == 2) continue;
        int base = nbrIdx[u];
        int d = deg[u];
        for (int k = 0; k < d; ++k) {
            int v = nbrs[base + k];
            if (dist2[v] == -1) { dist2[v] = dist2[u] + 1; queue[qt++] = v; }
        }
    }

    std::cout << "\nS = start, T = target, P = path, 1 = reachable in 1, * = reachable in 2\n\n";
    const int cellW = 6;
    int id = 1;
    for (int r = 0; r < rowsCount; ++r) {
        int L = rows[r];
        int padCells = maxLen - L;
        int padSpaces = padCells * (cellW / 2);
        for (int s = 0; s < padSpaces; ++s) std::cout << ' ';
        for (int c = 0; c < L; ++c) {
            if (id > n) break;
            std::string mark;
            if (id == start) mark = "S";
            else if (id == target) mark = "T";
            else if (onPath[id]) mark = "P";
            else if (dist2[id] == 1) mark = "1";
            else if (dist2[id] != -1 && dist2[id] <= 2) mark = "*";
            else { std::ostringstream oss; oss << id; mark = oss.str(); }
            int left = (cellW - (int)mark.size()) / 2;
            int right = cellW - left - (int)mark.size();
            for (int i = 0; i < left; ++i) std::cout << ' ';
            std::cout << mark;
            for (int i = 0; i < right; ++i) std::cout << ' ';
            ++id;
        }
        std::cout << "\n\n";
    }

    std::cout << "Reachable in 1 move from " << start << ": ";
    bool first = true;
    int baseS = nbrIdx[start];
    for (int k = 0; k < deg[start]; ++k) {
        int v = nbrs[baseS + k];
        if (!first) std::cout << ", ";
        std::cout << v;
        first = false;
    }
    if (deg[start] == 0) std::cout << "(none)";
    std::cout << "\n";

    std::cout << "Reachable in <=2 moves from " << start << ": ";
    first = true;
    for (int i = 1; i <= n; ++i) {
        if (i == start) continue;
        if (dist2[i] != -1 && dist2[i] <= 2) {
            if (!first) std::cout << ", ";
            std::cout << i;
            first = false;
        }
    }
    if (first) std::cout << "(none)";
    std::cout << "\n";

    if (dist[target] == -1) {
        std::cout << "Shortest path: none\n";
    } else {
        std::cout << "Shortest path (" << dist[target] << " moves): ";
        int stackSize = dist[target] + 1;
        int *stack = new int[stackSize];
        int idx = 0;
        int p = target;
        while (p != -1) { stack[idx++] = p; p = parent[p]; }
        for (int k = idx - 1; k >= 0; --k) {
            std::cout << stack[k];
            if (k > 0) std::cout << " -> ";
        }
        std::cout << "\n";
        delete[] stack;
    }

    delete[] rows;
    delete[] offset;
    delete[] cells;
    delete[] deg;
    delete[] nbrs;
    delete[] nbrIdx;
    delete[] dist;
    delete[] parent;
    delete[] queue;
    delete[] onPath;
    delete[] dist2;

    return 0;
}
