//
// Created by Jan Halemba on 19/01/2022.
//

#include "Dictionary.h"
#include "gtest/gtest.h"


TEST(AVLTree, TestNodeConstruct) {

    Dictionary<int, int> d;

    d.insert(10, 5);

    ASSERT_EQ(d.getRoot()->getKey(), 10);
    ASSERT_EQ(d.getRoot()->getRight(), nullptr);
    ASSERT_EQ(d.getRoot()->getLeft(), nullptr);
    ASSERT_EQ(d.getRoot()->getParent(), nullptr);
}


namespace {
    class AVLTest : public ::testing::Test {
    public:
        Dictionary<int, int>* d;
        void SetUp() override
        {
            d = new Dictionary<int, int>;
        }
        void TearDown() override
        {
            delete d;
        }
    };

    TEST_F(AVLTest, InsertTest) {
        d->insert(5, 2);
        d->insert(6, 7);
        d->insert(4, 8);

        auto* root = d->getRoot();

        EXPECT_EQ(root->getKey(), 5);
        EXPECT_EQ(root->getParent(), nullptr);
        EXPECT_EQ(root->getLeft()->getKey(), 4);
        EXPECT_EQ(root->getLeft()->getParent(), root);
        EXPECT_EQ(root->getRight()->getKey(), 6);
        EXPECT_EQ(root->getRight()->getParent(), root);
    }

    TEST_F(AVLTest, SingleRotateLeftOnInsert) {
        d->insert(5, 43);
        d->insert(6, 2);
        d->insert(7, 1);

        auto * root = d->getRoot();

        EXPECT_EQ(root->getKey(), 6);
        EXPECT_EQ(root->getParent(), nullptr);
        EXPECT_EQ(root->getLeft()->getKey(), 5);
        EXPECT_EQ(root->getLeft()->getParent(), root);
        EXPECT_EQ(root->getRight()->getKey(), 7);
        EXPECT_EQ(root->getRight()->getParent(), root);
    }

    TEST_F(AVLTest, SingleRotateRightOnInsert) {
        d->insert(5, 4);
        d->insert(4, 2);
        d->insert(3, 1);

        auto * root = d->getRoot();

        EXPECT_EQ(root->getKey(), 4);
        EXPECT_EQ(root->getParent(), nullptr);
        EXPECT_EQ(root->getLeft()->getKey(), 3);
        EXPECT_EQ(root->getLeft()->getParent(), root);
        EXPECT_EQ(root->getRight()->getKey(), 5);
        EXPECT_EQ(root->getRight()->getParent(), root);
    }

    TEST_F(AVLTest, TestHeight) {
        d->insert(5,1);
        d->insert(4,1);
        d->insert(9,1);
        d->insert(3, 1);
        d->insert(2, 3);
        d->insert(10, 4);
        d->insert(7, 9);

        EXPECT_EQ(d->getRoot()->getHeight(), 2);
    }

    TEST_F(AVLTest, TestRemove) {
        d->insert(5,1);
        d->insert(4,1);
        d->insert(9,1);
        d->insert(3, 1);
        d->insert(2, 3);
        d->remove(10);
        d->insert(7, 9);

        EXPECT_EQ(d->getRoot()->getRight()->getRight(), nullptr);
    }

    TEST_F(AVLTest, RemoveNonExistingElement) {
        d->insert(5, 4);
        d->insert(4, 2);
        d->insert(3, 1);
        d->remove(8);
        auto * root = d->getRoot();

        EXPECT_EQ(root->getKey(), 4);
        EXPECT_EQ(root->getParent(), nullptr);
        EXPECT_EQ(root->getLeft()->getKey(), 3);
        EXPECT_EQ(root->getLeft()->getParent(), root);
        EXPECT_EQ(root->getRight()->getKey(), 5);
        EXPECT_EQ(root->getRight()->getParent(), root);
    }

}