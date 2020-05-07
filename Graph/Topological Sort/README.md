# Topological Ordering
  - Definition: the topological ordering of a **directed** graph is a linear ordering of its vertices such that for every directed edge u->v, **u comes before v**
  - There are 2 common ways to find the topoligical order:
  - The 1st way is to use the **reverse** of the traversal path of a DFS
  - The 2nd way is to greedily take all nodes with **in_deg == 0** and push them into the topological ordering, then decrease the in_deg of other nodes accordingly (implementation using a C++ STL queue)
