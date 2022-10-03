#include "dfs.h"

DFS::DFS(NodeID start, const Graph& graph, bool full_traversal) :
    start_(start), graph_(graph), full_traversal_(full_traversal) { }

GraphTraversal::Iterator DFS::begin() {
  return GraphTraversal::Iterator(this, start_, graph_, full_traversal_);
}

GraphTraversal::Iterator DFS::end() {
  // Doesn't really matter what's returned because
  // the iterator's operator!=() doesn't use the
  // argument anyway.
  return GraphTraversal::Iterator(nullptr, start_, graph_);
}

void DFS::add(NodeID node) {
  to_visit_.push(node);
}

NodeID DFS::pop() {
  if (not to_visit_.empty()) {
    NodeID tmp = to_visit_.top();
    to_visit_.pop();
    return tmp;
  }
  
  return -1;
}

NodeID DFS::peek() const {
  return empty() ? -1 : to_visit_.top();
}

bool DFS::empty() const {
  return to_visit_.empty();
}
