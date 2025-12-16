#include <iostream>
#include <vector>
#include <utility>
#include <cmath>

using namespace std;

// directions: down, up, right, left
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

bool DFS(int r, int c,
    vector<vector<int>>& maze,
    vector<vector<bool>>& visited,
    vector<pair<int, int>>& path)
{
    int n = maze.size();
    int m = maze[0].size();

    if (r < 0 || c < 0 || r >= n || c >= m)
        return false;

    if (maze[r][c] == 1 || visited[r][c])
        return false;

    visited[r][c] = true;
    path.push_back(make_pair(r, c));

    if (r == n - 1 && c == m - 1)
        return true;

    for (int i = 0; i < 4; i++)
    {
        if (DFS(r + dr[i], c + dc[i], maze, visited, path))
            return true;
    }

    path.pop_back();
    return false;
}

int main()
{
    int n, m;
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<pair<int, int>> path;

    cout << "\nDFS Path:\n";
    if (DFS(0, 0, maze, visited, path))
    {
        for (size_t i = 0; i < path.size(); i++)
            cout << "(" << path[i].first << "," << path[i].second << ") ";
    }
    else
    {
        cout << "No Path";
    }

    cout << endl;
    return 0;
}
