#ifndef UNTITLED1_MULTILLIST_H
#define UNTITLED1_MULTILLIST_H

#include <iostream>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

class MultiLinkedList {
 public:
  struct ListNode {
    ListNode *next_name, *next_ext, *next_size;
    string infos[3];

    ListNode(const string &name, const string &ext, const string &size) {
      next_name = next_ext = next_size = nullptr;
      infos[0] = name;
      infos[1] = ext;
      infos[2] = size;
    }
  };
  ListNode *head_name, *head_ext, *head_size;
  int fileCount = 0;

  MultiLinkedList() { head_name = head_ext = head_size = nullptr; }
  /**
   * @brief Destroy the My Linked List object WIP.
   *
   */
  ~MultiLinkedList() {
    ListNode *curr_name = head_name, *curr_ext = head_ext,
             *curr_size = head_size;
    ListNode *nextNodeName = nullptr, *nextNodeExt = nullptr,
             *nextNodeSize = nullptr;

    while(curr_name != nullptr) {
      nextNodeName = curr_name->next_name;
      delete curr_name;
      curr_name = nextNodeName;
    }
    while(curr_ext != nullptr) {
      nextNodeExt = curr_ext->next_ext;
      delete curr_ext;
      curr_ext = nextNodeExt;
    }
    while(curr_size != nullptr) {
      nextNodeSize = curr_size->next_size;
      delete curr_size;
      curr_size = nextNodeSize;
    }
  }

  /**
   * @brief Creates a node with the specified name extension and specified
   * dimensions and adds it sequentially to the linked list. in order of name,
   * extension and size nodes; name pointers, extension pointers, and size
   * pointers are sequentially linked among themselves. (Ordered with respect to
   * ASCII Table.)
   * *********************************************************************************
   * @param name Value of the node's name in a string representation.
   * @param ext Value of the node's extension in a string representation.
   * @param size Value of the node's size in a string representation.
   */
  void addNode(const string &name, const string &ext, const string &size) {

    ListNode *node = new ListNode(name, ext, size);

    //////////////////////// NAME SIDE ////////////////////////
    ListNode *curr_name;
    if(head_name == nullptr || (head_name->infos[0] >= name)) {
      node->next_name = head_name;
      head_name = node;
    } else {
      curr_name = head_name;
      while(curr_name->next_name != nullptr &&
            curr_name->next_name->infos[0] < name) {
        curr_name = curr_name->next_name;
      }
      node->next_name = curr_name->next_name;
      curr_name->next_name = node;
    }

    //////////////////////// EXTENSION SIDE ////////////////////////
    ListNode *curr_ext;
    if(head_ext == nullptr || (head_ext->infos[1] >= ext)) {
      node->next_ext = head_ext;
      head_ext = node;
    } else {
      curr_ext = head_ext;
      while(curr_ext->next_ext != nullptr &&
            curr_ext->next_ext->infos[1] < ext) {
        curr_ext = curr_ext->next_ext;
      }
      node->next_ext = curr_ext->next_ext;
      curr_ext->next_ext = node;
    }

    //////////////////////// SIZE SIDE ////////////////////////
    ListNode *curr_size;
    if(head_size == nullptr || (stoi(head_size->infos[2]) >= stoi(size))) {
      node->next_size = head_size;
      head_size = node;
    } else {
      curr_size = head_size;
      while(curr_size->next_size != nullptr &&
            stoi(curr_size->next_size->infos[2]) < stoi(size)) {
        curr_size = curr_size->next_size;
      }
      node->next_size = curr_size->next_size;
      curr_size->next_size = node;
    }
    fileCount++;
  }

  /**
   * @brief Print all nodes infos like:
   * string name ||| string ext ||| string size
   */
  void printInfosName() const {
    for(ListNode *tmp = head_name; tmp != nullptr; tmp = tmp->next_name) {
      cout << "  > " << tmp->infos[0] << " ||| " << tmp->infos[1] << " ||| "
           << tmp->infos[2];
      cout << endl;
    }
    cout << endl;
  }

  /**
   * @brief Print all nodes infos like:
   * string ext ||| string name ||| string size
   */
  void printInfosExt() const {
    for(ListNode *tmp = head_ext; tmp != nullptr; tmp = tmp->next_ext) {
      cout << "  > " << tmp->infos[1] << " ||| " << tmp->infos[0] << " ||| "
           << tmp->infos[2];
      cout << endl;
    }
    cout << endl;
  }

  /**
   * @brief Print all nodes infos like:
   * string size ||| string name ||| string ext
   */
  void printInfosSize() const {
    for(ListNode *tmp = head_size; tmp != nullptr; tmp = tmp->next_size) {
      cout << "  > " << tmp->infos[2] << " ||| " << tmp->infos[0] << " ||| "
           << tmp->infos[1];
      cout << endl;
    }
    cout << endl;
  }

