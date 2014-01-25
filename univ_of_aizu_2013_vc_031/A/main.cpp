
// @snippet<sh19910711/contest-base:headers.cpp>
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

// @snippet<sh19910711/contest-base:solution/define_classes.cpp>
namespace solution {
  struct InputStorage;
  struct OutputStorage;
  struct Storages {
    InputStorage* in;
    OutputStorage* out;
  };
  class SolverInterface {
  public:
    virtual const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    SolverInterface* solver;
    Storages* storages;
  protected:
    virtual bool input( InputStorage* s ) = 0;
    virtual void output( const OutputStorage* s ) = 0; 
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    virtual bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual ~SolutionBase() {};
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
  };
}

// @snippet<sh19910711/contest-base:solution/typedef.cpp>
namespace solution {
  using namespace std;
  typedef long long Int;
  typedef long double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars


}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types

}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int A;
    Int B;
    Int C;
    Int D;
    Int E;
    Int NA;
    Int NB;
    Int NC;
  };
  struct OutputStorage {
    Int result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {
  class Solver: public SolverInterface {
  public:
    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = find_minimum(in->A, in->B, in->C, in->D, in->E, in->NA, in->NB, in->NC);
      return out;
    }

  protected:
    Int find_minimum( const Int& A, const Int& B, const Int& C, const Int& D, const Int& E, const Int& NA, const Int& NB, const Int& NC ) {
      Int res = NA * A + NB * B + NC * C;
      Int p[5];
      std::fill(p, p + 5, 0LL);
      if ( NC < D ) {
        p[0] = D * E;
        Int remains = D - NC;
        Int mb = std::min(NB, std::max(0LL, remains));
        Int ma = std::min(NA, std::max(0LL, remains - mb));
        p[1] = A * (NA - ma) + B * (NB - mb);
      } else {
        p[0] = NC * E;
        p[1] = NA * A + NB * B;
      }
      res = std::min(res, std::accumulate(p, p + 5, 0LL));
      return res;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      std::cin >> in->A >> in->B >> in->C >> in->D >> in->E;
      if ( in->A == 0 && in->B == 0 && in->C == 0 && in->D == 0 && in->E == 0 ) {
        return false;
      }
      std::cin >> in->NA >> in->NB >> in->NC;
      return true;
    }
    void output( const OutputStorage* out ) {
      std::cout << out->result << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  std::cin.sync_with_stdio(false);
  static solution::InputStorage in;
  static solution::OutputStorage out;
  static solution::Storages storages;
  static solution::Solution solution;
  static solution::Solver solver;
  storages.in = &in;
  storages.out = &out;
  solution.storages = &storages;
  solution.solver = &solver;
  return solution.run();
}
#endif

