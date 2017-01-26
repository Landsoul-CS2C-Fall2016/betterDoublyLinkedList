#pragma once

#ifndef _DOUBLY_LINKED_LIST_H_
#define _DOUBLY_LINKED_LIST_H_

#include <initializer_list>
#include <iostream>

template <typename T>
class DoublyLinkedList {
   // Any data members you need should go here, in the private section
   class Node {
   public:
      T value; // T value
      Node *prev, *next;

      Node(T value_arg, Node* prev_arg, Node* next_arg) : value(value_arg), prev(prev_arg), next(next_arg) {}
      ~Node() {
         if(next != nullptr) // if there is anything else in the DLL
            delete next;
      }

   };
   int listSize = 0;
   Node *first;
   Node *last;
public:
   class iterator {
      Node *nodePointer;
      bool isReversed;
      // Any data members you need should go here, in the private section
   public:
      iterator& operator--() {
         if (nodePointer != nullptr) { // iterates up until the end but goes no further.
            if (!isReversed) {
               nodePointer = nodePointer->prev;
            }
            else {
               nodePointer = nodePointer->next;
            }
         }
         //else {
         //   if (!isReversed)
         //      nodePointer = getLast();
         //   else
         //      nodePointer = getFirst();
         //}
         return *this;
      }
      iterator& operator++() { // iterates up until the end but goes no further.
         if (nodePointer != nullptr) {
            if (!isReversed) {
               nodePointer = nodePointer->next;
            }
            else {
               nodePointer = nodePointer->prev;
            }
         }
         return *this;
      }
      const T& operator*() const {
         return nodePointer->value;
      }
      bool operator!=(const iterator& other) const {
         return (this->nodePointer != other.nodePointer);
      }

      iterator() : nodePointer(nullptr), isReversed(false) {}
      iterator(bool isReversed) : nodePointer(nullptr), isReversed(isReversed) {}
      iterator(Node *node) : nodePointer(node), isReversed(false) {}
      iterator(Node *nPointer, bool isReversed) : nodePointer(nPointer), isReversed(isReversed) {}
      // This allows DoublyLinkedList to be able to look at/modify anything in
      // iterator, even if it's in the private section.
      friend class DoublyLinkedList;
   };

   DoublyLinkedList() : listSize(0), first(nullptr), last(nullptr) {}
   DoublyLinkedList(const DoublyLinkedList& other) {
      iterator position = other.begin();
      while (position != end()) {
         push_back(position.nodePointer->value);
         ++position;
      }
   }
   DoublyLinkedList(std::initializer_list<T> list) : DoublyLinkedList() {
      for (const auto item : list) {
         push_back(item);
      }
   }
   ~DoublyLinkedList() { delete first; }// recursively deletes every node in the DLL

   int size() const noexcept { return listSize; }
   void push_back(const T& value) {
      if (first == nullptr || last == nullptr) { // nothing in DLL
         Node *cur = new Node(value, nullptr, nullptr);
         first = cur;
         last = cur;
      }
      else {
         Node *cur = new Node(value, last, nullptr);
         last->next = cur;
         last = cur;
      }
      ++listSize;
   }
   void remove(const T& val) {
      iterator pos = begin();
      for (; pos != end();) { // check if the requested value is in the list, and if so, remove it.
         if (pos.nodePointer->value == val) {
            pos = erase(pos);
         }
         ++pos;
      }
   }
   iterator erase(iterator position){
      Node *pos = position.nodePointer;
      if (pos != nullptr) { // if you can even erase anything
         if (pos == first && pos == last) { // only one node
            first = last = nullptr;
            position.nodePointer = nullptr;
         }
         else if (pos == last) { // then its right will be a nullptr
            pos->prev->next = nullptr;
            last = pos->prev;
            --position;
         }
         else if (pos == first) { // then its left will be a nullptr
            pos->next->prev = nullptr;
            first = pos->next;
            ++position;
         }
         else { // its somewhere in the middle
            pos->next->prev = pos->prev;
            pos->prev->next = pos->next;
            if (!position.isReversed)
               --position;
            else
               ++position;
         }
         pos->prev = nullptr;
         pos->next = nullptr;
         delete pos;
         --listSize;
      }
      return position;
   }
   iterator insert(iterator position, const T& value) {
      if (first == nullptr && last == nullptr) { // there is nothing in the DLL & does the same as push_back
         Node *myNode = new Node(value, nullptr, nullptr);
         first = myNode;
         last = myNode;
         position.nodePointer = myNode;
      }
      else if (position.nodePointer == first) {
         Node *cur = new Node(value, position.nodePointer->prev, position.nodePointer);
         cur->next->prev = cur;
         first = cur;
      }
      else if (position.nodePointer == last) {
         push_back(value);
         position = last;
         return position;
      }
      else { // we are somewhere in the middle
         Node *cur = new Node(value, position.nodePointer, position.nodePointer->next);
         cur->next->prev = cur;
         cur->prev->next = cur;
         position = cur;
      }
      ++listSize;
      return position;
   }


   // one for iterating over const, one for iterating over non-const
   iterator begin() { return iterator(first); }
   iterator end() { return iterator(nullptr); }
   iterator rbegin() { return iterator(last, true); }
   iterator rend() { return iterator(nullptr, true); }

   iterator begin() const { return iterator(first); }
   iterator end() const { return iterator(nullptr); }
   iterator rbegin() const { return iterator(last, true); }
   iterator rend() const { return iterator(nullptr, true); }

   void print_list() { // for printing out a doublyLinkedList.
      iterator iter = begin();
      iterator end(end());
      std::cout << "\nThis is the Doubly Linked list:" << std::endl;
      for (int i = 1; iter != end; ++i) {
         if ((i % 4) == 0) { // every 4th node, print a new line
            std::cout << std::endl;
         }
         if (iter.nodePointer->prev == nullptr) {
            std::cout << " NULL ";
         }
         std::cout << "<={ " << *iter << " }=>";
         if (iter.nodePointer->next == nullptr) {
            std::cout << " NULL ";
         }
         ++iter;
      }
   }
};

#endif  // _DOUBLY_LINKED_LIST_H_
