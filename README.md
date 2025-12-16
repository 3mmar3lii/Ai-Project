# Maze Path Finding

A C++ implementation of various pathfinding algorithms to solve maze navigation problems. The project demonstrates how different search strategies explore and find paths through grid-based mazes.

## Problem Overview

The maze is represented as a 2D grid where:
- **Start Position**: Top-left corner `(0, 0)`
- **Goal Position**: Bottom-right corner `(n-1, m-1)`
- **Movement**: Only through valid, non-obstructed cells

The objective is to determine whether a path exists and, if so, identify it using different algorithmic approaches.

---

## Algorithms Implemented

### Depth-First Search (DFS)

Explores the maze by going as deep as possible before backtracking.

| Property | Description |
|----------|-------------|
| Data Structure | Stack / Recursion |
| Complete | Yes (finds a path if one exists) |
| Optimal | No (not guaranteed shortest path) |
| Memory | Low |
| Time Complexity | `O(n × m)` |

**How it works**: Starts at top-left, moves to neighbors, continues until hitting a dead end, then backtracks to try different directions.

---

### Iterative Deepening Search (IDS)

Combines the benefits of DFS (low memory) and BFS (completeness).

| Property | Description |
|----------|-------------|
| Data Structure | Stack with depth limit |
| Complete | Yes |
| Optimal | Yes (in terms of depth) |
| Memory | Low |
| Time Complexity | `O(n × m × d)` |

**How it works**: Performs DFS with increasing depth limits (0, 1, 2, ...) until the goal is found.

---

### Hill Climbing

A greedy algorithm that always moves toward the cell closest to the goal.

| Property | Description |
|----------|-------------|
| Data Structure | Heuristic-based selection |
| Complete | No (may get stuck) |
| Optimal | No |
| Memory | Very Low |
| Time Complexity | `O(d)` |

**How it works**: At each step, chooses the neighboring cell that minimizes distance to the goal. Can get stuck in local maxima.

---

### Breadth-First Search (BFS)

Explores the maze level by level, checking all nearby cells first.

| Property | Description |
|----------|-------------|
| Data Structure | Queue |
| Complete | Yes |
| Optimal | Yes (shortest path for equal costs) |
| Memory | Higher than DFS |
| Time Complexity | `O(n × m)` |

**How it works**: Explores all neighbors at the current depth before moving to the next level.

---

### Uniform Cost Search (UCS)

Finds the path with the lowest total cost, not just the shortest number of steps.

| Property | Description |
|----------|-------------|
| Data Structure | Priority Queue |
| Complete | Yes |
| Optimal | Yes (minimum cost path) |
| Memory | Moderate |
| Time Complexity | `O((n × m) × log(n × m))` |

**How it works**: Expands nodes with the least cumulative cost first. Works with different movement costs.

---

### A* Search

An informed search algorithm that combines actual cost and heuristic estimation.

| Property | Description |
|----------|-------------|
| Data Structure | Priority Queue |
| Complete | Yes |
| Optimal | Yes (with admissible heuristic) |
| Memory | Moderate |
| Time Complexity | `O((n × m) × log(n × m))` |

**How it works**: Uses `f(n) = g(n) + h(n)` where:
- `g(n)` = cost from start to current node
- `h(n)` = estimated cost from current node to goal

---

## Algorithm Comparison

| Algorithm | Time Complexity | Complete | Optimal | Memory | Best For |
|-----------|-----------------|----------|---------|--------|----------|
| DFS | `O(n × m)` | Yes | No | Low | Simple exploration |
| IDS | `O(n × m × d)` | Yes | Yes | Low | Memory-constrained |
| Hill Climbing | `O(d)` | No | No | Very Low | Fast approximation |
| BFS | `O(n × m)` | Yes | Yes | High | Shortest path (uniform cost) |
| UCS | `O((n×m) log(n×m))` | Yes | Yes | Moderate | Weighted graphs |
| A* | `O((n×m) log(n×m))` | Yes | Yes | Moderate | Best practical choice |

**Notation**:
- `n × m` = Grid dimensions (total cells)
- `d` = Depth of solution (path length)

---

## Project Structure

```
Ai-Project/
├── main.cpp           # Main entry point with all algorithms
├── dfs.cpp            # Depth-First Search implementation
├── bfs.cpp            # Breadth-First Search implementation
├── ids.cpp            # Iterative Deepening Search implementation
├── ucs.cpp            # Uniform Cost Search implementation
├── hill_climbing.cpp  # Hill Climbing implementation
├── DOCUMENTATION.md   # Detailed documentation
└── README.md          # This file
```

---

## Getting Started

### Prerequisites

- C++ Compiler (g++, clang++, or MSVC)
- C++11 or later

### Compilation

```bash
g++ -std=c++11 -o maze main.cpp
```

### Running

```bash
./maze
```

---

## Key Takeaways

- **DFS and BFS** are fast for simple mazes
- **IDS** trades time for low memory usage
- **Hill Climbing** is fast but unreliable
- **UCS and A*** guarantee optimal paths but are slower
- **A*** is generally the best practical choice for real-world applications

---

## Team Contributions

<table>
  <tr>
    <th>Team Member</th>
    <th>Algorithms</th>
  </tr>
  <tr>
    <td>Hassan Ahmed Rashed</td>
    <td rowspan="4">DFS (Depth-First Search)<br>IDS (Iterative Deepening Search)<br>Hill Climbing</td>
  </tr>
  <tr>
    <td>Muhamed Ahmed Abdelhadi</td>
  </tr>
  <tr>
    <td>Ahmed Mahmoud Nagii</td>
  </tr>
  <tr>
    <td>Mohamed Khaled Nouh</td>
  </tr>
  <tr>
    <td>Ammar Alaa Ibrahim</td>
    <td rowspan="4">BFS (Breadth-First Search)<br>UCS (Uniform Cost Search)<br>A* Search</td>
  </tr>
  <tr>
    <td>Mahmoud Khaled Elbrlosy</td>
  </tr>
  <tr>
    <td>Abdallah Mohamed Elkady</td>
  </tr>
  <tr>
    <td>Mahmoud Ahmed Mostafa</td>
  </tr>
</table>

---


