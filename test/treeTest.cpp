#include <gtest/gtest.h>
#include "nfatree.hpp"


using namespace NFA;

TEST(TreeTest, allocs){
    //this test asserts nothing, but is here for valgrind checks

    TreeNode n(0, "");
    n.nextStates.push_back(new TreeTransition());
    n.nextStates[0]->next = new TreeNode(1, "");

}

TEST(TreeTest, eclosureEmpty){
    TreeNode n(0, "");

    std::set<int> s = epsilonClosure(n);
    
    std::set<int> test;
    test.insert(0);

    ASSERT_TRUE(s == test);

}

TEST(TreeTest, eclosureSimple){

}