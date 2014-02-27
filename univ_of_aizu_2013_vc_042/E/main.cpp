
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

namespace setlib {
  class DisjointSets {
  public:
    std::vector<int> data;
    DisjointSets( int size ): data(size, -1) {};
    void init( int size ) { data.resize(size); std::fill( data.begin(), data.end(), -1 ); }
    bool merge( int x, int y ) {
      x = root(x), y = root(y);
      if ( x != y ) {
        if ( data[y] < data[x] ) std::swap( x, y );
        data[x] += data[y], data[y] = x;
      }
      return x != y;
    }
    bool same( int x, int y ) { return root(x) == root(y); }
    int root( int x ) { return data[x] < 0 ? x : data[x] = root(data[x]); }
  };
}

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
  const Int MAX_V = 1000 + 11;
  const Int MAX_E = 10000 + 11;
}

// @snippet<sh19910711/contest-base-simple:solution/template-storages.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    Int S[MAX_E];
    Int T[MAX_E];
    Int C[MAX_E];
  };
  
  struct Output {
    Int result;
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution-io.cpp>
namespace solution {
  struct SolutionIO {
    Input in;
    Output out;
    
    template <class Stream> bool input( Stream& s ) {
      if ( ! ( s >> in.N >> in.M && in.N ) ) return false;
      for ( auto i = 0; i < in.M; ++ i )
        if ( ! ( s >> in.S[i] >> in.T[i] >> in.C[i] ) ) return false;
      return true;
    }
    
    template <class Stream> bool output( Stream& s ) {
      return s << out.result << endl;
    }
  };
}

// @snippet<sh19910711/contest-base-simple:solution/solution.cpp>
namespace solution {
  struct Solution: SolutionIO {
    //
    // Implement here
    //
    
    typedef setlib::DisjointSets UnionFind;
    typedef std::tuple <Int, Int, Int> Edge;
    typedef std::priority_queue <Edge, std::vector<Edge>, std::greater<Edge>> EdgeQueue;
    typedef std::vector<Edge> EdgeVector;

    Int n;
    Int m;

    Solution() {}
    
    bool solve() {
      n = in.N;
      m = in.M;
      out.result = find_good_median();
      return true;
    }

    Int find_good_median() {
      EdgeQueue q;
      for ( auto i = 0; i < m; ++ i ) {
        q.push(Edge(in.C[i], in.S[i] - 1, in.T[i] - 1));
      }
      EdgeVector edges;
      UnionFind uf(MAX_V);
      while ( ! q.empty() ) {
        auto e = q.top(); q.pop();
        if ( ! uf.same(get<1>(e), get<2>(e)) ) {
          edges.push_back(e);
          uf.merge(get<1>(e), get<2>(e));
        }
      }
      return get<0>(edges[edges.size() / 2]);
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


