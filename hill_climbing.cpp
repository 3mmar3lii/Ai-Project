#include <bits/stdc++.h>
using namespace std;

// =================================================================
// Hill Climbing
// =================================================================
vector<pair<int,int>> HCPath;

double Heuristic(int r, int c, int goalR, int goalC, int choice) {
    if (choice == 1) return abs(r - goalR) + abs(c - goalC); // Manhattan
    else return sqrt(pow(r - goalR,2) + pow(c - goalC,2));   // Euclidean
}

bool HillClimbing(int startRow, int startCol, const vector<vector<int>>& Maze, int heuristicChoice) {
    int n = Maze.size(), m = Maze[0].size();
    int goalR = n-1, goalC = m-1;

    HCPath.clear();
    HCPath.push_back({startRow, startCol});

    int r = startRow, c = startCol;

    while (!(r == goalR && c == goalC)) {
        vector<pair<int,int>> neighbors;
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m && Maze[nr][nc] == 0)
                neighbors.push_back({nr,nc});
        }

        if (neighbors.empty()) return false; // dead end

        double bestH = Heuristic(r,c,goalR,goalC,heuristicChoice);
        pair<int,int> next = {r,c};
        for (auto& p : neighbors) {
            double h = Heuristic(p.first, p.second, goalR, goalC, heuristicChoice);
            if (h < bestH) {
                bestH = h;
                next = p;
            }
        }

        if (next.first == r && next.second == c) return false; // local maxima

        r = next.first;
        c = next.second;
        HCPath.push_back({r,c});
    }

    return true;
}

// =================================================================
// MAIN - Test Hill Climbing
// =================================================================
int main() {
    cout << "=== Hill Climbing Test ===" << endl;
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

    // Test with Manhattan Distance
    cout << endl << "Hill Climbing Path (Manhattan Heuristic):" << endl;
    if (HillClimbing(0, 0, Maze, 1)) {
        for (auto& p : HCPath)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
        cout << "Path length: " << HCPath.size() << endl;
    } else {
        cout << "No Path Found (local maxima or dead end)!" << endl;
    }

    // Test with Euclidean Distance
    cout << endl << "Hill Climbing Path (Euclidean Heuristic):" << endl;
    if (HillClimbing(0, 0, Maze, 2)) {
        for (auto& p : HCPath)
            cout << "(" << p.first << "," << p.second << ") ";
        cout << endl;
        cout << "Path length: " << HCPath.size() << endl;
    } else {
        cout << "No Path Found (local maxima or dead end)!" << endl;
    }

    return 0;
}
