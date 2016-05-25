//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>


HeapPriorityQueue::HeapPriorityQueue() {
  // Empty... nothing needs to be done.
}

HeapPriorityQueue::~HeapPriorityQueue() {
  // no clean-up to do, since the heap is not dynamically allocated
}

void HeapPriorityQueue::put_in(PuzzleState *elem) {
  // TODO:  Put your code here!
  heap.push_back(elem);
  int i = heap.size() - 1;
  while ((i > 0) && (elem->getBadness() < heap[(i-1)/2]->getBadness())) {
    heap[i] = heap[(i-1)/2];
    i = (i-1)/2;
  }
  heap[i] = elem;
}

PuzzleState * HeapPriorityQueue::take_out() {
  assert(!is_empty());
  // TODO:  Put your code here!
  PuzzleState *returnVal = heap[0];
  int size = (int)heap.size() - 1;
  int i = 0;
  int target = 0;
  int vall = heap[size]->getBadness();
  while (2*i+1 < size) {
    int left = 2*i+1;
    int right = left+1;
    int rightt = heap[right]->getBadness();
    int leftt = heap[left]->getBadness();
    if ((right < size) && (rightt < leftt)) {
      target = right;
    } else target = left;
    int targett = heap[target]->getBadness();
    if (targett < vall) {
      heap[i] = heap[target];
      i = target;
    }
    else break;
  }
  heap[i] = heap[size];
  heap.pop_back();
  return returnVal;
}

bool HeapPriorityQueue::is_empty() {
  return (heap.size() == 0);
}

int HeapPriorityQueue::parent(int index) {
  return (index - 1) / 2;
}

int HeapPriorityQueue::first_child(int index) {
  return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
  return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
  return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
  int fchild = first_child(index);
  return max(0, min(2, (int)heap.size() - fchild));
}

#endif
