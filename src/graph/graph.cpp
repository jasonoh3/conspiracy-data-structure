#include "graph.h"

Graph::Graph () { }

Graph::Graph(const string & node_file, const string & edge_file) {
    std::ifstream input_nodes(node_file);
    std::ifstream input_edges(edge_file);

    if (input_nodes.is_open() && input_edges.is_open()) {
        readNodes(input_nodes);
        readEdges(input_edges);

        input_edges.close();
        input_nodes.close();
    } else {
        throw std::invalid_argument("File Not Found");
    }

    // node list is emtpy
    if (n==0) {
        throw std::invalid_argument("Graph is Empty");
    }
}

void Graph::insertEdge(int source_id, int dest_id, int weight) {
    // make sure both nodes are in the graph
    if (nodes.find(source_id) != nodes.end() && nodes.find(dest_id) != nodes.end()) {
        Edge edge(source_id, dest_id, weight);
        nodes[source_id].adjacency_list.push_front(edge);
        m++;

        // insert edge into transpose
        transpose[dest_id].adjacency_list.push_front(Edge(dest_id, source_id, weight));
    }
}

void Graph::insertVertex(int id, int time) {
    Node node(id, time);
    if (time==0) {
        source_id = id;
    }

    nodes.insert({id, node});
    n++;

    // insert node into transpose graph
    transpose.insert({id, node});

    //keep track of largest retweet time
    if (time >= greatest_time) {
        greatest_node = id;
        greatest_time = time;
    }
}

void Graph::readEdges(std::istream& str) {
    std::string line;
    while (std::getline(str, line)) {
        std::stringstream lineStream(line);
        std::string cell;

        vector<int> data;
        while(std::getline(lineStream,cell, ' ')) {
            std::stringstream entry(cell);
            int entry_int = 0;
            entry >> entry_int;
            data.push_back(entry_int);
        }
        //make sure both edges are included in file
        if (data.size() == 2) {
            int source = data[0];
            int dest = data[1];

            //make sure both nodes already exist 
            if (nodes.find(source) == nodes.end() || nodes.find(dest) == nodes.end()) {
                continue;
            }
            int weight = getWeight(source, dest);
            insertEdge(source, dest, weight);
        }
    }
}

void Graph::readNodes(std::istream& str) {
    //number of columns in csv file
    unsigned NUM_COLS = 4;

    std::string line;
    //skips the first line containing column names
    std::getline(str,line);

    while (std::getline(str, line)) {
        std::stringstream lineStream(line);
        std::string cell;

        vector<int> data;
        while(std::getline(lineStream,cell, ',')) {
            // convert to int
            std::stringstream entry(cell);
            int entry_int = 0;
            entry >> entry_int;
            data.push_back(entry_int);
        }

        // check that record has no missing data
        if (data.size() == NUM_COLS) {
            int id = data[0];
            int time = data[1];
            insertVertex(id, time);
        }
    }
}

int Graph::getNumEdges() const {
    return m;
}

int Graph::getNumNodes() const {
    return n;
}

int Graph::getWeight(int source, int dest) const {
    return std::abs(nodes.at(source).time - nodes.at(dest).time);
}

int Graph::getSourceID() const {
    return source_id;
}

list<Graph::Edge> Graph::incidentEdges(int id) const {
    return nodes.at(id).adjacency_list;
}

int Graph::getTime(int id) const {
    return nodes.at(id).time;
}

int Graph::getGreatestNode() const {
    return greatest_node;
}

unordered_map<int, Graph::Node>::const_iterator Graph::begin() const {
    return nodes.cbegin();
}

unordered_map<int, Graph::Node>::const_iterator Graph::end() const {
    return nodes.cend();
}

Graph* Graph::getTranspose() const {
    return new Graph(transpose, n, m);
}

Graph::Graph(const unordered_map<int, Node>& input_nodes, int num_nodes, int num_edges) {
    nodes = unordered_map<int, Node>(input_nodes);
    n = num_nodes;
    m = num_edges;
}