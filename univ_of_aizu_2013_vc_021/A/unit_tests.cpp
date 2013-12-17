
// @snippet<sh19910711/contest:unit-tests.cpp>
#define __MY_UNIT_TEST__
#include "./main.cpp"
#include <gtest/gtest.h>

/*
 *  # Example
 *
 *  int add( int x, int y ) {
 *    return x + y;
 *  }
 *
 *  TEST(AddTest, Test1) {
 *    ASSERT_EQ(2, add(1, 1));
 *  }
 */

class SolverTest: public solution::Solver {
public:
  static int get_characters( const int& x ) {
    return solution::Solver::get_characters(x);
  }
};

TEST(Test, Test) {
  ASSERT_EQ(1, SolverTest::get_characters(1));
  ASSERT_EQ(21, SolverTest::get_characters(9));
  ASSERT_EQ(309, SolverTest::get_characters(99));
  ASSERT_EQ(165, SolverTest::get_characters(54));
  ASSERT_EQ(2836, SolverTest::get_characters(776));
}
