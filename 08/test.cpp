#include "binary_tree.h"
#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

TEST(BinaryTreeTest, DefaultConstructor) {
    bst<int, std::string> tree;
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
}

TEST(BinaryTreeTest, InsertAndSize) {
    bst<int, std::string> tree;
    
    auto result1 = tree.insert({1, "one"});
    EXPECT_TRUE(result1.second);
    EXPECT_EQ(result1.first->first, 1);
    EXPECT_EQ(tree.size(), 1);
    EXPECT_FALSE(tree.empty());
    
    auto result2 = tree.insert({2, "two"});
    EXPECT_TRUE(result2.second);
    EXPECT_EQ(tree.size(), 2);
    
    auto result3 = tree.insert({1, "ONE"});
    EXPECT_FALSE(result3.second);
    EXPECT_EQ(tree.size(), 2);
}

TEST(BinaryTreeTest, OperatorBracket) {
    bst<int, std::string> tree;
    
    tree[1] = "one";
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree[1], "one");
    
    tree[2] = "two";
    EXPECT_EQ(tree.size(), 2);
    EXPECT_EQ(tree[2], "two");
    
    tree[1] = "ONE";
    EXPECT_EQ(tree[1], "ONE");
    EXPECT_EQ(tree.size(), 2);
    
    tree[3];
    EXPECT_EQ(tree.size(), 3);
    EXPECT_EQ(tree[3], "");
}

TEST(BinaryTreeTest, AtMethod) {
    bst<int, std::string> tree;
    tree[1] = "one";
    tree[2] = "two";
    
    EXPECT_EQ(tree.at(1), "one");
    EXPECT_EQ(tree.at(2), "two");
    
    EXPECT_THROW(tree.at(3), std::out_of_range);
    
    const auto& const_tree = tree;
    EXPECT_EQ(const_tree.at(1), "one");
    EXPECT_THROW(const_tree.at(3), std::out_of_range);
}

TEST(BinaryTreeTest, FindAndContains) {
    bst<int, std::string> tree;
    tree[1] = "one";
    tree[2] = "two";
    tree[3] = "three";
    
    auto it1 = tree.find(2);
    EXPECT_NE(it1, tree.end());
    EXPECT_EQ(it1->first, 2);
    EXPECT_EQ(it1->second, "two");
    
    auto it2 = tree.find(5);
    EXPECT_EQ(it2, tree.end());
    
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    EXPECT_FALSE(tree.contains(5));
}

TEST(BinaryTreeTest, Erase) {
    bst<int, std::string> tree;
    tree[5] = "five";
    tree[3] = "three";
    tree[7] = "seven";
    tree[2] = "two";
    tree[4] = "four";
    tree[6] = "six";
    tree[8] = "eight";
    
    EXPECT_EQ(tree.size(), 7);
    
    EXPECT_EQ(tree.erase(2), 1);
    EXPECT_FALSE(tree.contains(2));
    EXPECT_EQ(tree.size(), 6);
    
    tree.erase(4);
    EXPECT_FALSE(tree.contains(4));
    EXPECT_EQ(tree.size(), 5);
    
    tree.erase(5);
    EXPECT_FALSE(tree.contains(5));
    EXPECT_EQ(tree.size(), 4);
    
    EXPECT_EQ(tree.erase(100), 0);
    EXPECT_EQ(tree.size(), 4);
}

TEST(BinaryTreeTest, Iterator) {
    bst<int, std::string> tree;
    tree[5] = "five";
    tree[3] = "three";
    tree[7] = "seven";
    tree[1] = "one";
    tree[4] = "four";
    tree[6] = "six";
    tree[9] = "nine";
    
    std::vector<int> keys;
    for (const auto& pair : tree) {
        keys.push_back(pair.first);
    }
    
    std::vector<int> expected = {1, 3, 4, 5, 6, 7, 9};
    EXPECT_EQ(keys, expected);
    
    auto it = tree.begin();
    EXPECT_EQ(it->first, 1);
    EXPECT_EQ(it->second, "one");
    
    ++it;
    EXPECT_EQ(it->first, 3);
    EXPECT_EQ(it->second, "three");
}

TEST(BinaryTreeTest, ConstIterator) {
    bst<int, std::string> tree;
    tree[2] = "two";
    tree[1] = "one";
    tree[3] = "three";
    
    const auto& const_tree = tree;
    
    std::vector<int> keys;
    for (auto it = const_tree.begin(); it != const_tree.end(); ++it) {
        keys.push_back(it->first);
    }
    
    EXPECT_EQ(keys, std::vector<int>({1, 2, 3}));
    
    auto it = const_tree.find(2);
    EXPECT_NE(it, const_tree.end());
    EXPECT_EQ(it->first, 2);
    EXPECT_EQ(it->second, "two");
}

TEST(BinaryTreeTest, Clear) {
    bst<int, std::string> tree;
    tree[1] = "one";
    tree[2] = "two";
    tree[3] = "three";
    
    EXPECT_EQ(tree.size(), 3);
    EXPECT_FALSE(tree.empty());
    
    tree.clear();
    
    EXPECT_EQ(tree.size(), 0);
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.begin(), tree.end());
}

