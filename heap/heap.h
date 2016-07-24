#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>

/**
  An implementation of a heap - a specialized tree-based
  data structure. Namely, this is a binary min-heap,
  in which the tree is a complete binary tree.
  This heap is implemented in a dynamic array.
  An instance of this class can be created when a pre-filled
  array is passed as a parameter to its constructor.
  The class implements common operations involving heaps.
  The description of Heap data structure can be found at -
  en.wikipedia.org/wiki/Heap_(data_structure)
*/

template<typename T>
class CHeap {
    std::vector<T> nodes;
    void sift_down (int, int);
    void sift_up (int);
  public:
    CHeap() {}
    CHeap (const std::vector<T>& arr) : nodes (arr) { heapify(); }
    ~CHeap() {}
    void heapify();
    void insert (T);
    bool empty() { return nodes.empty(); }
    // returns the node of minimum value after removing it from the heap
    T pop();
template<typename C>
    friend std::ostream& operator<< (std::ostream&, const CHeap<C>&);
};

/**
  min-heap is built from the bottom up by successively
  sifting downward to establish the heap property.
*/
template<typename T>
void CHeap<T>::heapify() {
  // start with the last parent node;
  // the last element index is (size - 1) and
  // the index of the i's node's parent is (i-1) / 2
  auto size = nodes.size();
  for(int i = (size - 2) / 2; i >= 0; i--) {
    sift_down (i, size);
  }
}

/**
  Move a node down in the tree, as long as needed; used
  to restore heap condition after deletion or replacement.
*/
template<typename T>
void CHeap<T>::sift_down (int i, int size) {
  if(size < 2) {
    return;
  }
  // the index of the left and the right child branch
  int ileft = 2*i + 1;
  int irght = 2*i + 2;
  int swap = i;
  if (*nodes[ileft] < *nodes[i]) {
    swap = ileft;
  }
  if ( (irght < size) && (*nodes[irght] < *nodes[swap]) ) {
    // if there is a right child and that child is less
    swap = irght;
  }
  if ( swap == i ) {
    // the node holds the lowest element
    return;
  } else {
    T tmp = nodes[i];
    nodes[i] = nodes[swap];
    nodes[swap] = tmp;
    if ((2*swap + 1) < size) {
      sift_down (swap, size);
    }
  }
}

/**
  Move a node up in the tree, as long as needed;
  used to restore heap condition after insertion.
*/
template<typename T>
void CHeap<T>::sift_up (int i) {
  // the index of the node's parent
  auto iparent = (i-1) / 2;
  if (*nodes[i] < *nodes[iparent]) {
    T tmp = nodes[i];
    nodes[i] = nodes[iparent];
    nodes[iparent] = tmp;
    if (iparent > 0) {
      sift_up (iparent);
    }
  }
}

/**
  deletes the root node followed by moving
  last node and sifting down to maintain heap.
*/
template<typename T>
T CHeap<T>::pop() {
  auto size = nodes.size();
  if (size > 0) {
    auto n = nodes[0];
    auto it = nodes.end() - 1;
    // decrease the size
    if (size > 1) {
      nodes[0] = *it;
      sift_down(0, size-1);
    }
    nodes.erase (it);
    return n;
  }
  // return nullptr;
}

/**
  adds the new element at the end of the heap in the first
  available free space. The elements are then sifted up
  untill the heap property has been reestablished.
*/
template<typename T>
void CHeap<T>::insert (T n) {
  if (n != nullptr) {
    nodes.emplace_back (n);
    sift_up (nodes.size() - 1);
  }
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const CHeap<T>& t) {
  auto size = t.nodes.size();
  out << " SIZE " << size << std::endl;
  for (int i = 0, j = 1, d = 0; i < size; i++) {
    out << *t.nodes[i];
    if ( (d == 0) || (i % d == 0) ) {
      j *= 2, d += j;
      out << std::endl;
    } else {
      out << " ";
    }
  }
  out << std::endl;
  return out;
}

#endif /* HEAP_H */
