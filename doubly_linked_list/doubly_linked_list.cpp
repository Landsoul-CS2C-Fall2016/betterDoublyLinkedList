// doubly_linked_list.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>

#include "doubly_linked_list.h"

// Simple main program that tests that the following methods work:
// DoublyLinkedList();  // default constructor
// DoublyLinkedList::push_back;
// DoublyLinkedList::begin();
// const T&amp; iterator::operator*() const;
int main() {
   DoublyLinkedList<std::string> mylist;
   std::list<std::string> fruit_list = { "fish", "orange", "fish", "oobleck",
      "tomato", "passion", "fish", "fish",
      "mango", "fish", "waifu", "porrage" };
   mylist.push_back("first");
   mylist.push_back("second");

   DoublyLinkedList<std::string>::iterator myiterator = mylist.begin();
   DoublyLinkedList<std::string>::iterator myiter;
   DoublyLinkedList<std::string> emptyList;

   DoublyLinkedList<std::string> fruits;
   int count = 1;

   for (const auto item : fruit_list) {
      myiter = fruits.begin();
      int randomPos = rand() % count;      
      for (int i = 1; i < randomPos; ++i)
         ++myiter;
      fruits.insert(myiter, item);
      ++count;
   }

   DoublyLinkedList<std::string> listCopy(fruits);
   if (*myiterator != "first") {
      std::cout << "Oh no!  Expected *myiterator == \"first\", "
         << "but actually *myiterator == " << *myiterator << std::endl;
   }
   mylist.print_list();
   std::cout << mylist.size() << std::endl;
   fruits.print_list();
   std::cout << fruits.size() << std::endl;
   listCopy.print_list();
   std::cout << listCopy.size() << std::endl;
   std::cout << "size of empty list: " << emptyList.size() << std::endl;

   DoublyLinkedList<std::string>::iterator fruitRemover = fruits.begin();
   for (int i = 1; i <= fruits.size();) {
      std::cout << "erasing: " << *fruitRemover << std::endl;
      fruitRemover = fruits.erase(fruitRemover);
   }
   std::cout << fruits.size() << std::endl;
   fruits.print_list();

   auto item = "fish";
   std::cout << "removing: " << item << std::endl;
   listCopy.remove(item);
   item = "oobleck";
   listCopy.remove(item);

   std::cout << listCopy.size() << std::endl;
   listCopy.print_list();

   return 0;
}

