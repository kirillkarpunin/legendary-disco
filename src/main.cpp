#include "modules/HashTable.h"

int main(){
    HashTable ht(99);

    ht.print();

    ht.insert("", 10);
    ht.insert("dogs", 15);
    ht.insert("rats", 3);
    ht.insert("snakes", 1);

    std::cout << ht["dogs"] << std::endl;
    std::cout << ht.search("dogs") << std::endl;

    ht.print();

    ht.remove("snakes");
    //ht.remove("hamsters");

    ht.print();

    ht.remove("");
    ht.remove("dogs");
    ht.remove("rats");

    //ht.remove("hamsters");

    return 0;
}