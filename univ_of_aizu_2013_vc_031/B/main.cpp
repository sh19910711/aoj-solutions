
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
  const Int SIZE = 100;
  
}

// @snippet<sh19910711/contest-base:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  typedef std::pair <Int, Int> Pos;
  class Rect: public std::pair <Pos, Pos> {
  public:
    Rect() {}
    Rect( const Pos& a, const Pos& b ) {}
    Int& left() { return this->second.first; }
    Int& right() { return this->first.first; }
    Int& top() { return this->first.second; }
    Int& bottom() { return this->second.second; }
    const Int& left() const { return this->second.first; }
    const Int& right() const { return this->first.first; }
    const Int& top() const { return this->first.second; }
    const Int& bottom() const { return this->second.second; }
  };
  typedef std::pair <Rect, Int> Vertex;
  typedef std::set <Vertex> Set;
  typedef std::map <Vertex, Int> Map;
  
}

// @snippet<sh19910711/contest-base:solution/storages-area.cpp>
namespace solution {
  struct InputStorage {
    Int N;
    Rect rects[SIZE];
  };
  struct OutputStorage {
    Int N;
    Int results[SIZE];
  };
}

// @snippet<sh19910711/contest-base:solution/solver-area.cpp>
namespace solution {

  class Search {
  public:
    const InputStorage* in;
    Set vertices;
    Int read_cnt;
    Int results[SIZE];

    void run() {
      vertices.clear();
      for ( Int i = 0; i < in->N; ++ i ) {
        Vertex v;
        v.first = in->rects[i];
        v.second = i;
        vertices.insert(v);
      }

      read_cnt = 1;
      read(vertices);
    }

    void read( Set K ) {
      while ( ! K.empty() ) {
        Vertex pivot = *K.begin();
        K.erase(pivot);
        results[pivot.second] = read_cnt ++;

        Int tx = std::numeric_limits<Int>::max();
        Int ty = pivot.first.bottom();

        for ( Set::const_iterator it_i = K.begin(); it_i != K.end(); ++ it_i ) {
          const Vertex& v = *it_i;
          if ( v.first.top() < ty && ty < v.first.bottom() ) {
            tx = std::min(tx, v.first.right());
          }
        }

        Set sub;
        for ( Set::const_iterator it_i = K.begin(); it_i != K.end(); ++ it_i ) {
          const Vertex& v = *it_i;
          if ( v.first.bottom() <= ty ) {
            if ( pivot.first.right() <= v.first.right() && v.first.left() <= tx ) {
              sub.insert(v);
            }
          }
        }

        for ( Set::const_iterator it_i = sub.begin(); it_i != sub.end(); ++ it_i ) {
          const Vertex& v = *it_i;
          K.erase(v);
        }

        read(sub);
      }
    }
  };

  class Solver: public SolverInterface {
  public:
    Search search;

    const OutputStorage* solve( const InputStorage* in, OutputStorage* out ) {
      out->N = in->N;
      search.in = in;
      search.run();
      std::copy(search.results, search.results + SIZE, out->results);
      return out;
    }
  protected:
  };
}

// @snippet<sh19910711/contest-base:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
    bool flag;
    void before_all_actions() {
      flag = false;
    }
    void after_action( const int& id ) {
      flag = true;
    }
    bool input( InputStorage* in ) {
      if ( ! ( std::cin >> in->N && in->N ) ) {
        return false;
      }
      for ( int i = 0; i < in->N; ++ i ) {
        Int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        in->rects[i].top() = std::min(y1, y2);
        in->rects[i].bottom() = std::max(y1, y2);
        in->rects[i].right() = std::min(x1, x2);
        in->rects[i].left() = std::max(x1, x2);
      }
      return true;
    }
    void output( const OutputStorage* out ) {
      if ( flag ) {
        std::cout << endl;
      }
      for ( int i = 0; i < out->N; ++ i ) {
        std::cout << out->results[i] << std::endl;
      }
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

