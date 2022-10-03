# Written Report

## Goals
_The full project proposal can be found [here](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/project-info/proposal.md)._
## Development
_The full development log (committed once a week throughout the project) can be found [here](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/project-info/weekly_notes.md)._
## Results
### Proof Of Completion/Correctness
#### Test Suite
We wrote a comprehensive [test suite](https://github.com/jasonoh3/conspiracy-data-structure/tree/main/tests) that tested each of our algorithms, including any and all edge cases. A summary of our test suite can be found [here](https://github.com/jasonoh3/conspiracy-data-structure#test-strategy). Based on this test suite, we know that our algorithms work as intended because we passed all of our tests. 
#### Output
We had a complete run of each of our coded algorithms on the 3,000 subgraphs and exported the results to a [csv file](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/wico_graph_results.csv). Our complete run of all the algorithms was done through a [helper class](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/src/AnalyzeGraphs.h). None of the algorithms on any subgraphs gave us any errors when we exported the results. 
### Discoveries About The Dataset
We analyzed the results from the [csv file](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/wico_graph_results.csv) output described above, using a [Jupyter Notebook](https://github.com/jasonoh3/conspiracy-data-structure/blob/main/data/analyze_results.ipynb) in Python to see if we made any discoveries about the dataset.
#### Strongly Connected Components 
To answer our leading question: _What is the difference in the social structure of groups who spread misinformation vs. non-misinformation?_
We extracted the number of strongly connected components for each subgraph. We then took the number of strongly connected components in each graph divided by the number of nodes in each graph to eliminate any effects where the number of nodes skewed the number of connected components. We then compared the average of this measure between misinformation and non-misinformation graphs, producing the plot below:

<img src="https://media.github-dev.cs.illinois.edu/user/12503/files/954616b5-a47d-4951-bf4c-84f8d69253bf" width="350">

This shows us that, on average, there are less strongly connected components in misinformation subgraphs than in non-misinformation subgraphs. If strongly connected components can be thought of as communities of retweeters, then this tells us that, on average, the network of retweeters of a given misinformation tweet have fewer distinct communities. This supports the idea of echo chambers leading to misinformation. False ideas are more likely to spread in tightly knit isolated networks that don't have dissenting opinions. 

#### Shortest Path
To answer the leading question: _How does information spread differently in misinformation vs. non-misinformation networks?_, we extracted the path of information flow from the source tweet to the last person to retweet the source tweet (in Dijkstra's algorithm, the start node is the greatest retweet and the end node is the source tweet, as explained below). We wanted to model whether or not the last retweeter retweeted directly from the source because they follow the source, or if they retweeted from people they follow who follow the source, etc. or if they have no follower connection to the source tweet at all.
##### What does it mean for information to flow from one node to another in this dataset?
We can infer that information flows from node A to node B if node B follows node A (an edge from node B to node A), and is retweeted after node A.
##### Meaning of the weights
It is the time delta between one retweet time to the other in a follower connection. 
##### Why choose the last retweeter?
We chose the last retweeter because it has the highest chance of having intermediary information flow. Since it was the last one, it has a higher chance of depending on other retweets.
##### What does the shortest weighted path mean?
If there was no path at all, then we can assume that the last retweeter got the information some other way other than the people they follow. We can also assume that the information didn't spread to them through the network of retweeters if the total weight of the shortest path is greater than their timestamp. That means that a retweeter didn't get their information from a follower connection somewhere along the way. If there is a shortest weighted path with weights less than the last retweet's timestamp, this means that there was a path through the retweeters that simulates the flow of information from the source to the last retweet.
##### What does this tell us?
The length of the shortest path, if any, tells us:
1. If information actually flows through the network (if not, we marked the length as 0)
3. How directly the flow of information from the source to the last retweeter is
	  1. If long, it means that it took a lot of intermediary retweeters for the last person to get the information

<img src="https://media.github-dev.cs.illinois.edu/user/12503/files/c0b2a091-de4a-43bb-a945-17d899c0e9c3" width="350">
<img src="https://media.github-dev.cs.illinois.edu/user/12503/files/20b4a314-92d2-44cf-83ab-376df6fa5363" width="350">

Despite misinformation subgraphs having shorter greatest retweet times on average, they have greater length shortest paths from the last retweeter to the source. This means that misinformation usually spreads quicker from the source but through more intermediary retweeters. Misinformation spreads like a giant game of telephone where the last person to get the information may not have even gotten it directly from the source.
