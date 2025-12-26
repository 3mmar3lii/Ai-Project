#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

// directions: down, up, right, left
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

bool DLS(int r, int c,
    const vector<vector<int>>& maze,
    vector<vector<bool>>& visited,
    vector<pair<int, int>>& path,
    int limit, int goalRow, int goalCol)
{
    int n = maze.size();
    int m = maze[0].size();

    if (r < 0 || c < 0 || r >= n || c >= m)
        return false;
    if (maze[r][c] == 1 || visited[r][c]) 
        return false;

    if (limit < 0) 
        return false;

    visited[r][c] = true;
    path.push_back(make_pair(r, c));

    if (r == goalRow && c == goalCol) 
        return true;

    for (int i = 0; i < 4; i++)
    {
        if (DLS(r + dr[i], c + dc[i], maze, visited, path, limit - 1,goalRow,goalCol))
            return true;
    }

    path.pop_back();
   // visited[r][c] = false;
    return false;
}

bool IDS(int startRow, int startCol,
    const vector<vector<int>>& maze,
    vector<pair<int, int>>& path,
    int goalRow,int goalCol)
{
    int n = maze.size();
    int m = maze[0].size();
    long long maxDepth = n * m;

    for (int depth = 0; depth <= maxDepth; depth++)
    {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        path.clear();
        if (DLS(startRow, startCol, maze, visited, path, depth,goalRow,goalCol))
            return true;
    }

    path.clear();
    return false;
}

int main()
{
    int n, m;
    cout << "Enter number of rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze (0 = empty, 1 = wall):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];
    }

    int goalRow, goalCol;
    cout << "Enter Goal (row and col) : ";
    cin >> goalRow >> goalCol;


    vector<pair<int, int>> path;

    cout << "\nIDS Path:\n";


    if (goalRow < 0 || goalCol < 0
        || goalRow >= n || goalCol >= m
        || maze[goalRow][goalCol] == 1
        || maze[0][0] == 1)
    {
        cout << "No Path";
        return 0;
    }


    if (IDS(0, 0, maze, path, goalRow, goalCol))
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
