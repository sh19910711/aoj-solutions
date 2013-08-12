
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

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class Vector {
  public:
    typedef ValueType Type;
    Type& operator [] ( const int& index ) { return data[index]; }
    const Type& operator [] ( const int& index ) const { return data[index]; }
  private:
    Type data[SIZE];
  };
}

// @snippet<sh19910711/contest:math/lcm.cpp>
namespace math {
  // @desc 最小公倍数を求める
  template <class T> T lcm( T a, T b ) {
    T larger = a > b ? a : b;
    T smaller = a > b ? b : a;
    T res = larger;
    while ( res % smaller != 0 )
      res += larger;
    return res;
  }
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
  template <typename Type, int SIZE_X, int SIZE_Y, int SIZE_Z> struct VectorTypes {
    typedef storage::Vector<Type   , SIZE_X> Type1D;
    typedef storage::Vector<Type1D , SIZE_Y> Type2D;
    typedef storage::Vector<Type2D , SIZE_Z> Type3D;
  };
  template <int SIZE_X, int SIZE_Y, int SIZE_Z> struct BasicVectors {
    typedef VectorTypes<Int    , SIZE_X , SIZE_Y , SIZE_Z> IntVectors;
    typedef VectorTypes<Double , SIZE_X , SIZE_Y , SIZE_Z> DoubleVectors;
    typedef VectorTypes<String , SIZE_X , SIZE_Y , SIZE_Z> StringVectors;
  };
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 3;
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  typedef BasicVectors<SIZE, SIZE, SIZE>::BasicVectors::IntVectors::Type1D List;
  
  List A;
  List M;
  
  List T;
  Int result;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve() {
      T = calc(A, M);
      result = calc_result(T);
    }
    
    Int calc_result( const List& T ) const {
      return math::lcm(T[0], math::lcm(T[1], T[2]));
    }
    
    List calc( const List& A, const List& M ) const {
      List res;
      for ( int i = 0; i < SIZE; ++ i )
        res[i] = calc(A[i], M[i]);
      return res;
    }
    
    Int calc( const Int& a, const Int& m ) const {
      Int t = 0;
      Int x = 1;
      do {
        x = ( a * x ) % m;
        t ++;
      } while ( x != 1 );
      return t;
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
    
    bool input() {
      for ( int i = 0; i < SIZE; ++ i ) {
        if ( ! ( std::cin >> A[i] >> M[i] ) )
          return false;
      }
      if ( A[0] == 0 && M[0] == 0 && A[1] == 0 && M[1] == 0 && A[2] == 0 && M[2] == 0 )
        return false;
      return true;
    }
    
    void output() {
      std::cout << result << endl;
    }
    
    Solver solver;
    
  private:
    
  };
}

// @snippet<sh19910711/contest:main.cpp>
#ifndef __MY_UNIT_TEST__
int main() {
  return solution::Solution().run();
}
#endif


