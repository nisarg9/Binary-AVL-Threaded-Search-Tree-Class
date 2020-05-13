/*test.cpp*/

//
// An AVL unit test based on Catch framework
//

#include <iostream>
#include <vector>
#include <algorithm>

#include "avlt.h"

#include "catch.hpp"

using namespace std;


TEST_CASE("(111) empty tree")
{
  avlt<int, int>  tree;

  REQUIRE(tree.size() == 0);
  REQUIRE(tree.height() == -1);
}


TEST_CASE("(112) case 1 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 100, 80, 60 };
  vector<int> heights = { 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 1:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(12) case 1 at the left")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 16, 10, 5, 4 };
  vector<int> heights = { 2, 0, 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(13) case 1 at the right")
{
  avlt<int, int>  tree;

  vector<int> keys = { 10, 9, 15, 14, 13 };
  vector<int> heights = { 2, 0, 0, 1, 0 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(21) case 2 at the left")
{
  avlt<int, int>  tree;

  vector<int> keys = { 10, 5, 7 };
  vector<int> heights = { 0, 0, 1 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(22) case 2 at the left")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 20, 10, 5, 7 };
  vector<int> heights = { 2, 0, 0, 0, 1 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(23) case 2 at the right")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 10, 20, 17, 18 };
  vector<int> heights = { 2, 0, 0, 0 , 1 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(31) case 3 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 10,13, 12 };
  vector<int> heights = { 0, 0, 1};

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(32) case 3 at the left")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 10, 20, 13, 12 };
  vector<int> heights = { 2, 0, 0, 0 , 1 };

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(33) case 3 at the right")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 10, 20, 17, 18 };
  vector<int> heights = { 2, 0, 0, 0, 1};

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(41) case 4 at the root")
{
  avlt<int, int>  tree;

  vector<int> keys = { 10, 12, 13 };
  vector<int> heights = { 0, 1, 0};

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(42) case 4 at the left")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 10, 20, 12, 13 };
  vector<int> heights = { 2, 0, 0, 1, 0};

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}

TEST_CASE("(43) case 4 at the right")
{
  avlt<int, int>  tree;

  vector<int> keys = { 15, 10, 20, 22, 25 };
  vector<int> heights = { 2, 0, 0, 1, 0};

  for (int key : keys)
  {
    tree.insert(key, -key);
  }

  //
  // size and height?  after rebalance should be 2:
  //
  REQUIRE(tree.size() == keys.size());

  auto maxH = std::max_element(heights.begin(), heights.end());
  REQUIRE(tree.height() == *maxH);
  // 
  // values inserted?
  //
  int value;

  for (int key : keys)
  {
    REQUIRE(tree.search(key, value));
    REQUIRE(value == -key);
  }

  //
  // heights correct after rebalance?
  //
  for (size_t i = 0; i < keys.size(); ++i)
  {
    REQUIRE((tree % keys[i]) == heights[i]);
  }
}