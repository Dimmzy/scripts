#include "MaxMinHeap.h"
#include <utility>

/**
 * Builds a Max-Min heap from the vector argument.
 * Performs the heapify function from the first non-leaf node.
 * @param arr the array we'll create a Max-Min heap from.
 */
void MaxMinHeap::buildHeap(std::vector<int> arr) {
  this->array = std::move(arr);
  int i = floor(this->array.size() / 2);
  for (; i >= 0; i--) {
    heapify(i);
  }
}

/**
 * Heapify swaps elements until the subtree conforms to the Heap properties (min or max according to level)
 * @param i the index of the root of the subtree we will heapify.
 */
void MaxMinHeap::heapify(int i) {
  int currentLevel = floor(log2(i+1)); // Find the level key resides on
  if (currentLevel % 2) { // Odd level -> min level
    heapifyMin(i);
  } else { // Else, Even level -> max level
    heapifyMax(i);
  }
}

/**
 * Performs Heapify upwards (aka Push Up), used when inserting an element to fix heap violations.
 * @param i the index of the root of the subtree we heapify upwards from.
 */
void MaxMinHeap::heapifyUp(int i) {
  if (i == 0) return;
  int parent = (i - 1) / 2;
  int currentLevel = floor(log2(i+1));
  if (currentLevel % 2) { // Max level
    if (this->array[parent] < this->array[i]) { // If the parent is smaller than the current node (on min level)
      std::swap(this->array[parent], this->array[i]); // Swap them
      heapifyUpMax(parent); // Keep going up
    } else {
      heapifyUpMin(i);
    }
  } else { // Min level
    if (this->array[parent] > this->array[i]) { // If the parent is larger than the current node (on max level)
      std::swap(this->array[parent],this->array[i]); // Swap them
      heapifyUpMin(parent);  // Keep going up, through a min level
    } else {
      heapifyUpMax(i);
    }
  }
}

/**
 * Performs heapifyUp on a Max Heap level
 * @param i index of the current root
 */
void MaxMinHeap::heapifyUpMax(int i) {
  if (i == 0) return; // If we're at the top level, nothing more to do
  int parent = (i - 1) / 2;
  if (parent == 0) return; // If no grandparents ( :( ) nothing to
  int grandparent = (parent - 1) / 2;
  if (this->array[i] >  this->array[grandparent]) { // Swaps with grandparents if needed and keeps going
    std::swap(this->array[i], this->array[grandparent]);
    heapifyUpMax(grandparent);
  }
}

/**
 * Performs heapifyUp on a Min Heap level
 * @param i index of the current root
 */
void MaxMinHeap::heapifyUpMin(int i) {
  if (i == 0) return; // At the top level
  int parent = (i - 1) / 2;
  if (parent == 0) return; // No grandparents
  int grandparent = (parent - 1) / 2;
  if (this->array[i] < this->array[grandparent]) { // Swaps with grandparents if needed and keeps going
    std::swap(this->array[i], this->array[grandparent]);
    heapifyUpMin(grandparent);
  }
}

/**
 * Performs Heapify on a max heap subtree.
 * @param i index of the current root
 */
void MaxMinHeap::heapifyMax(int i) {
  if (i >= this->array.size()) { // If the heapify index is out of range, throw exception
    throw std::invalid_argument("Index out of range of the array");
  }
  // Calculates the indices of the left and right children
  int leftChild = 2 * i + 1;
  int rightChild = 2 * i + 2;
  int minIndex = i;
  // Checks if any one of the children is larger (since we're on a max level) than the current root
  if (leftChild < this->array.size() && (this->array[leftChild] > this->array[minIndex]))
    minIndex = leftChild;
  if (rightChild < this->array.size() && (this->array[rightChild] > this->array[minIndex]))
    minIndex = rightChild;
  int leftGrandChild = 2 * (leftChild) + 1;
  // Checks the grandchildren, looking for the largest node
  for (int j = 0; j < 4 && leftGrandChild + j< this->array.size(); j++) {
    if (this->array[leftGrandChild + j] > this->array[minIndex])
      minIndex = leftGrandChild + j;
  }
  // Swaps largest node with the root
  std::swap(this->array[i], this->array[minIndex]);
  if (minIndex - leftChild > 1) { // Check if we swapped with grand child
    int parent = (minIndex - 1) / 2;
    // Keep swapping
    if (this->array[parent] > this->array[minIndex])
      std::swap(this->array[parent], this->array[minIndex]);
    heapifyMax(minIndex);
  }
}

