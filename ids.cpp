#include <bits/stdc++.h>
using namespace std;

// =================================================================
// IDS + DLS
// =================================================================
vector<pair<int,int>> IDSpath;

bool DLS(int row, int col, const vector<vector<int>>& Maze,
         vector<vector<bool>>& visited, int limit)
{
    int n = Maze.size(), m = Maze[0].size();

    if (row < 0 || col < 0 || row >= n || col >= m) return false;
    if (Maze[row][col] == 1 || visited[row][col]) return false;
    if (limit < 0) return false;

    visited[row][col] = true;
    IDSpath.push_back({row, col});

    if (row == n - 1 && col == m - 1) return true;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        if (DLS(row + dr[i], col + dc[i], Maze, visited, limit - 1))
            return true;
    }

    IDSpath.pop_back();
    visited[row][col] = false;
    return false;
}

bool IDS(int startRow, int startCol, const vector<vector<int>>& Maze)
{
    int n = Maze.size(), m = Maze[0].size();
    int maxDepth = n*m;

    for (int depth = 0; depth <= maxDepth; depth++) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        IDSpath.clear();
        if (DLS(startRow, startCol, Maze, visited, depth))
            return true;
    }

    IDSpath.clear();
    return false;
}

// =================================================================
// MAIN - Test IDS
// =================================================================
int main() {
    cout << "=== IDS Test ===" << endl;
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

    cout << endl << "IDS Path from (0,0) to (" << n-1 << "," << m-1 << "):" << endl;

    if (IDS(0, 0, Maze)) {
        for (auto& p : IDSpath)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
        cout << "Path length: " << IDSpath.size() << endl;
    } else {
        cout << "No Path Found!" << endl;
    }

    return 0;
}
