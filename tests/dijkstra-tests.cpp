#include "../cs225/catch/catch.hpp"
#include "../src/algorithms/dijkstra/dijkstra.h"
#include <stdexcept>


TEST_CASE("Small subgraph") {
    Graph g = Graph("tests/data/1/nodes.csv", "tests/data/1/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{152503266, 357564172};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 44342918);
}

TEST_CASE("Small subgraph 2") {
    Graph g = Graph("tests/data/3/nodes.csv", "tests/data/3/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{157991583, 106465291};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 51786);
}

TEST_CASE("Small subgraph 3") {
    Graph g = Graph("tests/data/12/nodes.csv", "tests/data/12/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{152926252, 150099934};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 220065);
}

TEST_CASE("Complex subgraph 1") {
    Graph g = Graph("tests/data/136/nodes.csv", "tests/data/136/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{37080791, 10849707};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 3948088);
}

TEST_CASE("Complex subgraph 2") {
    Graph g = Graph("tests/data/custom-dijkstra/3/nodes.csv", "tests/data/custom-dijkstra/3/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{4, 3, 2, 1, 0};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 800);
}

TEST_CASE("More than one edge subgraph") {
    Graph g = Graph("tests/data/16/nodes.csv", "tests/data/16/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{6602289, 54375993, 45161208};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 144851);
}

TEST_CASE("Multiple possible paths") {
    Graph g = Graph("tests/data/custom-dijkstra/0/nodes.csv", "tests/data/custom-dijkstra/0/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{3, 0};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 15);
}

// Happens when the retweeter didn't get their information from a follower connection
TEST_CASE("Sum of path > total propagation time") {
    Graph g = Graph("tests/data/custom-dijkstra/1/nodes.csv", "tests/data/custom-dijkstra/1/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{3, 2, 1, 0};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 1400);
    REQUIRE(d.getSumOfPath() > g.getTime(g.getGreatestNode()));
}

// https://courses.engr.illinois.edu/cs225/sp2019/assets/lectures/handouts/cs225sp19-40-Dijkstra-handout.pdf
TEST_CASE("Lecture graph - 12/02/19") {
    Graph g = Graph("tests/data/custom-dijkstra/lecture-graph/nodes.csv", "tests/data/custom-dijkstra/lecture-graph/edges.txt");
    
    g.insertVertex(1, 10);
    g.insertVertex(2, 10);
    g.insertVertex(3, 10);
    g.insertVertex(4, 10);
    g.insertVertex(5, 10);
    g.insertVertex(6, 10);
    g.insertVertex(7, 10);

    g.insertEdge(0, 1, 10);
    g.insertEdge(1, 2, 7);
    g.insertEdge(2, 5, 4);
    g.insertEdge(5, 6, 5);
    g.insertEdge(6, 4, 2);
    g.insertEdge(5, 4, 3);
    g.insertEdge(4, 2, 6);
    g.insertEdge(0, 7, 7);
    g.insertEdge(7, 4, 5);
    g.insertEdge(7, 6, 4);
    g.insertEdge(1, 3, 5);
    g.insertEdge(3, 0, 3);
    
    Dijkstra d; d.solve(g, 0, 2);
    vector<int> solution{0, 1, 2};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size() - 1);
    REQUIRE(d.getSumOfPath() == 17);
}

TEST_CASE("Edge case: empty graph") {
    REQUIRE_THROWS_AS(Graph("tests/data/empty/nodes.csv", "tests/data/empty/edges.txt"), std::invalid_argument);
}

TEST_CASE("Edge case: singleton") {
    Graph g = Graph("tests/data/custom-dijkstra/singleton/nodes.csv", "tests/data/custom-dijkstra/singleton/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size());
    REQUIRE(d.getSumOfPath() == 0);
}

TEST_CASE("Edge case: source node to end node but not the other-way around") {
    Graph g = Graph("tests/data/custom-dijkstra/2/nodes.csv", "tests/data/custom-dijkstra/2/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size());
    REQUIRE(d.getSumOfPath() == 0);
}

TEST_CASE("Edge case: multiple components and greatest time node is in a separate component from source node") {
    Graph g = Graph("tests/data/21/nodes.csv", "tests/data/21/edges.txt");
    Dijkstra d; d.solve(g, g.getGreatestNode(), g.getSourceID());
    vector<int> solution{};

    REQUIRE(d.getPath() == solution);
    REQUIRE(d.getLength() == solution.size());
    REQUIRE(d.getSumOfPath() == 0);
}
