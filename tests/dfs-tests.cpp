#include "../cs225/catch/catch.hpp"

#include <string>
#include <set>

#include "../src/algorithms/dfs/dfs.h"

///////////////////////////////////
//// Component Traversal Tests ////
///////////////////////////////////

TEST_CASE("Visit all nodes once no cycles") {
    const string node_file = "tests/data/29-modified/nodes.csv";
    const string edge_file = "tests/data/29-modified/edges.txt";

    const NodeID start = 75185029;
    const int kNumVisitedExpected = 5;
    const std::set<NodeID> kVisitedExpected =
    {
        75185029,
        58045313,
        129348059,
        9784003,
        58302875
    };

    Graph g(node_file, edge_file);
    DFS trav(start, g);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Visit all nodes once cycles level 1") {
    const string node_file = "tests/data/1/nodes.csv";
    const string edge_file = "tests/data/1/edges.txt";

    const NodeID start = 357564172;
    const int kNumVisitedExpected = 6;
    const std::set<NodeID> kVisitedExpected =
    {
        357564172,
        55077913,
        139259475,
        110976388,
        152897972,
        152503266,
    };

    Graph g(node_file, edge_file);
    DFS trav(start, g);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Visit node singleton component") {
    const string node_file = "tests/data/3/nodes.csv";
    const string edge_file = "tests/data/3/edges.txt";

    const NodeID start = 106465291;
    const int kNumVisitedExpected = 1;
    const std::set<NodeID> kVisitedExpected = {106465291};

    Graph g(node_file, edge_file);
    DFS trav(start, g);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Visit all nodes once cycles level 2") {
    const string node_file = "tests/data/136/nodes.csv";
    const string edge_file = "tests/data/136/edges.txt";

    const NodeID start = 10849707;
    const std::set<NodeID> kVisitedExpected =
    {
        61722443,
        10849707,
        152934873,
        155877082,
        40147830,
        83920561,
        28999427,
        37080791,
        147865784,
        57647698,
        421505842
    };
    const int kNumVisitedExpected = kVisitedExpected.size();

    Graph g(node_file, edge_file);
    DFS trav(start, g);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

//////////////////////////////
//// Full Traversal Tests ////
//////////////////////////////

TEST_CASE("Full traversal visit all nodes once no cycles") {
    const string node_file = "tests/data/29-modified/nodes.csv";
    const string edge_file = "tests/data/29-modified/edges.txt";

    const NodeID start = 75185029;
    const int kNumVisitedExpected = 7;
    const std::set<NodeID> kVisitedExpected =
    {
        129348059,
        58045313,
        9784003,
        608307019,
        11967166,
        75185029,
        58302875
    };

    Graph g(node_file, edge_file);
    DFS trav(start, g, true);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Full traversal visit all nodes once cycles level 1") {
    const string node_file = "tests/data/1/nodes.csv";
    const string edge_file = "tests/data/1/edges.txt";

    const NodeID start = 357564172;
    const int kNumVisitedExpected = 6;
    const std::set<NodeID> kVisitedExpected =
    {
        357564172,
        152897972,
        110976388,
        55077913,
        152503266,
        139259475,
    };

    Graph g(node_file, edge_file);
    DFS trav(start, g, true);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Full traversal Visit node singleton component") {
    const string node_file = "tests/data/3/nodes.csv";
    const string edge_file = "tests/data/3/edges.txt";

    const NodeID start = 106465291;
    const int kNumVisitedExpected = 9;
    const std::set<NodeID> kVisitedExpected =
    {
        106465291,
        654659472,
        767199474,
        61772667,
        319298723,
        157991583,
        681189134,
        85513862,
        55240541
    };

    Graph g(node_file, edge_file);
    DFS trav(start, g, true);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Full traversal Visit all nodes once cycles level 2") {
    const string node_file = "tests/data/136/nodes.csv";
    const string edge_file = "tests/data/136/edges.txt";

    const NodeID start = 10849707;
    const std::set<NodeID> kVisitedExpected = 
    {
        298858445,
        152477949,
        61722443,
        152934572,
        152534046,
        10849707,
        57976185,
        152934873,
        155877082,
        40147830,
        83920561,
        75782555,
        28999427,
        37080791,
        130947350,
        152500578,
        147865784,
        152674878,
        57647698,
        421505842,
        58371092,
        191858052
    };
    const int kNumVisitedExpected = kVisitedExpected.size();

    Graph g(node_file, edge_file);
    DFS trav(start, g, true);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
}

TEST_CASE("Full traversal visit all nodes multiple multi-node components") {
    const string node_file = "tests/data/multi-multi-node-components-custom/nodes.csv";
    const string edge_file = "tests/data/multi-multi-node-components-custom/edges.txt";

    const std::set<NodeID> kVisitedExpected = 
    {
        1 ,
        2 ,
        3 ,
        4 ,
        5 ,
        6 ,
        7 ,
        8 ,
        9 ,
        10,
        11,
        12,
        13,
        14,
        15,
        16,
        17,
    };
    const int kNumVisitedExpected = kVisitedExpected.size();

    Graph g(node_file, edge_file);
    const NodeID start = g.getSourceID();
    DFS trav(start, g, true);

    int num_visited = 0;
    std::set<NodeID> visited_actual;
    for (const auto& id : trav) {
        ++num_visited;
        visited_actual.insert(id);
    }

    REQUIRE(num_visited == kNumVisitedExpected);
    REQUIRE(visited_actual == kVisitedExpected);
    REQUIRE(num_visited == g.getNumNodes());
}