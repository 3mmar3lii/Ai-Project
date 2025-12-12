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
// BFS
// =================================================================
vector<pair<int,int>> BFSPath;

bool BFS(int startRow, int startCol, const vector<vector<int>>& Maze) {
    int n = Maze.size(), m = Maze[0].size();

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1, -1}));

    queue<pair<int,int>> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    bool found = false;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (r == n - 1 && c == m - 1) {
            found = true;
            break;
        }

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m &&
                Maze[nr][nc] == 0 && !visited[nr][nc]) {

                visited[nr][nc] = true;
                q.push({nr, nc});
                parent[nr][nc] = {r, c};
            }
        }
    }

    BFSPath.clear();

    if (!found) return false;

    int r = n - 1, c = m - 1;
    while (r != -1 && c != -1) {
        BFSPath.push_back({r, c});
        auto p = parent[r][c];
        r = p.first;
        c = p.second;
    }

    reverse(BFSPath.begin(), BFSPath.end());
    return true;
}

// =================================================================
// IDS + DLS
// =================================================================
vector<pair<int,int>> IDSpath;

bool DLS(int row, int col, const vector<vector<int>>& Maze,
         vector<vector<bool>>& visited, int limit)
{
    int n = Maze.size(), m = Maze[0].size();

    if (row < 0 || col < 0 || row >= n || col >= m) return false;
    if (Maze[row][col] == 1 || visited[row][col]) return false;
    if (limit < 0) return false;

    visited[row][col] = true;
    IDSpath.push_back({row, col});

    if (row == n - 1 && col == m - 1) return true;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    for (int i = 0; i < 4; i++) {
        if (DLS(row + dr[i], col + dc[i], Maze, visited, limit - 1))
            return true;
    }

    IDSpath.pop_back();
    visited[row][col] = false;
    return false;
}

bool IDS(int startRow, int startCol, const vector<vector<int>>& Maze)
{
    int n = Maze.size(), m = Maze[0].size();
    int maxDepth = n*m;

    for (int depth = 0; depth <= maxDepth; depth++) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        IDSpath.clear();
        if (DLS(startRow, startCol, Maze, visited, depth))
            return true;
    }

    IDSpath.clear();
    return false;
}

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
// MAIN
// =================================================================
int main() {
    cout << "Maze Problem: Find a path from (0,0) to (n-1,m-1)\n";
    cout << "(0 means empty, 1 means wall)\n\n";

    while (true) {

        int n, m;
        cout << "Enter number of rows and columns: ";
        cin >> n >> m;

        vector<vector<int>> Maze(n, vector<int>(m));

        cout << "Enter Maze:\n";
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> Maze[i][j];

        cout << "\nChoose Algorithm:\n";
        cout << "1 - DFS\n";
        cout << "2 - BFS\n";
        cout << "3 - IDS\n";
        cout << "4 - UCS\n";
        cout << "5 - Hill Climbing\n";

        int choice;
        cin >> choice;

        vector<vector<int>> Cost;
        int hcChoice = 1;

        if (choice == 4) {
            Cost.assign(n, vector<int>(m));
            cout << "Enter COST matrix:\n";
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    cin >> Cost[i][j];
        }
        if (choice == 5) {
            cout << "Choose Heuristic function:\n1 - Manhattan distance\n2 - Euclidean distance\n";
            cin >> hcChoice;
        }

        // solve
        if (choice == 1) {
            cout << "\nDFS Path:\n";
            vector<vector<bool>> visited(n, vector<bool>(m, false));
            vector<pair<int,int>> DFSpath;

            if (DFS(0,0,Maze,visited,DFSpath)) {
                for (auto&p:DFSpath) cout<<"("<<p.first<<","<<p.second<<") ";
                cout<<"\n";
            } else cout<<"No Path\n";
        }

        else if (choice == 2) {
            cout << "\nBFS Path:\n";
            if (BFS(0,0,Maze)) {
                for (auto&p:BFSPath) cout<<"("<<p.first<<","<<p.second<<") ";
                cout<<"\n";
            } else cout<<"No Path\n";
        }

        else if (choice == 3) {
            cout << "\nIDS Path:\n";
            if (IDS(0,0,Maze)) {
                for (auto&p:IDSpath) cout<<"("<<p.first<<","<<p.second<<") ";
                cout<<"\n";
            } else cout<<"No Path\n";
        }

        else if (choice == 4) {
            cout << "\nUCS Path:\n";
            if (UCS(0,0,Maze,Cost)) {
                for (auto&p:UCSPath) cout<<"("<<p.first<<","<<p.second<<") ";
                cout<<"\n";
            } else cout<<"No Path\n";
        }

        else if (choice == 5) {
            cout << "\nHill Climbing Path:\n";
            if (HillClimbing(0,0,Maze,hcChoice)) {
                for (auto&p:HCPath) cout<<"("<<p.first<<","<<p.second<<") ";
                cout<<"\n";
            } else cout<<"No Path (local maxima or dead end)\n";
        }

        cout << "\nType E to exit, or C to continue: ";
        string exitChoice;
        cin >> exitChoice;

        if (exitChoice == "E" || exitChoice == "e")
            break;

        cout << "\n--------------------------------------\n\n";
    }

    return 0;
}
