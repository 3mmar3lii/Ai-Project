# Maze Path Finding

This project implements several algorithms to find a path through a maze.  
The maze is represented as a grid of passable cells and obstacles.  
The start is at the *top-left corner, and the goal is at the **bottom-right corner*.  
Movement is allowed only through valid cells.  
This project demonstrates the use of search and path-finding algorithms in practice.

---

## Algorithms Used

### Depth-First Search (DFS)  
DFS explores the maze by going as deep as possible along one path, then backtracking when a dead end is reached.  
- Uses a stack or recursion  
- Finds a path if one exists  
- Not guaranteed to find the shortest path  

### Iterative Deepening Search (IDS)  
IDS combines DFS and BFS by performing DFS with increasing depth limits until the goal is found.  
- Low memory usage  
- Complete (guarantees a solution)  
- Slower due to repeated searches  

### Hill Climbing  
Hill Climbing is a greedy algorithm that moves toward the cell closest to the goal.  
- Uses a heuristic function (distance to goal)  
- Fast but may get stuck or fail  
- Not guaranteed to find a path  

### Breadth-First Search (BFS)  
BFS explores all neighbors level by level.  
- Uses a queue  
- Complete and finds the shortest path if all moves cost the same  
- Uses more memory than DFS  

### Uniform Cost Search (UCS)  
UCS finds the path with the lowest total cost.  
- Uses a priority queue  
- Complete and optimal  
- Works with different movement costs  

### A* Search  
A* combines cost and heuristic to find the most efficient path.  
- Uses f(n) = g(n) + h(n)  
- Complete and optimal with a good heuristic  
- Faster than UCS and BFS in practice  

---

## Time Complexity Comparison

| Algorithm | Time Complexity | Notes |
|-----------|----------------|-------|
| DFS | O(n × m) | Visits each cell once, may backtrack |
| IDS | O(n × m × d) | Repeats DFS for increasing depths, d = max depth |
| Hill Climbing | O(d) | Moves toward goal using heuristic, may fail |
| BFS | O(n × m) | Explores all reachable cells level by level |
| UCS | O((n × m) log(n × m)) | Uses priority queue based on path cost |
| A* | O((n × m) log(n × m)) | Uses heuristic to guide search efficiently |

*Legend:*  
- n → number of rows in the maze  
- m → number of columns in the maze  
- d → depth of the solution (path length)  

---

## Team Contributions

<table>
  <tr>
    <th>Team Member</th>
    <th>Algorithms</th>
  </tr>
  <tr>
    <td>Hassan Hamed Rashed</td>
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

## Implementation

The source code, execution instructions, and example results are available in the [project repository](#).  
Each algorithm can be run independently to find a path through any maze provided in the input format.

---