#include <bits/stdc++.h>
using namespace std;

// =================================================================
// UCS
// =================================================================
struct UCSNode {
    int r, c;
    int cost;
    bool operator>(const UCSNode& other) const {
        return cost > other.cost;
    }
};

vector<pair<int,int>> UCSPath;

bool UCS(int startRow, int startCol,
         const vector<vector<int>>& Maze,
         const vector<vector<int>>& Cost)
{
    int n = Maze.size(), m = Maze[0].size();

    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));

    priority_queue<UCSNode, vector<UCSNode>, greater<UCSNode>> pq;

    dist[startRow][startCol] = Cost[startRow][startCol];
    pq.push({startRow, startCol, Cost[startRow][startCol]});

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    while (!pq.empty()) {
        UCSNode cur = pq.top(); pq.pop();
        int r = cur.r, c = cur.c;

        if (r == n-1 && c == m-1) break;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                Maze[nr][nc] == 0)
            {
                int newCost = dist[r][c] + Cost[nr][nc];

                if (newCost < dist[nr][nc]) {
                    dist[nr][nc] = newCost;
                    parent[nr][nc] = {r,c};
                    pq.push({nr,nc,newCost});
                }
            }
        }
    }

    if (dist[n-1][m-1] == INT_MAX)
        return false;

    UCSPath.clear();
    int r = n-1, c = m-1;

    while (r != -1 && c != -1) {
        UCSPath.push_back({r,c});
        auto p = parent[r][c];
        r = p.first;
        c = p.second;
    }

    reverse(UCSPath.begin(), UCSPath.end());
    return true;
}

// =================================================================
// MAIN - Test UCS
// =================================================================
int main() {
    cout << "=== UCS Test ===" << endl;
    cout << "(0 means empty, 1 means wall)" << endl << endl;

    // Test Maze
    vector<vector<int>> Maze = {
        {0, 0, 1, 0},
        {1, 0, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 0}
    };

    // Cost Matrix (cost to enter each cell)
    vector<vector<int>> Cost = {
        {1, 2, 1, 1},
        {1, 1, 3, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 1}
    };

    int n = Maze.size(), m = Maze[0].size();

    cout << "Maze:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << Maze[i][j] << " ";
        cout << endl;
    }

    cout << endl << "Cost Matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << Cost[i][j] << " ";
        cout << endl;
    }

    cout << endl << "UCS Path from (0,0) to (" << n-1 << "," << m-1 << "):" << endl;

    if (UCS(0, 0, Maze, Cost)) {
        for (auto& p : UCSPath)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
        cout << "Path length: " << UCSPath.size() << endl;
    } else {
        cout << "No Path Found!" << endl;
    }

    return 0;
}
