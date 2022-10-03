#include "../cs225/catch/catch.hpp"
#include "../src/algorithms/dfs/dfs.h"
#include "../src/graph/graph.h"
#include "../src/algorithms/stronglyConnected/stronglyConnected.h"

#include <string>

TEST_CASE("Graph Transpose has same number of nodes and edges") {
    Graph g = Graph("data/wico-graph/Other_Graphs/1/nodes.csv", "data/wico-graph/Other_Graphs/1/edges.txt");
    Graph * tr = g.getTranspose();
    Graph tran = *tr;
    delete tr;

    REQUIRE(tran.getNumEdges()==g.getNumEdges());
    REQUIRE(tran.getNumNodes()==g.getNumNodes());
}

// the following test cases are to make sure the transpose 
// and dfs traversal of the transpose work correctly
TEST_CASE("Manual Graph 1 undirected for transpose and transpose DFS") {
    //Manual added test case
    Graph g;

    g.insertVertex(1, 0);
    g.insertVertex(2, 1);
    g.insertVertex(3, 2);
    g.insertVertex(4, 3);

    g.insertEdge(1 , 2, 1);
    g.insertEdge(2, 1, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 2, 1);
    g.insertEdge(4, 3, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 1, 3);
    g.insertEdge(1, 4, 3);

    Graph * tr = g.getTranspose();
    Graph tran = *tr;
    delete tr;

    SCC test(g);
    const int actualSCC = test.getSCCCount();
    const int expectedSCC = 1;

    REQUIRE(actualSCC == expectedSCC);
    REQUIRE(tran.getNumEdges()==g.getNumEdges());
    REQUIRE(tran.getNumNodes()==g.getNumNodes());

    SECTION("DFS traversal over transpose is in correct order") {
        //DFS undirected graph check
        const NodeID start = 1;
        const int kNumVisitedExpected = 4;
        const std::set<NodeID> kVisitedExpected =
        {
            1,
            4,
            3,
            2,
        };

        DFS trav(start, tran);
        int num_visited = 0;
        std::set<NodeID> visited_actual;
        for (const auto& id : trav) {
            ++num_visited;
            visited_actual.insert(id);
        }
        REQUIRE(num_visited == kNumVisitedExpected);
        REQUIRE(visited_actual == kVisitedExpected);
    }
}

TEST_CASE("Manual Graph 2 directed for transpose and transpose DFS") {
    Graph g;

    g.insertVertex(1, 0);
    g.insertVertex(2, 1);
    g.insertVertex(3, 2);
    g.insertVertex(4, 3);

    g.insertEdge(1 , 2, 1);
    g.insertEdge(2, 3, 1);
    g.insertEdge(3, 4, 1);
    g.insertEdge(4, 1, 3);

    Graph * tr = g.getTranspose();
    Graph tran = *tr;
    delete tr;

    SCC test(g);
    const int actualSCC = test.getSCCCount();
    const int expectedSCC = 1;

    REQUIRE(actualSCC == expectedSCC);
    REQUIRE(tran.getNumEdges()==g.getNumEdges());
    REQUIRE(tran.getNumNodes()==g.getNumNodes());

    SECTION("DFS traversal over transpose (directed) is in the right order") {
        const NodeID start = 1;
        const int kNumVisitedExpected = 4;
        const std::set<NodeID> kVisitedExpected =
        {
            1,
            4,
            3,
            2,
        };
        DFS trav(start, tran);
        int num_visited = 0;
        std::set<NodeID> visited_actual;
        for (const auto& id : trav) {
            ++num_visited;
            visited_actual.insert(id);
        }

        REQUIRE(num_visited == kNumVisitedExpected);
        REQUIRE(visited_actual == kVisitedExpected);
    }

    SECTION("Edges of transpose are reversed") {
        //Checking edges are reversed test
        unordered_map<int, int>idMap =
        {
            {1, 4},
            {4, 3},
            {3, 2},
            {2, 1},
        };

        for(auto it = tran.begin(); it!=tran.end();it++) {
            for(auto &edge: tran.incidentEdges(it->first)) {
                REQUIRE(idMap[edge.source_id] == edge.dest_id);
            }
        }
    }
}

