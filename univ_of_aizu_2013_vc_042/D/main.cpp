
// @snippet<sh19910711/contest-base-simple:header.cpp>
#define __THIS_IS_CPP11__
/* default headers {{{ */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <limits>
#include <cstdio>
#include <cmath>

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif
/* }}} */


// @snippet<sh19910711/contest-base-simple:solution/template-typedef.cpp>
namespace solution {
  /* primitives {{{ */
  using namespace std;
  typedef long long Int;
  typedef long double Double;
  typedef string String;
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:solution/template-constants.cpp>
namespace solution {
  const Int SIZE = 500 + 11;
  const String YES = "yes";
  const String NO = "no";
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int n;
    String A[SIZE];
  };
  
  struct Output {
    bool result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if ( ! ( s >> in.n && in.n ) ) return false;
      for ( auto i = 0; i < in.n; ++ i )
        if ( ! ( s >> in.A[i] ) ) return false;
      return true;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << ( out.result ? YES : NO ) << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    Solution() {}

    static const Int MAX_V = 26;
    
    Int n;
    String A[SIZE];
    bool G[MAX_V][MAX_V];

    bool solve() {
      n = in.n;
      copy(in.A, in.A + n, A);
      init_graph();
      out.result = check();
      return true;
    }

    void init_graph() {
      for ( auto i = 0; i < MAX_V; ++ i ) {
        for ( auto j = 0; j < MAX_V; ++ j ) {
          G[i][j] = false;
        }
      }
    }

    bool check() {
      for ( auto i = 0; i + 1 < n; ++ i ) {
        const String& a = A[i];
        const String& b = A[i + 1];
        Int na = a.size();
        Int nb = b.size();
        if ( na > nb && a.substr(0, nb) == b )
          return false;
        Int nab = min(na, nb);
        for ( auto j = 0; j < nab; ++ j ) {
          if ( a[j] != b[j] ) {
            G[a[j] - 'a'][b[j] - 'a'] = true;
            break;
          }
        }
      }
      for ( auto k = 0; k < MAX_V; ++ k ) {
        for ( auto i = 0; i < MAX_V; ++ i ) {
          for ( auto j = 0; j < MAX_V; ++ j ) {
            G[i][j] |= G[i][k] & G[k][j];
          }
        }
      }
      for ( auto i = 0; i < MAX_V; ++ i ) {
        if ( G[i][i] ) return false;
      }
      return true;
    }
    
    /* action methods {{{ */
    void before_action( const int& t_id ) {}
    
    void after_action( const int& t_id ) {}
    
    bool action( const int& t_id = -1 ) {
      before_action(t_id);
      bool res = input(std::cin) && solve() && output(std::cout);
      after_action(t_id);
      return res;
    }
    /* }}} */
  };
}

// @snippet<sh19910711/contest-base-simple:solution/runner-normal.cpp>
namespace solution {
  /* Runner Class {{{ */
  struct Runner {
    static int run() {
      bool f = false;
      while ( ! f ) {
        Solution* sol = new Solution;
        f = ! sol->action();
        delete sol;
      };
      return 0;
    }
  };
  /* }}} */
}

// @snippet<sh19910711/contest-base-simple:main_func.cpp>
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  return solution::Runner::run();
}

// @snippet<sh19910711/contest-base-simple:main.cpp>

