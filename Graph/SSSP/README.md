## Some key points to take note of:
- If the graph is **unweighted**, a simple if BFS can be used instead of Dijkstra
- If the graph has only **2 values of weights** (i.e 0 and 1), a BFS with deque implementation can also be used (this is called **0-1 BFS**)
- For BFS and Dijkstra, the problem of **Single-Source Shortest Path** can be extended into **Multi-Source Shortest Path** by pushing all the starting nodes into the queue/priority queue at the beginning and relax the neighbouring edges as normal
