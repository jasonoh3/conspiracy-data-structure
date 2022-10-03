# Proposal

## Leading Question
- What is the difference in social structure of groups who spread misinformation vs. non-misinformation? 
- How does information spread differently in misinformation vs. non-misinformation networks?

We'll answer the first question by extracting all the subgraphs' strongly connected components. We will then average the number of strongly connected components for all subgraphs labeled as conspiracy tweets and those for non-conspiracy tweets. Finally, we will compare these two numbers to understand how many, on average, subcommunities of retweeters there are for conspiracy vs. non-conspiracy tweets. This will help us understand the meaning of echo-chambers in misinformation.

We will then use Dijkstra's algorithm to find the shortest __weighted__ (weights are defined below in Dijkstra's algorithm section) path between the largest retweet time from the original tweet to the source node. We will then do this for each subgraph and compare the average length of the paths of conspiracy vs. non-conspiracy tweets. This will tell us, on average, how many retweeters the last retweeter depends on to get the information/misinformation.


## Dataset Acquisition and Processing

For this project, we will be using [The WICO Graph Dataset](https://datasets.simula.no/wico-graph/). In this dataset, nodes are users, and edges are follower connections between users. The dataset was collected from Twitter and contained 3000 subgraphs of Tweets manually classified as 5G-Corona Conspiracy, Other Conspiracy, and Non-Conspiracy. Each subgraph is associated with a specific source tweet and all of the retweeters of the source tweet. There is also user information, such as the number of friends and followers and the time difference from the source tweet. We will process the data to best support our project goals using __Python__ and __Pandas__ and store the dataset as a __CSV file__. We will drop missing data using these tools before importing it into our graph data structure. If there are uncorrectable errors in the dataset, we will also drop that specific piece of data. We will also add weights to the edges in Pandas for Dijkstra's algorithm.  

To fully understand the dataset, we read the [paper](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/data/dataset_info/Wico_Graph_Scroeder.pdf) and created a [notes summary](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/data/dataset_info/data_set_notes.md).

### Example Conspriacy Subgraph
![](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/data/wico-graph/Other_Graphs/20/plot.png)

## Graph Algorithms

### Traversals

We will use a __DFS Traversal__ as it is required to implement the __Strongly Connected Component__ algorithm. Subgraphs in the dataset are limited to 100 nodes, so we don't anticipate memory being an issue. This method will be implemented as an iterator (with the start pointing to the source node (the source tweet)), making it easy to use in other algorithms. The algorithm will be implemented with target efficiency __O(n + m)__, where n is the number of nodes in the graph and m is the number of edges.

### Other Algorithms

#### Strongly Connected Component

We will use __Kosaraju's Strongly Connected Component algorithm__ to extract "communities" within each subgraph of retweeters. This will allow us to operationalize "echo-chambers" and compare the average number of connected components of conspiracy versus non-conspiracy subgraphs. For example, we hypothesize that conspiracy subgraphs will have less connected components (i.e., the set of retweeters all follow each other, thus the retweeters aren't very diverse). The function will take a graph object and produce the number of strongly connected components in the graph. The expected runtime is __O(n + m)__ where n is the number of nodes and m is the number of edges. [Example](https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.741.3957&rep=rep1&type=pdf) and [Another Example](https://link.springer.com/chapter/10.1007/978-3-319-13186-3_53)

#### Dijkstra's Algorithm

We will use __Dijkstra's Algorithm__ to determine the shortest path between two nodes in the graph. The expected application is to find the the shortest weighted path from the source node to another node and weight the edges in the path by the absolute value of the difference in timestamps from the connection of each node (timestamps represent the time after the initial source tweet that a tweet was retweeted). The start node will be the node that has the largest retweet time from the original tweet, and the end node will be the user that tweeted the source tweet. This method will take in a graph object, start node, and end node, and produce a path between two nodes in the graph (sequence of nodes) and the path length. The target efficiency of the algorithm is __O(|E| + |V|log(|V|))__, where |V| is the number of nodes in the graph and |E| is the number of edges in the graph.

## Timeline

|Week|Task|
|----|----|
|1|Read the dataset research paper available [here](https://cdn.discordapp.com/attachments/899749423456874509/906232004461355058/Wico_Graph_Scroeder.pdf) and work to understand the dataset. Process the dataset such that it is compatible with the project.|
|2|Create data structure to store the graph and implement functionality to load dataset from a CSV file. Implement the DFS traversal algorithm. Test the dataset parsing and traversal code.|
|3|Implement the Strongly Connected Component algorithm and test.|
|4|Implement the Dijkstra's algorithm and test.|
|5|Create presentation and video deliverables.|