// the following tests make sure the number of strongly 
// connected components is correct
TEST_CASE("Graph with edges, but sccCount = number of nodes") {
    const string node_file = "tests/data/29-modified/nodes.csv";
	const string edge_file = "tests/data/29-modified/edges.txt";

    Graph g(node_file, edge_file);

    SCC test(g);
    const int actualSCC = test.getSCCCount();
    const int expectedSCC = 7; //Manual

    REQUIRE(actualSCC == expectedSCC);
}

TEST_CASE("Directed Graph, but sccCount = number of nodes") {
    const string node_file = "tests/data/3/nodes.csv";
	const string edge_file = "tests/data/3/edges.txt";
    
    Graph g(node_file, edge_file);
    SCC test(g);

    const int actualSCC = test.getSCCCount();
    const int expectedSCC = 9; //Manual

    Graph * tr = g.getTranspose();
    Graph tran = *tr;
    delete tr;

    REQUIRE(actualSCC == expectedSCC);
    REQUIRE(tran.getNumEdges()==g.getNumEdges());
    REQUIRE(tran.getNumNodes()==g.getNumNodes());
}

TEST_CASE("Undirected Graph with 1 SCC") {
    const string node_file = "tests/data/1/nodes.csv";
	const string edge_file = "tests/data/1/edges.txt";

    Graph g(node_file, edge_file);
    SCC test(g);

    const int actualSCC = test.getSCCCount();
    const int expectedSCC = 1; //Manual

    REQUIRE(actualSCC == expectedSCC);
}

TEST_CASE("Directed Graph with 1 SCC") {
    Graph g;
    g.insertVertex(0, 5);
    g.insertVertex(1, 4);
    g.insertVertex(2, 0);

    g.insertEdge(0, 1, 5);
    g.insertEdge(0, 2, 1);
    g.insertEdge(1, 2, 4);
    g.insertEdge(1, 0, 1);
    g.insertEdge(2, 1, 4);
    g.insertEdge(2, 0, 5);

    Graph * tr = g.getTranspose();
    Graph tran = *tr;
    delete tr;

    const int expectedSCC = 1;

    SCC test(g);

    const int actualSCC = test.getSCCCount();
    REQUIRE(actualSCC == expectedSCC);
    REQUIRE(tran.getNumEdges()==g.getNumEdges());
    REQUIRE(tran.getNumNodes()==g.getNumNodes());
}

TEST_CASE("4 Nodes with no edges") {
    Graph g;

    g.insertVertex(1, 0);
    g.insertVertex(2, 1);
    g.insertVertex(3, 2);
    g.insertVertex(4, 3);

    const int expectedSCC = g.getNumNodes();

    SCC test(g);

    const int actualSCC = test.getSCCCount();

    Graph * tr = g.getTranspose();
    Graph tran = *tr;
    delete tr;

    REQUIRE(actualSCC == expectedSCC);
    REQUIRE(tran.getNumEdges()==g.getNumEdges());
    REQUIRE(tran.getNumNodes()==g.getNumNodes());
}

TEST_CASE("Single node") {
    Graph g;
    g.insertVertex(1,0);
    SCC test(g);

    REQUIRE(test.getSCCCount() == 1);
    REQUIRE(test.getAllSCC()[0][0] == 1);
}

TEST_CASE("Node ids of SCCs are partitioned correctly") {
    Graph g;
    g.insertVertex(1,0);
    g.insertVertex(2,1);
    g.insertVertex(3,2);

    g.insertEdge(1,2,0);
    g.insertEdge(2,1,0);
    g.insertEdge(3,2,0);

    SCC test(g);
    REQUIRE(test.getSCCCount() == 2);
    REQUIRE(test.getAllSCC()[0][0] == 3);
    REQUIRE(test.getAllSCC()[1][0] == 2);
    REQUIRE(test.getAllSCC()[1][1] == 1);
}

TEST_CASE("Same node id doesn't belong to two different components") {
    Graph g = Graph("data/wico-graph/Other_Graphs/1/nodes.csv","data/wico-graph/Other_Graphs/1/edges.txt");
    SCC test(g);
    
    int count = 0;
    for (auto& scc : test.getAllSCC()) {
        for (auto& node : scc) {
            count++;
        }
    }

    REQUIRE(g.getNumNodes() == count);
}
