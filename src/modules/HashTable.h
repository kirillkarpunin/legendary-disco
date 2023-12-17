#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

class HashTable {
private:
    Node** hash_table;
    int capacity;
    int size;

    int hash(const std::string& key);
public:
    HashTable(int capacity);
    ~HashTable();

    int operator[] (const std::string& key);

    void insert(const std::string& key, int data);
    int search(const std::string& key);
    void remove(const std::string& key);
    void print();

    int length();
    bool is_full();
    void clear();
};


#endif //HASHTABLE_HASHTABLE_H
