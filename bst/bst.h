#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <vector>
#include <map>

/**
  An implementation of a binary search tree (BST).
  The description of this data structure can be found at -
     en.wikipedia.org/wiki/Binary_search_tree
  Namely, this is an AVL tree - self-balancing BST -
     en.wikipedia.org/wiki/AVL_tree
  BST support 3 main operations: insert, delete, lookup.
  This class template implements common operations involving BST.
  This AVL implementation uses rotations to maintain balance.
  See also tree rotation at -
     en.wikipedia.org/wiki/Tree_rotation
*/

namespace bst {

template<typename T>
  using SHPT = std::shared_ptr<T>;
template<typename T>
  using ARRT = std::vector<SHPT<T>>;

template<typename T>
struct Node {
  T key;
  // The balance factor of a node is the
  // height difference of its two child subtrees.
  char balanced;
  char height;
  SHPT<Node> parent;
  SHPT<Node> left;
  SHPT<Node> right;
  Node (const T& k, const SHPT<Node>& p) : key(k), parent(p) {
    balanced = 0x00;
    height = 0x00;
  }
  ~Node () {}
  inline void setHeight();
template<typename C>
  friend std::ostream& operator<< (std::ostream&, const Node<C>& n);
};

template<typename T>
void Node<T>::setHeight() {
  auto leftHeight = (left != nullptr) ? left->height : -0x01;
  auto rightHeight = (right!=nullptr) ? right->height: -0x01;
  height = std::max (leftHeight, rightHeight) + 0x01;
  balanced = rightHeight - leftHeight;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const Node<T>& n) {
  auto h = '0', b = '0';
  h += n.height;
  out << "(" << n.key << "," << h << ",";
  if (n.balanced < 0x00) {
    b -= n.balanced;
    out << "-";
  } else if (n.balanced > 0x00) {
    b += n.balanced;
    out << "+";
  }
  return out << b << ")";
}

template<typename T>
class bst {
    SHPT<Node<T>> root;
    auto search (const T&, SHPT<Node<T>>&);
    void insert (const T&, SHPT<Node<T>>&, SHPT<Node<T>>&);
    void replace_node_in_parent (const SHPT<Node<T>>&, SHPT<Node<T>>&);
    void right_rotation (SHPT<Node<T>>);
    void left_rotation (SHPT<Node<T>>);
    void rebalance (SHPT<Node<T>>);
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
void bst<T>::insert (const T& key, SHPT<Node<T>>& parent, SHPT<Node<T>>& n) {
  if (n == nullptr) {
    n = std::make_shared<Node<T>>(key, parent);
    rebalance (parent);
  } else if (key < n->key) {
    insert (key, n, n->left);
  } else {
    insert (key, n, n->right);
  }
}

template<typename T>
void bst<T>::replace_node_in_parent (const SHPT<Node<T>>& n, SHPT<Node<T>>& nn) {
  if (nn != nullptr) {
    nn->parent = n->parent;
  }
  if (n->parent != nullptr) {
    if (n == n->parent->left) {
      n->parent->left = nn;
    } else {
      n->parent->right = nn;
    }
  } else {
    root = nn;
  }
}

template<typename T>
void bst<T>::right_rotation (SHPT<Node<T>> n) {
  auto pivot = n->left;
  n->left = pivot->right;
  n->setHeight();
  if (n->left != nullptr) {
    n->left->parent = n;
  }
  pivot->right = n;
  replace_node_in_parent (n, pivot);
  n->parent = pivot;
}

template<typename T>
void bst<T>::left_rotation (SHPT<Node<T>> n) {
  auto pivot = n->right;
  n->right = pivot->left;
  n->setHeight();
  if (n->right != nullptr) {
    n->right->parent = n;
  }
  pivot->left = n;
  replace_node_in_parent (n, pivot);
  n->parent = pivot;
}

template<typename T>
void bst<T>::rebalance (SHPT<Node<T>> n) {
  n->setHeight();
  if (n->balanced < -0x01) {
    if (n->left->balanced > 0x00) {
      left_rotation (n->left);
    }
    right_rotation (n);
  } else if (n->balanced > 0x01) {
    if (n->right->balanced < 0x00) {
      right_rotation (n->right);
    }
    left_rotation (n);
  }
  if (n->parent != nullptr) {
    rebalance (n->parent);
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
    rebalance (n->parent);
  } else if (n->right != nullptr) {
    replace_node_in_parent (n, n->right);
    rebalance (n->parent);
  } else {       // this node has no children
    replace_node_in_parent (n, n->left); // replace with null
    rebalance (n->parent);
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
