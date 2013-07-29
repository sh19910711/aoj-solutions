
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

// @snippet<sh19910711/contest:solution/interface.cpp>
namespace solution {
  class SolutionInterface {
  public:
    virtual int run() = 0;
    
  protected:
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input() { return false; };
    virtual void output() {};
    
    SolutionInterface() {}
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution-base.cpp>
namespace solution {
  class SolutionBase: public SolutionInterface {
  public:
    virtual int run() {
      pre_calc();
      while ( action() );
      return 0;
    }
    
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef std::vector<std::string> VS;
  typedef long long LL;
  typedef int INT;
  typedef std::vector<INT> VI;
  typedef std::vector<VI> VVI;
  typedef std::pair<INT,INT> II;
  typedef std::vector<II> VII;
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  typedef std::map<II, int> Map;
  typedef std::map<int, II> Number2Pos;
}

// @snippet<sh19910711/contest:solution/variables-area.cpp>
namespace solution {
  // constant vars
  const int M_MAX = 1000000 + 11;
  const int SIZE = 4000 + 11;
  const int OFFSET = SIZE / 2;
  const int dr[4] = {0, -1, 0, 1};
  const int dc[4] = {1, 0, -1, 0};
  const int NONE = std::numeric_limits<int>::min();
  const II MEMO_NONE = II(NONE, NONE);

  // storages
  int m, n;
  int T[SIZE][SIZE];
  Number2Pos T_inv;
  int lr, lc;
  int hr, hc;
  II memo[SIZE][SIZE];

  II result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      II pos = T_inv[n];
      result = rec(pos.first, pos.second);
    }

    II rec( int r, int c ) {
      II& res = memo[r][c];
      if ( res != MEMO_NONE )
        return res;

      II ret = MEMO_NONE;
      const int dc[3] = {-1, 0, 1};
      for ( int k = 0; k < 3; ++ k ) {
        int nr = r + 1;
        int nc = c + dc[k];
        ret = max(ret, rec(nr, nc));
      }
      return res = ret;
    }

    void build_table() {
      int num = 1;
      int r = 0, c = 0, d = 0;
      int lim = 1;
      lr = lc = std::numeric_limits<int>::max();
      hr = hc = std::numeric_limits<int>::min();
      while ( num < M_MAX ) {
        for ( int k = 0; k < 2; ++ k ) {
          for ( int i = 0; i < lim; ++ i ) {
            lr = min(lr, r);
            lc = min(lc, c);
            hr = max(hr, r);
            hc = max(hc, c);
            T_inv[num] = II(r + OFFSET, c + OFFSET);
            T[r + OFFSET][c + OFFSET] = num;
            num ++;
            r += dr[k];
            c += dc[k];
          }
        }
        lim ++;
        for ( int k = 2; k < 4; ++ k ) {
          for ( int i = 0; i < lim; ++ i ) {
            lr = min(lr, r);
            lc = min(lc, c);
            hr = max(hr, r);
            hc = max(hc, c);
            T_inv[num] = II(r + OFFSET, c + OFFSET);
            T[r][c] = num;
            num ++;
            r += dr[k];
            c += dc[k];
          }
        }
        lim ++;
      }
    }
    
  private:
    
  };
}

// @snippet<sh19910711/contest:solution/solution.cpp>
namespace solution {
  class Solution: public SolutionBase {
  public:
  protected:
    virtual bool action() {
      init();
      if ( ! input() )
        return false;
      solver.solve();
      output();
      return true;
    }

    void pre_calc() {
      solver.build_table();
    }

    void init() {
      for ( int i = 0; i < SIZE; ++ i ) {
        for ( int j = 0; j < SIZE; ++ j ) {
          memo[i][j] = MEMO_NONE;
        }
      }
    }

    bool input() {
      if ( ! ( cin >> m >> n ) )
        return false;
      if ( n == 0 && m == 0 )
        return false;
      return true;
    }

    void output() {
      cout << result.second << " " << result.first << endl;
    }
    
  private:
    Solver solver;
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif

