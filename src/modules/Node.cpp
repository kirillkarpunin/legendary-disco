#include "Node.h"

#include <utility>

Node::Node(std::string key, int data): key(std::move(key)), data(data), is_deleted(false) {}

Node::~Node() = default;
