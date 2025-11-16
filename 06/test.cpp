#include "Vector.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 0);
}

TEST(VectorTest, SizeConstructor) {
    Vector<int> v(5);
    EXPECT_FALSE(v.empty());
    EXPECT_EQ(v.size(), 5);
    EXPECT_GE(v.capacity(), 5);
}

TEST(VectorTest, SizeValueConstructor) {
    Vector<int> v(3, 42);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 42);
    EXPECT_EQ(v[1], 42);
    EXPECT_EQ(v[2], 42);
}

TEST(VectorTest, PushBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
}

TEST(VectorTest, FrontBack) {
    Vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    
    EXPECT_EQ(v.front(), 10);
    EXPECT_EQ(v.back(), 30);
}

TEST(VectorTest, OperatorBracket) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    
    v[0] = 100;
    v[1] = 200;
    EXPECT_EQ(v[0], 100);
    EXPECT_EQ(v[1], 200);
}

TEST(VectorTest, Data) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    
    int* data = v.data();
    EXPECT_EQ(data[0], 1);
    EXPECT_EQ(data[1], 2);
}

TEST(VectorTest, Reserve) {
    Vector<int> v;
    EXPECT_EQ(v.capacity(), 0);
    
    v.reserve(10);
    EXPECT_GE(v.capacity(), 10);
    EXPECT_TRUE(v.empty());
    
    v.push_back(1);
    EXPECT_EQ(v.size(), 1);
    EXPECT_GE(v.capacity(), 10);
}

TEST(VectorTest, Resize) {
    Vector<int> v;
    v.resize(5);
    EXPECT_EQ(v.size(), 5);
    
    v.resize(3);
    EXPECT_EQ(v.size(), 3);
    
    v.resize(7, 99);
    EXPECT_EQ(v.size(), 7);
    EXPECT_EQ(v[6], 99);
}

TEST(VectorTest, PopBack) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    
    v.pop_back();
    EXPECT_EQ(v.size(), 2);
    EXPECT_EQ(v.back(), 2);
    
    v.pop_back();
    EXPECT_EQ(v.size(), 1);
    EXPECT_EQ(v.back(), 1);
    
    v.pop_back();
    EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Insert) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(3);
    
    auto it = v.insert(v.begin() + 1, 2);
    EXPECT_EQ(v.size(), 3);
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
    EXPECT_EQ(v[2], 3);
    EXPECT_EQ(*it, 2);
}

TEST(VectorTest, Reverse) {
    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    
    v.reverse();
    EXPECT_EQ(v[0], 4);
    EXPECT_EQ(v[1], 3);
    EXPECT_EQ(v[2], 2);
    EXPECT_EQ(v[3], 1);
}

TEST(VectorTest, CopyConstructor) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    
    Vector<int> v2(v1);
    EXPECT_EQ(v2.size(), 3);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 3);
    
    v2[0] = 100;
    EXPECT_EQ(v1[0], 1); 
}

TEST(VectorTest, MoveConstructor) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    
    Vector<int> v2(std::move(v1));
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_TRUE(v1.empty()); 
}

TEST(VectorTest, CopyAssignment) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    
    Vector<int> v2;
    v2 = v1;
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
}

TEST(VectorTest, MoveAssignment) {
    Vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    
    Vector<int> v2;
    v2 = std::move(v1);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_EQ(v2[0], 1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, ShrinkToFit) {
    Vector<int> v;
    v.reserve(10);
    v.push_back(1);
    v.push_back(2);
    
    EXPECT_GT(v.capacity(), 2);
    v.shrink_to_fit();
    EXPECT_EQ(v.capacity(), 2);
}

TEST(VectorBoolTest, DefaultConstructor) {
    Vector<bool> v;
    EXPECT_TRUE(v.empty());
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorBoolTest, SizeConstructor) {
    Vector<bool> v(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_FALSE(v[0]);
    EXPECT_FALSE(v[4]);
}

TEST(VectorBoolTest, SizeValueConstructor) {
    Vector<bool> v(3, true);
    EXPECT_EQ(v.size(), 3);
    EXPECT_TRUE(v[0]);
    EXPECT_TRUE(v[1]);
    EXPECT_TRUE(v[2]);
}

TEST(VectorBoolTest, PushBack) {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    
    EXPECT_EQ(v.size(), 3);
    EXPECT_TRUE(v[0]);
    EXPECT_FALSE(v[1]);
    EXPECT_TRUE(v[2]);
}

TEST(VectorBoolTest, OperatorBracket) {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    
    EXPECT_TRUE(v[0]);
    EXPECT_FALSE(v[1]);
    
    v[0] = false;
    v[1] = true;
    EXPECT_FALSE(v[0]);
    EXPECT_TRUE(v[1]);
}

TEST(VectorBoolTest, FrontBack) {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    
    EXPECT_TRUE(v.front());
    EXPECT_TRUE(v.back());
}

TEST(VectorBoolTest, Reserve) {
    Vector<bool> v;
    v.reserve(20);
    EXPECT_GE(v.capacity(), 20);
    
    for (int i = 0; i < 20; ++i) {
        v.push_back(i % 2 == 0);
    }
    
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(v[i], i % 2 == 0);
    }
}

TEST(VectorBoolTest, Resize) {
    Vector<bool> v;
    v.resize(5, true);
    EXPECT_EQ(v.size(), 5);
    EXPECT_TRUE(v[4]);
    
    v.resize(3);
    EXPECT_EQ(v.size(), 3);
    
    v.resize(7, false);
    EXPECT_EQ(v.size(), 7);
    EXPECT_FALSE(v[6]);
}

TEST(VectorBoolTest, Insert) {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    
    v.insert(1, true);
    EXPECT_EQ(v.size(), 3);
    EXPECT_TRUE(v[0]);
    EXPECT_TRUE(v[1]);
    EXPECT_FALSE(v[2]);
}

TEST(VectorBoolTest, Reverse) {
    Vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);
    
    v.reverse();
    EXPECT_FALSE(v[0]);
    EXPECT_TRUE(v[1]);
    EXPECT_FALSE(v[2]);
    EXPECT_TRUE(v[3]);
}

TEST(VectorBoolTest, CopyConstructor) {
    Vector<bool> v1;
    v1.push_back(true);
    v1.push_back(false);
    
    Vector<bool> v2(v1);
    EXPECT_EQ(v2.size(), 2);
    EXPECT_TRUE(v2[0]);
    EXPECT_FALSE(v2[1]);
}

TEST(VectorBoolTest, MemoryEfficiency) {
    Vector<bool> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i % 2 == 0);
    }
    EXPECT_LT(v.capacity() / 8, 100); 
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}