
// @snippet<sh19910711/contest-base:headers.cpp>
#define __THIS_IS_CPP11__
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

#ifdef __THIS_IS_CPP11__
#include <memory>
#include <array>
#endif


// @snippet<sh19910711/contest:utils/collection_prototype.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class Iterator, class Value> void fill( Iterator, const int&, const Value& );
  
  // copy(from, num, to)
  template <class Iterator> void copy( const Iterator& from, const int& num, Iterator& to );
  
  // sort(begin, num)
  template <class Iterator> void sort( Iterator begin, const int& n );
  
  // reverse(begin, num)
  template <class Iterator> void reverse( Iterator begin, const int& n );
  
#endif
}

// @snippet<sh19910711/contest:utils/misc_prototype.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b );
  template <class T> void min( T& a, const T& b );
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v );
  template <class T> T to_type( const std::string& s );
  
}

// @snippet<sh19910711/contest:utils_prototypes.cpp>

// @snippet<sh19910711/contest-base:solution/template-class.cpp>
namespace solution {
  struct Input;
  struct Output;
  struct Storages {
    Input* in;
    Output* out;
  };
}

// @snippet<sh19910711/contest-base:solution/solver-interface.cpp>
namespace solution {
  struct SolverInterface {
    virtual ~SolverInterface() {}
    virtual const Output* solve( const Input* in, Output* out ) = 0;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-interface.cpp>
namespace solution {
  struct SolutionInterface {
    virtual ~SolutionInterface() {};
    virtual int run() = 0;
    virtual bool action() = 0;
    virtual bool input( Input* s ) = 0;
    virtual void output( const Output* s ) = 0;
    virtual void before_all_actions() {}
    virtual void after_all_actions() {}
    virtual void before_action( const int& test_no ) {}
    virtual void after_action( const int& test_no ) {}
    SolverInterface* solver;
    Storages* storages;
  };
}

// @snippet<sh19910711/contest-base:solution/solution-base.cpp>
namespace solution {
  struct SolutionBase: SolutionInterface {
    virtual ~SolutionBase() {};
    
    int run() {
      this->before_all_actions();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      this->after_all_actions();
      return 0;
    }
    
