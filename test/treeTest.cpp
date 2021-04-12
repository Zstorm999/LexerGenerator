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

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected = {0};

    ASSERT_EQ(closure.size(), 1);
    ASSERT_TRUE(closure[0] == expected);
}

TEST(TreeTest, eclosureSimple){
    Tree t;
    t.addNode();
    t.addNode();
    t.addTransition(0, 1);
    
    
    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected0 = {0, 1};

    std::set<uint> expected1 = {1};

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

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected0 = {0, 1};

    std::set<uint> expected1 = {0, 1};

    ASSERT_EQ(closure.size(), 2);
    EXPECT_EQ(closure[0], expected0);
    EXPECT_EQ(closure[1], expected1);
}

TEST(TreeTest, eclosureNested){
    Tree t;
    t.addNode();
    t.addNode();
    t.addNode();

    t.addTransition(0, 1);
    t.addTransition(1, 2);

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected[] = {{0, 1, 2}, {1, 2}, {2}};

    ASSERT_EQ(closure.size(), 3);
    EXPECT_EQ(closure[0], expected[0]);
    EXPECT_EQ(closure[1], expected[1]);
    EXPECT_EQ(closure[2], expected[2]);

}

TEST(TreeTest, eclosureLoopNested){
    Tree t;
    t.addNode();
    t.addNode();
    t.addNode();

    t.addTransition(0, 1);
    t.addTransition(1, 2);
    t.addTransition(2, 0);

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected[] = {{0, 1, 2}, {0, 1, 2}, {0, 1, 2}};

    ASSERT_EQ(closure.size(), 3);
    EXPECT_EQ(closure[0], expected[0]);
    EXPECT_EQ(closure[1], expected[1]);
    EXPECT_EQ(closure[2], expected[2]);
}

TEST(TreeTest, eclosureReal){
    //Ex 2.2 from 'Basics of Compiler Design' by T. Mogensen
    Tree t;
    
    for(int i = 0; i< 7; i++) t.addNode();
    t.addNode("final");

    t.addTransition(0, 1);
    t.addTransition(1, 0, 'a');
    t.addTransition(0, 2);
    t.addTransition(2, 3);
    t.addTransition(2, 4);
    t.addTransition(3, 5, 'b');
    t.addTransition(4, 5, 'a');
    t.addTransition(5, 6, 'a');
    t.addTransition(6, 7, 'a');

    std::map<uint, std::set<uint>> closure = t.epsilonClosure();

    std::set<uint> expected[] = {
        {0, 1, 2, 3, 4},
        {1},
        {2, 3, 4},
        {3},
        {4},
        {5},
        {6},
        {7}
    };

    ASSERT_EQ(closure.size(), 8);

    for(int i = 0; i<8; i++){
        EXPECT_EQ(closure[i], expected[i]);
    }

}