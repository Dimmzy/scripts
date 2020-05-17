#ifndef MM14_DS__MAXMINHEAP_H_
#define MM14_DS__MAXMINHEAP_H_
#include <iostream>
#include <vector>
#include <cmath>


class MaxMinHeap {
 public:
  void buildHeap(std::vector<int> arr); // Builds the heap from a passed integer array
  void heapInsert(int key); // Inserts the key into the max-min heap and "fixes" the heap
  void heapDelete(int index); // Deletes the element in the given index
  void heapExtractMin(); // Prints and removes the minimal element
  void heapExtractMax(); // Prints and removes the maximal element
  void printHeap(); // Prints the heap in an array-like format
 private:
  std::vector<int> array; // Array representing a max-min heap
  void heapify(int i); // Performs heapify (Push Down)
  void heapifyUp(int i); // Performs heapify upwards (Push Up)
  void heapifyUpMax(int i); // Heapify upwards in case of Max Heap
  void heapifyUpMin(int i); // Heapify upwards in case of Min Heap
  void heapifyMax(int i); // Heapify in case of Max Heap
  void heapifyMin(int i); // Heapify in case of Min Heap
};

#endif //MM14_DS__MAXMINHEAP_H_
