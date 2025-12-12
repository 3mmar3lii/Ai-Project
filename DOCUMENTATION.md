# 🧭 Maze Pathfinding Algorithms - Complete Documentation

This documentation explains **5 pathfinding algorithms** used to find a path from the **top-left corner (0,0)** to the **bottom-right corner (n-1, m-1)** of a maze.

---

## 📋 Table of Contents

1. [The Maze Concept](#the-maze-concept)
2. [DFS (Depth-First Search)](#1-dfs-depth-first-search)
3. [BFS (Breadth-First Search)](#2-bfs-breadth-first-search)
4. [IDS (Iterative Deepening Search)](#3-ids-iterative-deepening-search)
5. [UCS (Uniform Cost Search)](#4-ucs-uniform-cost-search)
6. [Hill Climbing](#5-hill-climbing)
7. [Complete Mock Examples](#complete-mock-examples)
8. [Algorithm Comparison](#algorithm-comparison)

---

## The Maze Concept

### What is the Maze?
- A **2D grid** of cells
- `0` = **empty cell** (you can walk here)
- `1` = **wall** (blocked, cannot pass)

### The Goal
Find a path from **Start (0,0)** → **End (n-1, m-1)**

### Movement Directions
All algorithms move in **4 directions**:
```
        UP (-1, 0)
           ↑
LEFT (0,-1) ← [CELL] → RIGHT (0,+1)
           ↓
       DOWN (+1, 0)
```

The direction arrays in code:
```cpp
int dr[4] = {1, -1, 0, 0};  // row changes: down, up, stay, stay
int dc[4] = {0, 0, 1, -1};  // col changes: stay, stay, right, left
```

---

## 1. DFS (Depth-First Search)

### 🎯 Simple Explanation
Imagine you're in a maze with a flashlight. You pick ONE direction and keep going as far as possible. If you hit a wall or dead end, you **backtrack** and try another direction.

**Think of it like:** "Go deep first, then explore other paths"

### 🔄 How It Works Step-by-Step

```
START (0,0)
    ↓
  Go DOWN as far as possible
    ↓
  Hit dead end? BACKTRACK
    ↓
  Try another direction
    ↓
  Repeat until you reach END
```

### 📝 Code Breakdown

```cpp
bool DFS(int row, int col, vector<vector<int>>& Maze,
         vector<vector<bool>>& visited, vector<pair<int,int>>& path)
{
    // STEP 1: Get maze dimensions
    int n = Maze.size();      // number of rows
    int m = Maze[0].size();   // number of columns

    // STEP 2: Check if out of bounds
    if (row < 0 || col < 0 || row >= n || col >= m)
        return false;  // Invalid position!

    // STEP 3: Check if wall or already visited
    if (Maze[row][col] == 1 || visited[row][col])
        return false;  // Can't go here!

    // STEP 4: Mark as visited and add to path
    visited[row][col] = true;
    path.push_back({row, col});

    // STEP 5: Check if we reached the goal!
    if (row == n - 1 && col == m - 1)
        return true;  // 🎉 Found it!

    // STEP 6: Try all 4 directions recursively
    static int dr[4] = {1, -1, 0, 0};  // down, up, stay, stay
    static int dc[4] = {0, 0, 1, -1};  // stay, stay, right, left

    for (int i = 0; i < 4; i++) {
        if (DFS(row + dr[i], col + dc[i], Maze, visited, path))
            return true;  // Found path through this direction!
    }

    // STEP 7: Dead end - BACKTRACK!
    path.pop_back();  // Remove current cell from path
    return false;
}
```

### 🎮 Visual Mock Example

**Maze:**
```
  Col: 0   1   2
Row 0: [0] [1] [0]    0 = empty, 1 = wall
Row 1: [0] [0] [0]    Start: (0,0)
Row 2: [1] [0] [0]    Goal:  (2,2)
```

**DFS Execution:**
```
Step 1: At (0,0) → mark visited, add to path
        Path: [(0,0)]
        
Step 2: Try DOWN → (1,0) ✓ valid
        At (1,0) → mark visited, add to path
        Path: [(0,0), (1,0)]
        
Step 3: Try DOWN → (2,0) ✗ WALL!
        Try UP → (0,0) ✗ already visited!
        Try RIGHT → (1,1) ✓ valid
        At (1,1) → mark visited, add to path
        Path: [(0,0), (1,0), (1,1)]
        
Step 4: Try DOWN → (2,1) ✓ valid
        At (2,1) → mark visited, add to path
        Path: [(0,0), (1,0), (1,1), (2,1)]
        
Step 5: Try DOWN → (3,1) ✗ out of bounds!
        Try RIGHT → (2,2) ✓ valid
        At (2,2) → THIS IS THE GOAL! 🎉
        
Final Path: [(0,0), (1,0), (1,1), (2,1), (2,2)]
```

### ✅ Pros and ❌ Cons

| Pros | Cons |
|------|------|
| Uses less memory | May not find shortest path |
| Simple to implement | Can get stuck in long paths |
| Good for deep solutions | Not optimal |

---

## 2. BFS (Breadth-First Search)

### 🎯 Simple Explanation
Imagine you're the center of ripples in water. You explore **ALL cells at distance 1** first, then **ALL cells at distance 2**, and so on. This guarantees the **shortest path** (in terms of steps).

**Think of it like:** "Explore all neighbors first, then their neighbors"

### 🔄 How It Works Step-by-Step

```
START (0,0)
    ↓
Add to queue
    ↓
While queue not empty:
  - Take front cell
  - Add ALL valid neighbors to queue
  - Track who is parent of whom
    ↓
Reached END? → Reconstruct path from parents
```

### 📝 Code Breakdown

```cpp
bool BFS(int startRow, int startCol, const vector<vector<int>>& Maze) {
    int n = Maze.size(), m = Maze[0].size();

    // Keep track of visited cells
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    
    // Remember who we came from (for path reconstruction)
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1, -1}));

    // The queue - FIFO (First In, First Out)
    queue<pair<int,int>> q;
    q.push({startRow, startCol});
    visited[startRow][startCol] = true;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    bool found = false;

    while (!q.empty()) {
        // Get the FRONT of the queue
        auto [r, c] = q.front();
        q.pop();

        // Check if we reached the goal
        if (r == n - 1 && c == m - 1) {
            found = true;
            break;
        }

        // Explore all 4 neighbors
        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d], nc = c + dc[d];
            
            // Check if valid and not visited
            if (nr >= 0 && nc >= 0 && nr < n && nc < m &&
                Maze[nr][nc] == 0 && !visited[nr][nc]) {

                visited[nr][nc] = true;
                q.push({nr, nc});        // Add to queue
                parent[nr][nc] = {r, c}; // Remember parent
            }
        }
    }

    // Reconstruct path by following parents backward
    BFSPath.clear();
    if (!found) return false;

    int r = n - 1, c = m - 1;
    while (r != -1 && c != -1) {
        BFSPath.push_back({r, c});
        auto p = parent[r][c];
        r = p.first;
        c = p.second;
    }

    reverse(BFSPath.begin(), BFSPath.end());  // Flip to get start→end
    return true;
}
```

### 🎮 Visual Mock Example

**Maze:**
```
  Col: 0   1   2
Row 0: [0] [0] [0]    Start: (0,0)
Row 1: [0] [1] [0]    Goal:  (2,2)
Row 2: [0] [0] [0]
```

**BFS Execution (Level by Level):**
```
LEVEL 0:
  Queue: [(0,0)]
  Processing (0,0)
  
LEVEL 1: (distance 1 from start)
  Found neighbors: (1,0), (0,1)
  Queue: [(1,0), (0,1)]
  
LEVEL 2: (distance 2 from start)
  Processing (1,0) → neighbor: (2,0)
  Processing (0,1) → neighbor: (0,2)
  Queue: [(2,0), (0,2)]
  
LEVEL 3: (distance 3 from start)
  Processing (2,0) → neighbor: (2,1)
  Processing (0,2) → neighbor: (1,2)
  Queue: [(2,1), (1,2)]
  
LEVEL 4: (distance 4 from start)
  Processing (2,1) → neighbor: (2,2) 🎉 GOAL!
  
Path reconstruction (following parents backward):
  (2,2) ← (2,1) ← (2,0) ← (1,0) ← (0,0)
  
Final Path: [(0,0), (1,0), (2,0), (2,1), (2,2)]
Shortest path: 5 cells (4 moves)
```

### ✅ Pros and ❌ Cons

| Pros | Cons |
|------|------|
| **Guarantees shortest path** | Uses more memory |
| Complete (finds solution if exists) | Explores many cells |
| Optimal for unweighted graphs | |

---

## 3. IDS (Iterative Deepening Search)

### 🎯 Simple Explanation
Combine the **best of both worlds**: DFS's memory efficiency + BFS's completeness.

Run DFS multiple times:
- First with **depth limit 0** (only start)
- Then with **depth limit 1** (1 step away)
- Then with **depth limit 2** (2 steps away)
- Keep increasing until you find the goal!

**Think of it like:** "Try short paths first, then gradually try longer ones"

### 🔄 How It Works

```
for depth = 0 to maxDepth:
    Run DFS with limit = depth
    If found → return path
    Else → increase depth and try again
```

### 📝 Code Breakdown

```cpp
// DLS = Depth-Limited Search (DFS with a limit)
bool DLS(int row, int col, const vector<vector<int>>& Maze,
         vector<vector<bool>>& visited, int limit)
{
    int n = Maze.size(), m = Maze[0].size();

    // Boundary checks
    if (row < 0 || col < 0 || row >= n || col >= m) return false;
    if (Maze[row][col] == 1 || visited[row][col]) return false;
    
    // IMPORTANT: Check depth limit!
    if (limit < 0) return false;  // Can't go deeper!

    visited[row][col] = true;
    IDSpath.push_back({row, col});

    // Goal check
    if (row == n - 1 && col == m - 1) return true;

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    // Try all directions with reduced limit
    for (int i = 0; i < 4; i++) {
        if (DLS(row + dr[i], col + dc[i], Maze, visited, limit - 1))
            return true;
    }

    // Backtrack - IMPORTANT: unmark for next iterations!
    IDSpath.pop_back();
    visited[row][col] = false;  // Allow revisiting in next depth iteration
    return false;
}

// IDS = Iterative Deepening Search
bool IDS(int startRow, int startCol, const vector<vector<int>>& Maze)
{
    int n = Maze.size(), m = Maze[0].size();
    int maxDepth = n * m;  // Maximum possible path length

    // Try each depth level
    for (int depth = 0; depth <= maxDepth; depth++) {
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        IDSpath.clear();
        
        if (DLS(startRow, startCol, Maze, visited, depth))
            return true;  // Found at this depth!
    }

    IDSpath.clear();
    return false;
}
```

### 🎮 Visual Mock Example

**Maze:**
```
  Col: 0   1
Row 0: [0] [0]    Start: (0,0)
Row 1: [0] [0]    Goal:  (1,1)
```

**IDS Execution:**
```
═══ Depth Limit = 0 ═══
  Can only stay at (0,0)
  Goal is (1,1) → NOT FOUND
  
═══ Depth Limit = 1 ═══
  (0,0) → try DOWN (1,0) ← limit becomes 0
    At (1,0), can't go further (limit=0)
    Not the goal → BACKTRACK
  (0,0) → try RIGHT (0,1) ← limit becomes 0
    At (0,1), can't go further (limit=0)
    Not the goal → BACKTRACK
  NOT FOUND at depth 1
  
═══ Depth Limit = 2 ═══
  (0,0) → DOWN (1,0) ← limit=1
    (1,0) → try DOWN ← out of bounds
    (1,0) → try RIGHT (1,1) ← limit=0
      At (1,1) → THIS IS THE GOAL! 🎉
      
Final Path: [(0,0), (1,0), (1,1)]
Found at depth 2!
```

### ✅ Pros and ❌ Cons

| Pros | Cons |
|------|------|
| Memory efficient like DFS | Repeats work at each depth |
| Finds shortest path (like BFS) | Slower for deep solutions |
| Complete and optimal | |

---

## 4. UCS (Uniform Cost Search)

### 🎯 Simple Explanation
Like BFS, but each cell has a **COST** to enter it. We always expand the **cheapest total path** first. This finds the **minimum cost path**, not just the shortest by steps.

**Think of it like:** "Always pick the cheapest route so far"

**Real-world analogy:** GPS navigation choosing the fastest/cheapest route, not just the one with fewest turns.

### 🔄 How It Works

```
Use a PRIORITY QUEUE (min-heap)
    ↓
Always process the cell with LOWEST total cost first
    ↓
Update costs if we find cheaper paths
    ↓
Stop when we reach the goal
```

### 📝 Code Breakdown

```cpp
// Node structure with cost for priority queue
struct UCSNode {
    int r, c;      // position
    int cost;      // total cost to reach here
    
    // For min-heap: lower cost = higher priority
    bool operator>(const UCSNode& other) const {
        return cost > other.cost;
    }
};

bool UCS(int startRow, int startCol,
         const vector<vector<int>>& Maze,
         const vector<vector<int>>& Cost)  // NEW: cost matrix!
{
    int n = Maze.size(), m = Maze[0].size();

    // Track minimum cost to reach each cell
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    vector<vector<pair<int,int>>> parent(n, vector<pair<int,int>>(m, {-1,-1}));

    // MIN-HEAP priority queue
    priority_queue<UCSNode, vector<UCSNode>, greater<UCSNode>> pq;

    // Start with cost of starting cell
    dist[startRow][startCol] = Cost[startRow][startCol];
    pq.push({startRow, startCol, Cost[startRow][startCol]});

    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    while (!pq.empty()) {
        UCSNode cur = pq.top(); 
        pq.pop();
        int r = cur.r, c = cur.c;

        // Goal reached!
        if (r == n-1 && c == m-1) break;

        // Explore neighbors
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                Maze[nr][nc] == 0)
            {
                // Calculate new cost
                int newCost = dist[r][c] + Cost[nr][nc];

                // Found a CHEAPER path to this cell!
                if (newCost < dist[nr][nc]) {
                    dist[nr][nc] = newCost;
                    parent[nr][nc] = {r, c};
                    pq.push({nr, nc, newCost});
                }
            }
        }
    }

    // Reconstruct path
    if (dist[n-1][m-1] == INT_MAX) return false;

    UCSPath.clear();
    int r = n-1, c = m-1;
    while (r != -1 && c != -1) {
        UCSPath.push_back({r, c});
        auto p = parent[r][c];
        r = p.first;
        c = p.second;
    }
    reverse(UCSPath.begin(), UCSPath.end());
    return true;
}
```

### 🎮 Visual Mock Example

**Maze:**
```
  Col: 0   1   2
Row 0: [0] [0] [0]
Row 1: [0] [1] [0]
Row 2: [0] [0] [0]
```

**Cost Matrix:**
```
  Col: 0   1   2
Row 0: [1] [5] [1]     ← Cost to ENTER each cell
Row 1: [1] [X] [1]     (X = wall, cost doesn't matter)
Row 2: [1] [1] [1]
```

**UCS Execution:**
```
Start: (0,0) with cost 1
Priority Queue: [{(0,0), cost=1}]

Step 1: Pop (0,0), cost=1
  Neighbors: (1,0) cost=1+1=2, (0,1) cost=1+5=6
  PQ: [{(1,0), 2}, {(0,1), 6}]

Step 2: Pop (1,0), cost=2  ← CHEAPEST!
  Neighbors: (2,0) cost=2+1=3
  PQ: [{(2,0), 3}, {(0,1), 6}]

Step 3: Pop (2,0), cost=3  ← CHEAPEST!
  Neighbors: (2,1) cost=3+1=4
  PQ: [{(2,1), 4}, {(0,1), 6}]

Step 4: Pop (2,1), cost=4  ← CHEAPEST!
  Neighbors: (2,2) cost=4+1=5
  PQ: [{(2,2), 5}, {(0,1), 6}]

Step 5: Pop (2,2), cost=5 → GOAL! 🎉

Path: (0,0) → (1,0) → (2,0) → (2,1) → (2,2)
Total Cost: 5

Note: We avoided (0,1) because it costs 5 to enter!
```

### ✅ Pros and ❌ Cons

| Pros | Cons |
|------|------|
| Finds **minimum cost** path | Uses more memory |
| Handles weighted graphs | Slower than BFS for unweighted |
| Optimal and complete | |

---

## 5. Hill Climbing

### 🎯 Simple Explanation
A **greedy** algorithm that always moves to the neighbor that **looks closest to the goal**. It uses a **heuristic** (estimate) to decide.

**Think of it like:** "Always walk towards the mountain peak, don't look back"

**Heuristics used:**
1. **Manhattan Distance:** |x1-x2| + |y1-y2| (L-shaped path)
2. **Euclidean Distance:** √((x1-x2)² + (y1-y2)²) (straight line)

### 🔄 How It Works

```
Start at current position
    ↓
Calculate heuristic for ALL neighbors
    ↓
Move to the neighbor with LOWEST heuristic (closest to goal)
    ↓
Repeat until goal OR stuck (local maxima/dead end)
```

### 📝 Code Breakdown

```cpp
// Heuristic function - estimates distance to goal
double Heuristic(int r, int c, int goalR, int goalC, int choice) {
    if (choice == 1) 
        return abs(r - goalR) + abs(c - goalC);      // Manhattan
    else 
        return sqrt(pow(r - goalR, 2) + pow(c - goalC, 2)); // Euclidean
}

bool HillClimbing(int startRow, int startCol, 
                  const vector<vector<int>>& Maze, 
                  int heuristicChoice) 
{
    int n = Maze.size(), m = Maze[0].size();
    int goalR = n - 1, goalC = m - 1;

    HCPath.clear();
    HCPath.push_back({startRow, startCol});

    int r = startRow, c = startCol;

    while (!(r == goalR && c == goalC)) {
        // Find all valid neighbors
        vector<pair<int,int>> neighbors;
        int dr[4] = {1, -1, 0, 0};
        int dc[4] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i], nc = c + dc[i];
            if (nr >= 0 && nc >= 0 && nr < n && nc < m && Maze[nr][nc] == 0)
                neighbors.push_back({nr, nc});
        }

        // Dead end - no neighbors!
        if (neighbors.empty()) return false;

        // Find best neighbor (lowest heuristic)
        double bestH = Heuristic(r, c, goalR, goalC, heuristicChoice);
        pair<int,int> next = {r, c};
        
        for (auto& p : neighbors) {
            double h = Heuristic(p.first, p.second, goalR, goalC, heuristicChoice);
            if (h < bestH) {
                bestH = h;
                next = p;
            }
        }

        // Local maxima - can't find better neighbor!
        if (next.first == r && next.second == c) return false;

        // Move to best neighbor
        r = next.first;
        c = next.second;
        HCPath.push_back({r, c});
    }

    return true;
}
```

### 🎮 Visual Mock Example

**Maze:**
```
  Col: 0   1   2
Row 0: [0] [0] [0]
Row 1: [0] [1] [0]
Row 2: [0] [0] [0]

Goal: (2,2)
```

**Hill Climbing with Manhattan Distance:**
```
At (0,0): h = |0-2| + |0-2| = 4
  Neighbors:
    (1,0): h = |1-2| + |0-2| = 3 ✓ BETTER!
    (0,1): h = |0-2| + |1-2| = 3 ✓ (same)
  Move to (1,0) [first found with lower h]
  Path: [(0,0), (1,0)]

At (1,0): h = 3
  Neighbors:
    (0,0): h = 4 (worse)
    (2,0): h = |2-2| + |0-2| = 2 ✓ BETTER!
  Move to (2,0)
  Path: [(0,0), (1,0), (2,0)]

At (2,0): h = 2
  Neighbors:
    (1,0): h = 3 (worse)
    (2,1): h = |2-2| + |1-2| = 1 ✓ BETTER!
  Move to (2,1)
  Path: [(0,0), (1,0), (2,0), (2,1)]

At (2,1): h = 1
  Neighbors:
    (2,0): h = 2 (worse)
    (2,2): h = |2-2| + |2-2| = 0 ✓ GOAL!
  Move to (2,2)
  
Final Path: [(0,0), (1,0), (2,0), (2,1), (2,2)] 🎉
```

### ⚠️ The Problem: Local Maxima

**Maze where Hill Climbing FAILS:**
```
  Col: 0   1   2
Row 0: [0] [1] [0]
Row 1: [0] [1] [0]
Row 2: [0] [0] [0]
```

```
At (0,0): h = 4
  Only neighbor: (1,0) with h = 3
  Move to (1,0)

At (1,0): h = 3
  Neighbors:
    (0,0): h = 4 (worse)
    (2,0): h = 2 ✓
  Move to (2,0)

At (2,0): h = 2
  Neighbors:
    (1,0): h = 3 (worse)
    (2,1): h = 1 ✓
  Move to (2,1)

At (2,1): h = 1
  Neighbors:
    (2,0): h = 2 (worse)
    (2,2): h = 0 ✓ GOAL!

Still works here, but...
```

**Maze where it's STUCK:**
```
  Col: 0   1   2
Row 0: [0] [0] [1]
Row 1: [0] [1] [0]
Row 2: [1] [0] [0]
```

At some point, all neighbors are **worse or equal** → **LOCAL MAXIMA** → FAILS!

### ✅ Pros and ❌ Cons

| Pros | Cons |
|------|------|
| Very fast | **Not complete** (can get stuck) |
| Simple | **Not optimal** |
| Low memory | Fails on local maxima |

---

## Complete Mock Examples

### Example 1: Simple 3x3 Maze

**Input:**
```
Rows: 3, Cols: 3
Maze:
0 0 0
0 1 0
0 0 0
```

**Visual:**
```
[S] [ ] [ ]     S = Start (0,0)
[ ] [█] [ ]     █ = Wall
[ ] [ ] [E]     E = End (2,2)
```

**Results:**

| Algorithm | Path | Notes |
|-----------|------|-------|
| DFS | (0,0)→(1,0)→(2,0)→(2,1)→(2,2) | Goes deep first |
| BFS | (0,0)→(0,1)→(0,2)→(1,2)→(2,2) | Shortest path |
| IDS | (0,0)→(0,1)→(0,2)→(1,2)→(2,2) | Same as BFS |
| UCS | Depends on costs | Cheapest path |
| Hill Climbing | (0,0)→(1,0)→(2,0)→(2,1)→(2,2) | Greedy choice |

---

### Example 2: No Path Exists

**Input:**
```
Rows: 2, Cols: 2
Maze:
0 1
1 0
```

**Visual:**
```
[S] [█]
[█] [E]
```

**Result:** All algorithms return **"No Path"** because the goal is unreachable!

---

### Example 3: UCS with Different Costs

**Maze:**
```
0 0 0
0 0 0
0 0 0
```

**Cost Matrix:**
```
1  10  1
1  10  1
1   1  1
```

**Two possible paths:**
1. **Top path:** (0,0)→(0,1)→(0,2)→(1,2)→(2,2) = 1+10+1+1+1 = **14**
2. **Bottom path:** (0,0)→(1,0)→(2,0)→(2,1)→(2,2) = 1+1+1+1+1 = **5**

**UCS Result:** Bottom path (cost 5) ✓

---

## Algorithm Comparison

| Feature | DFS | BFS | IDS | UCS | Hill Climbing |
|---------|-----|-----|-----|-----|---------------|
| **Finds shortest path?** | ❌ | ✅ | ✅ | ✅ (by cost) | ❌ |
| **Complete?** | ✅ | ✅ | ✅ | ✅ | ❌ |
| **Memory usage** | Low | High | Low | High | Low |
| **Speed** | Fast | Medium | Slow | Medium | Very Fast |
| **Best for** | Any path | Shortest path | Limited memory | Weighted graphs | Quick estimate |
| **Uses costs?** | ❌ | ❌ | ❌ | ✅ | ❌ |
| **Uses heuristic?** | ❌ | ❌ | ❌ | ❌ | ✅ |

---

## Quick Reference: When to Use What?

| Scenario | Best Algorithm |
|----------|----------------|
| Just need ANY path | **DFS** |
| Need SHORTEST path (by steps) | **BFS** |
| Limited memory, need shortest | **IDS** |
| Each cell has different cost | **UCS** |
| Quick approximate path | **Hill Climbing** |

---

## How to Run the Program

```
1. Compile: g++ main.cpp -o maze
2. Run: ./maze

3. Enter rows and columns: 3 3
4. Enter maze:
   0 0 0
   0 1 0
   0 0 0

5. Choose algorithm: 2 (for BFS)

6. See the path!
```

---

## Key Concepts to Remember

1. **`visited` array** - Prevents infinite loops
2. **`parent` array** - Reconstructs the path backward
3. **Direction arrays `dr` and `dc`** - Move in 4 directions
4. **Backtracking** - DFS/IDS remove cell from path when stuck
5. **Priority Queue** - UCS always picks cheapest first
6. **Heuristic** - Hill Climbing estimates distance to goal

---

*Happy pathfinding! 🎮*
