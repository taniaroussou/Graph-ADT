# Graph-ADT
An undirected graph abstract data type in C that consists of basic operations and a shortest path implementation using Dijkstra's algorithm.

# Basic operations
- UGCreate(): Creates an empty graph.
- UGAddVertex(graph, vertex): Adds a vertex.
- UGRemoveVertex(graph, vertex): Removes a vertex (and all incident edges)
- UGAddEdge(graph, vertex1, vertex2): Adds an edge between two vertices
- UGRemoveEdge(graph, vertex1, vertex2): Removes an edge between two vertices
- UGGetAdjacent(graph, vertex): Returns a list of vertices adjacent to the given one
- UGShortestPath(hash, vertex1, vertex2): Returns the shortest path (list of vertices) between the given ones using Dijkstra’s algorithm. Returns an empty list if there is no such path.
- UGDestroy(graph): Destroys the graph by freeing all reserved memory.

# Compile and run commands

Compile and run: ```make

./graph```

> *This implementation: is based on a hash table with seperate chaining, uses adjacency lists and vertices are considered strings.*

# Hash Table ADT
Implementation of a hash table with seperate chaining. The keys are always strings and the data to be inserted can be of any type.

# Basic operations
- HTCreate(): Creates an empty hash
- HTSize(hash): Returns the number of elements in the hash
- HTGet(hash, key, pitem): Searches for key in the hash. If found, returns true and copies the item in the pitem pointer passed as argument.
- HTInsert(hash, key, item): Inserts a key (with its item) in the hash (replace if exists)
- HTRemove(hash, key): Removes the key from the hash
- HTVisit(hash, visit) : Calls visit(hash, key, item) for all entries in the hash (in arbitrary order). visit is a function given by the user.
- HTDestroy(hash): Destroys the hash by freeing all reserved memory.

# Compile and run commands

Compile: `make`
Run: `./hash_table`
