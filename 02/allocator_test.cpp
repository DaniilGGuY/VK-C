#include <gtest/gtest.h>
#include "allocator.h"

TEST(AllocatorTest, testInit) {
    Allocator* al = init_allocator(10);
    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 0);
    clear(al);
}

TEST(AllocatorTest, testSomeInits) {
    Allocator* al1 = init_allocator(5);
    Allocator* al2 = init_allocator(10);

    ASSERT_NE(al1, nullptr);
    ASSERT_NE(al2, nullptr);
    ASSERT_NE(al1->data, nullptr);
    ASSERT_NE(al2->data, nullptr);
    ASSERT_EQ(al1->size, 5);
    ASSERT_EQ(al2->size, 10);
    ASSERT_EQ(al1->offset, 0);
    ASSERT_EQ(al2->offset, 0);

    ASSERT_NE(al1, al2);
    ASSERT_LT(al1->size, al2->size);
    
    clear(al1);
    clear(al2);
}

TEST(AllocatorTest, testAllocReset) {
    Allocator* al = init_allocator(10);
    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 0);

    alloc(al, 10);

    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 10);

    reset(al);
    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 0);

    clear(al);
}

TEST(AllocatorTest, testAlloc) {
    Allocator* al = init_allocator(10);
    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 0);

    char* p1 = alloc(al, 10);

    ASSERT_EQ(p1, al->data);
    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 10);

    char* p2 = alloc(al, 10);
    ASSERT_EQ(p2, nullptr);
    ASSERT_NE(al, nullptr);
    ASSERT_NE(al->data, nullptr);
    ASSERT_EQ(al->size, 10);
    ASSERT_EQ(al->offset, 10);

    clear(al);
}

TEST(AllocatorTest, testTryToAllocNotInited) {
    Allocator* al1 = nullptr;
    Allocator* al2 = init_allocator(10);
    al2->data = nullptr;
    Allocator* al3 = init_allocator(10);
    al3->size = 0;

    char* p1 = alloc(al1, 10);
    ASSERT_EQ(p1, nullptr);

    char* p2 = alloc(al2, 10);
    ASSERT_EQ(p2, nullptr);

    char* p3 = alloc(al3, 10);
    ASSERT_EQ(p3, nullptr);

    clear(al1);
    clear(al2);
    clear(al3);
}

TEST(AllocatorTest, testMultipleAlloc) {
    Allocator* al = init_allocator(100);

    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(al->offset, i * 10);
        char* p = alloc(al, 10);
        ASSERT_EQ(p, al->data + al->offset - 10);
        ASSERT_EQ(al->offset, (i + 1) * 10);
    }

    clear(al);
}

TEST(AllocatorTest, testNullptr) {
    char* ptr = alloc(nullptr, 10);
    EXPECT_EQ(ptr, nullptr);
    reset(nullptr); 
    clear(nullptr);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}