TEST(BinaryTreeTest, ComplexTypes) {
    bst<std::string, int> tree;
    tree["apple"] = 5;
    tree["banana"] = 3;
    tree["cherry"] = 8;
    
    EXPECT_EQ(tree["apple"], 5);
    EXPECT_EQ(tree["banana"], 3);
    EXPECT_TRUE(tree.contains("cherry"));
    
    std::vector<std::string> keys;
    for (const auto& pair : tree) {
        keys.push_back(pair.first);
    }
    
    std::vector<std::string> expected = {"apple", "banana", "cherry"};
    EXPECT_EQ(keys, expected);
}

TEST(BinaryTreeTest, ComparisonFunction) {
    bst<int, std::string, std::greater<int>> tree;
    tree[5] = "five";
    tree[1] = "one";
    tree[3] = "three";
    tree[7] = "seven";
    
    std::vector<int> keys;
    for (const auto& pair : tree) {
        keys.push_back(pair.first);
    }
    
    std::vector<int> expected = {7, 5, 3, 1};
    EXPECT_EQ(keys, expected);
}

TEST(BinaryTreeTest, IteratorOperations) {
    bst<int, std::string> tree;
    tree[1] = "a";
    tree[2] = "b";
    tree[3] = "c";
    tree[4] = "d";
    
    auto it = tree.find(2);
    EXPECT_NE(it, tree.end());
    EXPECT_EQ(it->first, 2);
    
    --it;
    EXPECT_EQ(it->first, 1);
    
    ++it; 
    ++it;
    EXPECT_EQ(it->first, 3);
    
    auto old_it = it++;
    EXPECT_EQ(old_it->first, 3);
    EXPECT_EQ(it->first, 4);
    
    old_it = it--;
    EXPECT_EQ(old_it->first, 4);
    EXPECT_EQ(it->first, 3);
    
    ++it; 
    ++it;
    EXPECT_EQ(it, tree.end());
}

TEST(BinaryTreeTest, EraseByIterator) {
    bst<int, std::string> tree;
    tree[1] = "one";
    tree[2] = "two";
    tree[3] = "three";
    
    auto it = tree.find(2);
    EXPECT_NE(it, tree.end());
    tree.erase(it);
    
    EXPECT_EQ(tree.size(), 2);
    EXPECT_FALSE(tree.contains(2));
    EXPECT_TRUE(tree.contains(1));
    EXPECT_TRUE(tree.contains(3));
    
    std::vector<int> keys;
    for (const auto& pair : tree) {
        keys.push_back(pair.first);
    }
    std::sort(keys.begin(), keys.end());
    EXPECT_EQ(keys, std::vector<int>({1, 3}));
}

TEST(BinaryTreeTest, MoveSemantics) {
    bst<int, std::string> tree1;
    tree1[1] = "one";
    tree1[2] = "two";
    
    bst<int, std::string> tree2(std::move(tree1));
    
    EXPECT_EQ(tree2.size(), 2);
    EXPECT_TRUE(tree1.empty());
    EXPECT_EQ(tree2[1], "one");
    EXPECT_EQ(tree2[2], "two");
    
    bst<int, std::string> tree3;
    tree3 = std::move(tree2);
    
    EXPECT_EQ(tree3.size(), 2);
    EXPECT_TRUE(tree2.empty());
    EXPECT_EQ(tree3[1], "one");
    EXPECT_EQ(tree3[2], "two");
}

TEST(BinaryTreeTest, FindOnEmptyTree) {
    bst<int, std::string> tree;
    
    auto it = tree.find(5);
    EXPECT_EQ(it, tree.end());
    
    const auto& const_tree = tree;
    auto cit = const_tree.find(5);
    EXPECT_EQ(cit, const_tree.end());
}

TEST(BinaryTreeTest, AtThrowsException) {
    bst<int, std::string> tree;
    tree[1] = "one";
    
    EXPECT_NO_THROW(tree.at(1));
    EXPECT_THROW(tree.at(2), std::out_of_range);
    
    const auto& const_tree = tree;
    EXPECT_NO_THROW(const_tree.at(1));
    EXPECT_THROW(const_tree.at(2), std::out_of_range);
}

TEST(BinaryTreeTest, OperatorBracketCreatesNew) {
    bst<int, std::string> tree;
    
    EXPECT_EQ(tree.size(), 0);
    
    tree[1];
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree[1], "");
    
    tree[1] = "one";
    EXPECT_EQ(tree.size(), 1);
    EXPECT_EQ(tree[1], "one");
}

TEST(BinaryTreeTest, EdgeCases) {
    bst<int, std::string> tree;
    
    tree[1] = "one";
    EXPECT_EQ(tree.size(), 1);
    tree.erase(1);
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.begin(), tree.end());
    
    tree[3] = "three";
    tree[2] = "two";
    tree[1] = "one";
    
    std::vector<int> keys;
    for (const auto& pair : tree) {
        keys.push_back(pair.first);
    }
    EXPECT_EQ(keys, std::vector<int>({1, 2, 3}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}