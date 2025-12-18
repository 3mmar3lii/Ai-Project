#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>  

using namespace std;

// directions: down, up, right, left
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

bool BFS(int startRow, int startCol,
    const vector<vector<int>>& maze,
    vector<pair<int, int>>& path,
    int goalRow,int goalCol)
{
    int n = maze.size();
    int m = maze[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, make_pair(-1, -1)));

    queue<pair<int, int>> q;
    q.push(make_pair(startRow, startCol));
    visited[startRow][startCol] = true;

    bool found = false;

    while (!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();

        int r = cur.first;
        int c = cur.second;

        if (r == goalRow && c == goalCol)
        {
            found = true;
            break;
        }

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nc >= 0 &&
                nr < n && nc < m &&
                maze[nr][nc] == 0 &&
                !visited[nr][nc])
            {
                visited[nr][nc] = true;
                q.push(make_pair(nr, nc));
                parent[nr][nc] = make_pair(r, c);
            }
        }
    }

    if (!found)
        return false;

    // reconstruct path
    int r = goalRow;
    int c = goalCol;

    path.clear();
    while (r != -1 && c != -1)
    {
        path.push_back(make_pair(r, c));
        pair<int, int> p = parent[r][c];
        r = p.first;
        c = p.second;
    }

    reverse(path.begin(), path.end());
    return true;
}

int main()
{
    int n, m;
    cout << "Enter number of rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze (0 = empty, 1 = wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    

    cout << "\nBFS Path:\n";

    int goalRow, goalCol;
    cout << "Enter Goal (row and col) : ";
    cin >> goalRow >> goalCol;

    if (goalRow < 0 || goalCol < 0
        || goalRow >= n || goalCol >= m
        || maze[goalRow][goalCol] == 1
        || maze[0][0] == 1)
    {
        cout << "No Path";
        return 0;
    }
     
    vector<pair<int, int>> path;

    if (BFS(0, 0, maze, path,goalRow,goalCol))
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
