#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <algorithm>

using namespace std;

struct UCSNode {
    int r, c, cost;
    bool operator>(const UCSNode& other) const {
        return cost > other.cost;
    }
};

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

bool UCS(int startRow, int startCol,
    const vector<vector<int>>& maze,
    const vector<vector<int>>& costMatrix,
    vector<pair<int, int>>& path)
{
    int n = maze.size();
    int m = maze[0].size();

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int, int>>> parent(n, vector<pair<int, int>>(m, { -1,-1 }));

    priority_queue<UCSNode, vector<UCSNode>, greater<UCSNode>> pq;
    dist[startRow][startCol] = costMatrix[startRow][startCol];
    pq.push({ startRow, startCol, costMatrix[startRow][startCol] });

    while (!pq.empty())
    {
        UCSNode cur = pq.top(); pq.pop();
        int r = cur.r;
        int c = cur.c;

        if (r == n - 1 && c == m - 1) break;

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nc >= 0 && nr < n && nc < m && maze[nr][nc] == 0)
            {
                int newCost = dist[r][c] + costMatrix[nr][nc];
                if (newCost < dist[nr][nc])
                {
                    dist[nr][nc] = newCost;
                    parent[nr][nc] = { r,c };
                    pq.push({ nr, nc, newCost });
                }
            }
        }
    }

    if (dist[n - 1][m - 1] == INT_MAX)
        return false;

    path.clear();
    int r = n - 1, c = m - 1;
    while (r != -1 && c != -1)
    {
        path.push_back({ r,c });
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
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze (0 = empty, 1 = wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    vector<vector<int>> costMatrix(n, vector<int>(m));
    cout << "Enter COST matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> costMatrix[i][j];

    vector<pair<int, int>> path;
    cout << "\nUCS Path:\n";
    if (UCS(0, 0, maze, costMatrix, path))
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
