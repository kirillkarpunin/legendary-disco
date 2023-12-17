#ifndef HASHTABLE_NODE_H
#define HASHTABLE_NODE_H

#include <string>

struct Node {
    std::string key;
    int data;
    bool is_deleted;

    Node(std::string  key, int data);
    ~Node();
};


#endif //HASHTABLE_NODE_H
