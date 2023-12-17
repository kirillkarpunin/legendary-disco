#include <vector>
#include "modules/HashTable.h"

std::string random_string(){
    const std::string alphabet = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    srand(clock());
    std::string generated_string(7, '-');
    for (auto& elem: generated_string){
        elem = alphabet[rand()%alphabet.length()];
    }

    return generated_string;
}

std::string init_ht(HashTable* ht, int k){
    std::string str, ret_str;
    for (int i = 0; i < k; i++){
        str = random_string();
        ht->insert(str, i);

        if (i == k/2)
            ret_str = str;
    }

    return ret_str;
}

void research(int n){
    std::cout << "\n\nn = " << n << std::endl;

    time_t start, end;

    std::cout << "\t- O(n): ";

    std::vector<int> vec;

    start = clock();
    for (int i = 0; i < n; i++){
        vec.push_back(1);
    }
    end = clock();

    std::cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;


    std::cout << "\t- remove(worst_case): ";

    auto ht = new HashTable(n);
    std::string rem_str = init_ht(ht, n);

    start = clock();
    ht->remove(rem_str);
    end = clock();

    std::cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;


    std::cout << "\t- remove(common_case): ";

    ht->clear();
    rem_str = init_ht(ht, n/2);

    start = clock();
    ht->remove(rem_str);
    end = clock();

    std::cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;


    std::cout << "\t- remove(best_case): ";

    ht->clear();
    rem_str = init_ht(ht, 2);

    start = clock();
    ht->remove(rem_str);
    end = clock();

    std::cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;


    std::cout << "\t- O(1): ";

    start = clock();
    vec[0] = 1;
    end = clock();

    std::cout << (double)(end - start) / CLOCKS_PER_SEC * 1000 << std::endl;

    delete ht;
}

int main(){

    for (int n = 10; n < 100001; n*=10){
        research(n);
    }

    return 0;
}