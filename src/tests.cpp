#include <gtest/gtest.h>
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

int main(){
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

TEST(create, zero_size){
    EXPECT_ANY_THROW(HashTable ht(0));
}

TEST(create, negative_size){
    EXPECT_ANY_THROW(HashTable ht(-10));
}

TEST(insert, standard){
    HashTable ht(10);

    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);

    ht.insert("a", 0);

    EXPECT_EQ(ht.length(), 3);
}

TEST(insert, full_capacity){
    HashTable ht(5);

    ht.insert("a", 1);
    ht.insert("b", 2);
    ht.insert("c", 3);
    ht.insert("d", 4);
    ht.insert("e", 5);

    ht.insert("b", 123);

    EXPECT_TRUE(ht.is_full() && ht.length() == 5);
}

TEST(insert, overflown){
    HashTable ht(1);

    ht.insert("a", 1);
    EXPECT_ANY_THROW(ht.insert("b", 2));
}

TEST(insert, clear){
    HashTable ht(100);

    for(int i = 0; i < 100; i++){
        ht.insert(random_string(), i);
    }

    ht.clear();

    for(int i = 0; i < 100; i++){
        ht.insert(random_string(), i);
    }

    EXPECT_TRUE(ht.length() <= 100);
}

TEST(remove, empty_table){
    HashTable ht(10);

    EXPECT_ANY_THROW(ht.remove("a"));
}

TEST(remove, standard){
    HashTable ht(5);

    ht.insert("a", 1);
    ht.insert("z", 2);
    ht.insert("f", 3);
    ht.insert("k", 4);
    ht.insert("l", 5);

    ht.remove("k");
    ht.remove("a");
    ht.remove("z");

    int f = ht.search("f");
    int l = ht["l"];

    EXPECT_TRUE(ht.length() == 2 && f == 3 && l == 5);
}

TEST(remove, no_key){
    HashTable ht(5);

    ht.insert("a", 1);
    ht.insert("z", 2);
    ht.insert("f", 3);
    ht.insert("k", 4);
    ht.insert("l", 5);

    EXPECT_ANY_THROW(ht.remove("j"));
}

TEST(search, empty_table){
    HashTable ht(10);

    EXPECT_ANY_THROW(ht.search("a"));
}

TEST(search, no_key){
    HashTable ht(10);

    ht.insert("b", 2);

    EXPECT_ANY_THROW(ht.search("a"));
}

TEST(search, operator_test){
    HashTable ht(1);
    ht.insert("a", 1);
    int n = ht.search("a");
    int m = ht["a"];

    EXPECT_EQ(n, m);
}

TEST(search, delete_restore_search){
    HashTable ht(5);

    ht.insert("a", 1);
    ht.insert("z", 2);
    ht.insert("f", 3);
    ht.insert("k", 4);
    ht.insert("l", 5);

    ht.remove("k");
    ht.remove("a");
    ht.remove("z");

    ht.insert("a", 1);
    ht.insert("z", 2);

    int z = ht["z"];
    EXPECT_TRUE(ht.length() == 4 && z == 2);
}
