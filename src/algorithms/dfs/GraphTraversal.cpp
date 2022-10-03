#include "GraphTraversal.h"

using GTI = GraphTraversal::Iterator;
using std::list;

GTI::Iterator(GraphTraversal* gt,
              NodeID start_id,
              const Graph& graph,
              bool full_traversal) :
    start_(start_id), curr_(start_id), gt_(gt), 
    graph_(graph), full_traversal_(full_traversal) 
{
  visited_ids_.insert(start_id);
  if (gt) {
    addNeighbors(curr_);
    if (gt_->empty() and graph_.getNumNodes() > 0) {
      // if no neighbors added and there is at least one node
      capEnd();
    }
  }
}

GTI::Iterator(GraphTraversal* gt, 
              const Graph::Node& start_node, 
              const Graph& graph,
              bool full_traversal) :
    Iterator(gt, start_node.id, graph, full_traversal)
{ /*Nothing*/ }

GTI GTI::operator++() {
  if (not gt_->empty()) {

    bool feed_ahead;
    do {
      curr_ = gt_->pop();
      feed_ahead = visited_ids_.find(curr_) != visited_ids_.end();
    } while (not gt_->empty() and feed_ahead);

    visited_ids_.insert(curr_);

    if (curr_ != -1) {
      addNeighbors(curr_);
      if (gt_->empty()) {
        capEnd(feed_ahead);
      }
    }
  }

  return *this;
}	

NodeID GTI::operator*() {
  return curr_;
}

bool GTI::operator!=(const Iterator& other) {
  return gt_ and not gt_->empty();
}

void GTI::addNeighbors(NodeID curr) {
  if (graph_.getNumNodes() > 0 and graph_.getNumEdges() > 0 and curr >= 0) {
    list<Graph::Edge> incident_edges = graph_.incidentEdges(curr);

    for (auto& edge : incident_edges) {
      if (edge.source_id == curr and
          visited_ids_.find(edge.dest_id) == visited_ids_.end()) 
      {
        // only add if edge flows away from curr
        // and not yet visited
        gt_->add(edge.dest_id);
      }
    }
  }
}

void GTI::capEnd(bool feed_ahead) {
  NodeID to_add;
  if (full_traversal_ and visited_ids_.size() < size_t(graph_.getNumNodes())) {
    // Equivalent to the outer loop in traversals introduced in class
    do {
      to_add = (*node_iter_++).first;
    } while (visited_ids_.find(to_add) != visited_ids_.end());

    if (feed_ahead) {
      // Last node on stack is visited, need to feed ahead
      visited_ids_.insert(to_add);
      curr_ = to_add;
      addNeighbors(to_add);
    }
  } else {
    to_add = -1; // Sentinel value (to visit one past the end)
  }

  if (not feed_ahead) gt_->add(to_add);
}
