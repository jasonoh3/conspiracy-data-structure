#pragma once

#include <iterator>
#include <set>
#include <list>
#include <unordered_map>

#include "../../graph/graph.h"

typedef int NodeID; // For C L A R I T Y
using NodeIterator = std::unordered_map<NodeID, Graph::Node>::const_iterator;

/**
 * An abstract class representing a traversal of a
 * graph.
 *
 * @author Andrew Orals
**/
struct GraphTraversal {
  /**
  * A class outlining an iterator for using this
  * Graph Traversal.
  **/
  class Iterator : std::iterator<std::forward_iterator_tag, Graph::Node> {
    public:
      /**
      * Construct an iterator using the specified
      * traversal type starting at the node with
      * the given ID in the provided graph.
      *
      * @param gt A pointer to the traversal subtype
      * @param start_id The ID of the node at which to start the traversal
      * @param graph A const reference to the graph to traverse
      **/
      Iterator(GraphTraversal* gt, 
               NodeID start_id, 
               const Graph& graph,
               bool full_traversal = false);

      /**
      * Construct an iterator using the specified
      * traversal type starting at the given node
      * in the provided graph.
      *
      * @param gt A pointer to the traversal subtype
      * @param start_node The node at which to start the traversal
      * @param graph A const reference to the graph to traverse
      **/
      Iterator(GraphTraversal* gt, 
               const Graph::Node& start_node, 
               const Graph& graph,
               bool full_traversal = false);

      /**
      * Return an iterator at the next element in the traversal.
      *
      * @return an Iterator to the next element
      **/
      Iterator operator++();

      /**
      * Get the ID of the current node in this Traversal
      *
      * @return the ID of the current node in this Traversal
      **/
      NodeID operator*();

      /**
      * Determine whether this Traversal is not exhausted.
      *
      * @return true if this Traversal is NOT exhausted; else, false
      **/
      bool operator!=(const Iterator &other);
  
    private:
      /**
      * Return the nodes neighboring the node with the
      * given ID in the graph.
      **/
      void addNeighbors(NodeID curr);

      /**
       * After a connected component has been visited,
       * add a sentinel value if there are no nodes left to 
       * be visited, or add the next unvisited node if
       * the full_traversal switch is on.
       *
       * @param feed_ahead it is possible that the most recent
       * element popped from the stack when capEnd is called
       * has already been visited. Then, it is necessary to purge
       * this element and "feed ahead." true to feed ahead, false
       * otherwise.
      **/
      void capEnd(bool feed_ahead=false);

      const NodeID start_;
      NodeID curr_ = start_;
      GraphTraversal* gt_;
      const Graph& graph_;
      NodeIterator node_iter_ = graph_.begin();
      std::set<NodeID> visited_ids_;
      bool full_traversal_;
  };

  virtual Iterator begin() = 0;

  virtual Iterator end() = 0;

  virtual void add(NodeID node) = 0;

  virtual NodeID pop() = 0;

  virtual NodeID peek() const = 0;

  virtual bool empty() const = 0;
};
