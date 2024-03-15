# Blockchain

This project presents the concepet of `Blockchain` represented through a s BlockDAG (Directed Acyclic Graph) structure, a generalization of traditional blockchain technology allowing for parallel processing of transactions through branching and merging of blocks. The codebase is structured into several key parts, demonstrating the creation, manipulation, and analysis of the BlockDAG structure. Here's an in-depth overview based on the provided implementation:

## Key Concepts

- **Genesis Block**: The origin block from which all other blocks derive. It has no predecessors.
- **Normal Blocks**: Contain transactions, can have one or several preceding blocks.
- **Directed Acyclic Graph (DAG)**: A graph with directed edges where no cycles exist.

## Definitions

- `past(Node)`: Set of blocks directly or indirectly referenced by `Node` that must be applied before `Node`.
- `future(Node)`: Set of blocks that reference `Node` directly or indirectly and can only be applied after `Node`.
- `anticone(Node)`: Set of blocks for which the order with `Node` is ambiguous. Deciding their order is a key challenge.
- `tips(G)`: Blocks in graph `G` with no other blocks referencing them.

## BlockDAG

Unlike traditional blockchains that operate in a linear sequence of blocks, the BlockDAG structure enables a network of transactions that can branch and merge, allowing for parallel processing of transactions. The BlockDAG structure is represented using an adjacency list, a common approach for storing graphs. This representation is efficient in terms of space, especially when the graph is sparse, and is well-suited for exploring the connections between blocks.

The graph is initialized from a file containing the graph's structure, including the number of vertices and edges, and the connections between them. This information is used to populate the adjacency list and the index map, which provides a mapping between vertex names and their indices in the list. Edges between nodes (blocks) are added to the graph. This is a critical operation for constructing the BlockDAG, as it establishes the relationships between blocks, including their predecessors and successors.

## K-Cluster

The BlockDAG framework introduces an innovative approach to blockchain architecture, allowing for parallel processing of transactions. A key concept within this structure is the `k-cluster`, which helps manage the complexity of transaction ordering and consensus.

A `k-cluster` is a subset of nodes within the BlockDAG where each node's `anticone` (blocks with ambiguous ordering relative to this node) intersects with the subset in `k` or fewer other nodes. This concept is pivotal for streamlining the consensus process by limiting the ambiguity in transaction order.

- **K-Cluster Definition:** In a Directed Acyclic Graph (DAG) $\(G = (V, E)\)$, a subset $\(S \subseteq V\)$ is a `k-cluster` if for any node $\(B \in S\)$, it holds that $\(|anticone(B) \cap S| \leq k\)$.
- **Maximum K-Cluster:** For the DAG $\(G = (V, E)\)$, the `maximum k-cluster` ($\(MCS_k\)$) is a subset $\(S^* \subset V\)$ with the largest size satisfying $\(|anticone(B) \cap S^*| \leq k\)$, for every $\(B \in S^*\)$.

The `k-cluster` concept and the algorithm for identifying the `maximum k-cluster` are crucial for enhancing the BlockDAG's efficiency in processing transactions. By reducing order ambiguity among blocks, BlockDAGs can achieve faster consensus and handle a higher volume of transactions compared to traditional blockchain structures.

## Graph Traversal

Traversal operations, such as Breadth-First Search (BFS) and Depth-First Search (DFS), are implemented to explore the graph. These traversals are used to compute the past, future, and tips of a given block, as well as to check for cycles (which should not exist in a valid DAG).

**Past and Future Sets:**
The past and future sets of a node are computed using graph traversal algorithms. The Past function employs a direct traversal, while the Future function first creates a transpose of the graph (reversing the direction of all edges) and then performs the traversal. These sets are crucial for understanding the dependencies between blocks in the BlockDAG.

**Anticone and Tips:**
The Anticone function calculates the set of blocks that are neither in the past nor in the future of a given block, which helps in resolving order ambiguity. The Tips function identifies blocks with no incoming edges, indicating they are the most recent blocks added to the BlockDAG.

**Cycle Detection:**
A vital validation step for the BlockDAG is ensuring it remains acyclic. The HasCycle function utilizes topological sorting to detect cycles, employing a recursive DFS approach to explore the graph and mark nodes during the traversal to identify back edges.

**Utility Functions:**
The project includes several utility functions for manipulating linked lists and queues, which are used in graph traversal operations, and for memory management to ensure efficient and clean handling of dynamic data structures.

## Utility Functions in BlockDAG Implementation

The BlockDAG implementation relies on a set of utility functions designed to support efficient data manipulation, graph traversal, and memory management. These functions are integral to the system's functionality, ensuring smooth operation and the integrity of the BlockDAG structure. Here is an overview of these utility functions:

### Linked List Operations

Linked lists are used extensively for storing nodes in a manner that facilitates ordered insertion and traversal. The following functions are used to manage linked lists within the BlockDAG:

- **Create_Ord**: Initializes a new list node with a given name. This function is critical for building lists that represent the `past`, `future`, and `anticone` sets of a block.
- **Insert_Ord**: Inserts a node into a linked list in an ordered manner based on the node's name. This is essential for maintaining the sorted order of nodes in sets, which is particularly useful when displaying the sets to the user.
- **Contains_Ord**: Checks if a given name exists within a list. This function is used to determine set membership, such as verifying if a block is part of the `past` or `future` set of another block.
- **Free_Ord**: Frees the memory allocated for a linked list. Proper memory management is crucial to prevent memory leaks and ensure the efficient operation of the BlockDAG system.

### Queue Operations

Queues are used in BFS to manage the nodes being traversed. The following functions manage queue operations:

- **Create_Queue**: Initializes a new queue. This is essential for starting a BFS traversal.
- **Enqueue** and **Dequeue**: Add and remove elements from the queue, respectively. These operations are fundamental to the BFS traversal algorithm.
- **IsEmpty_Queue**: Checks if the queue is empty. This helps determine when the BFS traversal is complete.
- **Free_Queue**: Frees the memory allocated for the queue, emphasizing the importance of memory management in the system.
