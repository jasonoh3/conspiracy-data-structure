# Weekly Notes

## Week 1 (11-13)

In this week's meeting, we primarily focused on improving and reinforcing the project proposal. We first made the leading question more concrete by detailing how we will use strongly-connected components to characterize conspiracy tweets. We decided to do this by finding the number of strongly connected components for each subgraph in the dataset and then averaging this number across the entire dataset of subgraphs.  Next, we determined how we would weigh the edges in the graph. Each vertex has a timestamp relative to the source node of the tweet; however, the timestamps are not necessarily in non-decreasing order propagating out from the source node. Therefore, we will use the absolute difference between the timestamps of the two nodes that the edge connects as the edge weight. Using this information, we will use Dijkstra's algorithm to determine the shortest weighted path from the source node to the node with the greatest timestamp in the subgraph. This timestamp will be determined through the DFS algorithm. Finally, we clarified how we would resolve errors in the data structure. We decided to resolve these by dropping invalid nodes (invalid id, timestamp) and invalid edges (nonexistent nodes) using the Pandas library in Python.

For the data structure, we have decided to use an adjacency list. This is because we have 3000 subgraphs and would like to construct data structures for each subgraph efficiently. Each algorithm that we will implement involves iterating over the edges of the graph, and only adjacency lists offer the necessary efficiency for these algorithms.

### Data Structure Functions:

- constructor
- insertEdge
- insertVertex
- parseCSV
- incidentEdges

Division of work for the week:

__all implementors required to write applicable tests__

|Name|Tasks|
|---|---|
|Andrew|weight edges, parseCSV, header file|
|Ethan|insertEdge, insertVertex, parseCSV|
|Jason|incidentEdges, constructor|
|Colton|begin DFS|

## Week 2 (11-20)

In this week, we implemented the data structure for our final project. We decided to use an adjacency list because each algorithm we will implement involves iterating over the edges of the graph. Only adjacency lists offer the necessary efficiency for these algorithms. Firstly, the constructor for the class Graph is created, where two files (the node CSV and edge CSV) are inputted and parsed through helper functions (readEdges and readNodes). These helper functions populate their respective nested Node and Edge structs. The edges are weighted during this time using getWeight. Three other functions (insertEdge, insertVertex, incidentEdges) are implemented. insertEdge and insertVertex are used to populate the Node and Edge structs, and the incidentEdges returns a list of edges connected to the inputted node. Other public functions like getNumEdges and getTime will be used for our future algorithms. Finally, test cases check if the Graph constructor and Graph functions work as intended.

## Week 3 (11-27)

In this week, we implemented the graph traversal and depth-first search traversal (DFS) algorithm. We decided to use DFS as our traversal because it is required to implement the strongly connected component algorithm. In the GraphTraversal class, we have all the important/necessary operators (i.e., ++, !=, and *), iterators, and pure virtual functions (e.g., begin, end, add, pop, peek, and empty). In the DFS class, a sub-class of GraphTraversal, we implemented all the pure virtual functions as noted beforehand. Furthermore, for the DFS, we decided that we would DFS each graph individually rather than DFS every graph together. We would DFS every graph in the main. By completing the DFS, we can now continue onto the strongly connected algorithm, which is our next goal.

## Week 4 (12-4)

In this week, we added functionality to DFS to traverse the entire graph if the user chooses to. We started working on the strongly connected component algorithm. We also decided to switch from Floyd Warshall to Dijkstra's algorithm for finding the shortest path. We decided to do this because Dijkstra's algorithm's efficiency is better for our application and adjacency list structure.

## Week 5 (12-11) -- Final week
In this week, we fully implemented, debugged, and finalized our codebase. Depth-first search (DFS), Dijkstra's algorihtm, and Kosaraju's algorithm were fully implemented:

1. The DFS has a switch where we can travel every node and edge or travel to every node connected to the source node and travel to those edges.
2. Dijkstra's algorithm will follow convention and find the shortest weighted path from the start node to the end node.
3. Kosaraju's algorithm will follow convention and find the strongly connected components of a directed graph. 

All of these algorithms are fully tested and debugged. 

For the remaining days, we plan to restructure and refactor the code base such that the final presentation of the code base is human-readable and well-organized, and the README can easily trace each file. We will work on garnering the results of the misinformation dataset and creating our presentation video and paper.
