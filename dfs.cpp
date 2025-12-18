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
    vector<pair<int, int>>& path,
    int goalRow, int goalCol)
{
    int n = maze.size();
    int m = maze[0].size();

    if (r < 0 || c < 0 || r >= n || c >= m)
        return false;

    if (maze[r][c] == 1 || visited[r][c])
        return false;

    visited[r][c] = true;
    path.push_back({ r,c });

    if (r == goalRow && c == goalCol)
        return true;

    for (int i = 0; i < 4; i++)
    {
        if (DFS(r + dr[i], c + dc[i], maze, visited, path, goalRow, goalCol))
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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];
    }


    int goalRow, goalCol;
    cout << "Enter Goal (row and col) : ";
    cin >> goalRow >> goalCol;


    cout << "\nDFS Path:\n";

    if (goalRow < 0 || goalCol < 0
        || goalRow >= n || goalCol >= m
        || maze[goalRow][goalCol] == 1)
    {
        cout << "No Path";
        return 0;
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<pair<int, int>> path;

    if (DFS(0, 0, maze, visited, path, goalRow, goalCol))
    {
        for (int i = 0; i < path.size(); i++)
            cout << "(" << path[i].first << "," << path[i].second << ") ";
    }
    else
    {
        cout << "No Path";
    }

    cout << endl;
    return 0;
}
 