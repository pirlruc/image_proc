#include <gtest/gtest.h>

#define WITH_DEBUG
#include <improc/services/container.h>
#include <container.cpp>

TEST(Container,TestEmptyContainerConstructor) {
    improc::Container<int,std::any> container_empty {};
    EXPECT_EQ(container_empty.Size(),0);
}

TEST(Container,TestAddItemToContainer) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    EXPECT_EQ(container.Size(),1);
}

TEST(Container,TestAddDuplicateItemToContainer) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    EXPECT_THROW(container.Add(1,"Test 2"),improc::duplicated_key);
}

TEST(Container,TestAddDifferentItemsToContainer) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    container.Add(2,45);
    EXPECT_EQ(container.Size(),2);
}

TEST(Container,TestGetExistingItemFromContainer) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    container.Add(2,45);
    EXPECT_EQ(container.Get(1).type(),typeid(const char*));
    EXPECT_EQ(container.Get(2).type(),typeid(int));
    EXPECT_EQ(std::any_cast<int>(container.Get(2)),45);
    EXPECT_STREQ(std::any_cast<const char*>(container.Get(1)),"Test 1");
}

TEST(Container,TestGetNonExistingItemFromContainer) {
    improc::Container<int,std::any> container {};
    EXPECT_THROW(container.Get(1),improc::not_found_key);
}

TEST(Container,TestEraseNonExistingItemFromContainer) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    container.Erase(2);
    EXPECT_EQ(container.Size(),1);
}

TEST(Container,TestEraseExistingItemFromContainer) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    container.Add(2,45);
    container.Erase(1);
    EXPECT_EQ(container.Size(),1);
}

TEST(Container,TestClear) {
    improc::Container<int,std::any> container {};
    container.Add(1,"Test 1");
    container.Add(2,45);
    container.Clear();
    EXPECT_EQ(container.Size(),0);
}
