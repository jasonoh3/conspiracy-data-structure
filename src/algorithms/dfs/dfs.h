#pragma once

#include <stack>
using std::stack;

#include "GraphTraversal.h"

/**
 * A class representing a Depth-First Search traversal
 * of a Graph.
 *
 * @author Andrew Orals
**/
class DFS : public GraphTraversal {
  public:
    /**
    * Construct a DFS traversal using the provided
    * graph beginning at the node with the given ID.
    *
    * @param start The id of the starting node
    * @param graph A const reference to the 
    *              graph to traverse
    * @param full_traversal True to traverse whole 
    *                       graph, false to traverse 
    *                       connected component.
    *
    **/
    DFS(NodeID start, const Graph& graph, bool full_traversal=false);

    /**
    * Return an iterator to the start of the traversal.
    *
    * @return iterator to the start of the traversal
    **/
    GraphTraversal::Iterator begin() override;

    /**
    * Return an iterator one past the end of the traversal.
    *
    * @return iterator one past the end of the traversal
    **/
    GraphTraversal::Iterator end() override;

    /**
    * Add a node to the traversal by its ID.
    *
    * @param node The ID of the node to add
    **/
    void add(NodeID node) override;

    /**
    * Remove the current node from the traversal and 
    * return its ID.
    *
    * @return the popped NodeID
    **/
    NodeID pop() override;

    /**
    * Return the ID of the current node of this traversal.
    *
    * @return the ID of the current node
    **/
    NodeID peek() const override;

    /**
    * Determine whether this traversal is empty.
    *
    * @return true if this traversal is empty; else, false
    **/
    bool empty() const override;

  private:
    const NodeID start_;
    stack<NodeID> to_visit_;
    const Graph& graph_;
    const bool full_traversal_;
};
