
// @snippet<sh19910711/contest:headers.cpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <complex>
#include <functional>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

// @snippet<sh19910711/contest:solution/define_classes.cpp>
namespace solution {
  class Solution;
  class Solver;
  struct InputStorage;
  struct OutputStorage;
  struct DataStorage;
  class Storages;
}

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    
  protected:
    SolutionInterface() {}
    virtual bool action() = 0;
    virtual bool input( InputStorage& s ) { return false; };
    virtual void output( const OutputStorage& s ) const {};
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) const {}
    virtual void after_action( const int& test_no ) const {}
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {}
    virtual int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int s;
  };
  
  struct OutputStorage {
    String result;
  };
  
  struct DataStorage {
  };
  
  struct Storages {
    InputStorage  in;
    OutputStorage out;
    DataStorage   data;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    const OutputStorage& solve( const InputStorage& in, OutputStorage& out, DataStorage& data ) {
      out.result = generate_sub_fizzbuzz(in.s);
      return out;
    }
    
  protected:
    static String generate_sub_fizzbuzz( const Int& s ) {
      Int lb = 1;
      Int ub = 1000000000000000000LL;
      while ( ub - lb > 1 ) {
        Int mid = ( lb + ub ) / 2;
        if ( get_characters(mid) < s ) {
          lb = mid;
        } else {
          ub = mid;
        }
      }

      Int offset = s - get_characters(lb - 1) - 1;
      String tmp = "";
      for ( Int i = lb; i < lb + 100; ++ i ) {
        tmp += get_fizzbuzz_string(i);
      }
      return tmp.substr(offset, 20);
    }

    static String get_fizzbuzz_string( const Int& x ) {
      if ( x % 3 == 0 && x % 5 == 0 ) {
        return "FizzBuzz";
      } else if ( x % 3 == 0 ) {
        return "Fizz";
      } else if ( x % 5 == 0 ) {
        return "Buzz";
      } else {
        std::ostringstream oss;
        oss << x;
        return oss.str();
      }
      return "";
    }

    // [1, x]で何文字分進むか求める
    static Int get_characters( const Int& x ) {
      Int res = 0;
      Int k = 1;
      Int d = 1;
      while ( k <= x ) {
        Int nx = std::min(k * 10, x);
        Int y = k - 1;
        res += ( get_not_fizz_bizz(nx) - get_not_fizz_bizz(y) ) * d;
        k *= 10;
        d += 1;
      }
      res += ( x / 3 + x / 5 ) * 4;
      return res;
    }

    // not-fizzbuzz number in [1, x]
    static Int get_not_fizz_bizz( const Int& x ) {
      return x - x / 3 - x / 5 + x / 15;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    Solution() {}
    Solution(Storages* p): storages(p) {}
    
  protected:
    virtual bool action() {
      if ( ! this->input(this->storages->in) )
        return false;
      this->output(solver.solve(this->storages->in, this->storages->out, this->storages->data));
      return true;
    }

    bool input( InputStorage& in ) {
      return std::cin >> in.s;
    }

    void output( const OutputStorage& out ) const {
      std::cout << out.result << endl;
    }
    
  private:
    Solver solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  return solution::Solution(&solution::global_storages).run();
}
#endif

