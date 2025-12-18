#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

// Directions: Down, Up, Right, Left
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

// Manhattan distance heuristic
int manhattan_distance(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

struct Node
{
    int r, c;
    int f; // f = g + h
    int g; // cost from start
    bool operator>(const Node& other) const { return f > other.f; }
};

bool AStar(const vector<vector<int>>& maze,
    pair<int, int> start,
    pair<int, int> goal,
    vector<pair<int, int>>& path)
{
    int n = maze.size();
    int m = maze[0].size();

    priority_queue<Node, vector<Node>, greater<Node>> openSet;
    openSet.push({ start.first, start.second, manhattan_distance(start, goal), 0 });

    vector<vector<int>> gScore(n, vector<int>(m, 1e9));
    gScore[start.first][start.second] = 0;

    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, { -1,-1 }));

    vector<vector<bool>> closedSet(n, vector<bool>(m, false));

    while (!openSet.empty())
    {
        Node cur = openSet.top(); openSet.pop();
        int r = cur.r, c = cur.c;

        if (r == goal.first && c == goal.second)
        {
            // reconstruct path
            path.clear();
            while (r != -1 && c != -1)
            {
                path.push_back({ r,c });
                auto p = parent[r][c];
                r = p.first;
                c = p.second;
            }
            reverse(path.begin(), path.end());
            return true;
        }

        if (closedSet[r][c]) continue;
        closedSet[r][c] = true;

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m && maze[nr][nc] == 0)
            {
                int tentative_g = gScore[r][c] + 1;
                if (tentative_g < gScore[nr][nc])
                {
                    gScore[nr][nc] = tentative_g;
                    int f = tentative_g + manhattan_distance({ nr,nc }, goal);
                    parent[nr][nc] = { r,c };
                    openSet.push({ nr, nc, f, tentative_g });
                }
            }
        }
    }

    return false;
}

int main()
{
    int n, m;
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze (0 = empty, 1 = wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    pair<int, int> start = { 0,0 };
    pair<int, int> goal;
 
    cout << "Enter Goal (row and col) : ";
    cin >> goal.first >> goal.second;
    cout << "\nA* Path:\n";

    if (goal.first < 0 || goal.second < 0
        || goal.first >= n || goal.second >= m
        || maze[goal.first][goal.second] == 1
        || maze[0][0] == 1)
    {
        cout << "No Path";
        return 0;
    }


    vector<pair<int, int>> path;
    if (AStar(maze, start, goal, path))
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