    bool action() {
      if ( ! this->input(this->storages->in) ) {
        return false;
      }
      this->output(solver->solve(this->storages->in, this->storages->out));
      return true;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-primitive-types.cpp>
namespace solution {
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
}

// @snippet<sh19910711/contest-base:solution/template-constants.cpp>
namespace solution {
  // constants
  const Int SIZE = 100 + 11;
}

// @snippet<sh19910711/contest-base:solution/template-namespaces.cpp>
namespace solution {
  // namespaces, types
  using namespace utils;
  typedef std::array<Int, SIZE> IntArray;
  typedef std::array<bool, SIZE> BoolArray;
}

// @snippet<sh19910711/contest-base:solution/template-storage.cpp>
namespace solution {
  struct Input {
    Int N;
    Int M;
    IntArray U;
    IntArray V;
    IntArray F;
  };
  
  struct Output {
    Int result;
  };
  
}

// @snippet<sh19910711/contest-base:solution/template-solver-area.cpp>
namespace solution {
  typedef std::tuple<Int, Int> NodeBase;
  struct Node: NodeBase {
    Node() {}
    Node( const NodeBase& base ) { *this = base; }
    Node( const Int& to, const Int& cost ) {
      this->get_to() = to;
      this->get_cost() = cost;
    }

    Int& get_to() { return std::get<0>(*this); }
    const Int& get_to() const { return std::get<0>(*this); }
    Int& get_cost() { return std::get<1>(*this); }
    const Int& get_cost() const { return std::get<1>(*this); }
  };

  struct Finder {
    typedef std::vector<Node> NodeVector;
    typedef std::array<NodeVector, SIZE> AdjacentList;

    Int N;
    AdjacentList G;
    BoolArray used;
    Int cnt;

    void init() {
      N = in->N;
      fill(std::begin(used), SIZE, false);
      cnt = 0;
      generate_graph();
    }

    void generate_graph() {
      for ( auto& g : G ) g.clear();
      for ( auto i = 0; i < in->M; ++ i ) {
        const auto u = in->U[i] - 1;
        const auto v = in->V[i] - 1;
        const auto f = in->F[i];
        G[u].push_back(Node(v, f));
        G[v].push_back(Node(u, f));
      }
    }

    bool check_connected( const Int& from ) {
      Int tmp = 0;
      for ( const auto& e : G[from] ) {
        if ( used[e.get_to()] )
          ++ tmp;
      }
      return cnt == tmp;
    }

    Int get_sum() {
      Int res = 0;
      for ( auto i = 0; i < N; ++ i ) {
        if ( ! used[i] )
          continue;
        Int tmp = std::numeric_limits<Int>::max();
        for ( const auto& e : G[i] ) {
          if ( ! used[e.get_to()] )
            continue;
          min(tmp, e.get_cost());
        }
        if ( tmp != std::numeric_limits<Int>::max() )
          res += tmp;
      }
      return res;
    }

    Int rec( const Int& cur ) {
      Int res = std::numeric_limits<Int>::min();
      for ( auto i = cur; i < N; ++ i ) {
        if ( ! check_connected(i) )
          continue;
        used[i] = true;
        cnt ++;
        max(res, std::max(get_sum(), rec(i + 1)));
        cnt --;
        used[i] = false;
      }
      return res;
    }

    Int find() {
      return rec(0);
    }

    const Input* in;
    Finder( const Input* in ): in(in) { init(); }
    typedef std::unique_ptr<Finder> Pointer;
    static Pointer create( const Input* in ) { return Pointer(new Finder(in)); }
  };

  struct Solver: SolverInterface {
    const Output* solve( const Input* in, Output* out ) {
      auto finder = Finder::create(in);
      out->result = finder->find();
      return out;
    }
  };
}

// @snippet<sh19910711/contest-base:solution/template-solution.cpp>
namespace solution {
  struct Solution: SolutionBase {
    bool input( Input* in ) {
      if ( ! ( std::cin >> in->N >> in->M ) )
        return false;
      for ( auto i = 0; i < in->M; ++ i )
        if ( ! ( std::cin >> in->U[i] >> in->V[i] >> in->F[i] ) )
          return false;
      return true;
    }
    void output( const Output* out ) {
      std::cout << out->result << std::endl;
    }
  };
}

// @snippet<sh19910711/contest-base:main_func.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  // desc: http://meme.biology.tohoku.ac.jp/students/iwasaki/cxx/speed.html#id18
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  // 
  using namespace solution;
  static Input      in;
  static Output     out;
  static Storages   storages;
  static Solution   solution;
  static Solver     solver;
  storages.in       = &in;
  storages.out      = &out;
  solution.storages = &storages;
  solution.solver   = &solver;
  return solution.run();
}
#endif

// @snippet<sh19910711/contest:utils/collection.cpp>
namespace utils {
#ifdef __THIS_IS_CPP11__
  // fill(begin, num, value)
  template <class Iterator, class V> void fill( Iterator begin, const int& num, const V& value ) {
    std::fill(begin, begin + num, value);
  }
  
  // copy(from, num, to)
  template <class Iterator> void copy( const Iterator from, const int& num, Iterator to ) {
    std::copy(from, from + num, to);
  }
  
  // sort(begin, num)
  template <class Iterator> void sort( Iterator begin, const int& num ) {
    std::sort(begin, begin + num);
  }
  
  // reverse(begin, num)
  template <class Iterator> void reverse( Iterator begin, const int& num ) {
    std::reverse(begin, begin + num);
  }
  
#endif
}

// @snippet<sh19910711/contest:utils/misc.cpp>
namespace utils {
  // max(a, b), min(a, b)
  template <class T> void max( T& a, const T& b ) { a = std::max(a, b); }
  template <class T> void min( T& a, const T& b ) { a = std::min(a, b); }
  // to_s(v), ret = to_type(str)
  template <class T> std::string to_string( const T& v ) { std::ostringstream oss; oss << v; return oss.str(); }
  template <class T> T to_type( const std::string& s ) { std::istringstream iss(s); T res; iss >> res; return res; }
  
}

// @snippet<sh19910711/contest:utils.cpp>

// @snippet<sh19910711/contest-base:main.cpp>

