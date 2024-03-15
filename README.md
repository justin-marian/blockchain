# Blockchain

This project introduces the concept of `Blockchain` through a `BlockDAG` (`Directed Acyclic Graph`) structure. Unlike traditional blockchains that operate linearly, `BlockDAG` allows for branching and merging of transactions, enabling parallel processing. This approach is a generalization of traditional blockchain technology and is represented using adjacency lists for efficient and scalable graph management.

## Definitions

- **Genesis Block**: The initial block, with no predecessors.
- **Normal Blocks**: Contain transactions and may have multiple predecessors.
- **Directed Acyclic Graph (DAG)**: Ensures no cycles exist, maintaining the blockchain's integrity.

## Detailed Concepts

- `past(Node)`: Blocks referenced directly or indirectly by `Node`, necessary before `Node`.
- `future(Node)`: Blocks that reference `Node`, applicable only after `Node`.
- `anticone(Node)`: Blocks with ambiguous order relative to `Node`.
- `tips(G)`: Blocks in graph `G` with no referencing blocks, indicating recent additions.

## BlockDAG

BlockDAG deviates from the linear block sequence of traditional blockchains by leveraging a Directed Acyclic Graph (DAG) to enable branching and merging transactions for parallel processing.

Utilize adjacency lists for efficient graph representation, ideal for sparse graphs and exploring block connections. The graph initializes from a predefined file detailing vertices, edges, and their connections, populating the adjacency list and an index map for vertex-name mapping.

Adding edges between nodes is crucial, as it defines the BlockDAG's structure by outlining block relationships, including their predecessors and successors.

## K-Cluster

A key concept within this structure is the `k-cluster`, which helps manage the complexity of transaction ordering and consensus.

A `k-cluster` is a subset of nodes within the BlockDAG where each node's `anticone` (blocks with ambiguous ordering relative to this node) intersects with the subset in `k` or fewer other nodes. This concept is pivotal for streamlining the consensus process by limiting the ambiguity in transaction order.

- **K-Cluster Definition:** In a Directed Acyclic Graph (DAG) $\(G = (V, E)\)$, a subset $\(S \subseteq V\)$ is a `k-cluster` if for any node $\(B \in S\)$, it holds that $\(|anticone(B) \cap S| \leq k\)$.
- **Maximum K-Cluster:** For the DAG $\(G = (V, E)\)$, the `maximum k-cluster` ($\(MCS_k\)$) is a subset $\(S^* \subset V\)$ with the largest size satisfying $\(|anticone(B) \cap S^*| \leq k\)$, for every $\(B \in S^*\)$.

The `k-cluster` concept and the algorithm for identifying the `maximum k-cluster` are crucial for enhancing the BlockDAG's efficiency in processing transactions. By reducing order ambiguity among blocks, BlockDAGs can achieve faster consensus and handle a higher volume of transactions compared to traditional blockchain structures.

## Graph Traversal

Traversal operations, such as Breadth-First Search (BFS) and Depth-First Search (DFS), are implemented to explore the graph. These traversals are used to compute the `past`, `future`, and `tips` of a given block, as well as to check for cycles (which should not exist in a valid DAG).

**Past and Future Sets:**
Past and future sets are calculated using graph traversal. Past traverses directly, while Future reverses edges before traversal. These sets reveal block dependencies in BlockDAG.

**Anticone and Tips:**
The Anticone function determines blocks outside past and future sets, resolving order ambiguity. Tips identifies blocks lacking incoming edges, marking recent BlockDAG additions.

**Cycle Detection:**
`HasCycle` ensures BlockDAG's acyclicity, using topological sorting and recursive DFS to mark nodes, identifying back edges indicating cycles.

**Utility Functions:**
The project provides utility functions for linked list and queue manipulation, vital for graph traversal. These ensure efficient memory management and clean handling of dynamic data structures.

## Linked List

Linked lists are used extensively for storing nodes in a manner that facilitates ordered insertion and traversal. The following functions are used to manage linked lists within the BlockDAG:

- **Create_Ord**: Initializes a new list node with a given name. This function is critical for building lists that represent the `past`, `future`, and `anticone` sets of a block.
- **Insert_Ord**: Inserts a node into a linked list in an ordered manner based on the node's name. This is essential for maintaining the sorted order of nodes in sets, which is particularly useful when displaying the sets to the user.
- **Contains_Ord**: Checks if a given name exists within a list. This function is used to determine set membership, such as verifying if a block is part of the `past` or `future` set of another block.
- **Free_Ord**: Frees the memory allocated for a linked list. Proper memory management is crucial to prevent memory leaks and ensure the efficient operation of the BlockDAG system.

## Queue

Queues are used in BFS to manage the nodes being traversed. The following functions manage queue operations:

- **Create_Queue**: Initializes a new queue. This is essential for starting a BFS traversal.
- **Enqueue** and **Dequeue**: Add and remove elements from the queue, respectively. These operations are fundamental to the BFS traversal algorithm.
- **IsEmpty_Queue**: Checks if the queue is empty. This helps determine when the BFS traversal is complete.
- **Free_Queue**: Frees the memory allocated for the queue, emphasizing the importance of memory management in the system.
