
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
    virtual void pre_calc() {}
    virtual bool action() = 0;
    virtual void init() {};
    virtual bool input( Storages& s ) { return false; };
    virtual void output( const Storages& s ) const {};
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
      this->pre_calc();
      for (;;) {
        this->before_action(-1);
        if ( ! this->action() ) { this->after_action(-1); break; }
        this->after_action(-1);
      };
      return 0;
    }
  protected:
    SolutionBase() {}
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer_reference_count.cpp>
namespace misc {
  class SmartPointerReferenceCount {
  public:
    void add() { count ++; }
    int release() { return -- count; }
  private:
    int count;
  };
}

// @snippet<sh19910711/contest:misc/smart_pointer.cpp>
namespace misc {
  template <typename Type> class SmartPointer {
  public:
    SmartPointer(): pointer(0), reference(0) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(Type* value): pointer(value) {
      reference = new misc::SmartPointerReferenceCount();
      reference->add();
    }
    SmartPointer(const SmartPointer<Type>& sp): pointer(sp.pointer), reference(sp.reference) {
      reference->add();
    }
    ~SmartPointer() {
      if ( reference->release() == 0 ) {
        delete[] pointer;
        delete[] reference;
      }
    }
    Type& operator *() { return *pointer; }
    const Type& operator *() const { return *pointer; }
    Type* operator +( const int& x ) { return pointer + x; }
    const Type* operator +( const int& x ) const { return pointer + x; }
    Type* operator ->() { return pointer; }
    SmartPointer<Type>& operator = ( const SmartPointer<Type>& sp ) {
      if ( this != &sp ) {
        if ( reference->release() == 0 ) {
          delete[] pointer;
          delete[] reference;
        }
        pointer = sp.pointer;
        reference = sp.reference;
        reference->add();
      }
      return *this;
    }
  private:
    Type* pointer;
    misc::SmartPointerReferenceCount* reference;
  };
}

// @snippet<sh19910711/contest:storage/vector.cpp>
namespace storage {
  template <typename ValueType, int SIZE> class VectorClass {
  public:
    typedef VectorClass<ValueType, SIZE> SelfType;
    typedef ValueType Value;
    typedef misc::SmartPointer<ValueType> Pointer;
    VectorClass() { data = Pointer(new ValueType[SIZE]); size = 0; }
    ValueType& operator [] ( const int& index ) { return *(data + index); }
    const ValueType& operator [] ( const int& index ) const { return *(data + index); }
    
    void resize( const int& new_size ) { size = new_size; }
    
    void push_back( const ValueType& value ) {
      *(data + (size ++)) = value;
    }

    bool empty() { return size == 0; }
    
    template <class Func> void each( Func func ) {
      for ( int i = 0; i < size; ++ i )
        func(*(data + i));
    }
    
    template <class ReturnType, class Func> ReturnType map_to( Func func ) {
      ReturnType mapped;
      mapped.resize(size);
      for ( int i = 0; i < size; ++ i )
        mapped[i] = func(*(data + i));
      return mapped;
    }

    void sort() {
      std::sort(data + 0, data + size);
    }

    int upper_bound( const ValueType& v ) {
      return std::upper_bound(data + 0, data + size, v) - data;
    }

    ValueType sum() {
      return accumulate(data + 0, data + size, ValueType());
    }
    
  private:
    Pointer data;
    int size;
  };
}

// @snippet<sh19910711/contest:storage/vector_types.cpp>
namespace storage {
  const int VECTOR_NONE = -1;
  template <typename ValueType, int SIZE_X = VECTOR_NONE, int SIZE_Y = VECTOR_NONE, int SIZE_Z = VECTOR_NONE> struct Vector {
    typedef storage::VectorClass<ValueType, SIZE_X> Type__;
    typedef storage::VectorClass<Type__, SIZE_Y> Type_;
    typedef storage::VectorClass<Type_, SIZE_Z> Type;
  };
  template <typename ValueType, int SIZE_X, int SIZE_Y> struct Vector<ValueType, SIZE_X, SIZE_Y, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type_;
    typedef storage::VectorClass<Type_, SIZE_X> Type;
  };
  template <typename ValueType, int SIZE_X> struct Vector<ValueType, SIZE_X, VECTOR_NONE, VECTOR_NONE> {
    typedef storage::VectorClass<ValueType, SIZE_X> Type;
  };
}

// @snippet<sh19910711/contest:solution/typedef.cpp>
namespace solution {
  typedef std::istringstream ISS;
  typedef std::ostringstream OSS;
  typedef long long Int;
  typedef long double Double;
  typedef std::string String;
  
}

// @snippet<sh19910711/contest:solution/namespace-area.cpp>
namespace solution {
  // namespaces, types
  using namespace std;
  
}

// @snippet<sh19910711/contest:solution/consts-area.cpp>
namespace solution {
  // constant vars
  const int SIZE = 100 + 11;
  const Int CARD_IDENTITY = std::numeric_limits<Int>::min();
}

namespace solution {
  struct Result {
    int a;
    int b;
  };
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  // storages
  class Storages {
  public:
    typedef Int Card;
    typedef std::set<Card> Cards;

    Cards A, B;
    Int N;

    Result result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      s.B = get_diff_cards(s.A, s.N);
      s.result = do_simulation(s.A, s.B);
    }

    static Storages::Cards get_diff_cards( const Storages::Cards& A, const Int& N ) {
      Storages::Cards U;
      for ( int i = 1; i <= 2 * N; ++ i )
        U.insert(i);
      Storages::Cards res;
      std::set_difference(U.begin(), U.end(), A.begin(), A.end(), std::inserter(res, res.begin()));
      return res;
    }

    static Result do_simulation( Storages::Cards A, Storages::Cards B ) {
      typedef Storages::Cards::iterator Iterator;

      Result res;
      res.a = 0;
      res.b = 0;

      Storages::Card last_card = CARD_IDENTITY;
      bool taro_turn = true;
      while ( ! A.empty() && ! B.empty() ) {
        if ( taro_turn ) {
          Iterator it_upper = A.upper_bound(last_card);
          if ( it_upper != A.end() ) {
            last_card = *it_upper;
            A.erase(*it_upper);
          } else {
            last_card = CARD_IDENTITY;
          }
        } else {
          Iterator it_upper = B.upper_bound(last_card);
          if ( it_upper != B.end() ) {
            last_card = *it_upper;
            B.erase(*it_upper);
          } else {
            last_card = CARD_IDENTITY;
          }
        }
        taro_turn = ! taro_turn;
      }

      res.a = B.size();
      res.b = A.size();
      return res;
    }

  protected:
    
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
      this->init(*this->storages);
      if ( ! this->input(*this->storages) )
        return false;
      solver.solve(*this->storages);
      this->output(*this->storages);
      return true;
    }

    void init( Storages& s ) {
      s.A.clear();
      s.B.clear();
    }

    bool input( Storages& s ) {
      if ( ! ( std::cin >> s.N && s.N ) )
        return false;
      for ( int i = 0; i < s.N; ++ i ) {
        int a;
        std::cin >> a;
        s.A.insert(a);
      }
      return true;
    }

    void output( const Storages& s ) const {
      std::cout << s.result.a << std::endl;
      std::cout << s.result.b << std::endl;
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



