#include "HashTable.h"

HashTable::HashTable(int capacity): capacity(capacity), size(0) {
    if (capacity <= 0)
        throw std::invalid_argument("invalid size");

    hash_table = new Node*[capacity];
    for (int i = 0; i < capacity; i++){
        hash_table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++){
        delete hash_table[i];
    }
    delete [] hash_table;
}

int HashTable::hash(const std::string &key) {

    return (int)key[0] % capacity;

    /*
    // djb2 hashing

    long hash = 5381;
    for (auto ch : key){
        hash = ((hash << 5) + hash) + (int)ch;
    }
    return (int)(hash % capacity);
    */
}

void HashTable::insert(const std::string& key, int data) {
    if (size == capacity)
    {
        int start_index = hash(key);
        if (hash_table[start_index]->key == key){
            hash_table[start_index]->data = data;
            return;
        }

        int curr_index = (start_index + 1) % capacity;
        while (curr_index != start_index)
        {
            if (hash_table[curr_index]->key == key){
                hash_table[curr_index]->data = data;
                return;
            }
            curr_index = (curr_index + 1) % capacity;
        }

        throw std::overflow_error("hash table is overflown");
    }

    else
    {
        int curr_index = hash(key);
        while (hash_table[curr_index] && !hash_table[curr_index]->is_deleted && hash_table[curr_index]->key != key)
        {
            curr_index = (curr_index + 1) % capacity;
        }
        if (hash_table[curr_index] == nullptr)
        {
            hash_table[curr_index] = new Node(key, data);
            size++;
        }
        else
        {
            if (hash_table[curr_index]->is_deleted){
                hash_table[curr_index]->key = key;
                hash_table[curr_index]->is_deleted = false;
                size++;
            }
            hash_table[curr_index]->data = data;
        }
    }
}

int HashTable::search(const std::string& key) {
    if (size == 0)
        throw std::length_error("hash table empty");

    int start_index = hash(key);
    if (hash_table[start_index] == nullptr)
        throw std::invalid_argument("no such key: " + key);

    if (hash_table[start_index]->key == key && !hash_table[start_index]->is_deleted)
        return hash_table[start_index]->data;

    int curr_index = (start_index + 1) % capacity;
    while (curr_index != start_index)
    {
        if (hash_table[curr_index] == nullptr)
            throw std::invalid_argument("no such key: " + key);

        if (hash_table[curr_index]->key == key && !hash_table[curr_index]->is_deleted)
            return hash_table[curr_index]->data;
        curr_index = (curr_index + 1) % capacity;
    }

    throw std::invalid_argument("no such key: " + key);
}

void HashTable::remove(const std::string &key) {
    if (size == 0)
        throw std::length_error("hash table empty");

    int start_index = hash(key);
    if (hash_table[start_index] == nullptr)
        throw std::invalid_argument("no such key: " + key);

    if (hash_table[start_index]->key == key && !hash_table[start_index]->is_deleted){
        hash_table[start_index]->is_deleted = true;
        size--;
        return;
    }

    int curr_index = (start_index + 1) % capacity;
    while (curr_index%capacity != start_index)
    {
        if (hash_table[curr_index] == nullptr)
            throw std::invalid_argument("no such key: " + key);

        if (hash_table[curr_index]->key == key && !hash_table[curr_index]->is_deleted){
            hash_table[curr_index]->is_deleted = true;
            size--;
            return;
        }
        curr_index = (curr_index + 1) % capacity;
    }

    throw std::invalid_argument("no such key: " + key);
}

void HashTable::print() {
    std::cout << "size: " << size << std::endl;

    for (int i = 0; i < capacity; i++){
        if (hash_table[i] && !hash_table[i]->is_deleted)
            std::cout << "[" << i << "] " << hash_table[i]->key << ": " << hash_table[i]->data << std::endl;
    }
}

int HashTable::operator[](const std::string &key) {
    return search(key);
}

int HashTable::length() {
    return size;
}

bool HashTable::is_full() {
    return size == capacity;
}

void HashTable::clear() {
    if (size == 0) return;

    for (int i = 0; i < capacity; i++){
        if (hash_table[i]){
            hash_table[i]->is_deleted = true;
        }
    }
    size = 0;
}
