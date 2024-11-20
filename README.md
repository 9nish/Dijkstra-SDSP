# Single Destination Shortest Paths (Dijkstra's Algorithm)

This project implements **Dijkstra's Algorithm** to solve the **Single Destination Shortest Paths** problem in graphs with non-negative edges. The program is built entirely from scratch in C, including custom implementations for data structures like the **min-heap**. This implementation demonstrates algorithmic skills, data structure design, and low-level programming.

## Features
- Reads graph data from a file (`adjacencylist.txt`) in adjacency list format.
- Implements a **priority queue** as a min-heap to optimize Dijkstra's algorithm.
- Calculates the shortest paths and distances from all vertices to a single destination vertex.
- Outputs paths and distances in the required format, with `NO PATH` for unreachable vertices.

## Files
- `PES1UG19CS305_H.h`: Header file with function prototypes and data structure definitions.
- `PES1UG19CS305_F.c`: Implementation file with function definitions.
- `PES1UG19CS305_C.c`: Client/driver code to execute the program.
- `adjacencylist.txt`: Input file representing the graph in adjacency list format.

## Input Format
- The input file, `adjacencylist.txt`, contains the graph data:
  1. The first line specifies the number of vertices.
  2. Subsequent lines list the vertex number followed by pairs of neighboring vertices and edge weights.
  3. Example:
     ```plaintext
     4
     1 2 4 3 5 4 5
     4 1 7 3 3
     2 1 3 4 10
     ```
  - This describes a graph with 4 vertices:
    - Vertex `1` connects to `2` (weight `4`), `3` (weight `5`), `4` (weight `5`).
    - Vertex `4` connects to `1` (weight `7`), `3` (weight `3`).
    - Vertex `2` connects to `1` (weight `3`), `4` (weight `10`).

## Output Format
- Each line contains the shortest path from a vertex to the destination (last vertex), followed by the path's total weight.
- Example:
  ```plaintext
  1 1 4 5
  2 2 1 4 8
  3 NO PATH
  ```

## How to Run
1. Compile the files:
   ```bash
   gcc -c PES1UG19CS305_F.c
   gcc -c PES1UG19CS305_C.c
   gcc -o dijkstra PES1UG19CS305_F.o PES1UG19CS305_C.o -lm
   ```
2. Execute the program
    ./dijkstra
3. Modify adjacencylist.txt to test with different graphs. Follow the input format specified in the assignment description.

## Context
- This project was completed as part of the UE19CS251 - Design and Analysis of Algorithms course at PES University. The program adheres to the assignment requirements for implementing custom data structures and algorithms.

## References
- [Assignment Description (UE19CS251)](UE19CS251_DAA_Assignment_II.pdf)