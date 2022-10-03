# CS 225 Final Project

## Introduction

This project uses graph algorithms to understand the difference in social network structure of misinformation vs. non-misinformation tweets using [The WICO Graph Dataset](https://datasets.simula.no/wico-graph/).

## Deliverables 

- [Written report](https://github-dev.cs.illinois.edu/cs225-fa21/cbrunner-ethanbg2-jasonoh3-aorals2/blob/main/project-info/report.md)
- [Presentation](https://drive.google.com/file/d/1LJ5d06L81Ign9cu7c3R4uJWQfOx66O0k/view?usp=sharing) and [slides](https://www.canva.com/design/DAEyQ_CjX8o/vWUifHGMLb1em26csozz4Q/view?utm_content=DAEyQ_CjX8o&utm_campaign=designshare&utm_medium=link&utm_source=sharebutton)

## Project Structure

```
.
├── data
│   └── wico-graph
├── project-info
├── src
│   ├── algorithms
│   │   ├── dfs
│   │   ├── dijkstra
│   │   └── stronglyConnected
│   └── graph
├── tests
│   └── data
├── main.cpp
└── wico_graph_results.csv
```

The project codebase is located in `src`, where the three graph algorithms can be found in the `algorithms` directory. The `graph` directory contains the data structure used to represent the WICO graphs for analysis.

Tests for the implemented algorithms and data structures along with test datasets reside in the `tests` directory and the `data` subdirectory of `tests` respectively. 

Information about the dataset is located in the `data` directory. The full dataset on which the analysis is run is located in the `wico-graph` sub-directory.

All project information, including the proposal, weekly reports, and contract can be found in the `project-info` directory.

Driver code for running a basic analysis on the dataset is in the `main.cpp` file. Project results can be found in the file `wico_graph_results.csv` in the project root directory.

## Building and Running

To build the main executable, from the project root directory run

```
make
```

To run the main executable, from the project root directory run

```
./main
```

## Testing

To run the full test suite, from the project root directory run
```
make clean
make -j test
./test
```

### Test Strategy

The test suite tests all components of the codebase, including the graph data structure and each of the algorithms, namely: Depth-First Search, Kosaraju's Strongly Connected Components, and Dijkstra's Shortest Path.

__NOTE: Tests are run using graph samples pulled directly from the dataset along with custom, handmade graphs. All samples include illustrations for visual analysis.__

#### DFS

The DFS tests are divided into two categories: component and full-graph traversal.

1. For component traversal, correct behavior is tested on components with and without cycles, components with single nodes, and graphs with multiple components. For each graph, the set of nodes that the traversal visited and the number of nodes it visited are tested against the expected set of visited nodes and the expected number of visited nodes.
2. For full graph traversal, correct behavior is tested on full graphs with mixtures of components with and without cycles and components with single nodes. The verification strategy is the same as for individual component traversal.

#### Strongly Connected Components

Since Kosaraju's algorithm relies on the transpose of the graph and a DFS traversal of the transpose, we first tested the transpose. We ensured that all the edges were reversed, and DFS over the transpose visited the nodes in the expected order.

Finally, we tested the strongly connected component algorithm on directed and undirected graphs that could be verified by hand. We ensured that the algorithms counted the same number of components as we did by hand on small graphs.

#### Dijkstra's Algorithm

Dijkstra's algorithm is divided into four categories: simple, complex, edge case, and other subgraphs. For each test, there are three requirements it must pass: the actual data must equal the expected path, the expected length, and the expected sum of the path.

1. The simple subgraph tests are basic tests where the path has a length of 1, and the subgraph can easily be solved by hand.
2. The complex subgraph tests are far more complex in nodes and edges but can still be solved by hand.
3. The edge case subgraphs are, as the name implies, graphs with edge cases. These edge cases are an empty graph, a graph with only one node (singleton), a graph where a directed edge is from the source node to the end node but not the other way around, and a graph where the source node and end node are in different components.
4. The other subgraphs are graphs created by hand to ensure the validity of Dijkstra's algorithm. For example, a graph introduced in a previous lecture (12/02/19) was constructed for testing, and our Dijkstra's algorithm gave the same result as the lecture.
