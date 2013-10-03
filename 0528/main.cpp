
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

// @snippet<sh19910711/contest:text/suffix_array.cpp>
namespace text {
  class SuffixArray {
  public:
    typedef std::vector<int> VI;
    typedef VI::const_iterator Iterator;
    
    SuffixArray() { init(""); }
    SuffixArray( const std::string& s_ ) { init(s_); }
    
    void build() {
      int maxlen = n;
      for ( int i = 0; i < n; ++ i ) {
        rank[i] = s[i];
        maxlen = std::max( maxlen, s[i] + 1 );
      }
      VI cnt(maxlen, 0);
      for ( int i = 0; i < n; ++ i )
        cnt[rank[i]] ++;
      for ( int i = 1; i < maxlen; ++ i )
        cnt[i] += cnt[i-1];
      for ( int i = 0; i < n; ++ i )
        sa[--cnt[rank[i]]] = i;
      for ( k = 1; k < n; k *= 2 ) {
        VI r = rank;
        rank[sa[0]] = 0;
        for ( int i = 1; i < n; ++ i ) {
          int s1 = sa[i-1], s2 = sa[i];
          rank[s2] = r[s1] == r[s2] && std::max( s1, s2 ) + k < n && r[s1+k/2] == r[s2+k/2] ? rank[s1] : i;
        }
        for ( int i = 0; i < n; ++ i )
          cnt[i] = i;
        VI s = sa;
        for ( int i = 0; i < n; ++ i ) {
          int s1 = s[i] - k;
          if ( s1 >= 0 )
            sa[cnt[rank[s1]]++] = s1;
        }
      }
    }
    
    void init( const std::string& s_ ) {
      s = s_;
      n = s.size();
      sa.resize(n);
      rank.resize(n+1);
    }
    
    bool find( const std::string& key ) const {
      int lb = 0, ub = n;
      while ( ub - lb > 1 ) {
        int mid = ( lb + ub ) / 2;
        std::string t = s.substr( sa[mid] );
        if ( t.substr( 0, key.size() ) == key ) return true;
        else if ( t < key ) lb = mid;
        else ub = mid;
      }
      return false;
    }
    
    Iterator begin() const { return sa.begin(); }
    Iterator end() const { return sa.end(); }
    const int& operator []( const int& k ) const { return sa[k]; }
    int size() const { return n; }
    
  protected:
    std::string s;
    int n, k;
    VI sa;
    VI rank;
  };
}

// @snippet<sh19910711/contest:text/suffix_array_with_lcp.cpp>
namespace text {
  template <class SuffixArrayBase> class SuffixArrayWithLCP: public SuffixArrayBase {
  public:
    int lcp( int x, int y ) {
      int l = this->n - std::min( x, y );
      for ( int i = 0; i < l; ++ i )
        if ( this->s[x+i] != this->s[y+i] )
          return i;
      return l;
    }
    void init( const std::string& s_ ) {
      SuffixArrayBase::init(s_);
    }
  };
}

// @snippet<sh19910711/contest:text/suffix_array_with_height.cpp>
namespace text {
  template <class SuffixArrayBase> class SuffixArrayWithHeight: public SuffixArrayBase {
  public:
    typedef typename SuffixArrayBase::VI VI;
    
    void buildHeight() {
      int h = 0;
      for ( int i = 0; i < this->n; ++ i ) {
        int j = this->rank[i];
        if ( j == this->n - 1 ) {
          h = 0;
          continue;
        }
        int k = this->sa[j+1];
        if ( h > 0 )
          h = h - 1 + this->lcp( i + h - 1, k + h - 1 );
        else
          h = this->lcp( i, k );
        this->height[j] = h;
      }
    }
    void init( const std::string& s_ ) {
      SuffixArrayBase::init(s_);
      height.resize(std::max(0, this->n - 1));
    }
    
  protected:
    VI height;
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
  
  
}

// @snippet<sh19910711/contest:solution/storages-area.cpp>
namespace solution {
  typedef text::SuffixArrayWithHeight< text::SuffixArrayWithLCP<text::SuffixArray> > SuffixArray;
  
  // storages
  class Storages {
  public:
    String A;
    String B;
    SuffixArray SA;
    
    Int result;
  };
  
  Storages global_storages;
}

// @snippet<sh19910711/contest:solution/solver-area.cpp>
namespace solution {
  class Solver {
  public:
    void solve( Storages& s ) {
      init_suffix_array(s.A, s.SA);
      s.result = find_max_length(s.SA, s.B);
    }
    
  protected:
    static void init_suffix_array( const String& s, SuffixArray& sa ) {
      sa.init(s);
      sa.build();
      sa.buildHeight();
    }
    
    static Int find_max_length( const SuffixArray& sa, const String& s ) {
      Int len = 0;
      int n = s.size();
      for ( int i = 0; i + len < n; ) {
        if ( sa.find(s.substr(i, len + 1)) ) {
          len ++;
        } else {
          i ++;
        }
      }
      return len;
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
      this->init();
      if ( ! this->input(*this->storages) )
        return false;
      solver.solve(*this->storages);
      this->output(*this->storages);
      return true;
    }
    
    bool input( Storages& s ) {
      return std::cin >> s.A >> s.B;
    }
    
    void output( const Storages& s ) const {
      std::cout << s.result << std::endl;
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




