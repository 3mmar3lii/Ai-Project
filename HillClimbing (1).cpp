#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

double Heuristic(int r, int c, int goalR, int goalC, int choice)
{
    if (choice == 1) 
        return abs(r - goalR) + abs(c - goalC);
    else 
        return sqrt(pow(r - goalR, 2) + pow(c - goalC, 2));
}

bool HillClimbing(int startRow, int startCol,
    const vector<vector<int>>& maze,
    int heuristicChoice,
    vector<pair<int, int>>& path)
{
    int n = maze.size();
    int m = maze[0].size();
    int goalR = n - 1, goalC = m - 1;

    path.clear();
    path.push_back({ startRow, startCol });

    int r = startRow, c = startCol;

    while (!(r == goalR && c == goalC))
    {
        vector<pair<int, int>> neighbors;
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m && maze[nr][nc] == 0)
                neighbors.push_back({ nr,nc });
        }

        if (neighbors.empty()) return false; 

        double bestH = Heuristic(r, c, goalR, goalC, heuristicChoice);
        pair<int, int> next = { r,c };

        for (auto& p : neighbors)
        {
            double h = Heuristic(p.first, p.second, goalR, goalC, heuristicChoice);
            if (h < bestH)
            {
                bestH = h;
                next = p;
            }
        }

        if (next.first == r && next.second == c) return false; 

        r = next.first;
        c = next.second;
        path.push_back({ r,c });
    }

    return true;
}

int main()
{
    int n, m, hcChoice;
    cout << "Enter rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> maze(n, vector<int>(m));
    cout << "Enter maze (0 = empty, 1 = wall):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maze[i][j];

    cout << "Choose heuristic (1 = Manhattan, 2 = Euclidean): ";
    cin >> hcChoice;

    vector<pair<int, int>> path;
    cout << "\nHill Climbing Path:\n";
    if (HillClimbing(0, 0, maze, hcChoice, path))
    {
        for (size_t i = 0; i < path.size(); i++)
            cout << "(" << path[i].first << "," << path[i].second << ") ";
    }
    else
    {
        cout << "No Path (local maxima or dead end)";
    }

    cout << endl;
    return 0;
}
