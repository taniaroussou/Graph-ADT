# Graph-ADT
An undirected graph abstract data type in C that consists of basic operations and a shortest path implementation using Dijkstra's algorithm.

# Basic operations
- UGCreate(n): Creates an empty graph.
- UGAddVertex(graph, vertex): Adds a vertex.
- UGRemoveVertex(graph, vertex): Removes a vertex (and all incident edges)
- UGAddEdge(graph, vertex1, vertex2): Adds an edge between two vertices
- UGRemoveEdge(graph, vertex1, vertex2): Removes an edge between two vertices
- UGGetAdjacent(graph, vertex): Returns a list of vertices adjacent to the given one
- UGShortestPath(hash, vertex1, vertex2): Returns the shortest path (list of vertices) between the given ones using Dijkstra’s algorithm. Returns an empty list if there is no such path.
- UGDestroy(graph): Destroys the graph by freeing all reserved memory.

> This implementation uses adjacency lists and vertices are considered strings.