  /**
   * @brief Searches all nodes with the given string name.
   *
   * @param name string name of the file to search.
   */
  void searchFileName(const string &name) {
    bool flag = false;
    for(ListNode *tmp = head_name; tmp != nullptr; tmp = tmp->next_name) {
      if(tmp->infos[0] == name) {
        cout << "     " << tmp->infos[0] << " " << tmp->infos[1] << " "
             << tmp->infos[2];
        flag = true;
        cout << endl;
      }
    }
    if(flag) {
      cout << "\tSearch completed: File exists with name: " << name << endl;
    } else {
      cout << "\tThere is no file with that name." << endl;
    }
  }

  /**
   * @brief Searches all nodes with the given string extension.
   *
   * @param ext string extension of the file to search.
   */
  void searchFileExt(const string &ext) {
    bool flag = false;
    for(ListNode *tmp = head_ext; tmp != nullptr; tmp = tmp->next_ext) {
      if(tmp->infos[1] == ext) {
        cout << "  > " << tmp->infos[0] << " " << tmp->infos[1] << " "
             << tmp->infos[2];
        flag = true;
        cout << endl;
      }
    }
    if(flag) {
      cout << "\tSearch completed: Files with given extension found." << endl;
    } else {
      cout << "\tThere is no file with that extension." << endl;
    }
  }

  /**
   * @brief Searches all nodes with the given string size.
   *
   * @param size string size of the file to search.
   * @param upperSize string upper bound of the size to search.
   */
  void searchFileSize(const string &size, const string &upperSize = "") {
    bool flag = false;
    int searchSize = std::stoi(size);                 // Lower bound
    int upperBound = std::numeric_limits<int>::max(); // Default to INT_MAX

    if(!upperSize.empty()) {
      upperBound = std::stoi(upperSize); // Set the upper bound
    }

    for(ListNode *tmp = head_size; tmp != nullptr; tmp = tmp->next_size) {
      int fileSize = std::stoi(tmp->infos[2]); // Convert file size to int
      if(fileSize >= searchSize && fileSize <= upperBound) {
        cout << "    " << tmp->infos[0] << " " << tmp->infos[1] << " "
             << tmp->infos[2];
        flag = true;
        cout << endl;
      }
    }
    if(flag) {
      if(upperSize.empty()) {
        cout << "\tSearch completed: Files with sizes greater than or equal to "
             << size << " found." << endl;
      } else {
        cout << "\tSearch completed: Files with sizes between " << size
             << " and " << upperSize << " found." << endl;
      }
    } else {
      if(upperSize.empty()) {
        cout << "\tThere are no files with sizes greater than or equal to "
             << size << "." << endl;
      } else {
        cout << "\tThere are no files with sizes in the specified range."
             << endl;
      }
    }
  }

  /**
   * @brief Searches all nodes with the given string name and deletes that node.
   *
   * @param filename string name of the file.
   */
  void deleteNode(const string &filename) {
    ListNode *temp_name = head_name, *temp_ext = head_ext,
             *temp_size = head_size;
    ListNode *prev_name = nullptr, *prev_ext = nullptr, *prev_size = nullptr;

    if(temp_name != nullptr && temp_name->infos[0] == filename) {
      head_name = temp_name->next_name;
      head_ext = temp_ext->next_ext;
      head_size = temp_size->next_size;
      delete temp_name, temp_ext, temp_size;
      return;
    } else {
      while(temp_name != nullptr && temp_name->infos[0] != filename) {
        prev_name = temp_name;
        prev_ext = temp_ext;
        prev_size = temp_size;
        temp_name = temp_name->next_name;
        temp_ext = temp_ext->next_ext;
        temp_size = temp_size->next_size;
      }
      if(temp_name == nullptr) return;
      prev_name->next_name = temp_name->next_name;
      prev_ext->next_ext = temp_ext->next_ext;
      prev_size->next_size = temp_size->next_size;
      delete temp_name;
      temp_ext, temp_size;
    }
  }

  /**
   * @brief Destroyes multi-linked list and sets the file count to zero.
   *
   */
  void destroyList() {
    for(int i = 0; i < fileCount; i++) {
      ListNode *temp_name = head_name, *temp_ext = head_ext,
               *temp_size = head_size;
      if(temp_name != nullptr) {
        head_name = temp_name->next_name;
        head_ext = temp_ext->next_ext;
        head_size = temp_size->next_size;
      }
    }
    fileCount = 0;
  }
};

#endif // UNTITLED1_MULTILLIST_H