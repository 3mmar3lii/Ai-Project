#include <bits/stdc++.h>
using namespace std;

// =================================================================
// DFS
// =================================================================
bool DFS(int row, int col, vector<vector<int>>& Maze,
         vector<vector<bool>>& visited, vector<pair<int,int>>& path)
{
    int n = Maze.size();
    int m = Maze[0].size();

    if (row < 0 || col < 0 || row >= n || col >= m)
        return false;

    if (Maze[row][col] == 1 || visited[row][col])
        return false;

    visited[row][col] = true;
    path.push_back({row, col});

    if (row == n - 1 && col == m - 1)
        return true;

    static int dr[4] = {1, -1, 0, 0};
    static int dc[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        if (DFS(row + dr[i], col + dc[i], Maze, visited, path))
            return true;
    }

    path.pop_back();
    return false;
}

// =================================================================
// MAIN - Test DFS
// =================================================================
int main() {
    cout << "=== DFS Test ===" << endl;
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

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<pair<int,int>> path;

    cout << endl << "DFS Path from (0,0) to (" << n-1 << "," << m-1 << "):" << endl;

    if (DFS(0, 0, Maze, visited, path)) {
        for (auto& p : path)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
        cout << "Path length: " << path.size() << endl;
    } else {
        cout << "No Path Found!" << endl;
    }

    return 0;
}
