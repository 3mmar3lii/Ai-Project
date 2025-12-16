#include <bits/stdc++.h>
using namespace std;

// =================================================================
// BFS
// =================================================================
vector<pair<int,int>> BFSPath;

bool BFS(int startRow, int startCol, const vector<vector<int>>& Maze) {
    int n = Maze.size(), m = Maze[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1, -1}));

    queue<pair<int,int>> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    bool found = false;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == n - 1 && c == m - 1) {
            found = true;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m &&
                Maze[nr][nc] == 0 && !visited[nr][nc]) {

                visited[nr][nc] = true;
                q.push({nr, nc});
                parent[nr][nc] = {r, c};
            }
        }
    }

    BFSPath.clear();

    if (!found) return false;

    int r = n - 1, c = m - 1;
    while (r != -1 && c != -1) {
        BFSPath.push_back({r, c});
        auto p = parent[r][c];
        r = p.first;
        c = p.second;
    }

    reverse(BFSPath.begin(), BFSPath.end());
    return true;
}

// =================================================================
// MAIN - Test BFS
// =================================================================
int main() {
    cout << "=== BFS Test ===" << endl;
    cout << "(0 means empty, 1 means wall)" << endl << endl;

    // Test Maze
    vector<vector<int>> Maze = {
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    int n = Maze.size(), m = Maze[0].size();

    cout << "Maze:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << Maze[i][j] << " ";
        cout << endl;
    }

    cout << endl << "BFS Path from (0,0) to (" << n-1 << "," << m-1 << "):" << endl;

    if (BFS(0, 0, Maze)) {
        for (auto& p : BFSPath)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
        cout << "Path length: " << BFSPath.size() << endl;
    } else {
        cout << "No Path Found!" << endl;
    }

    return 0;
}
