#include "../cs225/catch/catch.hpp"
#include "../src/graph/graph.h"

/** Compares weights so that lists can be sorted
    @param edge1 the first edge to be compared
    @param edge2 the second edge to be compared
    @return true if edge1's weight > edge2's weight, else false
*/
bool compareWeight(const Graph::Edge& edge1, const Graph::Edge& edge2) {
    return edge1.weight > edge2.weight;
}

TEST_CASE("Small subraph 1 (Other)") {
    Graph g = Graph("data/wico-graph/Other_Graphs/1/nodes.csv", "data/wico-graph/Other_Graphs/1/edges.txt");
    
    SECTION("Source node") {
        int id = g.getSourceID();
        REQUIRE(id == 357564172);
        REQUIRE(g.getTime(id) == 0);
    }

    SECTION("Number of nodes and edges") {
        REQUIRE(g.getNumEdges() == 10);
        REQUIRE(g.getNumNodes() == 6);
    }

    SECTION("Edge weights") {
        std::list<Graph::Edge> list = g.incidentEdges(g.getSourceID());
        std::list<Graph::Edge> solution;
        
        Graph::Edge edge1(357564172, 152897972, 27606560);
        Graph::Edge edge2(357564172, 110976388, 27632473);
        Graph::Edge edge3(357564172, 55077913, 278);
        Graph::Edge edge4(357564172, 152503266, 44342918);
        Graph::Edge edge5(357564172, 139259475, 10924297);

        solution.push_back(edge1);
        solution.push_back(edge2);
        solution.push_back(edge3);
        solution.push_back(edge4);
        solution.push_back(edge5);

        list.sort(compareWeight);
        solution.sort(compareWeight);

        for (int i = 0; i < 5; ++i) {
            REQUIRE(list.front().weight == solution.front().weight);
            list.pop_front(); solution.pop_front();
        }
    }

    SECTION("Incident edges at source node") {
        std::list<Graph::Edge> list = g.incidentEdges(g.getSourceID());
        std::list<Graph::Edge> solution;
        
        Graph::Edge edge1(357564172, 152897972, 27606560);
        Graph::Edge edge2(357564172, 110976388, 27632473);
        Graph::Edge edge3(357564172, 55077913, 278);
        Graph::Edge edge4(357564172, 152503266, 44342918);
        Graph::Edge edge5(357564172, 139259475, 10924297);

        solution.push_back(edge1);
        solution.push_back(edge2);
        solution.push_back(edge3);
        solution.push_back(edge4);
        solution.push_back(edge5);

        list.sort(compareWeight);
        solution.sort(compareWeight);

        for (int i = 0; i < 5; ++i) {
            REQUIRE(list.front().source_id == solution.front().source_id);
            REQUIRE(list.front().dest_id == solution.front().dest_id);
            REQUIRE(list.front().weight == solution.front().weight);
            list.pop_front(); solution.pop_front();
        }
    }

    SECTION("Incident edges at a non-source vertex") {
        std::list<Graph::Edge> list = g.incidentEdges(152503266);
        std::list<Graph::Edge> solution;

        Graph::Edge edge1(152503266, 357564172, 44342918);
        solution.push_back(edge1);

        REQUIRE(list.front().source_id == solution.front().source_id);
        REQUIRE(list.front().dest_id == solution.front().dest_id);
        REQUIRE(list.front().weight == solution.front().weight);
    }
}

TEST_CASE("More complex subgraph") {
    Graph g = Graph("data/wico-graph/Non_Conspiracy_Graphs/25/nodes.csv", "data/wico-graph/Non_Conspiracy_Graphs/25/edges.txt");
    
    SECTION("Source node") {
        int id = g.getSourceID();
        REQUIRE(id == 33485356);
        REQUIRE(g.getTime(id) == 0);
    }

    SECTION("Number of nodes and edges") {
        REQUIRE(g.getNumEdges() == 30);
        REQUIRE(g.getNumNodes() == 84);
    }
    
    SECTION("Incident edges of source node") {
        std::list<Graph::Edge> list = g.incidentEdges(g.getSourceID());
        std::list<Graph::Edge> solution;
        
        Graph::Edge edge1(33485356, 61300604, 201536);
        solution.push_back(edge1);

        list.sort(compareWeight);
        solution.sort(compareWeight);

        REQUIRE(list.size() == 1);
        REQUIRE(list.front().source_id == solution.front().source_id);
        REQUIRE(list.front().dest_id == solution.front().dest_id);
        REQUIRE(list.front().weight == solution.front().weight);
    }
    
    SECTION("Weight of edge not connected to source node") {
       std::list<Graph::Edge> list = g.incidentEdges(29378779);

       REQUIRE(list.front().dest_id == 214914610);
       REQUIRE(list.front().source_id == 29378779);
       REQUIRE(list.front().weight == 75648);
    }
}

TEST_CASE("Greatest retweet time in the graph") {
    const string node_file = "tests/data/1/nodes.csv";
	const string edge_file = "tests/data/1/edges.txt";
    Graph g = Graph(node_file, edge_file);

    REQUIRE(g.getGreatestNode() == 152503266);
    REQUIRE(g.getTime(g.getGreatestNode()) == 44342918);

}

TEST_CASE("Edge Case: empty graph") {
	const string node_file = "tests/data/empty/nodes.csv";
	const string edge_file = "tests/data/empty/edges.txt";

	REQUIRE_THROWS_AS(Graph(node_file, edge_file), std::invalid_argument);
}

TEST_CASE("Edge Case: file not found") {
	const string node_file = "nodes.csv";
	const string edge_file = "edges.txt";

	REQUIRE_THROWS_AS(Graph(node_file, edge_file), std::invalid_argument);
}

TEST_CASE("Edge Case: add edge between two nodes that don't exist") {
    //expected behavior: it doesn't add that edge

    Graph g = Graph("tests/data/1-modified/nodes.csv", "tests/data/1-modified/edges.txt");

    REQUIRE(g.getNumNodes() == 5);
    REQUIRE(g.getNumEdges() == 8);
}
