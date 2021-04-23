// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

TEST_F(CollectionTest, CanAddToEmptyVector) {
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, the size should be 1
    ASSERT_EQ(collection->size(), 1);
}

TEST_F(CollectionTest, CanAddFiveValuesToVector) {
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());

    // if not empty, the size should be 5
    ASSERT_EQ(collection->size(), 5);
}

TEST_F(CollectionTest, MaxSizeIsGreaterThanSize) {
    // Check that max_size is greater than or equal to size for 0 entries
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // Check that max_size is greater than or equal to size for 1 entry
    add_entries(1);
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // Check that max_size is greater than or equal to size for 5 entries
    add_entries(4);
    ASSERT_TRUE(collection->max_size() >= collection->size());

    // Check that max_size is greater than or equal to size for 10 entries
    add_entries(5);
    ASSERT_TRUE(collection->max_size() >= collection->size());
}

TEST_F(CollectionTest, CapacityIsGreaterThanSize) {
    // Check that capacity is greater than or equal to size for 0 entries
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // Check that capacity is greater than or equal to size for 1 entry
    add_entries(1);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // Check that capacity is greater than or equal to size for 5 entries
    add_entries(4);
    ASSERT_TRUE(collection->capacity() >= collection->size());

    // Check that capacity is greater than or equal to size for 10 entries
    add_entries(5);
    ASSERT_TRUE(collection->capacity() >= collection->size());
}

TEST_F(CollectionTest, CanResizeUpCollection) {
    unsigned int size = 2;

    // Check that the size hasn't changed
    add_entries(size);
    ASSERT_EQ(collection->size(), size);

    // Check that the size has increased
    collection->resize(3);
    ASSERT_TRUE(collection->size() > size);
}

TEST_F(CollectionTest, CanResizeDownCollection) {
    unsigned int size = 2;

    // Check that the size hasn't changed
    add_entries(2);
    ASSERT_EQ(collection->size(), size);

    // Check that the size has decreased
    collection->resize(1);
    ASSERT_TRUE(collection->size() < size);
}

TEST_F(CollectionTest, CanResizeZeroCollection) {
    add_entries(2);
    collection->resize(0);

    // Check that the collection is empty and the size is 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

TEST_F(CollectionTest, CanClearCollection) {
    add_entries(1);
    collection->clear();

    // Check that the collection is empty and the size is 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

TEST_F(CollectionTest, CanEraseCollection) {
    add_entries(2);
    collection->erase(collection->begin(), collection->end());

    // Check that the collection is empty and the size is 0
    ASSERT_TRUE(collection->empty());
    ASSERT_EQ(collection->size(), 0);
}

TEST_F(CollectionTest, CanReserveCapacityChange) {
    unsigned int size = 2;
    unsigned int newSize = 4;

    add_entries(size);
    collection->reserve(newSize);

    // Check that the size hasn't changed
    ASSERT_EQ(collection->size(), size);
    // Check that the capacity has changed to the new size
    ASSERT_EQ(collection->capacity(), newSize);
}

TEST_F(CollectionTest, CanHandleOutOfRangeException) {
    add_entries(2);
    // Check that an out_of_range error is thrown when accessing a value that soesn't exist
    ASSERT_THROW(collection->at(9999), std::out_of_range);
}

TEST_F(CollectionTest, CanPopBackFromCollection) {
    add_entries(2);
    collection->pop_back();

    // Check that the size is 1 after popping a value off
    ASSERT_EQ(collection->size(), 1);
}

TEST_F(CollectionTest, CanHandleLengthError) {
    add_entries(1);
    // Check that a length_error is thrown when reserving a size greater than max_size
    ASSERT_THROW(collection->reserve(collection->max_size() + 1), std::length_error);
}
