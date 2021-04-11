#include <gtest/gtest.h>
#include "nfatree.hpp"

#include <algorithm>

using namespace NFA;

TEST(TreeTest, exceptions){

    Tree t;

    ASSERT_ANY_THROW(t.getNode(0));
    ASSERT_ANY_THROW(t.addTransition(0, 0));
    ASSERT_ANY_THROW(t.addTransition(0, 1));
    
    t.addNode();

    ASSERT_NO_THROW(t.getNode(0));
    ASSERT_NO_THROW(t.addTransition(0, 0));
    ASSERT_ANY_THROW(t.addTransition(0, 1));
}


TEST(TreeTest, eclosureEmpty){
    Tree t;
    t.addNode();

    std::map<int, std::set<int>> closure = t.epsilonClosure();

    std::set<int> expected; expected.insert(0);

    ASSERT_EQ(closure.size(), 1);
    ASSERT_TRUE(closure[0] == expected);
}

TEST(TreeTest, eclosureEmpty1){
    Tree t;
    t.addNode();

    std::map<int, std::set<int>> closure = t.epsilonClosure();

    std::set<int> expected; expected.insert(1);

    ASSERT_EQ(closure.size(), 1);
    ASSERT_TRUE(closure[1] == expected);
}

TEST(TreeTest, eclosureSimple){
    Tree t;
    t.addNode();
    t.addNode();
    t.addTransition(0, 1);
    
    
    std::map<int, std::set<int>> closure = t.epsilonClosure();

    std::set<int> expected0;
        expected0.insert(0);
        expected0.insert(1);

    std::set<int> expected1;
        expected1.insert(1);

    ASSERT_EQ(closure.size(), 2);
    EXPECT_EQ(closure[0], expected0);
    EXPECT_EQ(closure[1], expected1);


}

TEST(TreeTest, eclosureLoop){

    Tree t;
    t.addNode();
    t.addNode();
    t.addTransition(0, 1);
    t.addTransition(1, 0);

    std::map<int, std::set<int>> closure = t.epsilonClosure();

    std::set<int> expected0;
        expected0.insert(0);
        expected0.insert(1);

    std::set<int> expected1;
        expected1.insert(0);
        expected1.insert(1);

    ASSERT_EQ(closure.size(), 2);
    EXPECT_EQ(closure[0], expected0);
    EXPECT_EQ(closure[1], expected1);
}

TEST(TreeTest, eclosureNested){
    
}