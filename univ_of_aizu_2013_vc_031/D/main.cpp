
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
  typedef int Int;
  typedef double Double;
}

// @snippet<sh19910711/contest-base:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const Int SIZE = 30000 + 11;
  const Int INDEX_NONE = -1;
  const Double EPS = 1e-12;
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Int M;
    Int W;
    Int H;
    Int S;
    Int L[SIZE][2];
    Double A[SIZE][2];
  };
  struct OutputStorage {
    Int result;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {

  class SearchCand {
    typedef std::pair <Double, Int> Node; // (y, a_id)
  public:
    const InputStorage* in;
    Int N;
    Node S[SIZE];

    Int get_upper_first( const Double& y ) {
      const Node* ret = std::lower_bound(S, S + N, Node(y - EPS, -1));
      if ( ret == S + N )
        return N;
      return ret - S;
    }

    void run( const InputStorage* in ) {
      this->in = in;
      N = in->N;
      for ( int i = 0; i < N; ++ i ) {
        S[i] = Node(in->A[i][1], i);
      }
      std::sort(S, S + N);
    }
  };

  class SearchArea {
  public:
    const InputStorage* in;

    Int M;
    Double A[SIZE];
    Double S[SIZE];

    Double get_sum( const Int& s_id ) {
      return A[s_id];
    }

    // [l, r)
    Double get_sum( const Int& l, const Int& r ) {
      return S[r - 1] - S[l - 1];
      return get_area(r - 1) - get_area(l - 1);
    }

    Double get_area( const Int& s_id ) {
      return s_id < 0 ? 0 : S[s_id];
    }

    void run( const InputStorage* in ) {
      M = in->M;

      std::fill(A, A + SIZE, 0.0);
      for ( Int i = 0; i + 1 < M; ++ i ) {
        Int bottom[2] = {in->L[i][0], in->L[i][1]};
        Int top[2] = {in->L[i+1][0], in->L[i+1][1]};
        for ( Int j = 0; j < 2; ++ j )
          A[i] += ( top[j] - bottom[j] ) * in->W * 0.5;
      }

      std::fill(S, S + SIZE, 0.0);
      Double sum = 0.0;
      for ( Int i = 0; i + 1 < M; ++ i ) {
        sum += A[i];
        S[i] = sum;
      }
      this->in = in;
    }
  };

  class SearchAlmond {
  public:
    const InputStorage* in;
    SearchCand search_cand;

    Int N;
    Double W;
    Double P[SIZE][2];
    Double L[SIZE][2];

    Int M;
    Int A[SIZE];
    Int S[SIZE];

    void run( const InputStorage* in ) {
      this->in = in;

      N = in->N;
      W = in->W;

      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < 2; ++ j ) {
          P[i][j] = in->A[i][j];
          L[i][j] = in->L[i][j];
        }
      }

      // Cand
      search_cand.run(in);
      M = in->M;
      std::fill(A, A + SIZE, 0LL);
      for ( Int i = 0; i + 1 < M; ++ i ) {
        Int lb = search_cand.get_upper_first(std::min(L[i][0], L[i][1]) - EPS);
        Int ub = search_cand.get_upper_first(std::max(L[i + 1][0], L[i + 1][1]) + EPS);
        // check [lb, ub]
        for ( Int a_id = lb; a_id <= ub; ++ a_id ) {
          if ( is_upper(i, a_id) && ! is_upper(i + 1, a_id) ) {
            A[i] ++;
          }
        }
      }

      Int sum = 0;
      for ( Int i = 0; i + 1 < M; ++ i ) {
        sum += A[i];
        S[i] = sum;
      }
    }

    // [l, r)
    Int get_sum( const Int& l, const Int& r ) {
      return get_sum(r - 1) - get_sum(l - 1);
    }

    Int get_sum( const Int& id ) {
      return id < 0 ? 0 : S[id];
    }

    bool is_upper( const Int& l_id, const Int& p_id ) {
      Double vl_x = W;
      Double vl_y = L[l_id][1] - L[l_id][0];
      Double vp_x = P[p_id][0];
      Double vp_y = P[p_id][1] - L[l_id][0];
      // return vl_x * vp_x + vl_y * vp_y >= 0;
      Double cross = vl_x * vp_y - vl_y * vp_x;
      return cross > EPS;
    }
  };

  class SearchNumber {
  public:
    const InputStorage* in;
    SearchArea search_area;
    SearchAlmond search_almond;

    Int N;
    Int M;
    Int W;
    Int H;
    Int S;

    // search_area.get_sum(l, r) >= W * H - S
    bool check( const Int& l, const Int& r ) {
      Double s1 = search_area.get_sum(l, r);
      Double s2 = W * H - S;
      return s1 < s2 + EPS;
    }

    Int get_maximum() {
      Int res = 0;
      for ( Int l = 0, r = 0; l < M && r < M; ++ l ) {
        for ( r = l; r < M && check(l, r); ++ r )
          res = std::max(res, search_almond.get_sum(l, r));
      }
      return res;
    }

    Int run( const InputStorage* in ) {
      this->in = in;
      this->N = in->N;
      this->M = in->M;
      this->W = in->W;
      this->H = in->H;
      this->S = in->S;

      // S
      search_area.run(in);

      // Almond
      search_almond.run(in);

      return N - get_maximum();
    }
  };

  class Solver: public SolverInterface {
  public:
    SearchNumber search;

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->result = search.run(in);
      return out;
    }
  protected:
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N >> in->M >> in->W >> in->H >> in->S ) ) {
        return false;
      }
      if ( in->N == 0 && in->M == 0 && in->W == 0 && in->H == 0 && in->S == 0 ) {
        return false;
      }
      in->L[in->M][0] = in->L[in->M][1] = 0;
      in->M ++;
      for ( int i = 1; i < in->M; ++ i ) {
        std::cin >> in->L[i][0] >> in->L[i][1];
      }
      in->L[in->M][0] = in->L[in->M][1] = in->H;
      in->M ++;
      for ( int i = 0; i < in->N; ++ i ) {
        std::cin >> in->A[i][0] >> in->A[i][1];
      }
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