/**
 * Performs Heapify on a min heap subtree
 * @param i index of the current root.
 */
void MaxMinHeap::heapifyMin(int i) {
  if (i >= this->array.size()) { // If the heapify index is out of range, throw exception
   throw std::invalid_argument("Index out of range of the array");
  }
  // Calculates the indices of the left and right children
  int leftChild = 2 * i + 1;
  int rightChild = 2 * i + 2;
  int minIndex = i;
  // Checks if any one of the children is smaller (since we're on a min level) than the current root
  if (leftChild < this->array.size() && (this->array[leftChild] < this->array[minIndex]))
    minIndex = leftChild;
  if (rightChild < this->array.size() && (this->array[rightChild] < this->array[minIndex]))
    minIndex = rightChild;
  int leftGrandChild = 2 * (leftChild) + 1;
  // Checks the grandchildren, looking for the smallest node
  for (int j = 0; j < 4 && leftGrandChild + j< this->array.size(); j++) {
    if (this->array[leftGrandChild + j] < this->array[minIndex])
      minIndex = leftGrandChild + j;
  }
  // Swaps root with the smallest
  std::swap(this->array[i], this->array[minIndex]);
  if (minIndex - leftChild > 1) { // Check if we swapped with grand child
    int parent = (minIndex - 1) / 2;
    // Keep swapping
    if (this->array[parent] < this->array[minIndex])
      std::swap(this->array[parent], this->array[minIndex]);
    heapifyMin(minIndex);
  }
}

/**
 * Prints the Max-Min heap in an array-like format.
 */
void MaxMinHeap::printHeap() {
  int size = this->array.size();
  std::cout << "[";
  for (int i = 0; i < size - 1; i++) { //  Print array up to the last element
    std::cout << this->array[i] << ",";
  }
  std::cout << this->array[size-1] << "]" << std::endl; // Print last element and close bracket
}

/**
 * Inserts a key into the Max-Min heap.
 * It appends it to the end of the array and then uses heapify to fix the heap properties.
 * @param key the key we'll insert.
 */
void MaxMinHeap::heapInsert(int key) {
  this->array.push_back(key); // Append the new element to the end of the array
  heapifyUp(this->array.size() - 1); // Heapify up with the new key's index
}

/**
 * Given an index, deletes the element residing in that index.
 * @param index the index of the element we'll remove
 */
void MaxMinHeap::heapDelete(int index) {
  if (index >= this->array.size()) {
    std::cout << "Element does not exist" << std::endl;
    return;
  } else if (index == this->array.size() - 1) { // Deleting rightmost leaf, so just remove it
    this->array.pop_back();
    return;
  } else { // Replaces the rightmost leaf with the element to delete, deletes the leaf and performs heapify
    std::swap(this->array[index],this->array[this->array.size() - 1]);
    this->array.pop_back();
    heapify(index);
  }
}

/*
 * Prints the minimal element in the Max-Min heap.
 * Given the heap's properties, it has to either reside in the root (if it's the only element),
 * or in one of the children of the root.
 */
void MaxMinHeap::heapExtractMin() {
  if (this->array.empty())
    std::cout << "Heap is empty!" << std::endl;
  else if (this->array.size() == 1)
     std::cout << "Minimum key is " << this->array[0] << std::endl;
  else {
    if (this->array[2] > this->array[1])
      std::cout << "Minimum key is " << this->array[1] << std::endl;
    else
      std::cout << "Minimum key is " << this->array[2] << std::endl;
  }
}

/*
 * Prints the maximal element in the Max-Min heap.
 * Has to be the root because of the heap properties, unless the heap is empty.
 */
void MaxMinHeap::heapExtractMax() {
  if (this->array.empty())
    std::cout << "Heap is empty!" << std::endl;
  else
    std::cout << "Maximum key is " << this->array[0] << std::endl;
}

