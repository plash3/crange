#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>

namespace bst {

template<typename T>
  using SHPT = std::shared_ptr<T>;
template<typename T>
  using ARRT = std::vector<SHPT<T>>;

template<typename T>
struct Node {
  T key;
  SHPT<Node> parent;
  SHPT<Node> left;
  SHPT<Node> right;
  Node (const T& k, const SHPT<Node>& p) : key(k), parent(p) {}
  ~Node () { std::cout << *this << " DESTROYED" << std::endl; }
template<typename C>
  friend std::ostream& operator<< (std::ostream& out, const Node<C>& n) {
    return out << n.key;
  }
};

template<typename T>
class bst {
    SHPT<Node<T>> root;
    auto search (const T&, SHPT<Node<T>>&);
    void insert (const T&, const SHPT<Node<T>>&, SHPT<Node<T>>&);
    void replace_node_in_parent (const SHPT<Node<T>>&, SHPT<Node<T>>&);
    // Gets minimum node in a subtree.
    auto find_min (SHPT<Node<T>>&);
  public:
    bst() {}
    ~bst() {}
    auto find (const T& key) { return search (key, root); }
    void insert (const T& key) { return insert (key, root, root); }
    void erase (SHPT<Node<T>>&);
template<typename C>
    friend std::ostream& operator<< (std::ostream&, const bst<C>&);
};

template<typename T>
auto bst<T>::search (const T& key, SHPT<Node<T>>& n) {
  if (n == nullptr || n->key == key) {
    return n;
  } else if (key < n->key) {
    return search (key, n->left);
  } else {
    return search (key, n->right);
  }
}

template<typename T>
void bst<T>::insert (const T& key, const SHPT<Node<T>>& parent, SHPT<Node<T>>& n) {
  if (n == nullptr) {
    n = std::make_shared<Node<T>>(key, parent);
  } else if (key < n->key) {
    insert (key, n, n->left);
  } else {
    insert (key, n, n->right);
  }
}

template<typename T>
void bst<T>::replace_node_in_parent (const SHPT<Node<T>>& n, SHPT<Node<T>>& nn) {
  if (n->parent != nullptr) {
    if (n == n->parent->left) {
      n->parent->left = nn;
    } else {
      n->parent->right = nn;
    }
  }
  if (nn != nullptr) {
    nn->parent = n->parent;
  }
}

template<typename T>
auto bst<T>::find_min (SHPT<Node<T>>& n) {
  auto res = n;
  while (res->left != nullptr) {
    res = res->left;
  }
  return res;
}

template<typename T>
void bst<T>::erase (SHPT<Node<T>>& n) {
  if (n->left != nullptr && n->right != nullptr) {
    auto successor = find_min (n->right);
    n->key = successor->key;
    erase (successor);
  } else if (n->left != nullptr) {
    replace_node_in_parent (n, n->left);
  } else if (n->right != nullptr) {
    replace_node_in_parent (n, n->right);
  } else {       // this node has no children
    replace_node_in_parent (n, n->left); // replace with null
  }
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const bst<T>& t) {
  ARRT<Node<T>> frontier;
  frontier.push_back (t.root);
  while (!frontier.empty()) {
    ARRT<Node<T>> next;
    for (auto it = frontier.begin(); it != frontier.end(); ++it) {
      if ((*it)->left != nullptr) {
        next.push_back ((*it)->left);
      }
      if ((*it)->right != nullptr) {
        next.push_back ((*it)->right);
      }
      out << **it << " ";
    }
    out << std::endl;
    frontier = std::move (next);
  }
  return out;
}

} // namespace bst

#endif /* BST_H */
